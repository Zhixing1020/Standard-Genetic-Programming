#pragma once
#include "basicFunctions.h"

class Tree
{
public:
	int depth;
	int numNode;  //the number of nodes in the whole tree
	double perfScore;
	GOftn* root;
	Tree();
	~Tree();
	GOftn* createRandomNode(int depth);
	GOftn* createRandomTree(int depth = 1);
	void printTree(GOftn*inTree = NULL);
	GOftn** DFSvisit(int tsi, int* ci, GOftn** inTree = NULL);
	GOftn* getRanSubtree();  //return a deep copy of a random subtree
	GOftn* getSubtree(int si);  //return a deep copy of a certain sub tree
	int countDep(GOftn*inTree = NULL, int maxdepth = 0, int depth = 1);
	int countNode(GOftn*inTree = NULL);
	double eval(int ind);
	void mutateTree(GOftn** inTree=NULL, int depth = 0);
	void crossOver(Tree* donatingTree);  //get a sub tree from donatingTree and substitute into original tree, update the depth
	void deleteTree(GOftn* inTree=NULL);
	Tree & operator = (Tree&);   //deep clone between Tree class
};


//void printTree(GOftn* inTree, int depth = 0);
//void mutateTree(GOftn** inTree, int depth = 0);
//void crossOver(GOftn* treeToAlter, GOftn* donatingTree);
//void deleteTree(GOftn* inTree);
bool treeSortPredIncre(GOftn* t1, GOftn* t2);

void tourSel(Tree*tar, Tree*pop, Tree*ofsp);