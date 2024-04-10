#include <iostream>
#include <cstring>
#include "rbtree.h"

using namespace std;

int main() {

  //Code from previous version of rbtree.cpp (just copied it over and will edit it)
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

  return 0;
}
