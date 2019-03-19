#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include "CUnit.h"
#include "CCircuit.h"


using namespace std;

void genRandCircuit(int num_units, int gene_length, int * gene){
    for(int i=0;i<gene_length;i++){
        gene[i] = rand() % num_units;
        cout << "\n Gene[i] = " << gene[i];
    }
}

void populateUnits(int num_units, int * gene, CUnit * circuit){
    for(int i=0;i<num_units;i++){
        circuit[i].conc_num = rand() % (num_units+3);
        circuit[i].tails_num = rand() % (num_units+3);
        circuit[i].mark = false;
    }
}


int main(int argc, char * argv[])
{
    srand(time(NULL));
/*
    genRandCircuit(num_units, gene_length, gene);
    cout << endl;
*/
    

    //populateUnits(num_units, gene, circuit);


//    int int_circuit[2*num_units + 1];

/*
    circuit[0].conc_num = 1;
    circuit[0].tails_num = 2;
    circuit[0].mark = false;
    circuit[1].conc_num = 3;
    circuit[1].tails_num = 0;
    circuit[1].mark = false;
    circuit[2].conc_num = 0;
    circuit[2].tails_num = 4;
    circuit[2].mark = false;
*/

//    circuit[0].conc_num = 1;
//    circuit[0].tails_num = 5;
//    circuit[0].mark = false;
//    circuit[1].conc_num = 4;
//    circuit[1].tails_num = 5;
//    circuit[1].mark = false;
//    circuit[2].conc_num = 4;
//    circuit[2].tails_num = 5;
//    circuit[2].mark = false;
//
//    for(int i=0;i<num_units;i++){
//        cout << "unit " << i << ", conc= " << circuit[i].conc_num << ", tail= " << circuit[i].tails_num << endl;
//    }
//    unitsToIntArray(int_circuit, circuit, num_units);
//
//    for(int i=0;i<gene_length;i++){
//
//        cout << int_circuit[i] << " ";
//    }
    
    CUnit circuit[num_units];
    int int_array[num_units * 2 + 1] = {0,1,5,4,5,4,5};
//    int int_array[num_units * 2 + 1] = {0,1,2,3,0,0,4};
    
    intArrayToUnits(int_array, circuit, num_units);

    for(int i=0;i<num_units;i++){
        cout << "unit " << i << ", conc= " << circuit[i].conc_num << ", tail= " << circuit[i].tails_num << endl;
    }
    bool test;
    test = checkValidity(int_array, circuit, num_units);
    
    printf("\nValidity test = %d\n", int(test));
    
    return 0;
}
