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


double assess_fitness(double gormanium_mass, double waste_mass) {
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


bool all_units_marked(vector<CUnit> &circuit) {


  bool all_marked = true;


  for (int i = 0; i < circuit.size(); i++) {
    if (!circuit[i].mark) {
      all_marked = false;
    }
  }
  

}


vector<double> balance_mass(vector<CUnit> &circuit) {


  // Set feed circuit input to 10/100
  circuit[0].old_in_feed.conc = 10;
  circuit[0].old_in_feed.tail = 100;


  // Set marks on all units to false


  // Set the old values of all streams to 10/100
  while(!all_units_marked(circuit)) {

  }






}