#include"crossover.h"
#include"fitness.h"
#include"initialize.h"
#include"mutation.h"
#include"roulette_wheel_selection.h"
#include"tournament_selection.h"
using namespace std;

//x[Gen][No.][varNumber]
//x[代][个体/染色体编号][基因编号]
double x[totalGen][popScale][varsNumber] = {};
double xTemp[popScale][varsNumber] = {};
//fitness[个体/染色体编号]
double fitness[popScale];

int main()
{
	int Gen = 0;
	int currentScale;
	double bestIndividual;

	//initialization and evaluation
	for (currentScale = 0; currentScale < popScale; currentScale++)
	{
		for (int var = 0; var < varsNumber; var++)
			initialize(x[Gen][currentScale][var]);
		fitness[currentScale] = evaluate(x[Gen][currentScale]);
		fitnessP[currentScale].data = fitness[currentScale];
		//cout << fitnessP[currentScale].data << " " << currentScale << endl;
	}

	//fitness judgement
	qsort(fitnessP, popScale, sizeof(fitnessP[0]), compares);
	bestIndividual = fitnessP[0].data;

	//EVOLUTION
	while (abs(bestIndividual - minimum) > errorRange)
	{
		//selection
		int index;
		for (currentScale = 0; currentScale < popScale; currentScale++)
		{
			index=rouletteWheelSelection(fitness);//Roulette Wheel Selection
			index = tournamentSelection(fitness);//Tournament Selection
			//cout << index << "  " << fitness[index] << "  " << currentScale << endl;
			for (size_t var = 0; var < varsNumber; var++)
				xTemp[currentScale][var] = x[Gen][index][var];
		}

		//crossover
		for (size_t i = 0; i < popScale; i = i + 2)
			crossover(xTemp[i], xTemp[i + 1]);

		//mutation
		//put xTemp[][] into x[][][]
		//evaluate new generation
		for (size_t i = 0; i < popScale; i++)
		{
			for (size_t j = 0; j < varsNumber; j++)
			{
				mutation(xTemp[i][j]);
				x[Gen + 1][i][j] = xTemp[i][j];
			}
			fitness[i] = evaluate(x[Gen + 1][i]);
			fitnessP[i].data = fitness[i];
		}
		//fitness judgement
		qsort(fitnessP, popScale, sizeof(struct Origin), compares);
		if (bestIndividual > fitnessP[0].data)
		{
			bestIndividual = fitnessP[0].data;
		}

		cout << fixed << setprecision(10);
		cout << Gen << "   " << bestIndividual << "  ";
		for (int i = 0; i < 0; i++)
			cout << x[Gen][fitnessP[0].index][i] << "  ";
		cout << endl << endl;
		Gen++;
		//test
		//if (Gen == 1)
			//break;
	}
	system("pause");
}