#include <vector>

#include <stdio.h>
#include <CUnit.h>
#include <CCircuit.h>

//std::vector<CUnit> units(num_units);
int no_units = 2;

void unitsToIntArray(int *IntArray, CUnit *units_to_convert)
{
  //IntArray is where to store answer
  IntArray[0] = 0;
  for(int i = 1; i < no_units; i++)
  {
    IntArray[i] = units_to_convert[i].conc_num;
  }

}

bool checkValidity(CUnit *units, int no_units)
{
  bool conc_exit(false), tail_exit(false);

  markUnits(0, units, conc_exit, tail_exit); //units[0].id
  //if not traversed to exit
  if(!conc_exit && !tail_exit)
    {
      return false;
    }
  
  for(int i = 0; i < no_units; i++)
  {
    //if exits go to same place
    if(units[i].conc_num == units[i].tails_num)
    {
      return false;
    }
    //if conc goes to itself, tails goes to itself
    if(units[i].conc_num == i || units[i].tails_num == i)
    {
      return false;
    }
    //if not traversed at all
    if(!units[i].mark)
    {
      return false;
    }
  }
  return true;
}

//CUnit * units
void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit) {

  //if marked, dont bother
  if (units[unit_num].mark) return;
  //mark it as visited
  units[unit_num].mark = true;

  //If we have seen this unit already exit
  //Mark that we have now seen the unit
  //If conc_num does not point at a circuit outlet recursively call the function

  //if its next unit is not an exit, mark it
  if (units[unit_num].conc_num<num_units) {
    markUnits(units[unit_num].conc_num, units, conc_exit, tail_exit); //go to 
  } else {
    conc_exit = true;
    // ...Potentially do something to indicate that you have seen an exit
  }
  //If tails_num does not point at a circuit outlet recursively call the function 

  //if its next unit is not an exit, mark it
  if (units[unit_num].tails_num<num_units) {
    markUnits(units[unit_num].tails_num, units, conc_exit, tail_exit); 
  } else {
    tail_exit = true;
    // ...Potentially do something to indicate that you have seen an exit
  }
}
//CUnit* 





