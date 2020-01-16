#pragma once

#include <string>
#include "hyperParameter.h"
using namespace std;

//Master abstract class: GOftn: Genetic Optimize Function
class GOftn
{	
public:
	string label;
	int numChildren;
	GOftn* children[MAX_OP];
	GOftn() { } // to be used later
	virtual ~GOftn() { } // to be used later
	virtual double eval(int index) = 0;  //setting the 0 makes it a PURE
	virtual GOftn* clone() = 0; //make a deep copy of the current tree
	virtual string getLabel() = 0;
};

//class for storing constant values
class ConstNode : public GOftn {
	double constVal;
public:
	ConstNode();
	ConstNode(double preSetVal);
	double eval(int index);
	ConstNode* clone();
	string getLabel();
};

//class for using inputs
class InputNode : public GOftn {
	int inputIndex;
public:
	InputNode();
	InputNode(int inputInd);
	double eval(int index);
	InputNode* clone();
	void setValues(int inputInd);
	string getLabel();
};

//addition
class Add : public GOftn {
public:
	Add();
	double eval(int index);
	Add* clone();
	string getLabel();
};

//subtraction
class Subtract : public GOftn {
public:
	Subtract();
	double eval(int index);
	Subtract* clone();
	string getLabel();
};
//multiplication
class Multiply : public GOftn {
public:
	Multiply();
	double eval(int index);
	Multiply* clone();
	virtual string getLabel();
};
//division
class Divide : public GOftn {
public:
	Divide();
	double eval(int index);
	Divide* clone();
	string getLabel();
};
