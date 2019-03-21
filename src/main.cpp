#include <stdio.h>
#include <iostream>
#include "Genetic_Algorithm.h"
#include "CUnit.h"
#include "CCircuit.h"
#include "CStream.h"

#define DEBUG true

using namespace std;

int iter_max = 500;							// max number of iterations
double p_crossing = 0.9;						// probability of crossing over
double p_mutation = 0.1;						// probability of mutation
int no_units = 5;							// total number of units
int no_circuits = 20;						// total number of initial circuits
int iter_count = 0;							// iterations counter
int offspring_count = 0;					// offsprings per iterations counter
int best_count = 0;
double* fitness;							// list to store the fitness values of all circuits
double* fitness_adjusted;
CCircuit* parents;							// 2D array to store all parent circuits
CCircuit* offsprings;						// 2D array to store all offspring circuits
CCircuit best_circuit(no_units);			// object to store best circuit based on fitness calculation
CCircuit best_circuit_prev(no_units);
CCircuit offspringA, offspringB;

using namespace std;
/*
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

	generateCircuits(no_units, no_circuits, parents);
	fitness = new double[no_circuits];
		//computeFitness(parents, fitness, no_circuits);
	for (int i = 0; i < no_circuits; i++)
	{
		fitness[i] = balance_mass(parents[i], 1e-6);
		cout<< " " << fitness[i];
	}

	selectBestCircuit(parents, fitness, best_circuit, no_circuits, no_units);
	offsprings[0] = best_circuit;
	offspring_count++;
		cout << endl << "Hi" << endl;
	offspringA = parents[0];
	offspringB = parents[1];
	//offspringA.printCircuit();
	//offspringB.printCircuit();
	cout << endl << "Hi" << endl;
	//pairParents(parents, offspringA, offspringB, no_units, no_circuits, fitness);
	//offspringA.printCircuit();
	//offspringB.printCircuit();
	while (offspring_count < no_circuits)
		{
			// Create offsprings from two random parents (with mutation and crossover) -- check if valid and store in grid
			createOffsprings(parents, offspringA, offspringB, no_units, no_circuits, p_mutation, fitness, p_crossing);
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
	for(int i = 0; i < no_circuits; i++)
	{
		offsprings[i].printCircuit();
	}

}*/


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

	bool terminate = false;
	best_circuit_prev = parents[0];
	fitness = new double[no_circuits];
	fitness_adjusted = new double[no_circuits];
	double totalFitness;
	while (!terminate)
	{
		cout << "Iteration: " << iter_count << endl;
#ifdef DEBUG
        cout << "PARENTS" << endl;
        for (int i = 0; i < no_circuits; i++)
            parents[i].printCircuit();
#endif //!DEBUG


		// Calculate fitness of all circuits
		//computeFitness(parents, fitness, no_circuits);

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

		offspring_count = 0;
		//// Store highest fitness as offspring
		selectBestCircuit(parents, fitness, best_circuit, no_circuits, no_units);
		offsprings[0] = best_circuit;
		//best_circuit.printCircuit();
		offspring_count++;
#ifdef DEBUG
		cout << "BEST CIRCUIT" << endl;
		best_circuit.printCircuit();
        cout << "is best circuit valid? " << checkValidity(best_circuit) << endl;
        cout << "actual object's gene: " << best_circuit.feed_id;
        for(int aa=0;aa<no_units;aa++){
            cout << ", " << best_circuit.circuit_units[aa].tail_num;
            cout << ", " << best_circuit.circuit_units[aa].conc_num;
        }
#endif // DEBUG


		// While number of offsprings is less than number of parents
		while (offspring_count < no_circuits)
		{
			// Regulate fitness to all positive numbers
			totalFitness = adjustFitness(fitness, fitness_adjusted, no_circuits);

			// Create offsprings from two random parents (with mutation and crossover) -- check if valid and store in grid
			createOffsprings(parents, offspringA, offspringB, no_units, no_circuits, p_mutation, fitness_adjusted, p_crossing, totalFitness);
			if (checkValidity(offspringA) && offspring_count < no_circuits)
			{
//                intArrayToUnits(offspringA.circuit_ints, offspringA.circuit_units, no_units);
				offspringA.feed_id = offspringA.circuit_ints[0];
				offsprings[offspring_count] = offspringA;
				offspring_count++;
			}
			if (checkValidity(offspringB) && offspring_count < no_circuits)
			{
//                intArrayToUnits(offspringB.circuit_ints, offspringB.circuit_units, no_units);
				offspringB.feed_id = offspringB.circuit_ints[0];
				offsprings[offspring_count] = offspringB;
				offspring_count++;
			}
		}

		
#ifdef DEBUG
//        cout << " CHILDREN: " << endl;
//        offsprings[0].printCircuit();
//        for (int i = 0; i < no_circuits; i++)
//        {
//            cout << "\t A: ";
//            offsprings[i].printCircuit();
//        }

//        cout << "OFFSPRINGS" << endl;
//        for (int i = 0; i < no_circuits; i++)
//        {
//            offsprings[i].printCircuit();
//        }
#endif // DEBUG

		// Swap offsprings with parents
		swapGrids(parents, offsprings, no_circuits);

		// Update iteration
		iter_count++;
		//for(int i = 0; i < no_circuits; i++)
		//{
		//	cout << fitness[i] << " ";
		//}
        double bal = balance_mass(offsprings[0], 1e-6);
        if(bal > 60)
            cin.get();
		cout << endl << endl;
		//offsprings[0].printCircuit();
		//printf("Fitness %f \n\n", balance_mass(best_circuit, 1e-6));

		// Evaluate termination
		if (iter_count == iter_max) terminate = true;
	}

#ifdef DEBUG
    cout << "FITNESS:" << endl;
    for (int i = 0; i < no_circuits; i++)
    {
        cout << fitness[i] << " ";
    }
    cout << endl << endl << " PARENT: " << endl;
   	offsprings[0].printCircuit();
    
    cout << "iter: " << iter_count << endl;
    
#endif // DEBUG
	// Delete dynamically allocated memory
	delete[] parents;
	delete[] offsprings;
	delete[] fitness;

	system("pause");
	return 0;
}
