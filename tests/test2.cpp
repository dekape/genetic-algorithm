#include <cmath>
#include <ctime>
#include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"

//check the crossOver function

int main(int argc, char * argv[])
{
	double swap_limit = 1;
	double swap_nolimit = 0;
    const int num_units = 10;

	int vec1[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  10, 11, 10, 11, 10, 11, 10, 11 };

	int vec2[2 * num_units + 1] = { 0, 1, 11, 2, 11, 3, 11, 4, 11, 5, 11, 6, 11,
			  7, 11, 8, 11, 9, 11, 10, 11 };

	int vec3[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  10, 11, 10, 11, 10, 11, 10, 11 };

	int vec4[2 * num_units + 1] = { 0, 1, 11, 2, 11, 3, 11, 4, 11, 5, 11, 6, 11,
			  7, 11, 8, 11, 9, 11, 10, 11 };

	int vec5[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  10, 11, 10, 11, 10, 11, 10, 11 };

	int vec6[2 * num_units + 1] = { 0, 1, 11, 2, 11, 3, 11, 4, 11, 5, 11, 6, 11,
			  7, 11, 8, 11, 9, 11, 10, 11 };

	bool flag = false;
	bool flag_no = false;
	int cnt1 = 0;
	int cnt2 = 0;

	crossOver(vec1, vec2, num_units, swap_limit);

	for (int i = 0; i < 2 * num_units + 1; i++)
	{
		if (vec1[i] == vec3[i])
		{
			cnt1++;
		}
		if (vec2[i] == vec4[i])
		{
			cnt2++;
		}
	}

	if (cnt1 == cnt2)
	{
		for (int i = cnt1; i < 2 * num_units + 1; i++)
		{
			if (vec1[i] == vec4[i] && vec2[i] == vec3[i]) flag = true;
			else
			{
				flag = false;
				break;
			}
		}
	}

	crossOver(vec3, vec4, num_units, swap_nolimit);

	for (int i = 0; i < 2 * num_units + 1; i++)
	{
		if (vec3[i] == vec5[i] && vec4[i] == vec6[i]) flag_no = true;
		else
		{
			flag_no = false;
			break;
		}
	}

	std::cout << "Check crossOver function Case 1: ";
	if (flag == true)
		std::cout << "pass\n";
	else
		std::cout << "fail\n";

	std::cout << "Check crossOver function Case 2: ";
	if (flag_no == true)
		std::cout << "pass\n";
	else
		std::cout << "fail\n";
}
