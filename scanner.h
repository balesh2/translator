#ifndef _SCANNER_H
#define _SCANNER_H

#include "token.h"
#include "enum.h"

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<time.h>
#include<unistd.h>

using namespace std;

class Scanner
{
	public:
		Scanner(char*);
		~Scanner();
		
		Token createNewToken(char *token);
		Token checkOverflow(char*);
		Token getToken();
		Token peek();
		Token peekFurther();
		int checkSourceFile();	
	private:
		ifstream sourceFile;
		char cline[100];
		int lineNumber;
		int overflow;
		int peeked;
		int peekedFurther;
		int ignorePeek;
		Token peekToken;
		Token peekFurtherToken;
		char overflowToken[100];
};

#endif
