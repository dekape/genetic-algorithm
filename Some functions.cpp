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

		if (checkValidity(circuit, no_units))
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

void crossOver(int *circuitA, int *circuitB)
{
	int index = 1 + rand() % (2 * no_unit - 1);
	for (int i = index; i < 2 * no_unit + 1; i++)
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
	double totalFitness; //total fitness after fix
	double index1 = -1; //index for parentA
	double index2 = -1; //index for parentB

	int min_fit = 0; //compensation number to make sure all fitness numbers are larger than 0
	for (int i = 0; i < no_circuits; i++)
	{
		if (fitness[i] < min_fit)
		{
			min_fit = fitness[i]; //!!!!!!!
		}
	}

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
			break
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
				break //if it is equal, break anyways
			}
		}
	} while (index2 == -1);

	for (int i = 0; i < 2 * no_units + 1; i++) //assign it to the pointer of parentA and B
	{
		parentA[i] = circuits[index1][i];
		parentB[i] = circuits[index2][i];
	}
}