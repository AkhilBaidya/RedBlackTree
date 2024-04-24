#include <iostream>
#include <fstream>
#include <cstring>
#include "rbtree.h"

using namespace std;

void manInp(rbtree*);
void fileInp(rbtree*);

int main() {

  rbtree* tree = new rbtree();

  bool editing = true; //loops the command input process
  char command[15]; //user command

  while (editing) {

    cout << "What would you like to do? ADD to tree? PRINT tree? QUIT?" << endl;
    cin >> command;

    if (!strcmp(command, "ADD")) {
      char answer[10];
      cout << "Would you like to add a node yourself (man) or by a file (file)?" << endl;
      cin >> answer;
      
      if (!strcmp(answer, "man")) {
	manInp(tree);
	cout << "added" << endl;
      }

      else if (!strcmp(answer, "file")) {
	fileInp(tree);
	cout << "added" << endl;
      }

      else {
	cout << "Did not understand what you meant!" << endl;
      }
      
    }

    else if (!strcmp(command, "PRINT")) {
        cout << "Here's the tree:" << endl;
        tree -> print();
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
  cout << "What number would you like to add?" << endl;
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
  return;
}
