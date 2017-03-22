#include"checker.h"

/* ----------------------- PART 3 --------------------------
 * Title: Checker and Symbols Table
 * Description: The Checker is part 3 of the translator. It
 * 	takes the root of the parse tree and traverses it 
 * 	one or more times to construct the symbols table.
 * Input: A C-File (.cm) filename as input from the user.
 * Output: Syntax errors printed to the screen.
 * --------------------------------------------------------- */


/* ***************************************************************************
 * Function: Checker
 * Description: Checker class constructor
 * Parameters: void
 * Returns: None
 * *************************************************************************** */

Checker::Checker() {

}

/* ***************************************************************************
 * Function: ~Checker
 * Description: Checker class destructor
 * Parameters: void
 * Returns: None
 * *************************************************************************** */

Checker::~Checker() {

}

/* ***************************************************************************
 * Function: checkForSymbol
 * Description: checks for a symbol within the local table with an ID matching
 * 	the name given as a parameter.
 * Parameters: string name - name of the symbol to find.
 * Returns: 1 if the symbol is found; else 0.
 * *************************************************************************** */

int Checker::checkForSymbol(string name) {
	for(int i=0; i<localTable.size(); i++) {
		if(localTable[i].ID == name) {
			return 1;
		}
	}

	return 0;
}

/* ***************************************************************************
 * Function: getVarType
 * Description: finds the type of the variable within the local table with an 
 * 	ID matching the input string name.
 * Parameters: string name - name of the variable to find.
 * Returns: The type of the variable
 * *************************************************************************** */

int Checker::getVarType(string name) {
	for(int i=0; i<localTable.size(); i++) {
		if(localTable[i].ID == name) {
			if(localTable[i].entryType == FUNCTION) {
				return localTable[i].returnType;
			} else {
				return localTable[i].dataType;
			}
		}
	}

	return 0;
}

/* ***************************************************************************
 * Function: enumToString
 * Description: pulls the string corresponding to the parameter enumValue from 
 * 	the list of enum strings, enumString.
 * Parameters: int enumValue - the value to convert to string
 * Returns: The string corresponding to the given enum value
 * *************************************************************************** */

string Checker::enumToString(int enumValue) {
	string enumString[] = { "NOTHING", "EOF", "ERROR", "ELSE", "IF", "INT", "RETURN", "VOID",	"WHILE",
				"PLUS", "MINUS", "MULT", "DIV",	"LS", "LEQ", "GT", "GEQ", "EQ", 
				"NEQ", "ASSIGN", "SEMI", "COMMA", "LPAREN", "RPAREN", "LBRACKET", 
				"RBRACKET", "LBRACE", "RBRACE",	"READ", "WRITE", "NUMBER", "ID",
				"PROGRAM", "DECLARATION", "VARIABLE", "ARRAY", "FUNCTION",
				"EXPRESSION", "CALL", "COMPOUND", "TYPE_SPECIFIER", "PARAMETER_LIST",
				"PARAMETER", "STATEMENT_LIST", "STATEMENT", "ARGUMENTS", "END" };

	return enumString[enumValue];
}

/* ***************************************************************************
 * Function: check
 * Description: checks the node currentNode and returns the resulting globalTable
 * Parameters: TreeNode* currentNode - the node to check
 * Returns: globalTable - the globalTable constructed after checking currentNode
 * *************************************************************************** */

vector<Symbol> Checker::check(TreeNode* currentNode) {
	checkNode(currentNode);

	return globalTable;
}

/* ***************************************************************************
 * Function: getGlobalTable
 * Description: globalTable accessor
 * Parameters: void
 * Returns: globalTable - the globalTable
 * *************************************************************************** */

vector<Symbol> Checker::getGlobalTable() {
	return globalTable;
}

/* ***************************************************************************
 * Function: getLocalTable
 * Description: localTable accessor
 * Parameters: void
 * Returns: localTable - the localTable
 * *************************************************************************** */

vector<Symbol> Checker::getLocalTable() {
	return localTable;
}

/* ***************************************************************************
 * Function: checkNode
 * Description: checks the node currentNode
 * Parameters: TreeNode* currentNode - the node to check
 * Returns: void
 * *************************************************************************** */

void Checker::checkNode(TreeNode* currentNode) {
	Symbol newSymbol;
	int blockLevelUp = 0;
	int checkResult;

	if(currentNode->typeSpecifier == INT || currentNode->typeSpecifier == VOID){
		if(currentNode->nodeType == VARIABLE || currentNode->nodeType == ARRAY){
			insertSymbolTable(currentNode->sValue, currentNode->nodeType, currentNode->typeSpecifier, NULL, currentNode->nValue);
		}else if(currentNode->nodeType == FUNCTION){
			insertSymbolTable(currentNode->sValue, currentNode->nodeType, currentNode->typeSpecifier, currentNode->C1, currentNode->nValue);
		}
	}else if(currentNode->nodeType == VARIABLE || currentNode->nodeType == ARRAY){
		checkResult = checkForSymbol(currentNode->sValue);
		if(checkResult == 0){
			cout << "Variable used has not been declared" << endl;
		}else{
			currentNode->typeSpecifier = getVarType(currentNode->sValue);
		}	
	}

	if(currentNode->nodeType == STATEMENT || currentNode->nodeType == FUNCTION)
	{
		blockLevelUp = 1;
		increaseBlockLevel();
	}

	if(currentNode->C1 != nullptr){
		checkNode(currentNode->C1);
	}

	if(currentNode->C2 != nullptr){
		checkNode(currentNode->C2);
	}

	if(currentNode->C3 != nullptr){
		checkNode(currentNode->C3);
	}

	if(blockLevelUp == 1){
		decreaseBlockLevel();
	}

	if(currentNode->sibling != nullptr){
		checkNode(currentNode->sibling);
	}

}

/* ***************************************************************************
 * Function: decreaseBlockLevel
 * Description: decreases the global and local block levels
 * Parameters: void
 * Returns: void
 * *************************************************************************** */

void Checker::decreaseBlockLevel() {
	while(localTable.back().blockLevel == globalBlockLevel) {
		localTable.pop_back();
	}

	globalBlockLevel--;
	
	return;
}

/* ***************************************************************************
 * Function: insertSymbolTable
 * Description: inserts a symbol into the symbols table
 * Parameters: string name - the symbol's name
 * 	int incomingEntryType - the symbol's type
 * 	int incomingDataType - the symbol's data type
 * 	TreeNode* parameterList - a list of the parameters
 * 	int incomingArrayMax - the end of the array
 * Returns: void
 * *************************************************************************** */

void Checker::insertSymbolTable(string name, int incomingEntryType, int incomingDataType, TreeNode* parameterList, int incomingArrayMax) {
	Symbol newSymbol;

	newSymbol.ID = name;
	newSymbol.entryType = incomingEntryType;

	if(incomingEntryType == VARIABLE) {
		newSymbol.arrayMax = 0;
		newSymbol.dataType = incomingDataType;
		newSymbol.returnType = 0;
	} else if(incomingEntryType == ARRAY) {
		newSymbol.arrayMax = incomingArrayMax;
		newSymbol.dataType = incomingDataType;
		newSymbol.returnType = 0;
	} else if(incomingEntryType == FUNCTION) {
		newSymbol.arrayMax = 0;
		newSymbol.dataType = 0;
		newSymbol.returnType = incomingDataType;
	} else {
		cout << "Something is wrong with the Symbol " << newSymbol.ID << " with Type " << newSymbol.entryType << " \nInvalid Type" << endl;
	}

	newSymbol.blockLevel = globalBlockLevel;

	if(checkForSymbol(newSymbol.ID)){
		cout << "The Symbol " << newSymbol.ID << " has already been declared" << endl;
	}

	globalTable.push_back(newSymbol);
	localTable.push_back(newSymbol);

	return;
}

/* ***************************************************************************
 * Function: increaseBlockLevel
 * Description: increases the global block level by one
 * Parameters: void
 * Returns: void
 * *************************************************************************** */

void Checker::increaseBlockLevel() {
	globalBlockLevel++;
	return;
}

/* ***************************************************************************
 * Function: printSymbolTable
 * Description: prints the Symbol table to symbolTable.txt
 * Parameters: void
 * Returns: void
 * *************************************************************************** */

void Checker::printSymbolTable() {
	symbolTableFile.open("symbolTable.txt");

	symbolTableFile << "ID blockLevel entryType dataType returnType arrayMax" << endl;

	for(int i = 0; i < globalTable.size(); i++){
		symbolTableFile << globalTable[i].ID << " ";
		symbolTableFile << globalTable[i].blockLevel << " ";
		symbolTableFile << enumToString(globalTable[i].entryType)<< " ";
		symbolTableFile << enumToString(globalTable[i].dataType) << " ";
		symbolTableFile << enumToString(globalTable[i].returnType) << " ";
		symbolTableFile << globalTable[i].arrayMax << " ";
		symbolTableFile << endl;
	}

	return;
}

/* --------------------- END PART 3 ------------------------ */

