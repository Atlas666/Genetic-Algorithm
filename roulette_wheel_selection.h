#pragma once
#include"argument_setting.h"

int rouletteWheelSelection(double fitness[popScale])
{
	double r = proportion(seed);
	double sum = 0;
	double totalFitness = 0;

	for (size_t i = 0; i < popScale; i++)
	{
		fitnessR[i].data = 1 / (fitness[i] + 1);
		fitnessR[i].index = i;
	}

	for (size_t i = 0; i < popScale; i++)
		totalFitness += fitnessR[i].data;

	qsort(fitnessR, popScale, sizeof(struct Origin), compares);

	for (size_t i = 0; i < popScale; i++)
	{
		sum += fitnessR[i].data / totalFitness;

		if (sum > r)
		{
			return fitnessR[i].index;
			break;
		}
	}
}