#include <iostream>
#include "CUnit.h"
#include "Genetic_Algorithm.h"
#include "CCircuit.h"
#include "CStream.h"


int main(int argc, char * argv[]){
  //simple valid case
  int valid[3] = {0, 1, 2};
  
  //case when both product went to same unit
  int invalid[3] = {0, 2, 2};
  
  CUnit circuit[3];
  intArrayToUnits(valid, circuit, 1);  
  std::cout << "Check_Validity({0,1,2}):\n";
  if(checkValidity(valid, circuit, 1))
    
    std::cout << "pass\n";
  else
    std::cout << "fail\n";
  
  intArrayToUnits(invalid, circuit, 1);
  std::cout << "Check_Validity({0,2,2}):\n";
  if (checkValidity(invalid, circuit, 1))
    std::cout << "fail\n";
  else
    std::cout << "pass\n";
  
  //valid case, more than one unit
  int valid_2[7] = {0,1,2,3,0,0,4};
  CUnit circuit_2[7];
  intArrayToUnits(valid_2, circuit_2, 3);
  std::cout << "Check_Validity({0,1,2,3,0,0,4}):\n";
  if (checkValidity(valid_2, circuit_2, 3))
    std::cout << "pass\n";
  else
    std::cout << "fail\n";
  
  //case when some unit does not reach both ends
  int invalid_2[13] = {0,1,2,3,2,4,5,6,4,3,6,4,7};
  intArrayToUnits(invalid_2, circuit_2, 6);
  std::cout << "Check_Validity({0,1,2,3,2,4,5,6,4,3,6,4,7};):\n";
  if (checkValidity(invalid_2, circuit_2, 6))
    std::cout << "fail\n";
  else
    std::cout << "pass\n";
}