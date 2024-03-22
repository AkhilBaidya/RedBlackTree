//C++ Data Structures: Node Class Definitions - Akhil Baidya
//Submission Date: 3/22/2024
/*
Notes: This file defines the get and set functions (for the integer data, color, parent, left child, and right child of the node), constructor, and destructor of the node class.
*/

#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

//Constructors
node::node() {
  parent = NULL;
  left = NULL;
  right = NULL;
  data = 0;
  color = 'R';
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
  delete parent;
  delete left;
  delete right;
}
