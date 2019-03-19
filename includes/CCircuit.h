#pragma	once
#include <vector>
#include <stdio.h>
#include "CUnit.h"

using namespace std;

const int num_units = 10;

bool checkValidity(int *circuit_vector);

void markUnits(int unit_num);

double assessFitness(double gormanium_mass, double waste_mass);

bool allUnitsMarked(vector<CUnit> &circuit);

//vector<double> balanceMass(vector<CUnit> &circuit);