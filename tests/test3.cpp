#include <cmath>
#include <iostream>

#include "CUnit.h"
#include "CCircuit.h"
#include "Genetic_Algorithm.h"

int main(int argc, char * argv[])
{
	int vec1[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  10, 11, 10, 11, 10, 11, 10, 11 };

	int vec2[2 * num_units + 1] = { 0, 1, 11, 2, 11, 3, 11, 4, 11, 5, 11, 6, 11,
			  7, 11, 8, 11, 9, 11, 10, 11 };

	int vec3[2 * num_units + 1] = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9,
			  10, 11, 10, 11, 10, 11, 10, 11 };

	int vec4[2 * num_units + 1] = { 0, 1, 11, 2, 11, 3, 11, 4, 11, 5, 11, 6, 11,
			  7, 11, 8, 11, 9, 11, 10, 11 };

	crossOver(vec1, vec2, num_units);

	bool flag = false;
	int cnt1 = 0;
	int cnt2 = 0;

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

	std::cout << "Check crossOver function: ";
	if (flag == true)
		std::cout << "pass\n";
	else
		std::cout << "fail\n";
}