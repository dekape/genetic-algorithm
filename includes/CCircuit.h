#ifndef CCIRCUIT_H
#define CCIRCUIT_H

void unitsToIntArray(int *int_array, CUnit *units_to_convert, int no_units);

void intArrayToUnits(int *int_array, CUnit *circuit, int no_units);

bool checkValidity(int *int_array, CUnit *circuit, int no_units);

void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit, int no_units);

double assess_fitness(double gormanium_mass, double waste_mass);

#endif // !CCIRCUIT_H

