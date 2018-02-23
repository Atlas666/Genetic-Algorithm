#pragma once
#include<iostream>
#include<random>
#include<ctime>
#include<array>
#include<algorithm>
#include<cmath>
#include<iomanip>

const int varsNumber = 30;//quantity of variables
const double lower = -100;//lower boarder of variable
const double upper = 100;//upper boarder of variable

const int popScale = 100;//population scale
const int groupScale = 60;//¡û¡û¡û¡û¡û¡û¡û¡û¡û¡ûgroup scale
const int totalGen = 60000;//total generarion

const double rateCrossover = 0.7;//¡û¡û¡û¡û¡û¡û¡û¡û¡û¡ûrate of crossover
const double rateMutation = 0.07;//¡û¡û¡û¡û¡û¡û¡û¡û¡û¡ûrate of mutation

const double minimum = 0;//the value of minimum
const double errorRange = 0.01;//the error range you can accept

std::default_random_engine seed(time(NULL));
std::uniform_real_distribution<double> randomVar(lower, upper);
std::uniform_real_distribution<double> proportion(0, 1);
std::uniform_int_distribution<int> randomPos(1, varsNumber - 2);

struct Origin
{
	double data;
	int index;
} fitnessG[groupScale], fitnessP[popScale], fitnessR[popScale];
// "sortedFitness[i].data" is the porportion of fitness

int compares(const void *a, const void *b)
{
	if ((*(struct Origin *)a).data > (*(struct Origin *)b).data)
		return 1;
	else
		return -1;
}

int compareb(const void *a, const void *b)
{
	if ((*(struct Origin *)a).data < (*(struct Origin *)b).data)
		return 1;
	else
		return -1;
}