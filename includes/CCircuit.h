#ifndef CCIRCUIT_H
#define CCIRCUIT_H

#include <vector>
#include <stdio.h>
#include "CUnit.h"

using namespace std;

const int num_units = 10;

void markUnits(int unit_num);

double assessFitness(double gormanium_mass, double waste_mass);

bool allUnitsMarked(vector<CUnit> &circuit);

//vector<double> balanceMass(vector<CUnit> &circuit);

#endif // !CCIRCUIT_H

