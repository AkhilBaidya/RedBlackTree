//C++ Data Structures: Red Black Tree Class Definitions - Akhil Baidya
//Submission Date: 5/22/24

/*
Notes:
This is a self-balancing Binary Tree that takes integers from 1-999. This file defines how nodes are added to the tree, how they are deleted from the tree, how the tree prints itself, and how it reorders itself (see header file).

Sources:
Here are the rules that govern a Red Black Tree (taken from Canvas):
1) A node is either red or black.
2) The root is black.
3) All leaves (NULL) are black.
4) Both children of every red node are black.
5) Every simple path from a given node to any of its descendant leaves contains the same number of black nodes.

For Insertion:
Additionally, referred to https://www.geeksforgeeks.org/insertion-in-red-black-tree/, the web article by GeeksforGeeks on Red Black Tree insertion. This provided more clarity as to what triggers rotations in a red black tree (a null or black uncle) or a simple recoloring (a red uncle). Additionally, it provided general steps for the rotations and recoloring.

For Deletion:
I studied the process of deletion for red black trees through five sources. I reviewed a tutorial from programiz.com (https://www.programiz.com/dsa/red-black-tree) and a tutorial from GeeksForGeeks (https://www.geeksforgeeks.org/deletion-in-red-black-tree/) which helped me understand to perform standard BST Deletions before the special red black tree deletions that require reordering (these reorderings arise out of "double black" scenarios, where black depth is interfered with, and when a parent node has a single child). For the case scenarios for reordering (the six I have written as functions), I understood the process through a document written by Purdue (chrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/https://www.cs.purdue.edu/homes/ayg/CS251/slides/chap13c.pdf), a video by Mr. Galbraith (https://www.youtube.com/watch?v=BIflee1rLDY), and a video by Tushar Roy on Youtube (https://www.youtube.com/watch?v=CTvfzU_uNKE).
*/

#include <iostream>
#include <cstring>
#include "rbtree.h"

using namespace std;

//Constructor:
rbtree::rbtree() {
  head = NULL;
}

//Destructor:
rbtree::~rbtree() {
}


//PUBLIC FUNCTIONS: ----------

/*This is the add function which accesses the tree and adds some input in it in the fashion of a binary tree (going down to the right if input's value is larger than the current node's and down to the left if smaller or equal to). The input is added as a leaf to the tree, initially. Reorders are called after this addition.*/
void rbtree::add(int input) {
  node* current = head;
  node* previous = head;
  node* toAdd = new node(input); //This node will be added

  //Binary tree addition:

  //Case of a null head:
  if (current == NULL) {
    head = toAdd; //set the head to the input
    head -> setColor('B'); //the head should be black 
  }

  //Otherwise:
  else {
    while (current != NULL) { //find the parent of the location to add (by using previous, when current == NULL)
      previous = current;
      
      if (input <= current -> getData()) { //traverse down tree
	current = current -> getL();
      }

      else if (input > current-> getData()) { //traverse down tree
	current = current -> getR();
      }
    }
    
    if (input > previous -> getData()) { //add the new node as the right child of "previous" 
      previous -> setR(toAdd);
      toAdd -> setPar(previous);
    }

    else if (input <= previous -> getData()) { //or add the new node as the left child of "previous"
      previous -> setL(toAdd);
      toAdd -> setPar(previous);
    }
  }
  //Call reorder:
  reorder(toAdd);

  //Show tree updates:
  cout << "Current Tree:" << endl;
  print();
  return;
}

/*This is the print function which prints out the tree sideways with each node (including their values and colors). It calls a private function to do this.*/
void rbtree::print() {
  //If the head is not empty, then call the private function:
  if (head != NULL) {
    recPrint(head,0);
  }
  return;
}

/*This is the delete function. It takes in an integer, searches for it and deletes it from the tree, calling reordering if necessary*/
void rbtree::del(int input){

  //Search for the node to delete: 
  node* current = head;

  while (current != NULL && current -> getData() != input) { //reach spot to delete
    if (current -> getData() < input) { //traverse right
      current = current -> getR();
    }
    else if (current -> getData() > input) {//traverse left
      current = current -> getL();
    }
  }

  //Delete it:
  if (current != NULL) {
    //cout << "Found thing to delete" << endl;

    node* d = current; //node to delete
    node* l = d -> getL(); //its left
    node* r = d -> getR(); //its right

    //Case - Node is a Red Leaf:
    if (d -> getColor() == 'R' && d -> getL() == NULL & d -> getR() == NULL) {
      //cout << "it's a red leaf case" << endl;

      //Simply separate node from its parent and delete it:
      if (d == d -> getPar() -> getL()) {
	d -> getPar() -> setL(NULL);
	d -> setPar(NULL);

	delete d;
      }

      else if (d == d -> getPar() -> getR()) {
	d -> getPar() -> setR(NULL);
	d -> setPar(NULL);

	delete d;
      }
    }

    //Case - Node is the Head with no Children:
    else if (d == head && head -> getL() == NULL && head -> getR() == NULL) {
      //cout << "it's the head, just a head case" << endl;
      head = NULL;
      delete d;
    }

    //Case - Node has One Child and they are not Both Black:
    else if (r == NULL && l != NULL && !(d -> getColor() == 'B' && l -> getColor() == 'B') || l == NULL && r != NULL && !(r -> getColor() == 'B' && d -> getColor() == 'B')) {
      //cout << "has a child but not doubly black" << endl;

      node* p = d -> getPar(); //parent
      node* c; //child
      if (l != NULL) {
	c = l;
      }
      else if (r != NULL) {
	c = r;
      }
      //cout << "set child" << endl;

      //If the current node "d" is not the head:
      if (d != head) {
	d -> setData(c -> getData()); //replace d with c (by shifting c's data to d and changing d's color to black)
	d -> setColor('B');
	
	d -> setL(c -> getL()); //move c's children to d
	d -> setR(c -> getR());
	//cout << "edited"<< endl;
	if (c -> getL() != NULL) {
	  c -> getL() -> setPar(d);
	}
	if (c -> getR() != NULL) {
	  c -> getR() -> setPar(d);
	}
	//cout << "removed d's connections" << endl;

	c -> setL(NULL); //delete c
	c -> setR(NULL);
	c -> setPar(NULL);
	delete c;
	cout << "deleted c" << endl;
      }

      //If the current node "d" wanted to be deleted is the head: 
      else if (d == head) {
	head = c; //set the head as c and delete d (make sure the head is black)
	d -> setL(NULL);
	d -> setR(NULL);
	c -> setPar(NULL);
	delete d;
	head -> setColor('B');
      }
    }

    //Case - The Node to be Deleted has Two Children:
    else if (d -> getL() != NULL && d -> getR() != NULL) {
      //cout << "has two children" << endl;

      //Find successor (the largest number smaller than the node deleted):
      node* successor = d -> getL();
      while (successor -> getR() != NULL) {
	//cout << "need to recurse right" << endl;
	successor = successor -> getR(); //find a larger number if possible
      }
      d -> setData(successor -> getData()); //move the successor (its data) to d

      //Know that there will be nothing to the right of the successor:

      //If there is nothing to the left of the node:
      if (successor -> getL() == NULL) {
	if (successor -> getColor() == 'B') {
	  case1(successor); //run check due to doubly black scenario if successor (which is going to be deleted) is black (it is replaced by a null node which is also considered black)
	}

	//Disconnect successor from the tree:
	if (successor == successor -> getPar() -> getL()) { //its a left child
	  successor -> getPar() -> setL(NULL);
	  successor -> setPar(NULL);
	}
	else if (successor == successor -> getPar() -> getR()) { //its a right child
	  successor -> getPar() -> setR(NULL);
	  successor -> setPar(NULL);
	}
	successor -> setL(NULL);
	successor -> setR(NULL);
	delete successor; //delete it
      }

      //If there is something to the left of the successor:
      else if (successor -> getL() != NULL) {
	char color = successor -> getColor(); //color of the successor
	char color2 = successor -> getL() -> getColor(); //color of what is replacing the successor
	node* replace = successor -> getL(); //get what to replace the successor with 
	
	//cout << "successor has something to its left" << endl;
	//Replace successor with its left child:
	if (successor == successor -> getPar() -> getR()) { //successor is a right child
	  //cout << "to right" << endl;
	  successor -> getPar() -> setR(successor -> getL());
	  successor -> getL() -> setColor(successor -> getColor());
	  successor -> getL() -> setPar(successor -> getPar());
	}
	else if (successor == successor -> getPar() -> getL()) { //successor is a left child
	  //cout << "to left" << endl;
	  successor -> getPar() -> setL(successor -> getL());
	  successor -> getL() -> setColor(successor -> getColor());
	  successor -> getL() -> setPar(successor -> getPar());
	}
	else {
	  cout << "Should not be the case" << endl;
	}
	//cout << "did it" << endl;
	//Disconnect successor from tree and delete it:
	successor -> setPar(NULL);
	successor -> setL(NULL);
	successor -> setR(NULL);
	//cout << "set everything null" << endl;
	delete successor;

	//cout << "double black check" << endl;
	//If replaced a black successor with a black child, run check for doubly black scenario:
	if (color == 'B' && color2 == 'B') {
	  case1(replace);
	  //cout << "did it" << endl;
	}
      }
    }

    //Case (Doubly Black) - Node to be Deleted has one Right Black Child which replace it:
    else if (d -> getColor() == 'B' && l == NULL && r != NULL && r -> getColor() == 'B') {
      //cout << "doubly black from right" << endl;

      //Replace the node with its right child (copy data and left and right children of that child):
      d -> setData(r -> getData());
      d -> setL(r -> getL());
      d -> setR(r -> getR());

      //Delete the right child:
      r -> setPar(NULL);
      r -> setL(NULL);
      r -> setR(NULL);
      delete r;

      //Run doubly black check on the node to be deleted:
      case1(d);
    }

    //Case (Doubly Black) - Node to be Deleted has one Left Black Child which replace it:
    else if (d -> getColor() == 'B' && r == NULL && l != NULL && l -> getColor() == 'B') {
      //cout << "doubly black from left" << endl;

      //Replace the node with its left child (copy values):
      d -> setData(l -> getData());
      d -> setL(l -> getL());
      d -> setR(l -> getR());

      //Delete the left child:
      l -> setPar(NULL);
      l -> setL(NULL);
      l -> setR(NULL);
      delete l;

      //Run doubly black check on the node to be deleted:
      case1(d);
    }

    //Case (Doubly Black) - Node to be Deleted is a Black Leaf (no children):
    else if (d -> getL() == NULL && d -> getR() == NULL && d -> getColor() == 'B') {
      //cout << "black leaf so reordering then deleting" << endl;
      
      //Run doubly black check (and reorders) on this node first, and then delete it (effectively replacing it with its null child):
      case1(d);

      //Reordering done, so now delete the node:
      //cout << "reordered, now deleting" << endl;
      if (d == d -> getPar() -> getL()) {
	d -> getPar() -> setL(NULL);
      }
      else if (d == d -> getPar() -> getR()) {
	d -> getPar() -> setR(NULL);
      }
      d -> setPar(NULL);
      delete d;
    }
  }

  //Case - Value is not in tree:
    else {
      cout << "Value not found :'(" << endl;
    }
  
  return;
}

/*
This is the search function, which takes in an integer input and searches whether it is in the red black tree (returning a boolean)
 */
bool rbtree::search(int input) {
  node* current = head;

  //If the head already contains the number, return true:
  if (head != NULL & head -> getData() == input) {
    return true;
  }

  //Else, loop through the tree until arriving at a node which contains the number:
  else {
    while (current -> getData() != input && current != NULL) {
      if (current -> getData() <= input) {
	current = current -> getL();
      }
      else if (current -> getData() > input) {
	current = current -> getR();
      }
    }
    if (current != NULL) { //If reached a node, then the number is in the tree:
      return true;
    }
  }

  //Otherwise, the node is not in the tree:
  return false;
}

//PRIVATE FUNCTIONS: ----------

/*This is the recursive print function. It accesses the tree and takes in some current depth to print each node out (its depth, color, and value). This forms a sideways tree.*/
void rbtree::recPrint(node* input, int depth) {

  //When the code reaches the end of tree, print the current node with depth:
  if (input -> getR() == NULL && input -> getL() == NULL) {
    //Depth:
    for (int i = 0; i < depth; i++){
      cout << "\t";
    }
    //Value:
    cout << "[" << input -> getColor() << ":" << input -> getData() << "]" << endl;
    return;
  }

  //Print right, current, then left recursively (creating a sideways tree):

  //Recurse right:
  if (input -> getR() != NULL) {
    recPrint(input -> getR(), depth + 1);
  }

  //Print current:
  //Current node depth:
  for (int i = 0; i < depth; i++) {
      cout << "\t";
  }
  //Current node value:
  cout << "[" << input -> getColor() << ":" << input -> getData() << "]" << endl;

  //Recurse left:
  if (input -> getL() != NULL) {
    recPrint(input -> getL(), depth + 1);
  }
  return;
}

//REORDERING FOR DELETION (for double-black scenarios):
//The double-black node will be referred to as "x"

/*
case6 checks if the sibling has a red child which is RR or LL relative to the parent of x and reorders/recolors the tree accordingly:
 */
void rbtree::case6(node* input) {
  //cout << "entering case 6" << endl;
  //Key players:
  node* p = input -> getPar();
  node* g = p -> getPar();
  node* s;
  if (input == p -> getL()) {
    s = p -> getR();
  }
  else if (input == p -> getR()) {
    s = p -> getL();
  }

  //The sibling should not be null and should be black:
  if (s != NULL && s -> getColor() == 'B') {
    node* sL = s -> getL(); //get sibling's children
    node* sR = s -> getR();

    //cout << "actually do case 6" << endl;

    //LL case
    if (s == p -> getL() && sL != NULL && sL -> getColor() == 'R') {
      //Do a LL rotation on sL
      rotLL(sL);
      sL -> setColor('B');
    }

    //RR case
    else if (s == p -> getR() && sR != NULL && sR -> getColor() == 'R') {
      //Do a RR rotation on SR
      rotRR(sR);
      sR -> setColor('B');
    }
  }
  return;
}

/*
  case5 checks if the sibling has a red child (called if the child is RL or LR relative to the parent of x) and performs required rotations and coloring:
 */
void rbtree::case5(node* input) {
  //cout << "entering case 5" << endl;

  //Key players:
  node* p = input -> getPar();
  node* g = p -> getPar();
  node* s;
  if (input == p -> getL()) {
    s = p -> getR();
  }
  else if (input == p -> getR()) {
    s = p -> getL();
  }

  //Sibling should not be null and should be black:
  if (s != NULL && s -> getColor() == 'B') {
    node* sL = s -> getL(); //get sibling's children
    node* sR = s -> getR();
    //cout << "actually do case 5" << endl;

    //LR case
    if (s == p -> getL() && (sL == NULL && sR != NULL && sR -> getColor() == 'R' || sL -> getColor() == 'B' && sR != NULL && sR -> getColor() == 'R')) {
      //Rotate sL over S:
      node* sRL = sR -> getL(); //get sR's left child

      p -> setL(sR); //set parent's left as sR
      sR -> setPar(p);
      
      sR -> setL(s); //set sR's left as sibling
      s -> setPar(sR);
      
      s -> setR(sRL);//set sibling's right as sRL
      if (sRL != NULL) {
	sRL -> setPar(s);
      }
      
      //Recolor:
      s -> setColor('R');
      sR -> setColor('B');
    }

    //RL Case
    else if (s == p -> getR() && (sR == NULL && sL != NULL && sL -> getColor() == 'R' || sR -> getColor() == 'B' && sL != NULL && sL -> getColor() == 'R')) {
      //Rotate sR over S:
      node* sLR = sL -> getR(); //get right child of sL

      p -> setR(sL); //set parent's right as sL
      sL -> setPar(p);

      sL -> setR(s); //set sL's right as the sibling
      s -> setPar(sL);

      s -> setL(sLR); //set sibling's left as sLR
      if (sLR != NULL) {
	sLR -> setPar(s);
      }

      //Recolor:
      s -> setColor('R');
      sL -> setColor('B');
    }

    //Otherwise, move on to the next case:
    else {
      case6(input);
    }
  }

  //By default, just move on the next scenario:
  else {
    case6(input);
  }
  case6(input);
  return;
}

/*
  case4 checks if x's parent is red and it has a black sibling with black children:
 */
void rbtree::case4(node* input) {
  //cout << "entering case 4" << endl;

  //Key players:
  node* p = input -> getPar();
  node* g = p -> getPar();
  node* s;
  if (input == p -> getL()) {
    s = p -> getR();
  }
  else if (input == p -> getR()) {
    s = p -> getL();
  }

  //Sibling should not be null:
  if (s != NULL) {
    node* sL = s -> getL(); //get sibling's children
    node* sR = s -> getR();

    //If the parent is red and the sibling is black with black children:
    if (p -> getColor() == 'R' && s -> getColor() == 'B' && (sL == NULL || sL -> getColor() == 'B') && (sR == NULL || sR -> getColor() == 'B')) {
      //cout << "actually do case 4" << endl;
      p -> setColor('B'); //set the parent to black
      s -> setColor('R'); //set the sibling to red (effectively a swapping of colors)
    }

    //Otherwise, move on to the next case:
    else {
      case5(input);
    }
  }

  //If there is a null sibling, just move on to the next case:
  else {
    case5(input);
  }
  return;
}

/*
  case3 recolors the tree if x's sibling is black with black children:
 */
void rbtree::case3(node* input) { //Sibling is black
  //cout << "entering case 3" << endl;

  //Key players:
  node* p = input -> getPar();
  node* g = p -> getPar();
  node* s;
  if (input == p -> getL()) {
    s = p -> getR();
  }
  else if (input == p -> getR()) {
    s = p -> getL();
  }

  //The sibling should not be null:
  if (s != NULL) {
    node* sL = s -> getL(); //get sibling's children
    node* sR = s -> getR();

    //Reorder if sibling is black with black/null children:
    if (p -> getColor() == 'B' && s -> getColor() == 'B' && (sL == NULL || sL -> getColor() == 'B') && (sR == NULL || sR -> getColor() == 'B')) {
      //cout << "actually do case 3" << endl;

      //Color s red:
      s -> setColor('R');

      //Call case 1 on p:
      case1(p);  
    }
    else {
      case4(input); //else proceed to case 4
    }
  }
  else {
    case4(input); //if sibling is null, just move on
  }
  return;
}

/*
case2 reorders the red black tree if the sibling of doubly black node x is red and has black children:
 */
void rbtree::case2(node* input) {
  //cout << "entering case 2 for " << input -> getData() << endl;

  //Key players:
  node* p = input -> getPar(); //parent
  //cout << "parent" << p -> getData() << endl;
  node* g = p -> getPar(); //grandparent
  node* s; //sibling
  if (input == p -> getL()) {
    s = p -> getR();
  }
  else if (input == p -> getR()) {
    s = p -> getL();
  }
  //cout << "sibling" << s -> getData() << endl;
  //cout << "right child of parent is " << p -> getR() -> getData() << endl;

  //Sibling should not be null for this reordering:
  if (s != NULL) {
    node* sL = s -> getL(); //sibling's left child
    node* sR = s -> getR(); //sibling's right child

    //If sibling is red and has black/null children:
    if (s -> getColor() == 'R' && (sL == NULL||sL -> getColor() == 'B') && (sR == NULL||sR -> getColor() == 'B')) {
      //cout << "actually do case 2" << endl;

      //Rotate s over p:

      //If p is the head, then s must become the new head:
      if (head == p) {
	//cout << "set new head" << endl;
	head = s;
	s -> setPar(NULL);
      }

      //Otherwise, set grandparent's child as the sibling:
      else if (p == g -> getL()) {
	g -> setL(s);
	s -> setPar(g);
      }

      else if (p == g -> getR()) {
	g -> setR(s);
	s -> setPar(g);
      }

      //If the sibling was a right child, set its left child as the parent:
      if (s == p -> getR()) {
	//cout << "sibling was parents right child" << endl;
	s -> setL(p);
	p -> setPar(s);
	//cout << "set s' left as p and p's parent as s" << endl;
	
	p -> setR(sL); //the parent's right child becomes the sibling's left child
	if (sL != NULL) {
	  sL -> setPar(p);
	}
	//cout << "set p right as sL and sL parent as p" << endl;
      }

      //If the sibling was a left child, set its right child as the parent:
      else if (s == p -> getL()) {
	s -> setR(p);
	p -> setPar(s);
	//cout << "set s right as p and p parent as s" << endl; 

	p -> setL(sR); //the parent's left child becomes the sibling's right child
	if (sR != NULL) {
	  sR -> setPar(p);
	}
	//cout << "set p left as sR and sR parent as p" << endl;
      }
      //cout << "printing" << endl;
      //cout << head -> getData() << " " << head -> getL() -> getData() << " "  << head -> getR() -> getData() << endl;

      //Swap s and p's color:
      char color = p -> getColor();
      p -> setColor(s -> getColor());
      s -> setColor(color);
    }

    //Check for more doubly black scenarios (probably just need a call of case3 for any case - for potential future edits):
    if (p == s -> getL()) {
      if (sL != NULL && sL -> getColor() == 'B') {
	case3(input); //check if sL (when moved to parent) is black
      } 
    }

    else if (p == s -> getR()) {
      if (sR != NULL && sR -> getColor() == 'B') {
	case3(input); //check if sR (when moved to parent) is black
      }
    }

    else { //Otherwise, just move on to the next case:
      case3(input);
    }
  }
  
  else { //If sibling is null, just move on:
    case3(input);
  }
  return;
}

/*
This case1 function checks if a doubly black node is the head (if it is the head, don't do anything):
*/
void rbtree::case1(node* input) {
  //cout << "entering case 1" << endl;
  if (head == input) {
    return;
  }
  else {
    //cout << "move on to case 2" << endl;
    case2(input); //moving on to the next case if the node is not the head
  }
  return;
}

//REORDERING FOR INSERTION:

/*
This is the reorder function which calls the two main cases of reordering (red uncle or black uncle): 
*/
void rbtree::reorder(node* input) {

  //The parent must not be black for all rotations and, for all cases, the current node should be red:
  if (input -> getPar() != NULL && input -> getColor() == 'R' && input -> getPar() -> getColor() != 'B') {
    reorder2(input);
    //cout << "did a B-uncle reorder" << endl; (testing)

    //If the uncle is red:
    if (input -> getPar() != NULL && input -> getPar() -> getPar() != NULL) { //just in case, make sure there is a parent and grandparent
      if (input -> getPar() == input -> getPar() -> getPar() -> getL() && input -> getPar() -> getPar() -> getR() -> getColor() == 'R') {
	reorder1(input); //case if uncle is right child of grandparent
    }

      else if (input -> getPar() == input -> getPar() -> getPar() -> getR() && input -> getPar() -> getPar() -> getL() -> getColor() == 'R'){
	reorder1(input); //case if uncle is left child of grandparent
    }
      //cout << "did a R-uncle reorder" << endl; (testing)
  }
  }

  //A check for issues with head:
  if (head == NULL) {
    cout << "note: erasure" << endl;
  }

  //The root must always be set to black:
  if (head -> getColor() == 'R') {
    head -> setColor('B');
  }

  //Another check for issues with head:
  if (head == NULL) {
    cout << "note: woah there. this shouldn't be printed out" << endl;
  }
  return;
}

/*
This reorder1 function recolors the tree when the current node's uncle is red.
*/
void rbtree::reorder1(node* input) {
  //Big Case 1: The Parent's Sibling is Red

  //Quick Check (we want a parent):
  if (input -> getPar() == NULL) {
    return;
  }

  //Quick Check (we want a grandparent):
  if (input -> getPar() -> getPar() == NULL) {
    return;
  }
  
  if (input -> getPar() != NULL && input -> getPar() -> getPar() != NULL) {

    //If the uncle is the grandparent's right child (and it is not null and it is red): 
    if (input -> getPar() == input -> getPar() -> getPar() -> getL()) { 
      if (input -> getPar() -> getPar() -> getR() != NULL && input -> getPar() -> getPar() -> getR() -> getColor() == 'R') {
	//Node is added as red by default! Then change parent and parent's sibling to black and grandparent to red:
	input -> getPar() -> setColor('B');
	input -> getPar() -> getPar() -> getR() -> setColor('B');
	input -> getPar() -> getPar() -> setColor('R');
       
	//Check for more reorderings on the grandparent:
	reorder(input -> getPar() -> getPar());
      }
    }

    //If the uncle is the grandparent's left child (and it is not null and it is red):
    else if (input -> getPar() == input -> getPar() -> getPar() -> getR()) {
      if (input -> getPar() -> getPar() -> getL() != NULL && input -> getPar() -> getPar() -> getR() -> getColor() == 'R') {
	//Same
	input -> getPar() -> setColor('B');
	input -> getPar() -> getPar() -> getL() -> setColor('B');
	input -> getPar() -> getPar() -> setColor('R');
       
	reorder(input -> getPar() -> getPar());
      }      
    }
  }
  return;
}

/*This reorder function calls certain rotations when the current node's uncle is black or null.*/
void rbtree::reorder2(node* input) {
  //Big Case 2: The Parent's Sibling is Black or NULL

  //Quickly check if there is a parent and grandparent:
  if (input -> getPar() != NULL && input -> getPar() -> getPar() != NULL) {
    //cout << "stage 1" << endl; (testing)
    
    //If that is true:
    
    //If the uncle is the right child of the grandparent (and is null or black):
    if (input -> getPar() == input -> getPar() -> getPar() -> getL()) {
      //cout << "par is l" << endl; (testing)
      if (input -> getPar() -> getPar() -> getR() == NULL || input -> getPar() -> getPar() -> getR() -> getColor() == 'B') {
	//cout << "right uncle" << endl; (testing)
	
	if (input == input -> getPar() -> getL()) {
	//Do Left-Left rotation if current node is Left-Left to grandparent (left child of left child):
	  //cout << "calling LL" << endl; (testing)
	  rotLL(input);
	  node* p = input -> getPar();
	  //cout << "step:" << endl; (testing)
	  //print();
	  //cout << p -> getData() << endl;
	  //cout << p -> getColor() << endl;
	  //cout << p -> getPar() -> getData() << endl;
	  reorder(p); //Call more reordering on the parent, just in case
	}
	
	else if (input == input -> getPar() -> getR()) {
	//Do Left-Right rotation if node is Left-Right to grandparent:
	  //cout << "calling LR" << endl; (testing)
	  rotLR(input);
	  //cout << "step:" << endl; (testing)
	  //print();
	  reorder(input); //Call more reordering on the input (current node added), just in case
	}
      }
    }

    //If the uncle is the left child of the grandparent (and is null or black):
    else if (input -> getPar() == input -> getPar() -> getPar() -> getR()) {
      //cout << "par is r" << endl; (testing)
      if (input -> getPar() -> getPar() -> getL() == NULL || input -> getPar() -> getPar() -> getL() -> getColor() == 'B') {
	//cout << "right uncle" << endl; (testing)
	
	if (input == input -> getPar() -> getL()) { 
	//Do RL if node is RL to grandparent:
	  //cout << "calling RL" << endl; (testing)
	  rotRL(input);
	  //cout << "step: " << endl; (testing)
	  //print();
	  reorder(input); //Check for more reordering on input
	}
	
	else if (input == input -> getPar() -> getR()) {
	//Do RR if node is RR to grandparent:
	  //cout << "calling RR" << endl; (testing)
	  rotRR(input);
	  node* p = input -> getPar();
	  //cout << "step:" << endl; (testing)
	  //print();
	  reorder(p); //Check for more reordering on the parent
	}
      }
    }
  }
  return;
}

//ROTATIONS:

/*This rotLL function performs a Left-Left rotation.*/
void rbtree::rotLL(node* input) {

  //Involved nodes:
  node* c = input; //current
  node* cSib = input -> getPar() -> getR(); //current's sibling
  node* cL = input -> getL(); //current's left child
  node* cR = input -> getR(); //current's right child
  node* p = input -> getPar(); //parent
  node* pSib = input -> getPar() -> getPar() -> getR(); //uncle
  node* g = input -> getPar() -> getPar(); //grandparent
  node* gp = g -> getPar(); //grandparent's parent
  
  //Grandparent pntr to Par (its left) = CurSib (right of parent):
  g -> setL(cSib);
  if (cSib != NULL) {
    cSib -> setPar(g);
  }
  
  //Par pntr to CurSib (right pntr) = Grandparent (grandparent becomes parent's child):
  p -> setR(g);

  //If grandparent was the original head:
  if (g -> getPar() == NULL) {
    head = p; //set the new head as the parent
    p -> setPar(NULL);
    g -> setPar(p);
  }

  //If not:
  else { //set the parent as the child of the grandparent's parent
    if (gp -> getL() == g) {
      gp -> setL(p);
    }
    else if (gp -> getR() == g) {
      gp -> setR(p);
    }
    p -> setPar(gp);
    g -> setPar(p);
  }
  
  //Save the color of Par:
  char save = p -> getColor();
  
  //Par takes the Grandparent's color:
  p -> setColor(g -> getColor());
  
  //Grandparent takes the saved (parent's) color:
  g -> setColor(save);

  return;
}

/*
This rotLR function performs a Left-Right rotation. It also calls a LL rotation at the end.
*/
void rbtree::rotLR(node* input) {
  //Same notation as previous function:
  node* c = input;
  node* cSib = input -> getPar() -> getL();
  node* cL = input -> getL();
  node* cR = input -> getR();
  node* p = input -> getPar();
  node* pSib = input -> getPar() -> getPar() -> getR();
  node* g = input -> getPar() -> getPar();
  
  //Grand pntr to Par (its left) = Cur:
  g -> setL(c);
  c -> setPar(g);
  
  //Par pntr to Cur (its right) = CurL:
  p -> setR(cL);
  if (cL != NULL) { //if left child of current is an actual node, set its parent as the parent of the current node (otherwise no avoid doubly linking for seg faults)
    cL -> setPar(p);
    }
  
  //Cur pntr to CurL = Par:
  c -> setL(p);
  p -> setPar(c);

  if (head == g) { //if the head was the grandparent, set the head to the current node
    head = c;
  }
  
  //Perform a LL rotation on the parent:
  rotLL(p);

  return;
}

/*
This rotRR function performs a Right-Right rotation. 
*/
void rbtree::rotRR(node* input) {
  //Same notation as above:
  node* c = input;
  node* cSib = input -> getPar() -> getL();
  node* cL = input -> getL();
  node* cR = input -> getR();
  node* p = input -> getPar();
  node* pSib = input -> getPar() -> getPar() -> getL();
  node* g = input -> getPar() -> getPar();
  node* gp = g -> getPar();
  
  //Grandparent pntr to Par (its right) = CurSib (left of parent):
  g -> setR(cSib);
  if (cSib != NULL) {
    cSib -> setPar(g);
  }
  
  //Par pntr to CurSib (left pntr) = Grandparent:
  p -> setL(g);

  
  //If the grandparent was the original head:
  if (g -> getPar() == NULL) {
    head = p; //set the new head as the parent
    p -> setPar(NULL);
    g -> setPar(p);
  }

  //If not:
  else { //set the parent as the child of the grandparent's parent
    if (gp -> getL() == g) {
      gp -> setL(p);
    }
    else if (gp -> getR() == g) {
      gp -> setR(p);
    }
    p -> setPar(gp);
    g -> setPar(p);
  }
 
  //Save color of Parent:
  char save = p -> getColor();
  
  //Parent takes Grandparent's color:
  p -> setColor(g -> getColor());
  
  //Grandparent takes saved color:
  g -> setColor(save);

  return;
}

/*
This rotRL function performs a Right-Left rotation.
*/
void rbtree::rotRL(node* input) {
  //Same notation as above:
  node* c = input;
  node* cSib = input -> getPar() -> getR();
  //cout << "got csib" << endl; (testing)
  node* cL = input -> getL();
  //cout << "got left ch" << endl;
  node* cR = input -> getR();
  //cout << "got right ch" << endl;
  node* p = input -> getPar();
  //cout << "parent" << endl;
  node* pSib = input -> getPar() -> getPar() -> getL();
  //cout << "got uncle" << endl;
  node* g = input -> getPar() -> getPar();
  //cout << "got grandma" << endl;
  
  //Grand pntr to Par (its right) = Cur:
  g -> setR(c);
  c -> setPar(g);
  //cout << "set g right" << endl; (testing)
 
  //Par pntr to Cur (its left) = CurR:
  p -> setL(cR);
  if (cR != NULL) {
    cR -> setPar(p);
  }
  //cout << "p set left" << endl;
  
  //Cur pntr to CurR = Par:
  c -> setR(p);
  p -> setPar(c);
  //cout << "c set r" << endl;

  //If the head is the grandparent, set the head to the current node:
  if (head == g) {
    head = c;
  }
  
  //Perform RR rotation on Parent:
  //cout << "rotating RR" << endl; (testing)
  rotRR(p);
  //cout << "did the other rotate" << endl;

  return;
}



