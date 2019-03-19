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
	// Generate random valid circuits
	parents = new CCircuit[no_circuits];
	for (int i = 0; i < no_circuits; i++) parents[i].initialise(no_units);
	generateCircuits(no_units, no_circuits, parents);
	for (int i = 0; i < no_circuits; i++)
	{
		for (int j = 0; j < 2 * no_units + 1; j++)
		{
			cout << parents[i].circuit_ints[j] << " ";
		}
		cout << endl;
	}

	bool terminate = false;
	while (!terminate)
	{	

		// Calculate fitness of all circuits


		// Store highest fitness as offspring


		// While number of offsprings is less than number of parents
			// Select two random parents


			// Create offsprings from two parents (with mutation and crossover) -- check if valid

		
			// Store offsprings in offsprings grid

	
		// Swap offsprings with parents

		
		// Update iteration, check for termination
		iter_count++;
		cout << "Iteration: " << iter_count << endl;
		terminate = true;
	}




	// Delete dynamically allocated memory
	//delete[] parents;
	//delete[] offsprings;
	//delete[] fitness;
	//delete[] best_circuit;

	system("pause");
	return 0;
}

int main2(int argc, char * argv[])
{
	//// Allocate memory to parents and offspring
	//parents = new CUnit*[no_circuits];
	//offsprings = new CUnit*[no_circuits];
	//for (int i = 0; i < no_circuits; i++)
	//{
	//	parents[i] = new CUnit[no_units];
	//	offsprings[i] = new CUnit[no_units];
	//}

	//// Generate random circuits with CUnit objects. Feeder is always the 0th unit
	//int ** temp_parents = new int*[no_circuits];
	//for (int i = 0; i < no_circuits; i++)
	//	temp_parents[i] = new int[2 * no_units + 1];
	//generateCircuits(no_units, no_circuits, temp_parents);
	//for (int i = 0; i < no_circuits; i++)
	//	intArrayToUnits(temp_parents[i], parents[i], no_units);


	//for (int i = 0; i < no_circuits; i++)
	//{
	//	//cout << i <<"- 0 ";
	//	for (int j = 0; j < no_units; j++)
	//		cout << parents[i][j].tails_num << " " << parents[i][j].conc_num << " ";
	//	cout << endl;
	//}


	// Compute fitness of each circuit
	//fitness = new double[no_circuits];
	//computeFitness(parents, fitness, no_circuits);

	//// Get the best circuit
	//best_circuit = new CUnit[no_units];
	//selectBestCircuit(parents, fitness, best_circuit, no_circuits, no_units);

	// Delete dynamically allocated memory
	//for (int i = 0; i < no_circuits; i++) delete[] parents[i];
	//for (int i = 0; i < no_circuits; i++) delete[] offsprings[i];
	//delete[] parents;
	//delete[] offsprings;
	//delete[] fitness;
	//delete[] best_circuit;

	system("pause");
	return 0;
}