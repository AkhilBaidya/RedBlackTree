#ifndef NODE_H
#define NODE_H

//C++ Data Structures: Node Class Header File - Akhil Baidya
//Submission Deadline: 5/2/2024

/*
Notes: 
The Node Class will have a pointer to its parent and to its left and right children. It will also contain integer data and a color.
There will be get and set functions for all of these values, as well as a constructor and destructor.

Sources:
Referred to https://www.learncpp.com/cpp-tutorial/header-guards/, a tutorial provided by user "Alex" from the website "Learn C++" for header guard syntax (since node.h will be called multiple times, this helps prevent redefinition).
*/


#include <iostream>
#include <cstring>

using namespace std;

class node {

 public:

  //Constructors:
  node();
  node(int);

  //Destructor:
  ~node();

  //Set functions:
  void setPar(node*);
  void setL(node*);
  void setR(node*);
  void setData(int);
  void setColor(char);

  //Get functions:
  node* getPar();
  node* getL();
  node* getR();
  int getData();
  char getColor();
  
 private:
  //Values:
  node* parent;
  node* left;
  node* right;
  int data;
  char color;
};

#endif
