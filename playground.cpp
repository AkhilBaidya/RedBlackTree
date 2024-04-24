#include <iostream>
#include <fstream>
#include <cstring>
#include "rbtree.h"

using namespace std;

void manInp(rbtree*);
void fileInp(rbtree*);

int main() {

  //Code from previous version of rbtree.cpp (just copied it over and will edit it)
  rbtree* tree = new rbtree();

  bool editing = true; //loops the command input process
  char command[15]; //user command

  while (editing) {

    cout << "What would you like to do? ADD to tree? PRINT tree? QUIT?" << endl;
    cin >> command;

    if (!strcmp(command, "ADD")) {
    }

    else if (!strcmp(command, "PRINT")) {
      //if (head == NULL) {
      //cout << "There is no tree ~ <3" << endl
      //}

      //else {
        cout << "Here's the tree:" << endl;
        tree -> print();
	//}
    }

    else if (!strcmp(command, "QUIT")) {
      editing = false;
      cout << "Quitting..." << endl;
    }

    else {
      cout << "Didn't understand that." << endl;
      cout << "_          _" << endl;
      cout << " |_(0_0)?_|" << endl;
    }
  }
  return 0;
}

void manInp(rbtree* tree) {
  int toAdd;
  cin >> toAdd;
  tree -> add(toAdd);
  return;
}

void fileInp(rbtree* tree) {
  char fileN[20];
  int toAdd;
  cout << "What is the name of the file you wish to input? " << endl;
  cin >> fileN;
  
  ifstream file(fileN);
  while (file >> toAdd) {
    tree -> add(toAdd);
  }
}
