# RedBlackTree
A fun implementation of a Red Black Tree, a self-balancing Binary Tree! I love pointers!

In this program, you will be able to edit a Red Black Tree of numbers (contained in nodes). For this tree, nodes with lesser or equal value to some visited node in the tree are added to that node's left. 

# Running the Program
To run the program, you can compile the files in the manner shown below:
git -o finalProgramName playground.cpp rbtree.cpp node.cpp

Then run:
./finalProgramName

# Interacting with the Program
There are currently five commands you can input (all case-sensitive for now - use all caps): 

1. "ADD"
The program will tell you to add manually or by a file. To add manually write "man" and to add by file write "file."
Adding manually will allow you to input a number one at a time. This must be a number inputted for the program to work.
Adding by file will prompt you for a file name. Use the full name (ex. "num.txt"). This will add all the numbers in the file to the tree. A test file "num.txt" is provided here.

For better visualization, the tree is printed out after each addition.

2. "PRINT"
This prints out the tree sideways.

3. "DELETE"
The program will ask you for a number. Please input a number for this function to work. It will search for that number in the tree and, when first encountering it, will remove it from the tree.

4. "SEARCH" 
Similarly, the program will ask you for a number (please input a number). It will search for that number in the tree and tell you if it is in the tree.

5. "QUIT"
This exits the program.

# Sources
Sources are mentioned at the top comments of each file.
