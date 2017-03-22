#ifndef _CHECKER_H
#define _CHECKER_H

#include"enum.h"
#include"treenode.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

typedef struct
{
	string ID; 
	string rename;

	int arrayMax;
	int blockLevel;
	int dataType;
	int entryType;
	int returnType;

	TreeNode* parameterList;
} Symbol;

class Checker
{
	public:
		Checker(); //Constructor
		~Checker(); //Destructor

		int checkForSymbol(string name);
		int getVarType(string name);

		string enumToString(int enumValue);

		vector<Symbol> check(TreeNode* currentNode); //Start checking
		vector<Symbol> getGlobalTable();
		vector<Symbol> getLocalTable();

		void checkNode(TreeNode* currentNode);
		void decreaseBlockLevel();
		void insertSymbolTable(string name, 
			int incomingEntryType, 
			int incomingDataType, 
			TreeNode* parameterList, 
			int incomingArrayMax);
		void increaseBlockLevel();
		void printSymbolTable();

	private:
		int globalBlockLevel;
		int insertOrCheck;

		vector<Symbol> localTable;
		vector<Symbol> globalTable;

		TreeNode* root;
		ofstream symbolTableFile;
};

#endif
