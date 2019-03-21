#include <cmath>
#include <ctime>
#include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"

//check the mutate function

int main(int argc, char * argv[])
{
	double mute_limit = 1;
	double mute_nolimit = 0;
	const int num_units = 10;

	srand(time(NULL));
	int vec1[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  2, 5, 4, 11, 3, 6, 10, 7 };

	int vec2[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  2, 5, 4, 11, 3, 6, 10, 7 };

	int vec3[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  2, 5, 4, 11, 3, 6, 10, 7 };

	mutate(vec2, num_units, mute_limit);

	bool flag = true;
	bool flag_no = true;

	//check if there is always mutation
	for (int i = 0; i < 2 * num_units + 1; i++)
	{
		if (vec2[i] == vec1[i]){
			flag = false;
			break;
		}
	}

	mutate(vec3, num_units, mute_nolimit);

	//check if there are no mutation at all
	for (int i = 0; i < 2 * num_units + 1; i++)
	{
		if (vec3[i] != vec1[i]){
			flag_no = false;
			break;
		}
	}

	std::cout << "Check mutate function Case all mutate: ";
	if (flag == true)
		std::cout << "pass\n";
	else
		std::cout << "fail\n";

	std::cout << "Check mutate function Case no mutation: ";
	if (flag_no == true)
		std::cout << "pass\n";
	else
		std::cout << "fail\n";
}
