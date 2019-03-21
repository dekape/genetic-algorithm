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
	CCircuit(CCircuit &other);
	~CCircuit();

	CCircuit &operator=(const CCircuit &other);

	void printCircuit();
	void initialise(int no_units);
	int feed_id;
	int no_units;
	int* circuit_ints;
	CUnit* circuit_units;
};


bool checkValidity(CCircuit circuit);

void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit, int num_units);

void resetMarks(CUnit *units, int no_units);

void unitArrayToVector(CUnit *unit_array, vector<CUnit> &unit_vector, int num_units);

double balance_mass(CCircuit circuit_obj, double tol = 10e-7, double value_weight = 100,
                    double waste_weight = 500, double circuit_value_feed = 10, double circuit_waste_feed = 100);

#endif // !CCIRCUIT_H
