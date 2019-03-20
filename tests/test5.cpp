 #include <cmath>
 #include <ctime>
 #include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"

//
//void swapGridsTest(CCircuit * parents, CCircuit * offsprings, int no_circuits)
//{
//    swap(parents, offsprings);
//}

 int main(int argc, char * argv[])
 {
     srand(time(NULL));

     int no_units = 10;
     int no_circuits = 100;
     double mute_limit = 0.01;
     double swap_limit = 0.01;

     CCircuit * parents, * children;
     parents = new CCircuit[no_circuits];
     children = new CCircuit[no_circuits];

     for (int i = 0; i < no_circuits; i++)
     {
         parents[i].initialise(no_units);
         children[i].initialise(no_units);
     }

     generateCircuits(no_units, no_circuits, parents);

     std::cout << "generateCircuits test: pass" << std::endl;

     bool pa_in = false, pb_in = false;
     CCircuit parentA;
     CCircuit parentB;

     parentA.initialise(no_units);
     parentB.initialise(no_units);

     double * fitness = new double[no_circuits];
     for(int i=0;i<no_circuits;i++){
         fitness[i] = 1;
     }
     pairParents(parents, parentA, parentB, no_units, no_circuits, fitness);


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

     std::cout << "pairParents test: ";
     if (pa_in && pb_in)
         std::cout << "pass\n";
     else
         std::cout << "fail\n";

     createOffsprings(parents, parentA, parentB, no_units, no_circuits, mute_limit, swap_limit, fitness);
//     parentA.printCircuit();
//     std::cout << "-----" << std::endl;
//     parentB.printCircuit();
     std::cout << "createOffsprings test: pass" << std::endl;

     
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


//int main(){
//  return 0;
//}
