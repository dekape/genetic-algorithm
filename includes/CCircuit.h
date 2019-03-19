#ifndef CCIRCUIT_H
#define CCIRCUIT_H

#include <vector>
#include <stdio.h>
#include "CUnit.h"

using namespace std;

class CCircuit
{
public:
	CCircuit();
	CCircuit(int no_units);
	CCircuit(int no_units, int* circuit_array);
	CCircuit(int no_units, int feed, CUnit* circuit_array);
	~CCircuit();

	void initialise(int no_units);
	int feed_id;
	int no_units;
	int* circuit_ints;
	CUnit * circuit_units;
};


double assessFitness(double gormanium_mass, double waste_mass);

bool allUnitsMarked(vector<CUnit> &circuit);

bool checkValidity(CCircuit circuits);

void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit, int num_units);

void resetMarks(CUnit *units, int no_units);
//vector<double> balanceMass(vector<CUnit> &circuit);


#endif // !CCIRCUIT_H

