#ifndef _SCANNER_H
#define _SCANNER_H

#include"enum.h"
#include"token.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <unistd.h>

using namespace std;

class Scanner {
	public:
		Scanner(char*);
		~Scanner();
		
		int checkSourceFile();	

		Token checkOverflow(char*);
		Token createNewToken(char *token);
		Token getToken();
		Token peek();
		Token peekFurther();
	private:
		ifstream sourceFile;

		char cline[100];
		char overflowToken[100];

		int ignorePeek;
		int lineNumber;
		int overflow;
		int peeked;
		int peekedFurther;

		Token peekFurtherToken;
		Token peekToken;
};

#endif
