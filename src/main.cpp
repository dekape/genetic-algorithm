#include <stdio.h>
#include <iostream>
#include "Genetic_Algorithm.h"
#include "CUnit.h"
#include "CCircuit.h"
#include "CStream.h"

using namespace std;

int no_offsprings = 2;						// number of offsprings per generation
int p_crossing = 0.9;						// probability of crossing over
int p_mutation = 0.001;						// probability of mutation
int no_units = 10;							// total number of units
int no_circuits = 100;						// total number of initial circuits
int iter_count = 0;							// iterations counter
int offspring_count = 0;					// offsprings per iterations counter
double* fitness;							// list to store the fitness values of all circuits
CCircuit* parents;							// 2D array to store all parent circuits
CCircuit* offsprings;						// 2D array to store all offspring circuits
CCircuit best_circuit(no_units);			// object to store best circuit based on fitness calculation

using namespace std;

int main(int argc, char * argv[])
{
	// Allocate memory and initialise parents and offsprings grid
	parents = new CCircuit[no_circuits];
	offsprings = new CCircuit[no_circuits];
	for (int i = 0; i < no_circuits; i++)
	{
		parents[i].initialise(no_units);
		offsprings[i].initialise(no_units);
	}
	
	// Generate random valid circuits, store in parents
	generateCircuits(no_units, no_circuits, parents);
	cout << "PARENTS" << endl;
	for (int i = 0; i < no_circuits; i++)
		parents[i].printCircuit();

	bool terminate = false;
	fitness = new double[no_circuits];
	while (!terminate)
	{	
		// Calculate fitness of all circuits
		//computeFitness(parents, fitness, no_circuits);
		for (int i = 0; i < no_circuits; i++)
			fitness[i] = rand() % 150;


		//// Store highest fitness as offspring
		selectBestCircuit(parents, fitness, best_circuit, no_circuits, no_units);
		offsprings[0] = best_circuit;
		offspring_count++;

		// While number of offsprings is less than number of parents
		//while (offspring_count < no_circuits)
		//{
		// Create offsprings from two random parents (with mutation and crossover) -- check if valid
		createOffsprings(parents, offsprings, no_units, no_circuits, p_mutation, fitness);
		
		cout << "OFFSPRINGS" << endl;
		for (int i = 0; i < no_circuits; i++)
		{
			offsprings[i].printCircuit();
		}

		//
		//	// Store offsprings in offsprings grid, check if not overflowing
		//	offspring_count += 2;
		//}

	
		// Swap offsprings with parents

		
		// Update iteration
		iter_count++;
		cout << "Iteration: " << iter_count << endl;

		// Evaluate termination
		terminate = true;
	}



	// Delete dynamically allocated memory
	delete[] parents;
	//delete[] offsprings;
	//delete[] fitness;
	//delete[] best_circuit;

	system("pause");
	return 0;
}
