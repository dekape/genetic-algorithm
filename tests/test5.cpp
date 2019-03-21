#include <cmath>
 #include <ctime>
 #include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"

// check the functions used to generate offspring
// this includes the following functions:
//      generateCircuits
//      pairParents
//      createOffsprings
//      swapGrids

 int main(int argc, char * argv[])
 {
     srand(time(NULL));

     int no_units = 3;
     int no_circuits = 10;

     CCircuit * parents, * children;
     parents = new CCircuit[no_circuits];
     children = new CCircuit[no_circuits];

     for (int i = 0; i < no_circuits; i++)
     {
         parents[i].initialise(no_units);
         children[i].initialise(no_units);
     }

     bool not_empty = false;
     generateCircuits(no_units, no_circuits, parents);

     //if even one element is populate, the loop quits
     //this is a work around since we cannot check for empty in int array
     //C++ treat 0 and '\0' as the same thing.
     for(int i=0;i<no_circuits;i++){
         for(int j=0;j<2 * no_units + 1;j++){
             if(parents[i].circuit_ints[j] != '\0'){
                 std::cout << "not empty at " << i << " " << j << std::endl;
                 not_empty = true;
                 break;
             }
         }
         if(not_empty) break;
     }

     std::cout << "generateCircuits test: ";
     if (not_empty)
         std::cout << "pass\n";
     else
         std::cout << "fail\n";

     bool pa_in = false, pb_in = false;
     CCircuit parentA;
     CCircuit parentB;

     parentA.initialise(no_units);
     parentB.initialise(no_units);

     double * fitness = new double[no_circuits];
     for(int i=0;i<no_circuits;i++){
         fitness[i] = 1;
     }
     pairParents(parents, parentA, parentB, no_units, no_circuits, fitness, 0);

     //check that the returned parentA and parentB comes from the parent list.
     //parentA check
     for(int i=0;i<no_circuits;i++){
         for(int j=0;j<2 * no_units + 1;j++){
             if(parentA.circuit_ints[j] == parents[i].circuit_ints[j]) pa_in = true;
             else
             {
                 break;
             }
         }
         if(pa_in){
             break;
         }
     }
     //parentB check
     for(int i=0;i<no_circuits;i++){
         for(int j=0;j<2 * no_units + 1;j++){
             // std::cout << i << " " << j << std::endl;
             if(parentB.circuit_ints[j] == parents[i].circuit_ints[j]) pb_in = true;
             else
             {
                 break;
             }
         }
         if(pb_in){
             break;
         }
     }

     std::cout << "pairParents test: ";
     if (pa_in && pb_in)
         std::cout << "pass\n";
     else
         std::cout << "fail\n";

     bool ca_in = false, cb_in = false;
     CCircuit childA;
     CCircuit childB;

     //set mutation and crossover limit to 0, all children will be a copy of the parent
     createOffsprings(parentA, parentB, childA, childB, no_units, no_circuits, 0, fitness, 0, 0);
     
     //check childA
     for(int j=0;j<2 * no_units + 1;j++){
         // std::cout << i << " " << j << std::endl;
         if(childA.circuit_ints[j] == parentA.circuit_ints[j]) ca_in = true;
         else
         {
             break;
         }
     }
     //check childB
     for(int j=0;j<2 * no_units + 1;j++){
         // std::cout << i << " " << j << std::endl;
         if(childB.circuit_ints[j] == parentB.circuit_ints[j]) cb_in = true;
         else
         {
             break;
         }
     }
     std::cout << "createOffsprings test: ";
     if (ca_in && cb_in)
         std::cout << "pass\n";
     else
         std::cout << "fail\n";

     bool swapped = true;
     CCircuit * temp;
     temp = new CCircuit[no_circuits];

     generateCircuits(no_units, no_circuits, children);
     generateCircuits(no_units, no_circuits, temp);

     for(int j=0;j<no_circuits;j++){
         temp[j].initialise(no_units);
         for(int i=0;i<2 * no_units + 1;i++){
             children[j].circuit_ints[i] = 1;
             temp[j].circuit_ints[i] = 1;
         }
     }

     swapGrids(parents, children, no_circuits);

     //check parent is same as temp
     for(int j=0;j<no_circuits;j++){
         for(int i=0;i<2 * no_units + 1;i++){
             if(parents[j].circuit_ints[i] != temp[j].circuit_ints[i]){
                swapped = false;
                break;
             }
         }
     }

     std::cout << "swapGrids test: ";
     if (swapped)
         std::cout << "pass\n";
     else
         std::cout << "fail\n";

     delete [] parents;
     delete [] children;
}