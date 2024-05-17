#ifndef RBTREE_H
#define RBTREE_H

//C++ Data Structures: Red Black Tree Class Header File - Akhil Baidya
//Submisson Deadline: 5/22/2024

/*
Notes:
The Red Black Tree Class possesses several functions that add to (add), delete from (del), print from (print), search in (search), and manipulate the tree (private functions called after "add"). It also has a constructor and destructor, as a class.

Sources:
Referred to https://www.learncpp.com/cpp-tutorial/header-guards/, a tutorial provided by user "Alex" from the website "Learn C++" for header guard syntax. 
*/

#include <iostream>
#include <cstring>
#include "node.h"

/*Functions will be add, print, delete, and reorder*/

class rbtree {

public:

  //Constructor:
  rbtree();

  //Destructor:
  ~rbtree();

  //Add to Tree:
  void add(int);

  //Print Tree:
  void print();

  //Delete from Tree:
  void del(int);

  //Search in Tree:
  bool search(int);
  
private:
  //Key Data:
  node* head; //the head of the tree

  //Private Functions:

  //Reordering for deletion:
  void case1(node*);
  void case2(node*);
  void case3(node*);
  void case4(node*);
  void case5(node*);
  void case6(node*);
  
  //Reordering for insertion:
  void reorder(node*); //calls the other reorders
  void reorder1(node*); //called if parent's sibling is red
  void reorder2(node*); //called parent's sibling is black or NULL

  //Rotations:
  void rotLL(node*); //a Left-Left rotation (refers to position of current node with respect to grandparent node)
  void rotLR(node*); //a Left-Right rotation
  void rotRL(node*); //a Right-Left rotation
  void rotRR(node*); //a Right-Right rotation

  //Other (for recursive purposes):
  void recPrint(node*, int); //called by the print function to recursively go through tree
};

#endif
