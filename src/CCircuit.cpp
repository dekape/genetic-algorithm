#include <vector>

#include <stdio.h>
#include <CUnit.h>
#include <CCircuit.h>

//std::vector<CUnit> units(num_units);

void unitsToIntArray(int *IntArray, CUnit *units_to_convert, int no_units)
{
  //IntArray is where to store answer
  //CUnit * is array of CUnits
  IntArray[0] = 0; //source is always 0
  for(int i = 1; i < no_units*2 + 1; i+= 2)
  {
    IntArray[i] = units_to_convert[i/2].conc_num;
    IntArray[i+1] = units_to_convert[i/2].tails_num;
  }
}

bool checkValidity(int *circuit, int no_units, CUnit *units)
{
  bool conc_exit(false), tail_exit(false);

  markUnits(circuit[0], units, conc_exit, tail_exit); //units[0].id
  //if not traversed to exit
  if(!conc_exit && !tail_exit)
    {
      printf("\nOne or both exit not found");
      return false;
    }
  
  for(int i = 1; i < 2*no_units + 1; i+=2)
  {
    //if exits go to same place
    printf("\nBoth outputs go to same place");
    if(circuit[i] == circuit[i+1])
    //if(units[j].conc_num == units[j].tails_num)
    {
      return false;
    }
    //if conc goes to itself, tails goes to itself
    if(circuit[i] == i/2 || circuit[i+1] ==i/2)
    //if(units[j].conc_num == i || units[j].tails_num == i)
    {
      printf("\nOutput goes to itself");
      return false;
    }
    //if not traversed at all
    if(!units[i/2].mark)
    {
      printf("\nNot every unit traversed");
      return false;
    }
  }
  return true;
}

//CUnit * units
void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit) {

  //if marked, dont bother
  if (units[unit_num].mark) return;
  printf("\nLooking at unit %d", unit_num);
  //mark it as visited
  units[unit_num].mark = true;

  //If we have seen this unit already exit
  //Mark that we have now seen the unit
  //If conc_num does not point at a circuit outlet recursively call the function

  //if its next unit is not an exit, mark it
  if (units[unit_num].conc_num<num_units) {
    markUnits(units[unit_num].conc_num, units, conc_exit, tail_exit); //go to 
  } else {
    printf("\nFound an exit");
    conc_exit = true;
    // ...Potentially do something to indicate that you have seen an exit
  }
  //If tails_num does not point at a circuit outlet recursively call the function 

  //if its next unit is not an exit, mark it
  if (units[unit_num].tails_num<num_units) {
    markUnits(units[unit_num].tails_num, units, conc_exit, tail_exit); 
  } else {
    printf("\nFound an exit");

    tail_exit = true;
    // ...Potentially do something to indicate that you have seen an exit
  }
}
//CUnit* 





