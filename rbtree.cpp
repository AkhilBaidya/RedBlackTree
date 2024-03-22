//C++ Data Structures: Red Black Tree - Akhil Baidya
//Submission Date: 5/2/24
/*
Notes: This is a self-balancing Binary Tree that takes integers from 1-999. It can add them manually or through a file and print out the values.

Here are the values that govern a Red Black Tree (taken from Canvas):
1) A node is either red or black.
2) The root is black.
3) All leaves (NULL) are black.
4) Both children of every red node are black.
5) Every simple path from a given node to any of its descendant leaves contains the same number of black nodes.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include "node.h"

using namespace std;

//Function Prototypes:
void add(node*, node*);
void print(node*);
void check(node*);

/*In this main function, the user will be able to input commands to edit the Red Black Tree (adding values to it and printing it)*/
int main() {
  return 0;
}

//The add function accesses the tree and adds an input to it in the fashion of a binary tree (going down to the right if larger and down to the left if smaller or equal to). The input is added as a leaf to the tree, initially.
void add(node* head, node* input) {

}

//The print function accesses the tree and prints it out recursively, as a sideways tree. It will print out the color of each node as well as the node value.
void print(node* head) {

}

//The check function will reorganize the tree according to the 5 epic rules that govern a red black tree.
void check(node* head) {

}
