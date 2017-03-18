#ifndef _TOKEN_H
#define _TOKEN_H

#include<string>

using namespace std;

typedef struct
{
	int tokenType;
	string tokenValue;
	int tokenLineNumber;
} Token;

#endif
