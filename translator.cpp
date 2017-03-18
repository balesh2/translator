#include"token.h"
#include"enum.h"
#include"scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <unistd.h>

using namespace std;

/* ----------------------- PART 2 --------------------------
 * Title: Parser and Syntax Tree
 * Description: The Parser is Part 2 of the Translator. It
 *    will take a program and check the syntax for 
 *    correctness.
 * Input: A C-File (.cm) filename as input from the user.
 * Output: Syntax errors printed to the screen.
 * --------------------------------------------------------- */
/* --------------------- END PART 2 ------------------------ */

int main(int argc, char *argv[]) {
	Scanner* scan;
	char* myFile;
	Token token;
	int count = 0;

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
	scan = new Scanner(myFile);

	//tokenize
	do {
		token = (*scan).getToken();
		count++;
		cout << token.tokenValue << endl;
		cout << "Token Number: " << count << endl;
		cout.flush();
	} while(token.tokenType != END);

	cout << "Done Tokenizing" << endl;


	cout << "Check: done tokenizing" << endl;


	return 0;
}

