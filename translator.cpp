#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

/* ----------------------- PART 1 --------------------------
 * Title: Scanner and Tokens
 * Description: The Scanner is Part 1 of the Translator. It
 *    will take a file and tokenize it.
 * Input: A C-File (.cm) filename as input from the user.
 * Output: Tokens, printed to the screen.
 * --------------------------------------------------------- */

class Scanner {
	public:
		int openFile(char *myFile);
		char* getToken();
		int checkSourceFile();	
	private:
		ifstream sourceFile;
		char cline[100];
};

int Scanner::openFile(char *myFile) {
	//open the source file
	sourceFile.open(myFile);

	//check that the file was opened
	//and print success or error message
	if(sourceFile.is_open()) {
		cout << "File Opened Successfully." << endl;
		return 0;
	} else {
		cout << "Error Opening File." << endl;
		return -1;
	}
}

char* Scanner::getToken() {
	string line;
	char* token;

	token = strtok(NULL, " \t\r\a\n");

	if(token != NULL) {
		return token;
	} else {
		//get the next line from the file
		getline(sourceFile, line);
		//reformat the line to cstring
		strcpy(cline, line.c_str());
		//tokenize the line on whitespace
		token = strtok(cline, " \t\r\a\n");
		//return the tokens
		return token;
	}
}

int Scanner::checkSourceFile() {
	if(sourceFile.eof()) {
		return 1;
	} else {
		return 0;
	}
}

/* --------------------- END PART 1 ------------------------ */

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

	Scanner scan;
	char* myFile;
	char* token;
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

	//print out the file entered
	//cout << myFile << endl;

	//open the file. quit if it didn't work
	if(scan.openFile(myFile) == -1) {
		return -1;
	}

	//keep tokenizing until eof
	while(!(scan.checkSourceFile())) {
		//count++;
		//cout << "Token " << count << endl;
		token = scan.getToken();
		cout << token << endl;
	} 

	cout << "Check: done tokenizing" << endl;


	return 0;
}

