#include <stdio.h>
#include <iostream>
#include "Genetic_Algorithm.h"
#include "CUnit.h"
#include "CCircuit.h"

using namespace std;

int no_offsprings = 2;			// number of offsprings per generation
int p_crossing = 0.9;			// probability of crossing over
int p_mutation = 0.001;			// probability of mutation
int no_units = 10;				// total number of units
int no_circuits = 100;			// total number of initial circuits
int iter_count = 0;				// iterations counter
int offspring_count = 0;		// offsprings per iterations counter
double* fitness;				// list to store the fitness values of all circuits
CUnit* best_circuit;			// object to store best circuit based on fitness calculation
CUnit** parents;				// 2D array to store all parent circuits
CUnit** offsprings;				// 2D array to store all offspring circuits

int main(int argc, char * argv[])
{
	// Allocate memory to parents and offspring
	parents = new CUnit*[no_circuits];
	offsprings = new CUnit*[no_circuits];
	for (int i = 0; i < no_circuits; i++)
	{
		parents[i] = new CUnit[no_units];
		offsprings[i] = new CUnit[no_units];
	}

	// Generate random circuits with CUnit objects. Feeder is always the 0th unit
	//generateCircuits(no_units, no_circuits, parents);

	//for (int i = 0; i < no_circuits; i++)
	//{
	//	cout << i <<"- 0 ";
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
	for (int i = 0; i < no_circuits; i++) delete[] parents[i];
	for (int i = 0; i < no_circuits; i++) delete[] offsprings[i];
	delete[] parents;
	delete[] offsprings;
	delete[] fitness;
	delete[] best_circuit;

	system("pause");
	return 0;
}