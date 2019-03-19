#include <vector>
#include <stdio.h>
#include <CUnit.h>
#include <CCircuit.h>


using namespace std;
vector<CUnit> units(num_units);


bool Check_Validity(int *circuit_vector)
{
  return true;
}


void mark_units(int unit_num) {

  if (units[unit_num].mark) return;

  units[unit_num].mark = true;

  //If we have seen this unit already exit
  //Mark that we have now seen the unit
  //If conc_num does not point at a circuit outlet recursively call the function

  if (units[unit_num].conc_num<num_units) {
    mark_units(units[unit_num].conc_num);
  } else {
    // ...Potentially do something to indicate that you have seen an exit
  }
  //If tails_num does not point at a circuit outlet recursively call the function 

  if (units[unit_num].tails_num<num_units) {
    mark_units(units[unit_num].tails_num); 
  } else {
    // ...Potentially do something to indicate that you have seen an exit
  }
}


double assess_fitness(vector<CUnit> &circuit) {
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

	int output_num_1 = circuit.size();
	int output_num_2 = circuit.size() + 1;
	double gormanium_mass = 0;
	double waste_mass = 0;

	for (int i = 0; i < circuit.size(); i++)
	{
		if (circuit[i].conc_num == output_num_1) {
			gormanium_mass = circuit[i].conc_out.conc;
		}
		if (circuit[i].tail_num == output_num_2) {
			waste_mass = circuit[i].tail_out.tail;
		}
	}

  // Weights for gormanium and waste
  double gormanium_reward = 100;
  double waste_cost = 500;
  

  // Calculate weighted fitness value based on masses
  double fitness_score = (gormanium_mass * gormanium_reward)
                       - (waste_mass * waste_cost);

  
  return fitness_score;


}


bool all_units_marked(vector<CUnit> &circuit) {

  for (int i = 0; i < circuit.size(); i++) {
    if (!circuit[i].mark) {
	  return false;
    }
  }
  return true;

}


vector<double> balance_mass(vector<CUnit> &circuit) {


  // Set feed circuit input to 10/100
  circuit[0].old_in_feed.conc = 10;
  circuit[0].old_in_feed.tail = 100;


  // Set marks on all units to false
  for (int i = 0; i < circuit.size(); i++) {
	  circuit[i].mark = false;
	  circuit[i].curr_in_feed = circuit[i].old_in_feed;
  }


  do_unit_cal(0, circuit);



}

void do_unit_cal(int unit_index, vector<CUnit> &circuit) {
	// do_unit
	if (unit_index >= circuit.size()) {
		return;
	}

	circuit[unit_index].conc.valuable = 0.2 * circuit[unit_index].curr_in_feed.valuable;
	circuit[unit_index].conc.waste = 0.05 * circuit[unit_index].curr_in_feed.waste;
	circuit[unit_index].tail.valuable = 0.8 * circuit[unit_index].curr_in_feed.valuable;
	circuit[unit_index].tail.waste = 0.95 * circuit[unit_index].curr_in_feed.waste;
	circuit[unit_index].mark = true;

	if (circuit[unit_index].conc_num < circuit.size() && circuit[circuit[unit_index].conc_num].mark) {
		circuit[circuit[unit_index].conc_num].curr_in_feed.valuable += circuit[unit_index].conc.valuable;
		circuit[circuit[unit_index].conc_num].curr_in_feed.waste += circuit[unit_index].conc.waste;
	}
	else {
		do_unit_cal(cu.conc);
	}

	if (circuit[unit_index].tail_num < circuit.size() && circuit[circuit[unit_index].tail_num].mark) {
		circuit[circuit[unit_index].tail_num].curr_in_feed.valuable += circuit[unit_index].tail.valuable;
		circuit[circuit[unit_index].tail_num].curr_in_feed.waste += circuit[unit_index].tail.waste;
	}
	else {
		do_unit_cal(cu.tail);
	}
}