//C++ Data Structures: Red Black Tree Class Definitions - Akhil Baidya
//Submission Date: 5/2/24

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

Additionally, referred to https://www.geeksforgeeks.org/insertion-in-red-black-tree/, the web article by GeeksforGeeks on Red Black Tree insertion. This provided more clarity as to what triggers rotations in a red black tree (a null or black uncle) or a simple recoloring (a red uncle). Additionally, it provided general steps for the rotations and recoloring.
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

/*This is the delete function (work in progress)*/
void rbtree::del(int input){

  //Referred with https://www.programiz.com/dsa/red-black-tree

  //chrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/https://www.cs.purdue.edu/homes/ayg/CS251/slides/chap13c.pdf

  node* current = head;

  while (current != NULL && current -> getData() != input) { //reach spot to delete
    if (current -> getData() < input) {
      current = current -> getR();
      //cout << "current val: " << current -> getData();
    }
    else if (current -> getData() > input) {
      current = current -> getL();
      //cout << "current val (less
    }
  }

  //deletion
  if (current != NULL) {
    cout << "Found thing to delete" << endl;
    node* d = current; //to delete
    node* l = d -> getL();
    node* r = d -> getR();
    //case red leaf:
    if (d -> getColor() == 'R' && d -> getL() == NULL & d -> getR() == NULL) {
      cout << "it's a red leaf case" << endl;
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

    //case just head

    else if (d == head && head -> getL() == NULL && head -> getR() == NULL) {
      cout << "it's the head, just a head case" << endl;
      head = NULL;
      delete d;
    }

    //case if node to be deleted has one child and both are not black
    else if (r == NULL && l != NULL && !(d -> getColor() == 'B' && l -> getColor() == 'B') || l == NULL && r != NULL && !(r -> getColor() == 'B' && d -> getColor() == 'B')) {

      cout << "has a child but not doubly black" << endl;
      node* p = d -> getPar();
      node* c;
      if (l != NULL) {
	c = l;
      }
      else if (r != NULL) {
	c = r;
      }
      cout << "set child" << endl;

      if (d != head) {
	d -> setData(c -> getData());
	d -> setColor('B');
	d -> setL(c -> getL());
	d -> setR(c -> getR());

	cout << "edited"<< endl;
	if (c -> getL() != NULL) {
	  c -> getL() -> setPar(d);
	}
	if (c -> getR() != NULL) {
	  c -> getR() -> setPar(d);
	}
	/*if (c == d -> getL()) {
	  d -> setL(NULL);
	}
	else if (c == d -> getR()) {
	  d -> setR(NULL);
	  }*/
	cout << "removed d's connections" << endl;
	c -> setL(NULL);
	c -> setR(NULL);
	c -> setPar(NULL);
	delete c;
	cout << "deleted c" << endl;
      }
      else if (d == head) {
	head = c;
	d -> setL(NULL);
	d -> setR(NULL);
	c -> setPar(NULL);
	delete d;
	head -> setColor('B');
      }
    }

    //if the node to be deleted has two children
    else if (d -> getL() != NULL && d -> getR() != NULL) {

      cout << "has two children" << endl;
      //find successor

      node* successor = d -> getL();

      while (successor -> getR() != NULL) {
	cout << "need to recurse right" << endl;
	successor = successor -> getR(); //found successor
      }

      if (successor -> getL() != NULL) {
	cout << "successor has something to its left" << endl;
	if (successor == successor -> getPar() -> getR()) {
	successor -> getPar() -> setR(successor -> getL());
	successor -> getL() -> setColor(successor -> getColor());
	successor -> getL() -> setPar(successor -> getPar());
	}
	else if (successor == successor -> getPar() -> getL()) {
	  successor -> getPar() -> setL(successor -> getL());
	successor -> getL() -> setColor(successor -> getColor());
	successor -> getL() -> setPar(successor -> getPar());
	}
	successor -> setPar(NULL);
      }

      else if (successor -> getL() == NULL) {
	cout << "remove successor from end rather than replace" << endl;
	if (successor == successor -> getPar() -> getR()) {
	successor -> getPar() -> setR(NULL);
	successor -> setPar(NULL);
	}
	else if (successor == successor -> getPar() -> getL()) {
	  successor -> getPar() -> setL(NULL);
	  successor -> setPar(NULL);
	}
      }
      successor -> setL(NULL);
      successor -> setR(NULL); //disconnect
      d -> setData(successor -> getData());
      delete successor;
    }

    else if (d -> getColor() == 'B' && l == NULL && r != NULL && r -> getColor() == 'B') {
      cout << "doubly black from right" << endl;
      //if doubly black arises from right

      d -> setData(r -> getData());
      d -> setL(r -> getL());
      d -> setR(r -> getR());
      r -> setPar(NULL);
      r -> setL(NULL);
      r -> setR(NULL);

      delete r;
      case1(d);
      
    }

    else if (d -> getColor() == 'B' && r == NULL && l != NULL && l -> getColor() == 'B') {
      //doubly black from left
      cout << "doubly black from left" << endl;
      d -> setData(l -> getData());
      d -> setL(l -> getL());
      d -> setR(l -> getR());
      l -> setPar(NULL);
      l -> setL(NULL);
      l -> setR(NULL);

      delete l;
      case1(d);
    }

    //case of black leaf
    else if (d -> getL() == NULL && d -> getR() == NULL && d -> getColor() == 'B') {
      cout << "black leaf so reordering then deleting" << endl;
      case1(d); //reorder then delete d

      cout << "reordered, now deleting" << endl;
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
    else {
      cout << "value not found" << endl;
    }
  
  return;
  
  //Standard BST Deletion:
  
  //Case 0a: If the node to be deleted, d, has two children:
  //Go left and recursively go right until not possible. Reach node x
  //Replace d with x's value and delete x.
  //If x had a left child. Set that left child as the child of the parent of x (take x's position and color).

  
  
  //Case 0b: If the node to be deleted has one child and it is not the case that both are black:
  //The child, x, becomes the child of d's parent. And it becomes black.
  //Delete d.

  //Case 0c: If node to be deleted is red and is a leaf. Just delete it.


  //Black-Black Cases: Else (if both d and x are black (including when x is null) and d has one or no children)
  //x becomes child of d's parent. Delete d.

  //Now we still look at x. Get the sibling.

  //Do these cases if x is not the head:
  
  //Case 1:
  //If x's sibling (if x is null refer to the previous parent of d's other child) is black and has at least one red child:

  //a) If sib is left child and at least its left child is red (or both are) - LL rotate its left child
  //b) If sib is left and has a right red child (LR on right child)
  //c) If sib is right child and at least its right child is red (or both are) - RR rotate on right child
  //d) If sib is right child and has a left red child (RL rotate on left child)
  //Do not need to recurse on anything
  
  //Case 2:
  //If x's sibling is black and has no red children:

  //Sibling becomes red.
  //If Parent is already black, call all the case checks on the parent
  //Otherwise make the parent black

  //Case 3:
  //x's sibling is red

  //If sibling is a left child:

  //If sibling is a right child:
  //sibling takes parent's position.
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

void rbtree::case6(node* input) { //RR or LL case of siblings children being red.
  cout << "entering case 6" << endl;
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

  if (s != NULL && s -> getColor() == 'B') {
    node* sL = s -> getL();
    node* sR = s -> getR();

    //LL case
    if (s == p -> getL() && sL != NULL && sL -> getColor() == 'R') {
      //LL rotation on sL
      rotLL(sL);
      sL -> setColor('B');
    }

    //RR case
    else if (s == p -> getR() && sR != NULL && sR -> getColor() == 'R') {
      //RR rotation on SR
      rotRR(sR);
      sR -> setColor('B');
    }
  }
  return;
}

void rbtree::case5(node* input) { //RL or LR case of siblings children being red.
  cout << "entering case 5" << endl;
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
  if (s != NULL && s -> getColor() == 'B') {
    node* sL = s -> getL();
    node* sR = s -> getR();

    //LR case
      if (sL == NULL && sR != NULL && sR -> getColor() == 'R' || sL -> getColor() == 'B' && sR != NULL && sR -> getColor() == 'R') {
	//rotate left over S

	node* sRL = sR -> getL();
	p -> setL(sR);
	sR -> setPar(p);
	
	sR -> setL(s);
	s -> setPar(sR);
	
	s -> setR(sRL);
	if (sRL != NULL) {
	  sRL -> setPar(s);
	}
	s -> setColor('R');
	sR -> setColor('B');
      }
   
      //RL Case
      else if (sR == NULL && sL != NULL && sL -> getColor() == 'R' || sR -> getColor() == 'B' && sL != NULL && sL -> getColor() == 'R') {

	node* sLR = sL -> getR();
	p -> setR(sL);
	sL -> setPar(p);
	
	sL -> setR(s);
	s -> setPar(sL);
	
	s -> setL(sLR);
	if (sLR != NULL) {
	  sLR -> setPar(s);
	}
	s -> setColor('R');
	sL -> setColor('B');
      }

      else {
	case6(input);
      }
    }
  else {
    case6(input);
  }
  return;
}


void rbtree::case4(node* input) { //parent is red and s and s's children are black
  cout << "entering case 4" << endl;
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

  if (s != NULL) {
    node* sL = s -> getL();
    node* sR = s -> getR();

    if (p -> getColor() == 'R' && s -> getColor() == 'B' && sL == NULL && sR == NULL || p -> getColor() == 'R' && s -> getColor() == 'B' && sL -> getColor() == 'B' && sR -> getColor() == 'B') {
      p -> setColor('B');
      s -> setColor('R');
    }
    else {
      case5(input);
    }

  }
  else {
    case5(input);
  }
  return;
}


void rbtree::case3(node* input) { //Sibling is black
  cout << "entering case 3" << endl;
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

  if (s != NULL) {
  node* sL = s -> getL();
  node* sR = s -> getR();

  if (s -> getColor() == 'B') {
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
    case4(input);
  }
  return;
}

void rbtree::case2(node* input) { //the sibling of x is red
  cout << "entering case 2" << endl;
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

  if (s != NULL) {
  node* sL = s -> getL();
  node* sR = s -> getR();

  if (s -> getColor() == 'R') {
    //Rotate s over p:
    if (head == p) {
      head = s;
    }

    else if (p = g -> getL()) {
      g -> setL(s);
      s -> setPar(g);
    }

    else if (p = g -> getR()) {
      g -> setR(s);
      s -> setPar(g);
    }

    if (s = p -> getR()) {
      s -> setL(p);
      p -> setPar(s);

      p -> setR(sL);
      if (sL != NULL) {
	sL -> setPar(p);
      }
    }

    else if (s = p -> getL()) {
      s -> setR(p);
      p -> setPar(s);

      p -> setL(sR);
      if (sR != NULL) {
	sR -> setPar(p);
      }
    }

    //Swap s and p's color:
    char color = p -> getColor();
    p -> setColor(s -> getColor());
    s -> setColor(color);
  }

  if (p = s -> getL()) {
    if (sL != NULL && sL -> getColor() == 'B') {
      case3(input);
    } 
  }

  else if (p = s -> getR()) {
    if (sR != NULL && sR -> getColor() == 'B') {
      case3(input);
    }
  }

  else {
    case3(input);
  }
  
 }
  else {
    case3(input);
  }

  return;
}


void rbtree::case1(node* input) { //don't do anything if double-black is head
  cout << "entering case 1" << endl;
  if (head == input) {
    return;
  }
  else {
    case2(input);
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



