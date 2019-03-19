
#include "CCircuit.h"

using namespace std;


void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit, int num_units) {

	//if marked, dont bother
	if (units[unit_num].mark) return;
	printf("\nLooking at unit %d", unit_num);
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
		printf("\nFound an exit");
		conc_exit = true;
		// ...Potentially do something to indicate that you have seen an exit
	}
	//If tails_num does not point at a circuit outlet recursively call the function 

	//if its next unit is not an exit, mark it
	if (units[unit_num].tails_num < num_units) {
		markUnits(units[unit_num].tails_num, units, conc_exit, tail_exit, num_units);
	}
	else {
		printf("\nFound an exit");

		tail_exit = true;
		// ...Potentially do something to indicate that you have seen an exit
	}
}


bool checkValidity(int *int_array, CUnit *circuit, int no_units)
{
	bool conc_exit(false), tail_exit(false);

	markUnits(int_array[0], circuit, conc_exit, tail_exit, no_units); //units[0].id
	//if not traversed to exit
	if (!conc_exit && !tail_exit)
	{
		printf("\nOne or both exit not found");
		return false;
	}
	//check traverse every one
	for (int i = 0; i < no_units; i++)
	{
		if (!circuit[i].mark)
		{
			printf("\nNot every unit traversed");
			return false;
		}
	}
	printf("\n Conc? %d \n Tail? %d", (int)conc_exit, (int)tail_exit);
	for (int i = 1; i < 2 * no_units + 1; i += 2)
	{
		//reset flags
		if (int_array[i] == i / 2 || int_array[i + 1] == i / 2)
			//if(units[j].conc_num == i || units[j].tails_num == i)
		{
			printf("\nOutput goes to itself");
			return false;
		}
		//do mark units
		//if exits go to same place
		if (int_array[i] == int_array[i + 1])
			//if(units[j].conc_num == units[j].tails_num)
		{
			printf("\nBoth outputs go to same place");
			return false;
		}
		printf("\nChecking we can find both exits from unit %d", i / 2);
		conc_exit = false; tail_exit = false; resetMarks(circuit, no_units);
		markUnits(i / 2, circuit, conc_exit, tail_exit, no_units);
		if (!conc_exit || !tail_exit)
		{
			printf("\nCan't find an exit from unit %d", i / 2);
			return false;
		}
		//if conc goes to itself, tails goes to itself

		//if not traversed at all
	}
	return true;
}


void resetMarks(CUnit *units, int no_units)
{
	for (int i = 0; i < no_units; i++)
	{
		units[i].mark = false;
	}
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


  for (int i = 0; i < circuit.size(); i++) {
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