#ifndef _TOKEN_H
#define _TOKEN_H

#include <string>

using namespace std;

typedef struct {
	int tokenLineNumber;
	int tokenType;

	string tokenValue;
} Token;

#endif
