#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include "CUnit.h"
#include "CCircuit.h"

using namespace std;

void generateCircuits(int no_units, int no_circuits, int** parents);

bool checkValidity(int *int_array, CUnit *circuit, int no_units);

void computeFitness(CUnit** circuits, double*fitness, int no_circuits);

void selectBestCircuit(CUnit**circuits, double* fitness, CUnit* best_circuit, int no_circuits, int no_units);

void crossOver(int *circuitA, int *circuitB, int no_units);

void mutate(int *circuit, int no_unit);

void pairParents(int ** circuits, int * parentA, int * parentB, int no_units, int no_circuits, double* fitness);

void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit);

bool checkValidity(int *int_array, CUnit *circuit, int no_units);

void resetMarks(CUnit *units, int no_units);