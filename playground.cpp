//C++ Data Structures: Playground for Red Black Tree (how the user interacts with the tree) - Akhil Baidya
//Submission Date: 5/2/2024

/*
Notes: In this program, the user will be able to interact with a Red Black Tree. They can add to the tree (manually or through a file), delete from it, print from it, or quit the program. See README file for instructions. 
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include "rbtree.h"

using namespace std;

//Function Prototypes:
void manInp(rbtree*); //manual input
void fileInp(rbtree*); //file input

//Main function: The user inputs commands here to edit the red black tree
int main() {
  rbtree* tree = new rbtree(); //create a red black tree

  bool editing = true; //loops the command input process
  char command[15]; //stores the user command
  
  while (editing) {
    cout << "What would you like to do? ADD to tree? PRINT tree? QUIT?" << endl;
    cin >> command;

    //Adding to the tree:
    if (!strcmp(command, "ADD")) {
      char answer[10];
      cout << "Would you like to add a node yourself (man) or by a file (file)?" << endl;
      cin >> answer;

      //Manual input:
      if (!strcmp(answer, "man")) {
	manInp(tree);
	cout << "added" << endl;
      }

      //File input:
      else if (!strcmp(answer, "file")) {
	fileInp(tree);
	cout << "added" << endl;
      }

      else {
	cout << "Did not understand what you meant!" << endl;
      }
      
    }

    //Printing from the tree:
    else if (!strcmp(command, "PRINT")) {
        cout << "Here's the tree:" << endl;
        tree -> print();
    }

    //Quitting program:
    else if (!strcmp(command, "QUIT")) {
      editing = false; //end loop
      cout << "Quitting..." << endl;
    }

    //Nonsensical input response:
    else {
      cout << "Didn't understand that." << endl;
      cout << "_          _" << endl;
      cout << " |_(0_0)?_|" << endl;
    }
  }
  return 0;
}

//This manInp function adds values, inputted by the user, one at a time to the tree:
void manInp(rbtree* tree) {
  int toAdd;
  cout << "What number would you like to add?" << endl;
  cin >> toAdd;
  tree -> add(toAdd); //add input
  return;
}

//This fileInp function takes a file and adds all of its data to the tree:
void fileInp(rbtree* tree) {
  char fileN[20];
  int toAdd;
  cout << "What is the name of the file you wish to input? " << endl;
  cin >> fileN;
  
  ifstream file(fileN); //get file

  //In a loop, continously add elements in file to the tree:
  while (file >> toAdd) {
    tree -> add(toAdd);
  }
  return;
}
