#include <stdio.h>
#include <iostream>
#include "Genetic_Algorithm.h"
#include "CUnit.h"
#include "CCircuit.h"
#include "CStream.h"
#include <string>
#include <omp.h>
#include <string>
#include <mpi.h>
//#define DEBUG


using namespace std;

// PROBLEM PARAMETERS
int iter_max = 5000;						// max number of iterations/generations
int no_threads = 2;							// number of OMP threads to be used in parallel
int no_units = 10;							// total number of units
int no_circuits = 100;						// total number of initial circuits
int best_count_lim = 500;					// how many generations of the same best circuit are required to terminate the loop
double p_crossing = 0.9;					// probability of crossing over
double p_mutation = 0.01;					// probability of mutation

// INITIATE USEFUL VARIABLES AND ARRAYS
int iter_count = 0;							// iterations counter
int offspring_count = 0;					// offsprings per iterations counter
int best_count = 0;							// count for how many generations the best circuit has been the same 
double highest_fit;							// highest fitness value for each generation
double highest_fit_prev;					// previous highest fitness value
double* fitness;							// list to store the fitness values of all circuits
double* fitness_adjusted;					// adjusted fitness to relative fitness
double totalFitness;						// absolute range of fitness values

// INITIATE USEFUL CIRCUIT VARIABLES
CCircuit* parents;							// 2D array to store all parent circuits
CCircuit* offsprings;						// 2D array to store all offspring circuits
CCircuit best_circuit(no_units);			// object to store best circuit based on fitness calculation
CCircuit best_circuit_prev(no_units);		// space to store the best circuit from previous iterations
CCircuit parentA, parentB;					// objects to store the pair of parents for procriation
CCircuit offspringA, offspringB;			// object to store the offpsrings from each pair of parents

using namespace std;

int main(int argc, char * argv[])
{

	int num_procs;
	int proc_id;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	
	// Command line properties
	if (argc == 6)
	{
		
		//cout << endl << "Proper usage is Genetic_Algorithm <no_units> <iter_max> <best_count_lim> <p_mutation>" << endl;
		//cout<<"See documentation for further details" << endl;
		//return 1;
		
		if (stoi(argv[5]) <= 0)
		{
			cout << "\n Number of threads needs to positive \n";
			return -1;
		}

		no_units = stoi(argv[1]);
		iter_max = stoi(argv[2]);
		best_count_lim = stoi(argv[3]);
		p_mutation = stod(argv[4]);
		no_threads = stoi(argv[5]);
	}

	omp_set_dynamic(0);
	omp_set_num_threads(no_threads);

	// Allocate memory and initialise parents and offsprings grid
	srand(10 * proc_id * time(NULL));
	parents = new CCircuit[no_circuits];
	offsprings = new CCircuit[no_circuits];
	for (int i = 0; i < no_circuits; i++)
	{
		parents[i].initialise(no_units);
		offsprings[i].initialise(no_units);
	}
	

	// Generate random valid circuits, store in parents
	generateCircuits(no_units, no_circuits, parents);


	bool terminate = false;								// check for loop termination
	best_circuit_prev = parents[0];						// initialise previous best circuit as the first parent circuit
	highest_fit_prev = -1e-18;							// initialise the highest fit for previous operation as a very big negative number
	fitness = new double[no_circuits];					// allocate space for fitness values
	fitness_adjusted = new double[no_circuits];			// allocate space for adjusted fitness values


	// Initiate iterations
	while (!terminate)
	{	
		// Reset offsppring count for new iteration
		offspring_count = 0;
    
#ifdef DEBUG
		cout << "PARENTS" << endl;
		for (int i = 0; i < no_circuits; i++)
			parents[i].printCircuit();
#endif //!DEBUG


		// Calculate fitness of all parent circuits
#pragma omp parallel for
		for (int i = 0; i < no_circuits; i++)
		{
			fitness[i] = balance_mass(parents[i], 1e-6);
 		}
#ifdef DEBUG
		cout << "FITNESS:" << endl;
		for (int i = 0; i < no_circuits; i++)
		{
			cout << fitness[i] << " ";
		}
		cout << endl;
#endif //!DEBUG
    
		// Store highest fitness circuit as offspring
		highest_fit = selectBestCircuit(parents, fitness, best_circuit, no_circuits, no_units);
		offsprings[0] = best_circuit;
		offspring_count++;

#ifdef DEBUG
		cout << "BEST CIRCUIT" << endl;
		best_circuit.printCircuit();
#endif // DEBUG

		// Regulate fitness to all positive numbers
		totalFitness = adjustFitness(fitness, fitness_adjusted, no_circuits);

		// Create as many offsprings as there are parents
		while (offspring_count < no_circuits)
		{
			// Select pair of parents based on their fitnesses
			pairParents(parents, parentA, parentB, no_units, no_circuits, fitness_adjusted, totalFitness);

			// Create offsprings from two parents (with mutation and crossover) -- check if valid and store in grid
			createOffsprings(parentA, parentB, offspringA, offspringB, no_units, no_circuits, p_mutation, fitness_adjusted, p_crossing, totalFitness);

			if (checkValidity(offspringA) && offspring_count != no_circuits)
			{
				offspringA.feed_id = offspringA.circuit_ints[0];
				offsprings[offspring_count] = offspringA;
				offspring_count++;
			}
			if (checkValidity(offspringB) && offspring_count != no_circuits)
			{
				offspringB.feed_id = offspringB.circuit_ints[0];
				offsprings[offspring_count] = offspringB;
				offspring_count++;
			}
		}
		

#ifdef DEBUG
		cout << "OFFSPRINGS" << endl;
		for (int i = 0; i < no_circuits; i++)
		{
			offsprings[i].printCircuit();
		}
#endif // DEBUG
	
		// Swap offsprings with parents as offsprings will be used as parents for next iteration
		swapGrids(parents, offsprings, no_circuits);

		
		// Update iteration, print current result to screen
		iter_count++;
		/*cout << " ITERATION " << iter_count << ":" << endl;
		cout << " Fitness: " << highest_fit << endl;
		cout << " Circuit: "; best_circuit.printCircuit();
		cout << endl;*/

		// Evaluate termination if maximum amount of generations are reached
		// or if best circuit hasn't changed for 200 iterations
		if (iter_count == iter_max) terminate = true;
		if (highest_fit > highest_fit_prev)
		{
			highest_fit_prev = highest_fit;
			best_circuit_prev = best_circuit;
			best_count = 1;
		}
		else
		{
			best_count++;
		}

		if (best_count >= best_count_lim) terminate = true;
	}

	// Print out final result
	cout << "\n Process: " << proc_id << endl;
	cout << " FINAL CIRCUIT" << endl;
	if(iter_count < iter_max) cout << " Iterations " << iter_count  - best_count_lim<< ":" << endl;
	else cout << " Iterations " << iter_count << ":" << endl;
	cout << " Fitness: " << highest_fit << endl;
	cout << " Circuit: "; best_circuit.printCircuit();
	cout << endl;

	// Wait for all processes to finish their search
	MPI_Barrier(MPI_COMM_WORLD);

	// Struct for easy MPI_REDUCE usage
	struct {
		double fitness;
		int index;
	} in, out;
	in.fitness = highest_fit;
	in.index = proc_id;

	// Reduce max fitness over all processes
	MPI_Reduce(&in, &out, 1, MPI_DOUBLE_INT, MPI_MAXLOC, 0, MPI_COMM_WORLD);
	// Let everyone know best processes ID
	MPI_Bcast(&out.index, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// Print out final result for all processes
	if (proc_id == 0) {
		cout << "--------------------- OVERALL BEST CIRCUIT ----------------" << endl;
		cout << "\n Process: " << out.index << endl;
		cout << " FINAL CIRCUIT" << endl;
		cout << " Fitness: " << out.fitness << endl;
	}
	// The best process gets the honour of printing its circuit
	MPI_Barrier(MPI_COMM_WORLD);
	if (proc_id == out.index) {
		cout << " Circuit: "; best_circuit.printCircuit();
	}
	// Just so they print nicely :)
	MPI_Barrier(MPI_COMM_WORLD);
	if (proc_id == 0) {
		cout << endl;
		cout << "-----------------------------------------------------------" << endl;
	}



	// Delete dynamically allocated memory
	delete[] parents;
	delete[] offsprings;
	delete[] fitness;
	delete[] fitness_adjusted;

	MPI_Finalize();
	return 0;
}