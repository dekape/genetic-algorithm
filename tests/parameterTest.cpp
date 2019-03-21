#include <stdio.h>
#include <iostream>
#include "Genetic_Algorithm.h"
#include "CUnit.h"
#include "CCircuit.h"
#include "CStream.h"
//#define DEBUG

using namespace std;

int iter_max = 5000;						// max number of iterations
int p_crossing = 0.9;						// probability of crossing over
int p_mutation = 0.001;						// probability of mutation
int no_units = 5;							// total number of units
int no_circuits = 10;						// total number of initial circuits
int iter_count = 0;							// iterations counter
int offspring_count = 0;					// offsprings per iterations counter
int best_count = 0;
double* fitness;							// list to store the fitness values of all circuits
CCircuit* parents;							// 2D array to store all parent circuits
CCircuit* offsprings;						// 2D array to store all offspring circuits
CCircuit best_circuit(no_units);			// object to store best circuit based on fitness calculation
CCircuit best_circuit_prev(no_units);

using namespace std;

void altOffspring(int begin_range, int end_range, int step_size){
    for(int i=begin_range;i<end_range;i+=step_size){
        //do thing

    }
}

void altCrossingRate(double min_rate, double max_rate, double step_size){
    for(double i=min_rate;i<max_rate;i+=step_size){

    }
}

void altMutateRate(double min_rate, double max_rate, double step_size){
    for(double i=min_rate;i<max_rate;i+=step_size){

    }
}

void altPenaltynReward(){

}

int main(int argc, char * argv[])
{



    //write stat to file


}
