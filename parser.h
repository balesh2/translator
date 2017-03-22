#ifndef _PARSER_H
#define _PARSER_H

#include "enum.h"
#include "scanner.h"
#include "treenode.h"
#include "token.h"

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<time.h>
#include<unistd.h>

class Parser {
	public:
		Parser(char*); //Constructor
		~Parser(); //Destructor
		
		TreeNode* Parse(); //Starts Parser
		void printParseTree(); //Print resulting Parse tree
		void printNode(TreeNode* currentNode); //Prints a node from the parse tree

	private:
	
		TreeNode* root; 
		Scanner* scan;
		ofstream parseTreeFile;
		
		
		TreeNode* argsFunc(Token token);
		TreeNode* argsListFunc(Token token);
		TreeNode* callFunc(Token token);
		TreeNode* callStmtFunc(Token token);
		TreeNode* compareExprFunc(Token token);
		TreeNode* compoundStmtFunc(Token token);
		TreeNode* expressionFunc(Token token); 
		TreeNode* funDeclFunc(Token token);
		TreeNode* gainFunc(Token token);	
		TreeNode* iterStmtFunc(Token token);
		TreeNode* localDeclFunc(Token token);
		TreeNode* localVarDeclFunc(Token token);
		TreeNode* numberFunc(Token token);
		TreeNode* paramFunc(Token token);
		TreeNode* paramsListFunc(Token token);
		TreeNode* programFunc(Token token);
		TreeNode* readStmtFunc(Token token);
		TreeNode* returnStmtFunc(Token token);
		TreeNode* selectStmtFunc(Token token);
		TreeNode* stmtFunc(Token token);
		TreeNode* stmtListFunc(Token token);
		TreeNode* varDeclFunc(Token token);
		TreeNode* varFunc(Token token);
		TreeNode* writeStmtFunc(Token token);
		
		string enumToString(int enumValue);
};

#endif
