#include <iostream>
#include "treeGeneOps.h"
#include "tools.h"
#include <algorithm>

using namespace std;

Tree::Tree()
{
	root = createRandomTree();
	depth = countDep();
	numNode = countNode();
	perfScore = 1e37;
}
Tree::~Tree()
{
	deleteTree();
}
GOftn* Tree::createRandomTree(int depth) {
	GOftn* retFtn = createRandomNode(depth);

	for (int i = 0; i < retFtn->numChildren; i++) {
		retFtn->children[i] = createRandomTree(depth + 1);
	}
	return retFtn;
}
GOftn* Tree::createRandomNode(int depth) {
	int randn = 0;
	int numFtnChoices = 2;
	GOftn* retFtn = NULL;

	if (depth < MAX_TREE_DEPTH) numFtnChoices = 6;  //if the depth is greater than 3 only allow const or inputs
	randn = rand() % numFtnChoices;		//generate random int

	switch (randn) {	//move random 
	case 0:
		retFtn = (GOftn*) new ConstNode();
		break;
	case 1:
		retFtn = (GOftn*) new InputNode();
		break;
	case 2:
		retFtn = (GOftn*) new Add();
		break;
	case 3:
		retFtn = (GOftn*) new Subtract();
		break;
	case 4:
		retFtn = (GOftn*) new Multiply();
		break;
	case 5:
		retFtn = (GOftn*) new Divide();
		break;
	default:
		cerr << "invalid random number, bad news\n\n\n";
		break;
	}
	return retFtn;
}
void Tree::printTree(GOftn*inTree)
{
	if (inTree == NULL)
		inTree = root;
	//inorder visit
	if (inTree->numChildren == 2)
	{
		printf("(");
		printTree(inTree->children[0]);
		printf("%s", inTree->getLabel().c_str());
		printTree(inTree->children[1]);
		printf(")");
	}
	else if (inTree->numChildren == 1)
	{
		printf("%s", inTree->getLabel().c_str());
		printf("(");
		printTree(inTree->children[0]);
		printf(")");
	}
	else if (inTree->numChildren == 0)
	{
		printf("%s", inTree->getLabel().c_str());
	}
	if (inTree == root) printf("\n");
	return;
}
void Tree::deleteTree(GOftn*inTree)
{
	if (inTree == NULL)
	{
		inTree = root;
	}
	for (int i = 0; i<inTree->numChildren; i++) {  //free any children first
		deleteTree(inTree->children[i]);
	}
	delete inTree;
}
GOftn** Tree::DFSvisit(int tsi, int* ci, GOftn**inTree)
{
	if (inTree == NULL)
	{
		inTree = &root;
	}
	if (*ci == tsi)
		return inTree;
	else
	{
		GOftn** tmpTree;
		for (int i = 0; i < (*inTree)->numChildren; i++)
		{
			if ((*inTree)->children[i] == NULL)
				printf("the children is NULL\n");
			*ci = *ci + 1;
			tmpTree = DFSvisit(tsi, ci, &(*inTree)->children[i]);
			if (tmpTree)
			{
				return tmpTree;
			}
				
		}
	}
	return NULL;
}
GOftn* Tree::getSubtree(int si)
{
	//si: the visiting order (index) of the root of the sub tree

	//find the subtree
	int cnt = 0;
	GOftn** subRoot = DFSvisit(si, &cnt);
	if (cnt < si)
	{
		printf("cnt %d <si %d, numNode\n", cnt, si, numNode);
		printf("root: %s\n", root->getLabel().c_str());
	}
	//clone
	return (*subRoot)->clone();
}
GOftn* Tree::getRanSubtree()
{
	int si = rand() % numNode;
	return getSubtree(si);
}
int Tree::countNode(GOftn*inTree)
{
	if (inTree == NULL)
	{
		inTree = root;
	}
	if (inTree->numChildren == 0)
		return 1;
	else
	{
		int cnt = 0;
		for (int i = 0; i < inTree->numChildren; i++)
		{
			cnt += countNode(inTree->children[i]);
		}
		return 1 + cnt;
	}
}
int Tree::countDep(GOftn*inTree, int maxdepth, int depth)
{
	if (inTree == NULL)
	{
		inTree = root;
	}
	if (depth > maxdepth)
		maxdepth = depth;
	for (int i = 0; i < inTree->numChildren; i++)
	{
		maxdepth = countDep(inTree->children[i], maxdepth, depth+1);
	}
	return maxdepth;
}
double Tree::eval(int ind)
{
	return root->eval(ind);
}
void Tree::mutateTree(GOftn** inTree, int depth) {
	if (inTree == NULL)
	{
		inTree = &root;
	}
	double randNum0t1 = rand() / (double)RAND_MAX;
	if (randNum0t1 < MUTATION_THRESH) {
		//create new node
		GOftn* newNode = createRandomNode(depth + 1);//create a random node to replace current node
		int childrenToMove = min(newNode->numChildren, (*inTree)->numChildren);
		for (int i = 0; i<childrenToMove; i++) {
			newNode->children[i] = (*inTree)->children[i];
		}
		int numNewChildren = newNode->numChildren - childrenToMove;
		if (numNewChildren > 0)
		{
			for (int i = childrenToMove; i<(childrenToMove + numNewChildren); i++) {
				newNode->children[i] = createRandomTree(depth + 1);
			}
		}
		else //clear the memory the subtree of inTree
		{
			for (int i = childrenToMove; i<(*inTree)->numChildren; i++) {
				deleteTree((*inTree)->children[i]);
			}
		}
		delete *inTree;		//free memory held by old node
		*inTree = newNode;	//replace old ptr with ptr to new
		this->depth = countDep();
		this->numNode = countNode();
	}
	for (int i = 0; i<(*inTree)->numChildren; i++) {
		mutateTree(&(*inTree)->children[i], depth + 1);
	}
}
void Tree::crossOver(Tree* donateTree)
{
	double randNum0t1 = rand() / (double)RAND_MAX;
	if (randNum0t1 < CROSSOVER_THRESH) {
		//get a random sub tree from donateTree
		GOftn* newSubTree = donateTree->getRanSubtree();
		//get a random sit of this tree
		int ci = 0, target = rand() % numNode;
		GOftn** receNode = DFSvisit(target, &ci);
		//deleteTree and substitute
		deleteTree(*receNode);
		*receNode = newSubTree;
	}
	depth = countDep();
	numNode = countNode();
}
Tree& Tree::operator=(Tree& t)
{
	if (this->root != NULL)
		deleteTree(this->root);
	if (t.root == this->root)
		return *this;
	this->depth = t.depth;
	this->numNode = t.numNode;
	this->perfScore = t.perfScore;
	this->root = t.root->clone();
	return *this;
}

bool treeSortPredIncre(Tree* t1, Tree* t2){
	return t1->perfScore > t2->perfScore;
}

void tourSel(Tree*tar, Tree*pop, Tree*ofsp)
{
	int i = rand() % POP_SIZE;
	Tree selTree;
	selTree = pop[i];
	for (int j = 1; j < TOU_SIZE; j++)
	{
		int ii = rand() % POPSIZE;
		if ((double)rand() / RAND_MAX < 0.5 && ii != i)
		{
			if (pop[ii].depth <= MAX_TREE_DEPTH && pop[ii].perfScore < selTree.perfScore)
			{
				selTree = pop[ii];
			}
		}
		else
		{
			if (ofsp[ii].depth <= MAX_TREE_DEPTH && ofsp[ii].perfScore < selTree.perfScore)
			{
				selTree = ofsp[ii];
			}
		}
	}
	*tar = selTree;
}
