//C++ Data Structures: Node Class Definitions - Akhil Baidya
//Submission Date: 5/2/2024

/*
Notes: This file defines the get and set functions (for the integer data, color, parent, left child, and right child of the node), constructor, and destructor of the node class.
*/

#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

//Constructors
node::node() {
  parent = NULL; //set pointers to null
  left = NULL;
  right = NULL;
  data = 0;
  color = 'R'; //by default, the node is red
}

node::node(int input) {
  parent = NULL;
  left = NULL;
  right = NULL;
  data = input;
  color = 'R';
}

//Destructor
node::~node() {
  delete parent; //delete pointers
  delete left;
  delete right;
}

//Set functions:
void node::setPar(node* input) {
  parent = input;
}

void node::setL(node* input) {
  left = input;
}

void node::setR(node* input) {
  right = input;
}

void node::setData(int input) {
  data = input;
}

void node::setColor(char input) {
  color = input;
}

//Get functions:
node* node::getPar() {
  return parent;
}

node* node::getL() {
  return left;
}

node* node::getR() {
  return right;
}

int node::getData() {
  return data;
}

char node::getColor() {
  return color;
}
