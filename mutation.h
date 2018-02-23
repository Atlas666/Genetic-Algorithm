#pragma once
#include"argument_setting.h"

void mutation(double& var)
{
	double r = proportion(seed);
	if (r < rateMutation)
		var = randomVar(seed);
}