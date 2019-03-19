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
    
    
    return 0;
}
