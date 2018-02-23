#pragma once
#include"argument_setting.h"
#include"fitness.h"

void initialize(double& var)
{
	var = randomVar(seed);
}