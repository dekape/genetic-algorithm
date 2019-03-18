void unitsToIntArray(int *IntArray, CUnit *units_to_convert, int no_units);

bool checkValidity(int *circuit, int no_units, CUnit *units);

void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit);

const int num_units = 10;
