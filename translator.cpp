#include"token.h"
#include"enum.h"
#include"treenode.h"
#include"scanner.h"
#include"parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
	Scanner* scan;
	char* myFile;
	Token token;
	int count = 0;
	TreeNode* root;

	//check command line args
	if(argc > 2) {
		cout << "ERROR: Too many command line arguments entered." << endl;
		return -1;
	} else if(argc == 1) {
		cout << "ERROR: Please enter a file to parse as a command line argument when running the file." << endl;
		return -1;
	} else if(argc == 2) {
		myFile = argv[1];
		cout << "Opening file: " << myFile << endl;
	}

	//init the scanner and open the file
	Parser* parse = new Parser(myFile);

	//Run the parse Function
	root = parse->Parse();
	cout << "End of File" << endl;


	parse->printParseTree();

	return 0;
}

