#include"enum.h"
#include"token.h"
#include"treenode.h"
#include"scanner.h"
#include"parser.h"
#include"checker.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <unistd.h>

using namespace std;

/* ***************************************************************************
 * Function: main
 * Description: runs the translator on the file given as argv[1]
 * Parameters: int argc - the number of arguments in argv - requires argc = 2
 * 	char *argv[] - the input parameters - requires argv[1] be a file name
 * Returns: 0 - finish with no error
 * 	1 - finish with error
 * *************************************************************************** */

int main(int argc, char *argv[]) {
	char* myFile;
	TreeNode* root;

	//check command line args
	//require two arguments
	if(argc > 2) {
		cout << "ERROR: Too many command line arguments entered." << endl;
		return -1;
	} else if(argc == 1) {
		cout << "ERROR: Please enter a file to parse as a command line argument when running the file." << endl;
		return -1;
	} else if(argc == 2) {
		//get the filename given as the second argument
		myFile = argv[1];
		//Tell the user which file will be opened
		cout << "Opening file: " << myFile << endl;
	}

	//init parser and checker
	//note: parser inits scanner
	Parser* parse = new Parser(myFile);
	Checker* check = new Checker();

	//parse
	root = parse->Parse();
	cout << "Parsed." << endl;


	//check
	check->check(root);
	cout << "Checked." << endl;

	//print parse tree
	parse->printParseTree();
	cout << "Parse Tree Printed to parseTree.txt." << endl;

	//print symbol table
	check->printSymbolTable();
	cout << "Symbol Table Printed to symbolTable.txt." << endl;

	return 0;
}

