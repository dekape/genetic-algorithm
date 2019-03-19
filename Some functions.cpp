//some functions

void crossOver(int *circuitA, int *circuitB, int no_unit, int swap_limit)
{
	double swap_rate = ((double)rand()) / RAND_MAX;

	if (swap_rate > (1 - swap_limit))
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

void pairParents(int ** circuits, int * parentA, int * parentB, int no_units, int no_circuits, double* fitness)
{
	double totalFitness = 0; //total fitness after fix
	int index1 = -1; //index for parentA
	int index2 = -1; //index for parentB

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

	double ref1 = ((double)rand()) / RAND_MAX; //get a random number within the range of totalFitness
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
		double ref2 = ((double)rand()) / RAND_MAX; //get another random number
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

void createOffsprings(int ** parents, int ** children, int no_units, int no_circuits, double mute_limit, double* fitness)
{
	int num = 0;
	int* parentA = new int[2 * no_units + 1];
	int* parentB = new int[2 * no_units + 1];
	do
	{
		pairParents(parents, parentA, parentB, no_units, no_circuits, fitness);
		crossOver(parentA, parentB, no_units);
		mutate(parentA, no_units, mute_limit);
		mutate(parentB, no_units, mute_limit);
		if (true)
		{
			for (int i = 0; i < 2 * no_units + 1; i++) //assign it
			{
				children[num][i] = parentA[i];
			}
			num++;
		}

		if (true)
		{
			for (int i = 0; i < 2 * no_units + 1; i++) //assign it
			{
				children[num][i] = parentB[i];
			}
			num++;
		}
	} while (num < no_circuits);
	delete[] parentA;
	delete[] parentB;
}

void checkTermination(int iter_count, int** offspring, int convergence_limit)
{
	int count = 0;
	int convergenceCount = 0;
	int maxfitness = 0;
	double* fitness[no_circuits];
		do
		{
			for (int i = 0; i < no_circuits; i++)
			{
				fitness[i] = balance_mass(parents[i], tol = 1e-7);
			}
			createOffsprings(parents, children, no_units, no_circuits, mute_limit, swap_limit, fitness);
			//Two ways 1. compare the fitness[0] each time 2. compare each elements of the first children
			if (balance_mass(children[0], tol = 1e-7) > max_fitness)
			{
				max_fitness = balance_mass(children[0]);
				convergenceCount = 1;
			}
			else if (fitness[0] == max_fitness)
			{
				convergenceCount++;
			}
			if (convergenceCount >= convergence_limit) break;
			std::swap(parent, children);
			count++
		} while (count < iter_count);
}