/*	Genetic Algorithm	start from 2018.2.4   */
#include<iostream>
#include<ctime>
#include<random>
#include<array>
#include<iomanip>
#include<algorithm>
using namespace std;

//random number generator
default_random_engine engine(time(NULL));
uniform_real_distribution<double> randomNum(0, 1);
uniform_real_distribution<double> randomInd(-5, 5);
uniform_int_distribution<int> randomPos(1, 3);

//set constant rate and constant number
const double crossoverRate = 0.6;
const double mutationRate = 0.04;
const int popScale = 100;
const int totalGen = 1000;

//keep the origin index
struct Origin
{
	double data;
	int index;
} sortedFitness[popScale];// "sortedFitness.data" is the porportion of fitness
array <double, popScale> fitness = {};

//variable name[Gen][Num]
//x?s is the population after rolette wheel selection
array <array<double, popScale>, totalGen + 1> x1, x1s = {};
array <array<double, popScale>, totalGen + 1> x2, x2s = {};
array <array<double, popScale>, totalGen + 1> x3, x3s = {};
array <array<double, popScale>, totalGen + 1> x4, x4s = {};

//GA function declaration
void initialize(double&, double&, double&, double&);//done
double evaluateFitness(double, double, double, double);//done
double getTotalFitness(array<double, popScale>);//done
int rouletteWheelSelection(struct Origin sortedFitness[]);//done
void crossover(double&, double&, double&, double&
	, double&, double&, double&, double&);
void mutation(double&);//done
void replace(double&,double&);//done

//sub function declaration
int compare(const void *, const void *);//   ???  →→→"NEED MORE RESEARCH!!!←←←  ???

//main function
int main()
{
	int Gen = 1;
	double totalFitness = 0;
	double bestIndividual = 0;//
	array <double, 4> bestsolution = {};

	//①initialize the population
	//②calculate fitness
	//③add fitness
	//④caculate fitness proportion
	//⑤input fitness proportion
	for (size_t pop = 0; pop < popScale; pop++)
	{
		initialize(x1[Gen][pop], x2[Gen][pop], x3[Gen][pop], x4[Gen][pop]);//①
		fitness[pop] = evaluateFitness(x1[Gen][pop], x2[Gen][pop], x3[Gen][pop], x4[Gen][pop]);//②
	}
	totalFitness = getTotalFitness(fitness);//③
	for (size_t i = 0; i < popScale; i++)
	{
		sortedFitness[i].data = fitness[i] / totalFitness;//④⑤
		sortedFitness[i].index = i;
	}

	//sort fitness
	const static int n= sizeof(fitness) / sizeof(double);
	qsort(sortedFitness, n, sizeof(struct Origin), compare);

	//keep best individual ???
	bestIndividual = sortedFitness[0].data*totalFitness;
	bestsolution[0] = x1[Gen][sortedFitness[0].index];
	bestsolution[1] = x2[Gen][sortedFitness[0].index];
	bestsolution[2] = x3[Gen][sortedFitness[0].index];
	bestsolution[3] = x4[Gen][sortedFitness[0].index];

	//!!EVOLUTION!!
	for (Gen = 1; Gen < totalGen; Gen++)//                   !!!!!!test for 1st time!!!!!!
	{
		//Roulette Wheel Selection
		static int currentScale = 0;
		while (currentScale < popScale)
		{
			int chosenIndex;
			chosenIndex = rouletteWheelSelection(sortedFitness);
			x1s[Gen][currentScale] = x1[Gen][chosenIndex];
			x2s[Gen][currentScale] = x2[Gen][chosenIndex];
			x3s[Gen][currentScale] = x3[Gen][chosenIndex];
			x4s[Gen][currentScale] = x4[Gen][chosenIndex];
			currentScale++;
		}

		//crossover
		for (size_t pop = 0; pop < popScale; pop += 2)
		{
			crossover(x1s[Gen][pop], x2s[Gen][pop], x3s[Gen][pop], x4s[Gen][pop]
				, x1s[Gen][pop + 1], x1s[Gen][pop + 1]
				, x1s[Gen][pop + 1], x1s[Gen][pop + 1]);
		}

		//mutation
		for (size_t i = 0; i < popScale; i++)
		{
			mutation(x1s[Gen][i]);
			mutation(x2s[Gen][i]);
			mutation(x3s[Gen][i]);
			mutation(x4s[Gen][i]);
		}

		//input x?s into x?
		for (size_t pop = 0; pop < popScale; pop++)
		{
			x1[Gen + 1][pop] = x1s[Gen][pop];
			x2[Gen + 1][pop] = x2s[Gen][pop];
			x3[Gen + 1][pop] = x3s[Gen][pop];
			x4[Gen + 1][pop] = x4s[Gen][pop];
		}

		//new population evaluation
		for (size_t pop = 0; pop < popScale; pop++)
		{
			fitness[pop] = evaluateFitness(x1[Gen+1][pop], x2[Gen+1][pop], x3[Gen+1][pop], x4[Gen+1][pop]);//②
		}
		totalFitness = getTotalFitness(fitness);//③
		for (size_t i = 0; i < popScale; i++)
		{
			sortedFitness[i].data = fitness[i] / totalFitness;//④⑤
			sortedFitness[i].index = i;
		}
			//sort fitness
		qsort(sortedFitness, n, sizeof(struct Origin), compare);
			//compare Gen i best and Gen i+1 best
		if (bestIndividual < sortedFitness[0].data*totalFitness)
		{
			bestIndividual = sortedFitness[0].data*totalFitness;
			bestsolution[0] = x1[Gen][sortedFitness[0].index];
			bestsolution[1] = x2[Gen][sortedFitness[0].index];
			bestsolution[2] = x3[Gen][sortedFitness[0].index];
			bestsolution[3] = x4[Gen][sortedFitness[0].index];
		}


		//reset all the arguments
		currentScale = 0;
		for (size_t i = 0; i < popScale-1; i++)
			fitness[i] = 0;
	}
	cout << "After " << Gen << " times evolution" << endl;
	cout << "The maximum value for 1/(x1^2 + x2^2 + x3^2 + x4^2 + 1) is ";
	cout << bestIndividual << endl;
	system("pause");
}

//GA function definintion
void initialize(double& var1, double& var2, double& var3, double& var4)
{
	var1 = randomInd(engine);
	var2 = randomInd(engine);
	var3 = randomInd(engine);
	var4 = randomInd(engine);
}

double evaluateFitness(double x1, double x2, double x3, double x4)
{
	return 1 / (x1 * x1 + x2 * x2 + x3 * x3 + x4 * x4 + 1);
}

double getTotalFitness(array <double, popScale> fitness)
{
	double totalFitness = 0;
	for (size_t i = 0; i < popScale; i++)
		totalFitness += fitness[i];
	return totalFitness;
}

int rouletteWheelSelection(struct Origin sortedFitness[])
{
	double totalProbability = 0;
	double randomProbabiliy = randomNum(engine);

	//selection
	for (size_t sortedPop = 0; sortedPop < popScale; sortedPop++)
	{
		totalProbability += sortedFitness[sortedPop].data;
		if (totalProbability > randomProbabiliy)
		{
			return sortedFitness[sortedPop].index;
			break;
		}
	}
}

void crossover(double& x1, double& x2, double& x3, double& x4
	,double& y1, double& y2, double& y3, double& y4)
{
	double random = randomNum(engine);
	int pos = randomPos(engine);

	if (random < crossoverRate)
	{
		switch (pos)
		{
		case 1:
			swap(x2, y2);
			swap(x3, y3);
			swap(x4, y4);
			break;
		case 2:
			swap(x3, y3);
			swap(x4, y4);
			break;
		case 3:
			swap(x4, y4);
			break;
		default:
			break;
		}
	}
}

void mutation(double& var)
{
	double random = randomNum(engine);

	if (random < mutationRate)
	{
		var = randomInd(engine);
	}
}

void replace(double& var1, double& var2)
{
	swap(var1, var2);
}

//sub function definition
int compare(const void *a, const void *b)
{
	if ((*(struct Origin *)a).data < (*(struct Origin *)b).data)
		return 1;
	else
		return -1;
}