#include <cmath>
#include <ctime>
#include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"

int main(int argc, char * argv[])
{
<<<<<<< HEAD
	double mute_limit = 1; // will always mutate
	double mute_nolimit = 0; // will never mutate
    const int num_units = 10;
=======
	double mute_limit = 1;
	double mute_nolimit = 0;
>>>>>>> frank
	srand(time(NULL));
	int vec1[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  2, 5, 4, 11, 3, 6, 10, 7 };

	int vec2[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  2, 5, 4, 11, 3, 6, 10, 7 };

	int vec3[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  2, 5, 4, 11, 3, 6, 10, 7 };

	mutate(vec2, num_units, mute_limit);

<<<<<<< HEAD
	bool flag = true;
	bool flag_no = true;

	//check if there is always mutation
	for (int i = 0; i < 2 * num_units + 1; i++)
	{
		if (vec2[i] == vec1[i]){
			flag = false;
=======
	bool flag = false;
	bool flag_no = false;

	for (int i = 0; i < 2 * num_units + 1; i++)
	{
		if (vec2[i] != vec1[i]) flag = true;
		else
		{
		    flag = false;
>>>>>>> frank
			break;
		}
	}

	mutate(vec3, num_units, mute_nolimit);

<<<<<<< HEAD
	//check if there are no mutation at all
	for (int i = 0; i < 2 * num_units + 1; i++)
	{
		if (vec3[i] != vec1[i]){
			flag_no = false;
=======
	for (int i = 0; i < 2 * num_units + 1; i++)
	{
		if (vec3[i] == vec1[i]) flag_no = true;
		else
		{
		    flag_no = false;
>>>>>>> frank
			break;
		}
	}

<<<<<<< HEAD
	std::cout << "Check mutate function Case all mutate: ";
	if (flag == true)
		std::cout << "pass\n";
	else
		std::cout << "fail\n";

	std::cout << "Check mutate function Case no mutation: ";
=======
	std::cout << "Check mutate function Case 1: ";
	if (flag == true)
		std::cout << "pass\n";
	else
		std::cout << "fail\n"; 
	
	std::cout << "Check mutate function Case 2: ";
>>>>>>> frank
	if (flag_no == true)
		std::cout << "pass\n";
	else
		std::cout << "fail\n";
}
