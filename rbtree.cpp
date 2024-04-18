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
#include "rbtree.h"

using namespace std;

/*
//Function Prototypes:
void add(node*, node*);
void print(node*, int);
void check(node*);
*/

/*In this main function, the user will be able to input commands to edit the Red Black Tree (adding values to it and printing it)*/
/*int main() {

  node* head = new node();
  head = NULL; //initial head of tree

  bool editing = true; //loops the command input process
  char command[15]; //user command

  while (editing) {

    cout << "What would you like to do? ADD to tree? PRINT tree? QUIT?" << endl;
    cin >> command;

    if (!strcmp(command, "ADD")) {
    }

    else if (!strcmp(command, "PRINT")) {
      if (head == NULL) {
	cout << "There is no tree ~ <3" << endl
      }

      else {
	cout << "Here's the tree:" << endl;
	print(head, 0);
      }
    }
    
    else if (!strcmp(command, "QUIT")) {
      editing = false;
      cout << "Quitting..." << endl;
    }

    else {
      cout << "Didn't understand that." << endl;
      cout << "_          _" << endl;
      cout << " \_(0_0)?_/" << endl;
    }
    
  }

  cout << "Thank you for witnessing this Red Black Tree program!" << endl;
  
  return 0;
}
*/

rbtree::rbtree() { //constructor
  head = NULL;
}

rbtree::~rbtree() { //destructor
}

//The add function accesses the tree and adds an input to it in the fashion of a binary tree (going down to the right if larger and down to the left if smaller or equal to). The input is added as a leaf to the tree, initially.
void rbtree::add(int input) {
  node* current = head;
  node* previous = head;
  
  node* toAdd = new node(input);

  if (current == NULL) { //case of null head
    head = toAdd;
    head -> setColor('B'); //when adding to root 
  }
  
  else {
    while (current != NULL) { //find parent of place to add

      previous = current;
      
      if (input <= current -> getData()) {
	current = current -> getL();
      }

      else if (input > current-> getData()) {
	current = current -> getR();
      }
    }
    
    if (input > previous -> getData()) { //add the new node
      previous -> setR(toAdd);
    }

    else if (input <= previous -> getData()) {
      previous -> setL(toAdd);
    }
  }

  return;
}

void rbtree::print() {
  if (head != NULL) {
    recPrint(head,0);
  }
  return;
}

void rbtree::del(int input){
  return;
}

//The print function accesses the tree and prints it out recursively, as a sideways tree. It will print out the color of each node as well as the node value.
void rbtree::recPrint(node* input, int depth) {
  //at end of tree, print current with depth
  if (input -> getR() == NULL && input -> getL() == NULL) {
    //depth
    for (int i = 0; i < depth; i++){
      cout << "\t";
    }
    //value
    cout << "[" << input -> getColor() << ":" << input -> getData() << "]" << endl;
    return;
  }

  //print right, current, then left recursively

  if (input -> getR() != NULL) {
    recPrint(input -> getR(), depth + 1); //recurse right
  }

  //current node depth
  for (int i = 0; i < depth; i++){
      cout << "\t";
    }

  //current node value
  cout << "[" << input -> getColor() << ":" << input -> getData() << "]" << endl;

  if (input -> getL() != NULL) {
    recPrint(input -> getL(), depth + 1); //recurse left
  }
  return;
}

//The reorder functions will reorganize the tree according to the 5 epic rules that govern a red black tree.
void rbtree::reorder1(node* input) {

  //This source helped me understand the two main cases for tree insertion:
  //https://www.geeksforgeeks.org/insertion-in-red-black-tree/
  
  //Big Case 1: The Parent's Sibling is Red

  if (input -> getPar() == NULL) {
    return;
  }

  if (input -> getPar() -> getPar() == NULL) {
    return;
  } //return statements for this recursive function

  //If current node's parent if parent is not null is left node of grandparent - if grandparents right child is not null and red:
  
  if (input -> getPar() != NULL && input -> getPar() -> getPar() != NULL) {

    if (input -> getPar() == input -> getPar() -> getPar() -> getL()) { 

      if (input -> getPar() -> getPar() -> getR() != NULL && input -> getPar() -> getPar() -> getR() -> getColor() == 'R') {
	//Be adding the node as red! Then Change parent and parent's sibling to black and grandparent to red


	input -> getPar() -> setColor('B');
	input -> getPar() -> getPar() -> getR() -> setColor('B');
	input -> getPar() -> getPar() -> setColor('R');
       
	//Recursively do this on grandparent
	reorder1(input -> getPar() -> getPar());
      }
      
    }

    //If current node's parent if parent is not null is right node of grandparent - if grandparent's left child is not null and red:

    else if (input -> getPar() == input -> getPar() -> getPar() -> getR()) {

      if (input -> getPar() -> getPar() -> getL() != NULL && input -> getPar() -> getPar() -> getR() -> getColor() == 'R') {
	
	input -> getPar() -> setColor('B');
	input -> getPar() -> getPar() -> getL() -> setColor('B');
	input -> getPar() -> getPar() -> setColor('R');
       
	//Recursively do this on grandparent
	reorder1(input -> getPar() -> getPar());
      }      
    }
  }
  return;
}

void rbtree::reorder2(node* input) {

  //Big Case 2: The Parent's Sibling is Black or NULL

  if (input -> getPar() != NULL && input -> getPar() -> getPar() != NULL) {

    //If that is true:
    if (input -> getPar() == input -> getPar() -> getPar() -> getL()) {
      if (input -> getPar() -> getPar() -> getR() == NULL || input -> getPar() -> getPar() -> getR() -> getColor() == 'B') {
	if (input == input -> getPar() -> getL()) {
	//Do LL is node is LL to grandparent:
	//Recolor
	}
	if (input == input -> getPar() -> getR()) {
	//Do LR if node is LR to grandparent:
	//Recolor
	}
      }
    }
    if (input -> getPar() == input -> getPar() -> getPar() -> getR()) {
      if (input -> getPar() -> getPar() -> getL() == NULL || input -> getPar() -> getPar() -> getL() -> getColor == 'B') {
	if (input == input -> getPar() -> getL()) { 
	//Do RL if node is RL to grandparent:
	}
	if (input == input -> getPar() -> getR()) {
	//Do RR if node is RR to grandparent:
	}
      }
    }
  }
}

void rbtree::rotLL(node* input) {

  node* c = input;
  node* cSib = input -> getPar() -> getR();
  node* cL = input -> getL();
  node* cR = input -> getR();
  node* p = input -> getPar();
  node* pSib = input -> getPar() -> getPar() -> getR();
  node* g = input -> getPar() -> getPar();
  //Cur, CurSib, CurL, CurR, Par, ParSib, ParSibL, ParSibR, Grandpar

  //Grandpar pntr to Par (its left) = CurSib (right of parent)
  g -> setL(cSib);
  
  //Par pntr to CurSib (right pntr) = Grand
  p -> setR(g);
  
  //Par pntr to grand is null
  p -> setPar(NULL);
  
  //Save color of Par
  char save = p -> getColor();
  
  //Par = Grand color
  p -> setColor(g -> getColor());
  
  //Grand = saved color
  g -> setColor(save);

  return;
}

void rbtree::rotLR(node* input) {
  //same notation as above
  node* c = input;
  node* cSib = input -> getPar() -> getL();
  node* cL = input -> getL();
  node* cR = input -> getR();
  node* p = input -> getPar();
  node* pSib = input -> getPar() -> getPar() -> getR();
  node* g = input -> getPar() -> getPar();
  
  //Grand pntr to Par (its left) = Cur
  g -> setL(c);
  
  //Par pntr to Cur (its right) = CurL
  p -> setR(cL);
  
  //Cur pntr to CurL = Par
  c -> setL(p);
  
  //LL on Parent
  rotLL(p);

  return;
}

void rbtree::rotRR(node* input) {
  //same notation as above
  node* c = input;
  node* cSib = input -> getPar() -> getL();
  node* cL = input -> getL();
  node* cR = input -> getR();
  node* p = input -> getPar();
  node* pSib = input -> getPar() -> getPar() -> getL();
  node* g = input -> getPar() -> getPar();

  //Grandpar pntr to Par (its right) = CurSib (left of parent)
  g -> setR(cSib);
  
  //Par pntr to CurSib (left pntr) = Grand
  p -> setL(g);
  
  //Par pntr to Grand = null
  p -> setPar(NULL);
  
  //Save color of Par
  char save = p -> getColor();
  
  //Par = Grand color
  p -> setColor(g -> getColor());
  
  //Grand = saved color
  g -> setColor(save);

  return;
}

void rbtree::rotRL(node* input) {
  node* c = input;
  node* cSib = input -> getPar() -> getR();
  node* cL = input -> getL();
  node* cR = input -> getR();
  node* p = input -> getPar();
  node* pSib = input -> getPar() -> getPar() -> getL();
  node* g = input -> getPar() -> getPar();
  
  //Grand pntr to Par (its right) = Cur
  g -> setR(c);
 
  //Par pntr to Cur (its left) = CurR
  p -> setL(cR);
  
  //Cur pntr to CurR = Par
  c -> setR(p);
  
  //RR on Parent
  rotRR(p);

  return;
}



