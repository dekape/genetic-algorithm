#include <stdio.h>
#include <iostream>
#include "Genetic_Algorithm.h"
#include "CUnit.h"
#include "CCircuit.h"
#include "CStream.h"
//#define DEBUG

using namespace std;

// PROBLEM PARAMETERS
int iter_max = 500;							// max number of iterations/generations
double p_crossing = 0.9;					// probability of crossing over
double p_mutation = 0.1;					// probability of mutation
int no_units = 5;							// total number of units
int no_circuits = 100;						// total number of initial circuits

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
	// Allocate memory and initialise parents and offsprings grid
	srand(time(NULL));
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
		cout << " ITERATION " << iter_count << ":" << endl;
		cout << " Fitness: " << highest_fit << endl;
		cout << " Circuit: "; best_circuit.printCircuit();
		cout << endl;

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
		if (best_count >= 200) terminate = true;
	}

	// Print out final result
	cout << "\n FINAL CIRCUIT" << endl;
	cout << " Iterations " << iter_count  - best_count<< ":" << endl;
	cout << " Fitness: " << highest_fit << endl;
	cout << " Circuit: "; best_circuit.printCircuit();
	cout << endl;

	// Delete dynamically allocated memory
	delete[] parents;
	delete[] offsprings;
	delete[] fitness;
	delete[] fitness_adjusted;

	system("pause");
	return 0;
}