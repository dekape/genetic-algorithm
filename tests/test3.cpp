#include <cmath>
#include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"

//check the fitness result from balance_mass function

using namespace std;


int main(int argc, char * argv[])
{


    // Intitialise test circuit as array of ints
    // Provided in lecture slides
    int num_units = 5;
    double actual_fitness = 24.82;
    int * test_array = new int[11]{0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1};

    // Create unit array from int array of circuit
    CUnit test_circuit[5];
    //intArrayToUnits(test_array, test_circuit, num_units);

    CCircuit cc(5, test_array);


    //// Check if our test case is valid
    //bool valid_test = checkValidity(cc);
    //if (!valid_test) {
    //    cout << "Invalid test.\n";
    //    cout << "fail\n";
    //}


    // Finally convert to vector of units
    vector<CUnit> circuit_vector(num_units);
    unitArrayToVector(test_circuit, circuit_vector, num_units);


    // Balance masses of circuit and get final outputs
    double fitness;
    fitness = balance_mass(cc, 10e-8);


    // See if the difference is within tolerance
    double difference = fitness - actual_fitness;
    cout << "The finess result is : " << fitness << endl;

    printf("\n");
    if (abs(difference) < 10e-2) {
        std::cout << "pass\n";
    }
    else
    {
        std::cout << "fail\n";
    }

}
