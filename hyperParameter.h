#pragma once
#define MAX_OP 2

const int POP_SIZE = 1000;
const int NUM_GENERATIONS = 100;
const int MAX_TREE_DEPTH = 17;
const double MUTATION_THRESH = 0.1;
const double CROSSOVER_THRESH = 0.5;
const int TOU_SIZE = 7;

const int NUM_INPUTS = 9;
const int MAX_INDIMEN = 1;
const int MAX_OUTDIMEN = 1;
static double inputs[NUM_INPUTS*MAX_INDIMEN] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
static double outputs[NUM_INPUTS*MAX_OUTDIMEN] = { 6, 15, 28, 45, 66, 91, 120, 153, 190 }; //2x^2 + 3x + 1