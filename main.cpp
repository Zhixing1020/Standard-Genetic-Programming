//			
#include <iostream>
#include <cmath>
#include <algorithm>
#include <time.h>
#include "basicFunctions.h"
#include "treeGeneOps.h"
#include "tools.h"
#include "hyperParameter.h"
using namespace std;

void main (int argc, char * const argv[]) {
	srand(0);  //seed the RNG
	double sumAbsErr, err = 0.0;
	//create array to store N trees
		
	// create the inital tree population 
	Tree population[POP_SIZE + 1];
	Tree offsprings[POP_SIZE];
	
	for (int i = 0; i<POP_SIZE; i++) {
		sumAbsErr = 0.0;
		for (int j = 0; j<NUM_INPUTS; j++) {
			err = outputs[j] - (population[i].eval(j));
			sumAbsErr += abs(err);
		}
		//printf("evaluating tree %d: %f \n", i, sumAbsErr);
		if (sumAbsErr == 0) {
			printf("found a solution with 0 error\n");
			population[i].printTree();
		}
		if (isnan(sumAbsErr)) sumAbsErr = 1E+37; //max double val
		population[i].perfScore = sumAbsErr;
	}

	for (int gen=0; gen<NUM_GENERATIONS; gen++) {
		
		
		//sort by performance (sort in increasing order so we work on first N)
		//sort(population, population + POP_SIZE, treeSortPredIncre);
		for (int i = 0; i < POP_SIZE; i++)
		{
			offsprings[i] = population[i];
		}

		for (int i = 0; i < POP_SIZE; i++)
		{
			int donateCndi = rand() % POP_SIZE;
			offsprings[i].crossOver(&offsprings[donateCndi]);
			offsprings[i].mutateTree();
			sumAbsErr = 0.0;
			for (int j = 0; j<NUM_INPUTS; j++) {
				err = outputs[j] - (offsprings[i].eval(j));
				sumAbsErr += abs(err);
			}
			//printf("evaluating tree %d: %f \n", i, sumAbsErr);
			if (sumAbsErr == 0) {
				printf("found a solution with 0 error\n");
				offsprings[i].printTree();
				break;
			}
			if (isnan(sumAbsErr)) sumAbsErr = 1E+37; //max double val
			offsprings[i].perfScore = sumAbsErr;
		}

		//tournament selection 
		double minScore = 1e37;
		for (int i = 0; i < POP_SIZE; i++)
		{
			tourSel(&population[i], population, offsprings);
			if (population[i].perfScore < minScore/*population[POP_SIZE].perfScore*/)
			{
				population[POP_SIZE] = population[i];
			}
		}

		//record the best individual
		printf("Generation %d the best score is: %f\n", gen, population[POP_SIZE].perfScore);
	}
	population[POP_SIZE].printTree();
	printf("the best score is: %f\n", population[POP_SIZE].perfScore);
}