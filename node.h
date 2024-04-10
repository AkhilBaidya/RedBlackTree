#ifndef NODE_H
#define NODE_H

//C++ Data Structures: Node Class Header File - Akhil Baidya
//Submission Deadline: 3/22/2024
/*
Notes: The Node Class will have a pointer to its parent and to its left and right children. It will also contain integer data and a color. 
There will be get and set functions for all of these values, on top of a constructor and destructor.
Header guards from https://www.learncpp.com/cpp-tutorial/header-guards/
*/


#include <iostream>
#include <cstring>

using namespace std;

class node {

 public:

  //constructors:
  node();
  node(int);

  //destructor:
  ~node();

  //set functions:
  void setPar(node*);
  void setL(node*);
  void setR(node*);
  void setData(int);
  void setColor(char);

  //get functions:
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
