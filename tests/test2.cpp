#include <cmath>
#include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"
//

void intArrayToUnits_2(int *int_array, CUnit *circuit, int no_units)
{
    for(int i = 1; i < no_units*2; i+=2)
    {
        circuit[i/2].conc_num = int_array[i];
        circuit[i/2].tail_num = int_array[i + 1];
        circuit[i / 2].id = i / 2;
    }
}

int main(int argc, char * argv[])
{
    CUnit * circ = new CUnit[2];
    int * array = new int[5]{0,1,2,3,4};
    
    intArrayToUnits(array, circ, 2);
    
//    cout << "\nused in  : " << circ.feed_id;
    for(int aa=0;aa<2;aa++){
        cout << ", " << circ[aa].conc_num;
        cout << ", " << circ[aa].tail_num;
    }
    cout << endl;
    
    
    return 0;
}

//    int vec1[2*num_units+1] = {0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
//                10, 11, 10, 11, 10, 11, 10, 11}  ;
//
//    int vec2[2*num_units+1] = {0, 1, 11, 2, 11, 3, 11, 4, 11, 5, 11, 6, 11,
//            7, 11, 8, 11, 9, 11, 10, 11}  ;
//
//    std::cout << "Evaluate_Circuit(vec1, 0.0, 1) close to 42000.0:\n";
//    if (std::fabs(Evaluate_Circuit(vec1, 0.0, 1)-42000.0)<1.0e-8)
//        std::cout << "pass\n";
//    else
//        std::cout << "fail\n";
//
//
//    std::cout << "Evaluate_Circuit(vec2, 0.0, 1) close to 42000.0:\n";
//    if (std::fabs(Evaluate_Circuit(vec2, 0.0, 1 - 37500.0)>1.0e-8))
//        std::cout << "pass\n";
//    else
//        std::cout << "fail";
//
//}
