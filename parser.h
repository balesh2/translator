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
		TreeNode* Parse(); //Start Parser

		Parser(char*);
		~Parser();

		TreeNode* programFunc(Token token); //declListFunc
		TreeNode* varDeclFunc(Token token); //typeSpec ID ; | typeSpec ID [ NUM ] ;
		// typeSpec -> int | void
		TreeNode* funDeclFunc(Token token); //typeSpec ID ( params ) compoundStmt
		TreeNode* paramsListFunc(Token token); //paramListFunc, paramFunc | paramFunc
		TreeNode* paramFunc(Token token); //typeSpec ID | typeSpec ID [ ]
		TreeNode* compoundStmtFunc(Token token); // { localDeclFunc stmtListFunc }
		TreeNode* localDeclFunc(Token token); // localDeclFunc varDeclFunc | empty
		TreeNode* localVarDeclFunc(Token token);
		TreeNode* stmtListFunc(Token token); // stmtListFunc stmtFunc | empty
		TreeNode* stmtFunc(Token token); // expressStmtFunc | compoundStmtFunc | selectStmtFunc | iterStmtFunc | returnStmtFunc
		TreeNode* selectStmtFunc(Token token); //if ( expressionFunc ) stmtFunc | if ( expressionFunc ) stmtFunc else stmtFunc
		TreeNode* iterStmtFunc(Token token); //while ( expressionFunc ) stmtFunc
		TreeNode* returnStmtFunc(Token token); //return ; | return expressionFunc ;
		TreeNode* readStmtFunc(Token token); //READ ID ;
		TreeNode* writeStmtFunc(Token token); //WRITE ID ;
		TreeNode* callStmtFunc(Token token); // ID ( argsFunc ) ;
		TreeNode* callFunc(Token token); // ID ( argsFunc )
		TreeNode* gainFunc(Token token); //varFunc = expressionFunc ;	
		TreeNode* varFunc(Token token); //ID | ID [ expressionFunc ]
		TreeNode* compareExprFunc(Token token); //addExprFunc relop addExprFunc | addExprFunc
		TreeNode* expressionFunc(Token token); 
		TreeNode* numberFunc(Token token);
		// relop -> <= | < | > | >= | == | !=
		// addop -> + | -
		// mulop -> * | /
		TreeNode* argsFunc(Token token); //argsListFunc | empty
		TreeNode* argsListFunc(Token token); //argsListFunc , expressionFunc | expressionFunc

		TreeNode* root; 

		Scanner* scan;

};

#endif
