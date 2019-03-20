#include <stdio.h>
#include <iostream>
#include "Genetic_Algorithm.h"
#include "CUnit.h"
#include "CCircuit.h"
#include "CStream.h"
#define DEBUG

using namespace std;

int iter_max = 2;							// max number of iterations
int p_crossing = 0.9;						// probability of crossing over
int p_mutation = 0.001;						// probability of mutation
int no_units = 5;							// total number of units
int no_circuits = 10;						// total number of initial circuits
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
	for(int i = 0; i < no_circuits; i++)
	{
		parents[i].printCircuit();
	}
	//bool terminate = false;
	fitness = new double[no_circuits];
	for (int i = 0; i < no_circuits; i++)
	{
		fitness[i] = rand() % 150;
	}

	selectBestCircuit(parents, fitness, best_circuit, no_circuits, no_units);
	//printf("\nBest circuit:");
	//best_circuit.printCircuit();
	offsprings[0] = best_circuit;
	offspring_count++;
	CCircuit offspringA(no_units), offspringB(no_units);
	while (offspring_count < no_circuits)
		{
			// Create offsprings from two random parents (with mutation and crossover) -- check if valid and store in grid
			createOffsprings(parents, offspringA, offspringB, no_units, no_circuits, p_mutation, fitness);
			if (checkValidity(offspringA) && offspring_count != no_circuits)
			{
				offsprings[offspring_count] = offspringA;
				offspringA.printCircuit();
				offspring_count++;
			}
			if (checkValidity(offspringB) && offspring_count != no_circuits)
			{
				offsprings[offspring_count] = offspringB;
				offspring_count++;
			}
		}

	//printf("\n2 valid? %d\n", (int) checkValidity(offspringB, true));
	//offspringB.printCircuit();

	/*while (!terminate)
	{	
#ifdef DEBUG
		cout << "PARENTS" << endl;
		for (int i = 0; i < no_circuits; i++)
			parents[i].printCircuit();
#endif //!DEBUG


		// Calculate fitness of all circuits
		//computeFitness(parents, fitness, no_circuits);
#ifdef DEBUG
		cout << "FITNESS:" << endl;
		for (int i = 0; i < no_circuits; i++)
		{
			fitness[i] = rand() % 150;
			cout << fitness[i] << " ";
		}
		cout << endl;
#endif //!DEBUG


		//// Store highest fitness as offspring
		offsprings[0] = best_circuit;
		offspring_count++;
#ifdef DEBUG
		cout << "BEST CIRCUIT" << endl;
		best_circuit.printCircuit();
#endif // DEBUG


		// While number of offsprings is less than number of parents
		CCircuit offspringA, offspringB;
		while (offspring_count < no_circuits)
		{
			// Create offsprings from two random parents (with mutation and crossover) -- check if valid and store in grid
			createOffsprings(parents, offspringA, offspringB, no_units, no_circuits, p_mutation, fitness);
			if (checkValidity(offspringA) && offspring_count != no_circuits)
			{
				offsprings[offspring_count] = offspringA;
				offspring_count++;
			}
			if (checkValidity(offspringB) && offspring_count != no_circuits)
			{
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
	
		// Swap offsprings with parents
		swapGrids(parents, offsprings, no_circuits);
		
		// Update iteration
		iter_count++;
		cout << "Iteration: " << iter_count << endl;

		// Evaluate termination
		terminate = true;
	}*/



	// Delete dynamically allocated memory
	delete[] parents;
	delete[] offsprings;
	delete[] fitness;
	//delete[] best_circuit;

}