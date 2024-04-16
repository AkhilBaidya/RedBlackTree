#ifndef RBTREE_H
#define RBTREE_H

//Header file for rbtree
//Header guards from https://www.learncpp.com/cpp-tutorial/header-guards/
#include <iostream>
#include <cstring>
#include "node.h"

/*Functions will be add, print, delete, and reorder*/

class rbtree {

public:
  rbtree(); //constructor
  ~rbtree(); //destructor

  void add(int);
  void print();
  void del(int);
  
private:
  node* head;
  void reorder1(node*); //parent's sibling is red
  void reorder2(node*); //parent's sibling is black or NULL
  void rotLL(node*); //rotations
  void rotLR(node*);
  void rotRL(node*);
  void rotRR(node*);
  void recPrint(node*, int);
};

#endif
