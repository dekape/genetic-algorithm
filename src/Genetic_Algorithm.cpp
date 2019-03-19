#include "Genetic_Algorithm.h"

using namespace std;

void intArrayToUnits(int *int_array, CUnit *circuit, int no_units)
{
    for(int i=1;i<no_units*2 + 1;i+=2){
        circuit[i/2].conc_num = int_array[i];
        circuit[i/2].tails_num = int_array[i + 1];
    }
}

void unitsToIntArray(int *int_array, CUnit *units_to_convert, int no_units)
{
	//int_array is where to store answer
	//CUnit * is array of CUnits
	int_array[0] = 0; //source is always 0
	for (int i = 1; i < no_units * 2 + 1; i += 2)
	{
		int_array[i] = units_to_convert[i / 2].conc_num;
		int_array[i + 1] = units_to_convert[i / 2].tails_num;
	}
}

//void generateCircuitUnits(int no_units, int no_circuits, CUnit** parents)
//{
//	int valid_count = 0;
//	srand(time(NULL));
//	CUnit* circuit = new CUnit[no_units];
//
//	do
//	{
//		for (int i = 0; i < no_units; i++)
//		{
//			circuit[i] = CUnit(i, rand() % no_units, rand() % no_units);
//		}
//
//		if (checkValidity(circuit, 0, no_units))
//		{
//
//			// Add circuit to parents grid as Unit object
//			for (int i = 0; i < no_units; i++)
//			{
//				//cout << parents[0][0].id << endl;
//				parents[valid_count][i] = circuit[i];
//			}
//
//			// Increment number of valid circuits
//			valid_count++;
//		}
//	} while (valid_count < no_circuits);
//
//}

void computeFitness(CUnit** circuits, double*fitness, int no_circuits)
{
	for (int i = 0; i < no_circuits; i++)
	{
		fitness[i] = rand() % 100;
	}
}


void selectBestCircuit(CUnit**circuits, double* fitness, CUnit* best_circuit, int no_circuits, int no_units)
{
	int max_fit = 0;
	int i_max = 0;
	for (int i = 0; i < no_circuits; i++)
	{
		if (fitness[i] > max_fit)
		{
			fitness[i] = max_fit;
			i_max = i;
		}
	}

	for (int i = 0; i < no_units; i++)
	{
		best_circuit[i] = circuits[i_max][i];
	}
}


void generateCircuits(int no_units, int no_circuits, int** parents)
{
	int valid_count = 0;
	srand(time(NULL));
	int* circuit = new int[2 * no_units + 1];
	int indexConsenOut = 1 + 2 * (rand() % no_units);
	int indexTailingOut = 1 + (2 * (rand() % no_units) + 1);

	do
	{
		for (int i = 0; i < 2 * no_units + 1; i++)
		{
			if (i == indexConsenOut) circuit[i] = 10;
			else if (i == indexTailingOut) circuit[i] = 11;
			else circuit[i] = rand() % no_units;
		}

		if (true)	// CHECK VALIDITY HERE!!
		{
			// Add circuit to parents grid as Unit object
			for (int i = 0; i < 2 * no_units + 1; i++)
			{
				//cout << parents[0][0].id << endl;
				parents[valid_count][i] = circuit[i];
			}

			// Increment number of valid circuits
			valid_count++;
		}
	} while (valid_count < no_circuits);

}


void crossOver(int *circuitA, int *circuitB, int no_units)
{
	int index = 1 + rand() % (2 * no_units - 1);
	for (int i = index; i < 2 * no_units + 1; i++)
	{
		int temp = circuitA[i];
		circuitA[i] = circuitB[i];
		circuitB[i] = temp;
	}
}


void mutate(int *circuit, int no_unit)
{
	double mute_rate; //come out a random rate

	double mute_limit = 0.01; //mutation probability

	for (int i = 0; i < 2 * no_unit + 1; i++)
	{
		mute_rate = ((double)rand()) / RAND_MAX;
		if (mute_rate <= mute_limit && i != 0)
		{
			circuit[i] = (circuit[i] + no_unit + 2 + rand() % (no_unit + 2)) % (no_unit + 2);
		}
		else if (mute_rate <= mute_limit && i == 0)
		{
			circuit[i] = (circuit[i] + no_unit + rand() % no_unit) % no_unit;
		}
	}
}


void pairParents(int ** circuits, int * parentA, int * parentB, int no_units, int no_circuits, double* fitness)
{
	double totalFitness;	//total fitness after fix
	int index1 = -1;		//index for parentA
	int index2 = -1;	//index for parentB
	double ref1, ref2;

	int min_fit = 0; //compensation number to make sure all fitness numbers are larger than 0
	for (int i = 0; i < no_circuits; i++)
	{
		if (fitness[i] < min_fit)
		{
			min_fit = fitness[i]; //!!!!!!!
		}
	}

	totalFitness = 0;
	for (int i = 0; i < no_circuits; i++) //fix the fitness array and calculate the totalFitness
	{
		fitness[i] -= min_fit;
		totalFitness += fitness[i];
	}

	ref1 = ((double)rand()) / RAND_MAX; //get a random number within the range of totalFitness
	double refNum1 = ref1 * totalFitness;
	double fitnessRef = 0; //use a reference number to get the index
	int* fitnessind = new int[int(totalFitness)];

	for (int i = 0; i < no_circuits; i++) //get the index from the random number
	{
		fitnessRef += fitness[i];
		if (fitnessRef >= refNum1)
		{
			index1 = i;
			break;
		}
	}
	fitnessRef = 0; //clear the fitness reference

	do
	{
		ref2 = ((double)rand()) / RAND_MAX; //get another random number
		double refNum2 = ref2 * totalFitness;

		for (int i = 1; i < no_circuits; i++)
		{
			fitnessRef += fitness[i];
			if (fitnessRef >= refNum2)
			{
				if (index1 != i) //make sure it's not equal to parentA
				{
					index2 = i;
				}
				break; //if it is equal, break anyways
			}
		}
	} while (index2 == -1);

	for (int i = 0; i < 2 * no_units + 1; i++) //assign it to the pointer of parentA and B
	{
		parentA[i] = circuits[index1][i];
		parentB[i] = circuits[index2][i];
	}
}


void markUnits(int unit_num, CUnit *units, bool &conc_exit, bool &tail_exit, int num_units) {

	//if marked, dont bother
	if (units[unit_num].mark) return;
	printf("\nLooking at unit %d", unit_num);
	//mark it as visited
	units[unit_num].mark = true;

	//If we have seen this unit already exit
	//Mark that we have now seen the unit
	//If conc_num does not point at a circuit outlet recursively call the function

	//if its next unit is not an exit, mark it
	if (units[unit_num].conc_num < num_units) {
		markUnits(units[unit_num].conc_num, units, conc_exit, tail_exit, num_units); //go to 
	}
	else {
		printf("\nFound an exit");
		conc_exit = true;
		// ...Potentially do something to indicate that you have seen an exit
	}
	//If tails_num does not point at a circuit outlet recursively call the function 

	//if its next unit is not an exit, mark it
	if (units[unit_num].tails_num < num_units) {
		markUnits(units[unit_num].tails_num, units, conc_exit, tail_exit, num_units);
	}
	else {
		printf("\nFound an exit");

		tail_exit = true;
		// ...Potentially do something to indicate that you have seen an exit
	}
}


bool checkValidity(int *int_array, CUnit *circuit, int no_units)
{
	bool conc_exit(false), tail_exit(false);

	markUnits(int_array[0], circuit, conc_exit, tail_exit, no_units); //units[0].id
	//if not traversed to exit
	if (!conc_exit && !tail_exit)
	{
		printf("\nOne or both exit not found");
		return false;
	}
	//check traverse every one
	for (int i = 0; i < no_units; i++)
	{
		if (!circuit[i].mark)
		{
			printf("\nNot every unit traversed");
			return false;
		}
	}
	printf("\n Conc? %d \n Tail? %d", (int)conc_exit, (int)tail_exit);
	for (int i = 1; i < 2 * no_units + 1; i += 2)
	{
		//reset flags
		if (int_array[i] == i / 2 || int_array[i + 1] == i / 2)
			//if(units[j].conc_num == i || units[j].tails_num == i)
		{
			printf("\nOutput goes to itself");
			return false;
		}
		//do mark units
		//if exits go to same place
		if (int_array[i] == int_array[i + 1])
			//if(units[j].conc_num == units[j].tails_num)
		{
			printf("\nBoth outputs go to same place");
			return false;
		}
		printf("\nChecking we can find both exits from unit %d", i / 2);
		conc_exit = false; tail_exit = false; resetMarks(circuit, no_units);
		markUnits(i / 2, circuit, conc_exit, tail_exit, no_units);
		if (!conc_exit || !tail_exit)
		{
			printf("\nCan't find an exit from unit %d", i / 2);
			return false;
		}
		//if conc goes to itself, tails goes to itself

		//if not traversed at all
	}
	return true;
}


void resetMarks(CUnit *units, int no_units)
{
	for (int i = 0; i < no_units; i++)
	{
		units[i].mark = false;
	}
}