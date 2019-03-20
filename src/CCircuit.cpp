#include "CCircuit.h"
#include "Genetic_Algorithm.h"

using namespace std;

CCircuit::CCircuit()
{
	this->circuit_ints = nullptr;
	this->circuit_units = nullptr;
}

void CCircuit::initialise(int no_units)
{
	this->feed_id = -1;
	this->no_units = no_units;
	this->circuit_ints = new int[2 * no_units + 1];
	this->circuit_units = new CUnit[no_units];
}

CCircuit::CCircuit(int no_units)
{
	this->feed_id = -1;
	this->no_units = no_units;
	this->circuit_ints = new int[2*no_units + 1];
	this->circuit_units = new CUnit[no_units];
}
CCircuit::CCircuit(int no_units, int* circuit_array)
{
	this->feed_id = circuit_array[0];
	this->no_units = no_units;
	if (circuit_ints == nullptr) this->circuit_ints = new int[2 * no_units + 1];
	for (int i = 0; i < 2 * no_units + 1; i++)
		this->circuit_ints[i] = circuit_array[i];
	if (circuit_units == nullptr) this->circuit_units = new CUnit[no_units];
	intArrayToUnits(circuit_array, this->circuit_units, no_units);
}

CCircuit::CCircuit(int no_units, int feed, CUnit* circuit_array)
{
	this->feed_id = feed;
	this->no_units = no_units;
	this->circuit_units = new CUnit[no_units];
	for (int i = 0; i < no_units; i++)
		this->circuit_units[i] = circuit_array[i];
	this->circuit_ints = new int[2 * no_units + 1];
	unitsToIntArray(this->circuit_ints, feed, circuit_array, no_units);
}

CCircuit::~CCircuit()
{
	//delete[] circuit_ints;
	//delete[] circuit_units;
}

CCircuit::CCircuit(CCircuit &other)
{
	this->feed_id = other.feed_id;
	this->no_units = other.no_units;
	circuit_ints = new int[no_units * 2 + 1];
	circuit_units = new CUnit[no_units];

	for (int i = 0; i < no_units * 2 + 1; i++)
		circuit_ints[i] = other.circuit_ints[i];
	for (int i = 0; i < no_units; i++)
		circuit_units[i] = other.circuit_units[i];
}

void CCircuit::printCircuit()
{
	for (int j = 0; j < 2 * this->no_units + 1; j++)
	{
		cout << this->circuit_ints[j] << " ";
	}
	cout << endl;
}

void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit, int num_units) {
	//if marked, dont bother
	if (units[unit_num].mark)return;
	//mark it as visited
	units[unit_num].mark = true;

	//If we have seen this unit already exit
	//Mark that we have now seen the unit
	//If conc_num does not point at a circuit outlet recursively call the function

	//if its next unit is not an exit, mark it
	if (units[unit_num].conc_num < num_units) {
		markUnits(units[unit_num].conc_num, units, conc_exit, tail_exit, num_units); //go to
	}
	else {
		if(units[unit_num].conc_num == num_units)
		{
			conc_exit = true;
			}
		// ...Potentially do something to indicate that you have seen an exit
	}
	//If tails_num does not point at a circuit outlet recursively call the function

	//if its next unit is not an exit, mark it
	if (units[unit_num].tail_num < num_units) {
		markUnits(units[unit_num].tail_num, units, conc_exit, tail_exit, num_units);
	}
	else {
		if(units[unit_num].tail_num == num_units + 1)
		{
			tail_exit = true;
        }
		// ...Potentially do something to indicate that you have seen an exit
	}
}

void resetMarks(CUnit *units, int no_units)
{
  for(int i = 0; i < no_units; i++)
  {
    units[i].mark = false;
  }
}


bool checkValidity(CCircuit circuit)
{
	int no_units = circuit.no_units;
	CUnit* circuit_units = circuit.circuit_units;
	int *int_array = circuit.circuit_ints;
	bool conc_exit(false), tail_exit(false);

	resetMarks(circuit_units, no_units);
	markUnits(int_array[0], circuit_units, conc_exit, tail_exit, no_units); //units[0].id
	//if not traversed to exit
	if (!conc_exit || !tail_exit)
	{
		return false;
	}
	//check traverse every one
	for (int i = 0; i < no_units; i++)
	{
		if (!circuit_units[i].mark)
		{
			return false;
		}
	}
	for (int i = 1; i < 2 * no_units + 1; i += 2)
	{
		//reset flags
		if (int_array[i] == i / 2 || int_array[i + 1] == i / 2)
			//if(units[j].conc_num == i || units[j].tails_num == i)
		{
			return false;
		}
		//do mark units
		//if exits go to same place
		if (int_array[i] == int_array[i + 1])
			//if(units[j].conc_num == units[j].tails_num)
		{
			return false;
		}
		conc_exit = false; tail_exit = false; resetMarks(circuit_units, no_units);
		markUnits(i / 2, circuit_units, conc_exit, tail_exit, no_units);
		if (!conc_exit || !tail_exit)
		{
			return false;
		}
		//if conc goes to itself, tails goes to itself

		//if not traversed at all
	}
	return true;
}




// CIRCUIT MODELLING TEAM CODE BELOW //

void unitArrayToVector(CUnit *unit_array, vector<CUnit> &unit_vector, int num_units) {

	// One by one insert unit from array into vector
	for (int i = 0; i < num_units; i++) {
		unit_vector.push_back(unit_array[i]);
	}

}



double balance_mass(CCircuit circuit_obj, double tol) {
	/* Calculate fitness value of circuit.
	Parameters
	----------
	CCircuit circuit_obj: custom circuit object
		Circuit for which fitness should be calculated
	double tol: value greater than 0
		Tolerance under which we accept circuit has converged
	Returns
	-------
	double fitness_score:
		Total performance of this circuit
	*/


	// Take array from circuit object and create vector
	vector<CUnit> circuit;
	unitArrayToVector(circuit_obj.circuit_units, circuit, circuit_obj.no_units);
	int feed_index = circuit_obj.feed_id;
	int num_units = circuit_obj.no_units;
	//vector<CUnit> circuit(num_units, circuit_obj.circuit_units[0]);


	// Set all input feeds to 10-100 - initial guess
	for (int i = 0; i < num_units; i++) {
		// Current feeds
		circuit[i].curr_in_feed.value = 10;
		circuit[i].curr_in_feed.waste = 100;
	}


	double value_change;
	double waste_change;
	double max_value_change;
	double max_waste_change;
	double max_total_change = tol + 1;
	// Keep going until convergence
	int num_iterations = 0;
	while (max_total_change > tol && num_iterations++ < 100)
	{
		// Reset maximum change in feed values overall in circuit
		max_total_change = 0;

		// Calculate flowrate of all components
		for (int i = 0; i < num_units; i++) {
			// Calculate values of concentrate stream
			circuit[i].conc.value = 0.2 * circuit[i].curr_in_feed.value;
			circuit[i].conc.waste = 0.05 * circuit[i].curr_in_feed.waste;

			// Calculate values of tail stream
			circuit[i].tail.value = 0.8 * circuit[i].curr_in_feed.value;
			circuit[i].tail.waste = 0.95 * circuit[i].curr_in_feed.waste;

			// Store into old feeds
			circuit[i].old_in_feed = circuit[i].curr_in_feed;
			circuit[i].curr_in_feed.value = 0;
			circuit[i].curr_in_feed.waste = 0;
		}

		// Reset circuit feed to 10-100
		circuit[feed_index].curr_in_feed.value = 10;
		circuit[feed_index].curr_in_feed.waste = 100;

		// Add all the output feeds of each cell to the
		// inputs of the cells they point to
		for (int i = 0; i < num_units; i++) {

			// Else add to circuit total output feed
			if (circuit[i].conc_num != num_units) {
				circuit[circuit[i].conc_num].curr_in_feed += circuit[i].conc;
			}


			// Do the same for the final tail
			// NOTE: I'm skipping adding anything to the circuits
			// total tail output, we dont need it so no need to
			// calculate it
			if (circuit[i].tail_num != num_units + 1)
			{
				circuit[circuit[i].tail_num].curr_in_feed += circuit[i].tail;
			}

		}

		// Initialise mass change storage
		double value_change;
		double waste_change;
		double max_value_change = -1;
		double max_waste_change = -1;

		for (int i = 0; i < num_units; i++) {
			// Calculate maximum change in all feed stream values
			value_change = abs(circuit[i].curr_in_feed.value - circuit[i].old_in_feed.value);
			max_value_change = max(max_value_change, value_change);

			// Calculate maximum change in all feed stream wastes
			waste_change = abs(circuit[i].curr_in_feed.waste - circuit[i].old_in_feed.waste);
			max_waste_change = max(max_waste_change, waste_change);

		}

		// Overall maximum change in circuit feed
		max_total_change = max(max_value_change, max_waste_change);

	}
	// Important values for circuit
	double circuit_value = 0;
	double circuit_waste = 0;

	// If this unit isnt the last step in the circuit,
	// then add to next units input feed
	for (int i = 0; i < num_units; ++i)
	{
		if (circuit[i].conc_num == num_units)
		{
			circuit_value += circuit[i].conc.value;
			circuit_waste += circuit[i].conc.waste;
		}

	}

	// Calculate weighted fitness value based on masses
	double fitness_score = (circuit_value * 100)
		- (circuit_waste * 500);
	return fitness_score;


}
