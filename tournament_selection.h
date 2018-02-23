#pragma once
#include"argument_setting.h"

static std::array<int, popScale>index = {};

int tournamentSelection(double fitness[popScale])
{
	//initialize the index
	for (int i = 0; i < popScale; i++)
		index[i] = i;

	//shuffle the index
	std::shuffle(index.begin(), index.end(), seed);

	//form a new group
	for (size_t i = 0; i < groupScale; i++)
	{
		fitnessG[i].data = fitness[index[i]];
		fitnessG[i].index = index[i];
	}

	//sort the group
	qsort(fitnessG, groupScale, sizeof(struct Origin), compares);

	return fitnessG[0].index;
}