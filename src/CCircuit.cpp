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
	this->no_units = -1;
	this->circuit_ints = new int[2 * no_units + 1];
	this->circuit_units = new CUnit[no_units];
}

CCircuit::CCircuit(int no_units)
{
	this->feed_id = -1;
	this->no_units = -1;
	this->circuit_ints = new int[2*no_units + 1];
	this->circuit_units = new CUnit[no_units];
}

CCircuit::CCircuit(int no_units, int* circuit_array)
{
	this->feed_id = circuit_array[0];
	this->no_units = no_units;
	this->circuit_ints = new int[2 * no_units + 1];
	for (int i = 0; i < 2 * no_units + 1; i++)
		this->circuit_ints[i] = circuit_array[i];
	this->circuit_units = new CUnit[no_units];
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
	delete[] circuit_ints;
	delete[] circuit_units;
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

void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit, int num_units) {
	//if marked, dont bother
	if (units[unit_num].mark)return;
	//mark it as visited
	units[unit_num].mark = true;
	
	//If we have seen this unit already exit
	//Mark that we have now seen the unit
	//If conc_num does not point at a circuit outlet recursively call the function

	//if its next unit is not an exit, mark it
	if (units[unit_num].conc_num < num_units - 1) {
		markUnits(units[unit_num].conc_num, units, conc_exit, tail_exit, num_units); //go to 
	}
	else {
		conc_exit = true;
		// ...Potentially do something to indicate that you have seen an exit
	}
	//If tails_num does not point at a circuit outlet recursively call the function 

	//if its next unit is not an exit, mark it
	if (units[unit_num].tails_num < num_units) {
		markUnits(units[unit_num].tails_num, units, conc_exit, tail_exit, num_units);
	}
	else {

		tail_exit = true;
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
	if (!conc_exit && !tail_exit)
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

double assessFitness(double gormanium_mass, double waste_mass) {
  /* Return a fitness value given the masses of the ouputs from a circuit.


  Notes
  -----
  The weights used here as the rewards and costs
  prescribed in the documentation provided by stephen.


  Parameters
  ----------
  double gormanium_mass: value between 0 and 10
    Mass of pure product from circuit

  double waste_mass: value between 0 and 100
    Mass of waste from circuit


  Returns
  -------
  double fitness_score: 
    Score calculate by weighted sum of gormanium and
    waste masses
  */


  // Weights for gormanium and waste
  double gormanium_reward = 100;
  double waste_cost = 500;
  

  // Calculate weighted fitness value based on masses
  double fitness_score = (gormanium_mass * gormanium_reward)
                       - (waste_mass * waste_cost);

  return fitness_score;
}


bool allUnitsMarked(vector<CUnit> &circuit) {

  bool all_marked = true;


  for (int i = 0; i < (int)circuit.size(); i++) {
    if (!circuit[i].mark) {
      all_marked = false;
    }
  }
  
  return all_marked;
}

//
//vector<double> balanceMass(vector<CUnit> &circuit) {
//
//
//  // Set feed circuit input to 10/100
//  circuit[0].old_in_feed.conc = 10;
//  circuit[0].old_in_feed.tail = 100;
//
//
//  // Set marks on all units to false
//
//
//  // Set the old values of all streams to 10/100
//  while(!allUnitsMarked(circuit)) {
//
//  }
//
//
//}