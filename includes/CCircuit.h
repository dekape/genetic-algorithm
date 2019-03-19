#ifndef CCIRCUIT_H
#define CCIRCUIT_H

#include <vector>
#include <stdio.h>
#include "CUnit.h"

using namespace std;

double assessFitness(double gormanium_mass, double waste_mass);

bool allUnitsMarked(vector<CUnit> &circuit);

bool checkValidity(int *int_array, CUnit *circuit, int no_units);

void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit, int num_units);

void resetMarks(CUnit *units, int no_units);
//vector<double> balanceMass(vector<CUnit> &circuit);

void unitArrayToVector(CUnit *unit_array, vector<CUnit> &unit_vector, int num_units);

double balance_mass(vector<CUnit> &circuit, double tol);


#endif // !CCIRCUIT_H

