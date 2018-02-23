#pragma once
#include"argument_setting.h"

double evaluate(double x[])
{
	double sum = 0;
	for (int i = 0; i < varsNumber; i++)
		sum += (x[i] ) * (x[i] );
	return sum;
}
