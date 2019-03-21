#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include "CUnit.h"
#include "CCircuit.h"

using namespace std;

void unitsToIntArray(int *int_array, int feed_id, CUnit *units_to_convert, int no_units);

void intArrayToUnits(int *int_array, CUnit *circuit, int no_units);

void generateCircuits(int no_units, int no_circuits, CCircuit* parents);

void computeFitness(CCircuit* parents, double*fitness, int no_circuits);

void crossOver(int *circuitA, int *circuitB, int no_units, double p_crossing);

void mutate(int *circuit, int no_unit, double mute_limit);

void pairParents(CCircuit *parents, CCircuit &parentA, CCircuit & parentB, int no_units, int no_circuits,double * fitness, double totalFitness);

void createOffsprings(CCircuit& parentA, CCircuit& parentB, CCircuit& childA, CCircuit& childB, int no_units, int no_circuits, double mute_limit, double* fitness, double cross_limit, double totalFitness);

void swapGrids(CCircuit* parents, CCircuit* offsprings, int no_circuits);

double selectBestCircuit(CCircuit* circuits, double* fitness, CCircuit& best_circuit, int no_circuits, int no_units);

double adjustFitness(double* fitness, double* fitness_adjusted, int no_circuits);

#endif // !GENETIC_ALGORITHM_H