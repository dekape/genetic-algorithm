#include <stdio.h>
#include <iostream>
#include "Genetic_Algorithm.h"
#include "CUnit.h"
#include "CCircuit.h"
#include "CStream.h"
//#define DEBUG

using namespace std;

int iter_max = 1000;							// max number of iterations
int p_crossing = 0.9;						// probability of crossing over
int p_mutation = 0.001;						// probability of mutation
int no_units = 5;							// total number of units
int no_circuits = 10;						// total number of initial circuits
int iter_count = 0;							// iterations counter
int offspring_count = 0;					// offsprings per iterations counter
int best_count = 0;
double* fitness;							// list to store the fitness values of all circuits
CCircuit* parents;							// 2D array to store all parent circuits
CCircuit* offsprings;						// 2D array to store all offspring circuits
CCircuit best_circuit(no_units);			// object to store best circuit based on fitness calculation
CCircuit best_circuit_prev(no_units);

using namespace std;

int main(int argc, char * argv[])
{
	// Allocate memory and initialise parents and offsprings grid
	int test[5] = {0, 2, 1, 3, 2};
	CCircuit test_1(2, test);
	bool t = checkValidity(test_1);
	printf("\nTest valid? %d", (int) t);
	double val;
	val = balance_mass(test_1, 1e-6);
	printf("\nVal: %f", val);
	return 0;
}

	