#include <iostream>
#include "CUnit.h"
#include "Genetic_Algorithm.h"
#include "CCircuit.h"
#include "CStream.h"

int main(int argc, char * argv[]){
  //simple valid case
  int valid[3] = {0, 1, 2};
  CCircuit test_valid(1, valid);
  //case when both product went to same unit
  int invalid[3] = {0, 2, 2};
  CCircuit test_invalid(1, invalid);
  if(checkValidity(test_valid))
    std::cout << "pass\n";
  else
    std::cout << "fail\n";

  std::cout << "checkValidity({0,2,2}):\n";
  if (checkValidity(test_invalid))
    std::cout << "fail\n";
  else
    std::cout << "pass\n";

  //valid case, more than one unit
  int valid_2[7] = {0,1,2,3,0,0,4};
  CCircuit test_valid_2(3, valid_2);
  std::cout << "checkValidity({0,1,2,3,0,0,4}):\n";
  if (checkValidity(test_valid_2))
    std::cout << "pass\n";
  else
    std::cout << "fail\n";

  //case when some unit does not reach both ends
  int invalid_2[13] = {0,1,2,3,2,4,5,6,4,3,6,4,7};
  CCircuit test_invalid_2(6, invalid_2);
  std::cout << "checkValidity({0,1,2,3,2,4,5,6,4,3,6,4,7};):\n";
  if (checkValidity(test_invalid_2))
    std::cout << "fail\n";
  else
    std::cout << "pass\n";
}
