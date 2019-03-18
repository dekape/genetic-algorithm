//
//  validityTest.cpp
//  IronFist
//
//  Created by Nitchakul Pipitvej on 18/3/19.
//  Copyright © 2019 np2618. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int NO_UNIT = 5;

class CUnit {
public:

    vector<int> instream;

    //index of the unit to which this unit’s concentrate stream is connected
    int conc_num;
    //index of the unit to which this unit’s concentrate stream is connected
    int tails_num;
    //A Boolean that is changed to true if the unit has been seen
    bool mark;

    /*

     ...other member functions and variables of CUnit

     */
};

void genRandCircuit(int no_units, int gene_length, int * gene){
    gene[0] = 0; // feed
    for(int i=1;i<gene_length;i++){
        gene[i] = rand() % no_units;
    }
}

void populateUnits(int no_units, int * gene, CUnit * circuit){
    for(int i=0;i<no_units;i++){
        circuit[i].conc_num = gene[(i * 2) + 1];
        circuit[i].tails_num = gene[(i * 2) + 2];
    }
}

int main(){
    int gene_length = NO_UNIT * 2 + 1;
    int * gene = new int(gene_length);

    genRandCircuit(NO_UNIT, gene_length, gene);

    for(int i=0;i<gene_length;i++){

        cout << gene[i] << " ";
    }

    cout << endl;

    CUnit circuit[NO_UNIT];

    populateUnits(NO_UNIT, gene, circuit);

    for(int i=0;i<NO_UNIT;i++){
        cout << "unit " << i << ", conc= " << circuit[i].conc_num << ", tail= " << circuit[i].tails_num << endl;
    }

}
