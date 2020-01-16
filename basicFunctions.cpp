#include <iostream>
#include <sstream>
#include "basicFunctions.h"
using namespace std;

//
//		ConstNode
//
ConstNode::ConstNode(){
	this->numChildren = 0;
	this->constVal = rand()/(double)RAND_MAX;
	char str[20] = "";
	sprintf(str, "%f", constVal);
	this->label = str;
}
ConstNode::ConstNode(double preSetVal){
	this->numChildren = 0;
	this->constVal = preSetVal;
	char str[20] = "";
	sprintf(str, "%f", constVal);
	this->label = str;
}
double ConstNode::eval(int index){
	return constVal;
}
ConstNode* ConstNode::clone(){
	ConstNode* retTree = new ConstNode(constVal);
	return retTree; 
}
string ConstNode::getLabel(){
	return this->label;
}
//
//		InputNode
//
InputNode::InputNode(){
	this->numChildren = 0;
	inputIndex = rand() % MAX_INDIMEN;
	setValues(inputIndex);
}
InputNode::InputNode(int inputInd) {
	this->numChildren = 0;
	setValues(inputInd);
}
double InputNode::eval(int index){
	return inputs[index*MAX_INDIMEN + this->inputIndex];
}
void InputNode::setValues(int inIndex){
	char str[20] = "";
	sprintf(str, "x%d", inIndex);
	this->label = str;
}
InputNode* InputNode::clone(){
	InputNode* retTree = new InputNode();
	retTree->setValues(this->inputIndex);
	return retTree; 
}
string InputNode::getLabel(){
	return this->label;
}
//
//		Add
//
Add::Add(){
	this->numChildren = 2;
	label = "+";
}
double Add::eval(int index){
	if (this->children[0]!=NULL && this->children[1]!=NULL){
		return this->children[0]->eval(index) + this->children[1]->eval(index);
	}
	else {
		cerr << "left and right not defined in add"<<endl;
		return -1.0;
	}
}
Add* Add::clone(){
	Add* retNode = new Add();
	for (int i=0; i<numChildren; i++) {
		retNode->children[i] = this->children[i]->clone();
	}
	return retNode;
}
string Add::getLabel(){
	return this->label;
}
//
//		Subtract
//
Subtract::Subtract(){
	this->numChildren = 2;
	this->label = "-";
}
double Subtract::eval(int index){
	if (this->children[0] != NULL && this->children[1] != NULL) {
		return this->children[0]->eval(index) - this->children[1]->eval(index);
	}
	else {
		cerr << "left and right not defined in add" << endl;
		return -1.0;
	}
}
Subtract* Subtract::clone(){
	Subtract* retNode = new Subtract();
	for (int i=0; i<this->numChildren; i++) {
		retNode->children[i] = this->children[i]->clone();
	}
	return retNode;
}
string Subtract::getLabel(){
	return this->label;
}
//
//		Multiply
//
Multiply::Multiply(){
	numChildren = 2;
	label = "*";
}
double Multiply::eval(int index){
	if (this->children[0] != NULL && this->children[1] != NULL) {
		return this->children[0]->eval(index) * this->children[1]->eval(index);
	}
	else {
		cerr << "left and right not defined in add" << endl;
		return -1.0;
	}
}
Multiply* Multiply::clone(){
	Multiply* retNode = new Multiply();
	for (int i=0; i<numChildren; i++) {
		retNode->children[i] = this->children[i]->clone();
	}
	return retNode;
}
string Multiply::getLabel(){
	return label;
}
//
//		Divide
//
Divide::Divide(){
	numChildren = 2;
	label = "/";
}
double Divide::eval(int index){
	if (this->children[0] != NULL && this->children[1] != NULL) {
		double v0 = children[0]->eval(index);
		double v1 = children[1]->eval(index);
		if (v1 != 0)
			return v0 / v1;
		else
			return v0;
	}
	else {
		cerr << "left and right not defined in multiply"<<endl;
		return -1.0;
	}
}
Divide* Divide::clone(){
	Divide* retNode = new Divide;
	for (int i=0; i<numChildren; i++) {
		retNode->children[i] = this->children[i]->clone();
	}
	return retNode;
}
string Divide::getLabel(){
	return label;
}