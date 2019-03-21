#include "Genetic_Algorithm.h"

using namespace std;

void intArrayToUnits(int *int_array, CUnit *circuit, int no_units)
{
    for(int i = 1; i < no_units*2; i+=2)
	{
        circuit[i/2].conc_num = int_array[i];
        circuit[i/2].tail_num = int_array[i + 1];
		circuit[i / 2].id = i / 2;
    }
}

void unitsToIntArray(int *int_array, int feed_id, CUnit *units_to_convert, int no_units)
{
	//int_array is where to store answer
	//CUnit * is array of CUnits
	int_array[0] = feed_id; //source is always 0
	for (int i = 1; i < no_units * 2 + 1; i += 2)
	{
		int_array[i] = units_to_convert[i / 2].conc_num;
		int_array[i + 1] = units_to_convert[i / 2].tail_num;
	}
}


void computeFitness(CCircuit* parents, double* fitness, int no_circuits)
{
	for (int i = 0; i < no_circuits; i++)
	{
		//cout << parents[i].circuit_units[0].curr_in_feed.value << " ";
		fitness[i] = balance_mass(parents[i], 10e-7);
		//cout << parents[i].circuit_units[0].curr_in_feed.value << " ";
		cout << endl;
	}
}


double selectBestCircuit(CCircuit* circuits, double* fitness, CCircuit& best_circuit, int no_circuits, int no_units)
{
	// From an array of circuits and their respective fitness values,
	// select circuit with highest fitness and stores it in CCircuit best_circuit
	// returns the highest fitness value

	double max_fit = fitness[0];
	int i_max = 0;
	for (int i = 0; i < no_circuits; i++)
	{
		if (fitness[i] > max_fit)
		{
			max_fit = fitness[i];
			i_max = i;
		}
	}
	best_circuit = circuits[i_max];

	return max_fit;
}


void generateCircuits(int no_units, int no_circuits, CCircuit* parents)
{
	// Generates random valid circuits and stores them as objects in parents array

	int valid_count = 0;								// count of valid circuits
	srand(time(NULL));									// set random seed
	int* circuit_array = new int[2 * no_units + 1];		// int array to store circuit generated
	int indexConsenOut;									// unit index of the concentrate output
	int indexTailingOut;								// unit index of the waste output
	CCircuit Circuit(no_units);							// Circuit object to store the valid circuit

	do
	{
		// Random index for concentrate and waste units, the first must be an odd number the second an even number
		// to guarantee the concentrate and waste do not end up in the same unit
		// Saves time on the validity check
		indexConsenOut = 1 + 2 * (rand() % no_units);
		indexTailingOut = 1 + (2 * (rand() % no_units) + 1);

		// Generate random units for the circuit array
		for (int i = 0; i < 2 * no_units + 1; i++)
		{
			if (i == indexConsenOut) circuit_array[i] = no_units;
			else if (i == indexTailingOut) circuit_array[i] = no_units + 1;
			else circuit_array[i] = rand() % no_units;
		}

		// Transfer circuit array to Circuit object
		// Optimisation issue: would have been better to check validity with int_array before adding information to Circuit object
		// But check_validity requires a Circuit object
		for (int i = 0; i < 2 * no_units + 1; i++) Circuit.circuit_ints[i] = circuit_array[i];
		Circuit.feed_id = circuit_array[0];
		Circuit.no_units = no_units;
		intArrayToUnits(circuit_array, Circuit.circuit_units, no_units);

		// Check circuit validity
		if (checkValidity(Circuit))
		{
			// Add circuit to parents grid
			parents[valid_count] = Circuit;
      
			// Increment number of valid circuits
			valid_count++;
		}
		
	} while (valid_count < no_circuits);

	delete[] circuit_array;
}



void crossOver(int *circuitA, int *circuitB, int no_unit, double p_crossing)
{
	double p_cross_rate = ((double)rand()) / RAND_MAX;
	if(p_cross_rate <= p_crossing)
	{
		int index = 1 + rand() % (2 * no_unit - 1);
		for (int i = index; i < 2 * no_unit + 1; i++)
		{
			int temp = circuitA[i];
			circuitA[i] = circuitB[i];
			circuitB[i] = temp;
		}
	}
}


void mutate(int *circuit, int no_unit, double mute_limit)
{
	double mute_rate; //come out a random rate

	//double mute_limit = 0.01; //mutation probability

	for (int i = 0; i < 2 * no_unit + 1; i++)
	{
		mute_rate = ((double)rand()) / RAND_MAX;

		if (mute_rate <= mute_limit && i != 0)
		{
			int temp = circuit[i];
			do
			{
				circuit[i] = (circuit[i] + no_unit + 2 + rand() % (no_unit + 2)) % (no_unit + 2);
			} while (temp == circuit[i]);

		}
		else if (mute_rate <= mute_limit && i == 0)
		{
			int temp = circuit[i];
			do
			{
				circuit[i] = (circuit[i] + no_unit + rand() % no_unit) % no_unit;
			} while (temp == circuit[i]);
		}
	}
}


void pairParents(CCircuit *circuits, CCircuit &parentA, CCircuit &parentB, int no_units, 
					int no_circuits, double* fitness, double totalFitness)
{

	int index1 = -1; //index for parentA
	int index2 = -1; //index for parentB
	double ref1 = ((double)rand()) / RAND_MAX; //get a random number within the range of totalFitness
	double refNum1 = ref1 * totalFitness;
	double fitnessRef = 0; //use a reference number to get the index

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
		double ref2 = ((double)rand()) / RAND_MAX; //get another random number
		double refNum2 = ref2 * totalFitness;

		for (int i = 0; i < no_circuits; i++)
		{
			fitnessRef += fitness[i]; //ignore the first choice
			if (fitnessRef >= refNum2)
			{
				index2 = i;
				break; //if it is equal, break anyways
			}
		}
	} while (index2 == -1);
 
	parentA = circuits[index1];
	parentB = circuits[index2];

}


void createOffsprings(CCircuit& parentA, CCircuit& parentB, CCircuit& childA, CCircuit& childB, 
						int no_units, int no_circuits, double mute_limit, 
						double* fitness_adjusted, double cross_limit, double totalFitness)
	{
	// Creates a pair of offsprings from a pair of parents
	// Offsprings created through cross-over and mutation
	// Probability for cross-over passed as cross_limit
	// Probability for mutation passed as mute_limit
	// Stores offsprings in childA and childB

	mutate(parentA.circuit_ints, no_units, mute_limit);
	mutate(parentB.circuit_ints, no_units, mute_limit);
	crossOver(parentA.circuit_ints, parentB.circuit_ints, no_units, cross_limit);

	
	intArrayToUnits(parentA.circuit_ints, parentA.circuit_units, no_units);
	intArrayToUnits(parentB.circuit_ints, parentB.circuit_units, no_units);

	childA = parentA;
	childB = parentB;
}

void swapGrids(CCircuit* parents, CCircuit* offsprings, int no_circuits)
{
	for (int i = 0; i < no_circuits; i++)
	{
		parents[i] = offsprings[i];
	}
}


double adjustFitness(double* fitness, double* fitness_adjusted, int no_circuits)
{
	// Scales fitness to the absolute range of fitness values
	// Stores the adjusted values in fitness_adjusted
	// Returns the range as a double
	for(int i = 0; i < no_circuits; i++)
	{
		fitness_adjusted[i] = fitness[i];
	}
	
	
	double totalFitness = 0; //total fitness after fix

	int min_fit = 0; //compensation number to make sure all fitness numbers are larger than 0
	for (int i = 0; i < no_circuits; i++)
	{
		if (fitness[i] < min_fit)
		{
			min_fit = fitness[i];
		}
	}

	for (int i = 0; i < no_circuits; i++) //fix the fitness array and calculate the totalFitness (whether to just change the fitness array or just make a new array?)
	{
		fitness_adjusted[i] -= min_fit;
		totalFitness += fitness_adjusted[i];
	}

	return totalFitness;
}




