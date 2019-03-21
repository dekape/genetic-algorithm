#include <cmath>
#include <iostream>
#include <chrono>


#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"


using namespace std;

int main(int argc, char * argv[])
{
    auto t1 = std::chrono::high_resolution_clock::now();
    
    
    // Intitialise test circuit as array of ints
    // Provided in lecture slides
    int num_units = 15;
    double actual_fitness = 10.47;
    int * test_array = new int[31];
    test_array[0] = 6; test_array[1] = 16; test_array[2] = 7;
    test_array[3] = 7; test_array[4] = 13; test_array[5] = 11;
    test_array[6] = 12; test_array[7] = 15; test_array[8] = 5;
    test_array[9] = 3; test_array[10] = 6; test_array[11] = 0;
    test_array[12] = 2; test_array[13] = 14; test_array[14] = 12;
    test_array[15] = 1; test_array[16] = 12; test_array[17] = 14;
    test_array[18] = 11; test_array[19] = 5; test_array[20] = 16;
    test_array[21] = 11; test_array[22] = 9; test_array[23] = 4;
    test_array[24] = 1; test_array[25] = 0; test_array[26] = 8;
    test_array[27] = 5; test_array[28] = 10; test_array[29] = 2;
    test_array[30] = 6;
    
    
    // Create unit array from int array of circuit
    //CUnit test_circuit[5];
    //intArrayToUnits(test_array, test_circuit, num_units);
    
    CCircuit cc(num_units, test_array);
    
    
    //// Check if our test case is valid
    //bool valid_test = checkValidity(cc);
    //if (!valid_test) {
    //    cout << "Invalid test.\n";
    //    cout << "fail\n";
    //}
    
    
    // Finally convert to vector of units
    // vector<CUnit> circuit_vector(num_units);
    // unitArrayToVector(test_circuit, circuit_vector, num_units);
    
    
    // Balance masses of circuit and get final outputs
    double fitness;
    fitness = balance_mass(cc, 10e-5);
    
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
    
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "time laspe : "
    << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
    << " milliseconds\n";
    
}