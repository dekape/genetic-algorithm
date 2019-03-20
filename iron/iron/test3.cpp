#include <cmath>
#include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"


using namespace std;


int main(int argc, char * argv[])
{


    // Intitialise test circuit as array of ints
    // Provided in lecture slides 
    int num_units = 5;
    double actual_fitness = 24.82;
    int test_array[11] = {0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1};

    
    // Create unit array from int array of circuit
    /*CUnit test_circuit[5];
    intArrayToUnits(test_array, test_circuit, num_units);*/


    //// Check if our test case is valid
    //bool valid_test = checkValidity(test_array, test_circuit, num_units);
    //if (!valid_test) {
    //    cout << "Invalid test.\n";
    //    cout << "fail\n";
    //}

    
    // Finally create the circuit object
	CCircuit circuit_obj(num_units, test_array);

    
    // Balance masses of circuit and get final outputs
    double fitness;
    fitness = balance_mass(circuit_obj, 10e-8);  
	cout << fitness << endl;

    // See if the difference is within tolerance
    double difference = fitness - actual_fitness;
	printf("\n");
    if (abs(difference) < 10e-6) {
        std::cout  << "pass\n";
	} 
    else
    {
	    std::cout << "fail\n";
    }
    

	system("pause");

}