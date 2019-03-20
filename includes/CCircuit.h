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

	CCircuit &operator=(const CCircuit &other)
	{
		if (this != &other)
		{
			delete[] circuit_ints;
			delete[] circuit_units;

			feed_id = other.feed_id;
			no_units = other.no_units;
			circuit_ints = new int[no_units * 2 + 1];
			circuit_units = new CUnit[no_units];

			for (int i = 0; i < no_units * 2 + 1; i++)
				circuit_ints[i] = other.circuit_ints[i];
			for (int i = 0; i < no_units; i++)
				circuit_units[i] = other.circuit_units[i];
		}

		return *this;
	}

	void printCircuit();
	void initialise(int no_units);
	int feed_id;
	int no_units;
	int* circuit_ints;
	CUnit* circuit_units;
};


double assessFitness(double gormanium_mass, double waste_mass);

bool allUnitsMarked(vector<CUnit> &circuit);

bool checkValidity(CCircuit circuit);

void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit, int num_units);

void resetMarks(CUnit *units, int no_units);

void unitArrayToVector(CUnit *unit_array, vector<CUnit> &unit_vector, int num_units);

double balance_mass(CCircuit circuit, double tol);

void cal_convergence_value(vector<CUnit> &circuit, double value_c, double waste_c);

void do_unit_cal(int unit_index, vector<CUnit> &circuit);

#endif // !CCIRCUIT_H

