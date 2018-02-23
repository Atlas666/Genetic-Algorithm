#pragma once
#include"argument_setting.h"

void crossover(double first[],double second[])
{
	double r = proportion(seed);
	static int pos;
	if (r < rateCrossover)
	{
		pos = randomPos(seed);
		for (pos; pos < varsNumber; pos++)
		{
			std::swap(first[pos], second[pos]);
		}
	}
}