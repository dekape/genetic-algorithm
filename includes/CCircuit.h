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

double balance_mass(CCircuit circuit, double tol);

#endif // !CCIRCUIT_H
