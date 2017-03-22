#include "parser.h"

/* ----------------------- PART 2 --------------------------
 * Title: Parser and Syntax Tree
 * Description: The Parser is Part 2 of the Translator. It
 *    will take a program and check the syntax for 
 *    correctness.
 * Input: A C-File (.cm) filename as input from the user.
 * Output: Syntax errors printed to the screen.
 * --------------------------------------------------------- */


Parser::Parser(char* myFile) {
	this->scan = new Scanner(myFile);
}

Parser::~Parser() {
	delete this->scan;
}

TreeNode* Parser::Parse() {
	//cout << "IN Parser::Parse()" << endl;

	//get a token from the scanner
	Token token = scan->getToken();
	//build the tree rooted at the token just received from the scanner
	root = programFunc(token);

	return root;
}


void Parser::printParseTree() {
	parseTreeFile.open("parseTree.txt");	
	parseTreeFile << "Root" << endl;
	printNode(root);
	parseTreeFile.close();

	return;
}

void Parser::printNode(TreeNode* currentNode) {
	parseTreeFile << "Node Type: " << enumToString(currentNode->nodeType) << endl;
	parseTreeFile << "Line Number: " << currentNode->lineNumber << endl;
	parseTreeFile << "Name: " << currentNode->sValue << endl;
	parseTreeFile << "Value: " << currentNode->nValue << endl;
	parseTreeFile << "Data Type: " << enumToString(currentNode->typeSpecifier) << endl;
	parseTreeFile << endl;

	if(currentNode->C1 != nullptr){
		parseTreeFile << "Child 1" << endl;
		printNode(currentNode->C1);
	}

	if(currentNode->C2 != nullptr){
		parseTreeFile << "Child 2" << endl;
		printNode(currentNode->C2);
	}

	if(currentNode->C3 != nullptr){
		parseTreeFile << "Child 3" << endl;
		printNode(currentNode->C3);
	}

	if(currentNode->sibling != nullptr){
		parseTreeFile << "Sibling" << endl;
		printNode(currentNode->sibling);
	}

	return;
}

TreeNode* Parser::argsFunc(Token token) {
	//cout << "IN Parser::argsFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;

	if(token.tokenType == NUMBER){
		newNode->nodeType = NUMBER;
		newNode->nValue = atoi(token.tokenValue.c_str());

		peekToken = scan->peek();

		if(peekToken.tokenType == COMMA){
			newToken = scan->getToken();
			newToken = scan->getToken();
			newNode->sibling = argsFunc(newToken);
		}else if(peekToken.tokenType == RPAREN){
			return newNode;
		}
	}else if(token.tokenType == ID){
		peekToken = scan->peek();
		if(peekToken.tokenType == LBRACKET){
			newNode->nodeType == ARRAY;
			newToken = scan->getToken();
			newToken = scan->getToken();
			//REVISIT
			newNode->C1 = expressionFunc(newToken);
			newToken = scan->getToken();
			if(newToken.tokenType != RBRACKET){
				//ERROR
				cout << "ERROR at line " << newNode->lineNumber << ": Improperly closed array" << endl;
			}
			peekToken = scan->peek();
		}else if(peekToken.tokenType == COMMA){
			newNode->nodeType == VARIABLE;
		}

		if(peekToken.tokenType == COMMA){
			newToken = scan->getToken();
			newToken = scan->getToken();
			newNode->sibling = argsFunc(newToken);
		}else if(peekToken.tokenType == RPAREN){
			return newNode;
		}
	}else{
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Argument error." << endl;
	}

	return newNode;
}

TreeNode* Parser::argsListFunc(Token token) {
	//cout << "IN Parser::argsListFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();

	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = ARGUMENTS;

	newNode->sibling = argsFunc(token);

	return newNode;

}

TreeNode* Parser::callFunc(Token token) {
	//cout << "IN Parser::callFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;
	
	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = CALL;

	newNode->typeSpecifier = VOID; //????

	if(token.tokenType != ID){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Missing Function Call ID." << endl;
	}
	newNode->sValue = token.tokenValue;
	newToken = scan->getToken();
	if(newToken.tokenType != LPAREN){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Function call is missing parens." << endl;
	}
	newToken = scan->getToken();
	newNode->C1 = argsListFunc(newToken);
	newToken = scan->getToken();
	if(newToken.tokenType != RPAREN){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Improperly closed parens" << endl;
	}

	return newNode;
}

TreeNode* Parser::callStmtFunc(Token token) {
	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;
	
	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = CALL;

	newNode->typeSpecifier = VOID; //????

	if(token.tokenType != ID){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Function call is lacking ID" << endl;
	}
	newNode->sValue = token.tokenValue;
	newToken = scan->getToken();
	if(newToken.tokenType != LPAREN){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Function call lacking parenthesis" << endl;
	}
	newToken = scan->getToken();
	newNode->C1 = argsListFunc(newToken);
	newToken = scan->getToken();
	if(newToken.tokenType != RPAREN){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Improperly closed parens" << endl;
	}
	newToken = scan->getToken();
	if(newToken.tokenType != SEMI){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Missing semicolon" << endl;

	}
	peekToken = scan->peek();
	if(peekToken.tokenType == RBRACE){
		return newNode;
	}

	newToken = scan->getToken();
	newNode->sibling = stmtFunc(newToken);

	return newNode;
}

TreeNode* Parser::compareExprFunc(Token token) {
	//cout << "IN Parser::compareExprFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;

	newNode->C1 = expressionFunc(token);
	newToken = scan->getToken();
	newNode->nodeType = newToken.tokenType;
	newToken = scan->getToken();
	newNode->C2 = expressionFunc(newToken);
	return newNode;
}

TreeNode* Parser::compoundStmtFunc(Token token) {
	//cout << "IN Parser::compoundStmtFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;

	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = COMPOUND;

	if(token.tokenType == LBRACE){
		newToken = scan->getToken();
		if(newToken.tokenType == INT || newToken.tokenType == VOID){
			newNode->C1 = localDeclFunc(newToken);
			newToken = scan->getToken();
		}else{
			newNode->C1 = localDeclFunc(newToken);
		}
		newNode->C2 = stmtListFunc(newToken);
	}else{
		//ERROR
		cout << "ERROR a line " << newNode->lineNumber << ": Expected a Left Brace" << endl;
	}
	newToken = scan->getToken();
	if(newToken.tokenType != RBRACE){
		//ERROR
		cout << "ERROR a line " << newNode->lineNumber << ": Expected a Right Brace" << endl;
	}

	return newNode;
}

TreeNode* Parser::expressionFunc(Token token) {

	//cout << "IN Parser::expressionFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;
	TreeNode* tempNode = new TreeNode();

	newNode->lineNumber = token.tokenLineNumber;

	peekToken = scan->peek();
	if(token.tokenType == ID && peekToken.tokenType != LPAREN){
		tempNode = varFunc(token);
	}else if(token.tokenType == ID && peekToken.tokenType == LPAREN){
		tempNode = callFunc(token);
	}else if(token.tokenType == NUMBER){
		tempNode = numberFunc(token);
	}else{
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Expression has neither Variable nor Number" << endl;
	}

	peekToken = scan->peek();

	if((peekToken.tokenType != PLUS) && (peekToken.tokenType != MINUS) && (peekToken.tokenType != MULT) && (peekToken.tokenType != DIV)){
		return tempNode;
	}
	newToken = scan->getToken();
	newNode->C1 = tempNode;

	newNode->nodeType = newToken.tokenType;
	newToken = scan->getToken();
	peekToken = scan->peek();
	if(newToken.tokenType == ID){
		if(peekToken.tokenType != SEMI && peekToken.tokenType != RPAREN && peekToken.tokenType != RBRACE){
			newNode->C2 = expressionFunc(newToken);
		}else{
			newNode->C2 = varFunc(newToken);
		}
	}else if(newToken.tokenType == NUMBER){
		if(peekToken.tokenType != SEMI && peekToken.tokenType != RPAREN && peekToken.tokenType != RBRACE){
			newNode->C2 = expressionFunc(newToken);
		}else{
			newNode->C2 = numberFunc(newToken);
		}
	}
	return newNode;

}

TreeNode* Parser::funDeclFunc(Token token) {
	//cout << "IN Parser::funDeclFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;
	Token peekFurtherToken;

	newNode->lineNumber = token.tokenLineNumber;
	newNode->typeSpecifier = token.tokenType;

	newToken = scan->getToken();

	newNode->sValue = token.tokenValue;

	newToken = scan->getToken();

	if(newToken.tokenType == LPAREN){
		newNode->nodeType = FUNCTION;
		newToken = scan->getToken();
		newNode->C1 = paramsListFunc(newToken);
		newToken = scan->getToken();
		if(newToken.tokenType == RPAREN){
			newToken = scan->getToken();
			newNode->C2 = compoundStmtFunc(newToken);
		}else{
			//ERROR
			cout << "ERROR at line " << newNode->lineNumber << ": Expected Right Paren" << endl;
		}
	}else{
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Expected Left Paren" << endl;
	}

	peekToken = scan->peek();
	if(peekToken.tokenType == END){
		return newNode;
	}else{
		newToken = scan->getToken();
		newNode->sibling = funDeclFunc(token);
	}

	return newNode;
}

TreeNode* Parser::gainFunc(Token token) {
	//cout << "IN Parser::gainFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;
	newNode->C1 = varFunc(token);
	newToken = scan->getToken();

	if(newToken.tokenType != ASSIGN){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Missing assignment character" << endl;
	}

	newNode->nodeType = ASSIGN;

	newToken = scan->getToken();
	
	newNode->C2 = expressionFunc(newToken);
	
	newToken = scan->getToken();
	if(newToken.tokenType != SEMI){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Missing semicolon" << endl;

	}

	peekToken = scan->peek();
	if(peekToken.tokenType == RBRACE){
		return newNode;
	}else{
		newToken = scan->getToken();
		newNode->sibling = stmtFunc(newToken);
	}

	return newNode;
}

TreeNode* Parser::iterStmtFunc(Token token) {
	//cout << "IN Parser::iterStmtFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = STATEMENT;
	newNode->sValue = token.tokenValue;

	if(token.tokenType != WHILE){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Probably won't see this error" << endl;
	}
	newToken = scan->getToken();
	if(newToken.tokenType != LPAREN){
		//ERROR
		cout << "ERROR at line" << newNode->lineNumber << ": WHILE statement, but no parenthesis" << endl;
	}
	newToken = scan->getToken();
	newNode->C1 = compareExprFunc(newToken);
	newToken = scan->getToken();
	if(newToken.tokenType != RPAREN){
		//ERROR
		cout << "ERROR at line" << newNode->lineNumber << ": Parenthesis not properly closed" << endl;
	}
	newToken = scan->getToken();
	newNode->C2 = compoundStmtFunc(newToken);
			
	peekToken = scan->peek();
	if(peekToken.tokenType == RBRACE){
		return newNode;
	}

	newToken = scan->getToken();
	newNode->sibling = stmtFunc(newToken);

	return newNode;
}

TreeNode* Parser::localDeclFunc(Token token) {
	//cout << "IN Parser::localDeclFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = DECLARATION;

	if(token.tokenType == VOID || token.tokenType == INT){
		newNode->sibling = localVarDeclFunc(token);
	}else{
		newNode->sibling = NULL;
	}

	return newNode;

}

TreeNode* Parser::localVarDeclFunc(Token token) {
	//cout << "IN Parser::localVarDeclFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;

	if(token.tokenType == INT || token.tokenType == VOID){
		newNode->typeSpecifier = token.tokenType;
	}else{
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Missing a type specifier" << endl;
	}
	newToken = scan->getToken();
	if(newToken.tokenType != ID){
		//ERROR
		cout << "ERROR a line " << newNode->lineNumber << ": Missing a variable or array name" << endl;
	}
	newNode->sValue = newToken.tokenValue;
	peekToken = scan->peek();
	if(peekToken.tokenType == LBRACKET){
		newNode->nodeType = ARRAY;
		newToken = scan->getToken();
		newToken = scan->getToken();
		if(newToken.tokenType == NUMBER){
			newNode->nValue = atoi(newToken.tokenValue.c_str());
			newToken = scan->getToken();
			if(newToken.tokenType != RBRACKET){
				//ERROR
				cout << "ERROR at line " << newNode->lineNumber << ": Array isn't properly closed" << endl;
			}
		}else if(newToken.tokenType != RBRACKET){
			//ERROR
			cout << "ERROR at line " << newNode->lineNumber << ": Improperly closed array." << endl;
		}
	}
	newToken = scan->getToken();
	if(newToken.tokenType != SEMI){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Missing semicolon" << endl;
	}

	peekToken = scan->peek();
	if(peekToken.tokenType == VOID || peekToken.tokenType == INT){
		newToken = scan->getToken();
		newNode->sibling = localVarDeclFunc(token);
	}

	return newNode;
}

TreeNode* Parser::numberFunc(Token token) {

	//cout << "IN Parser::numberFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;

	newNode->lineNumber = token.tokenLineNumber;
	if(token.tokenType != NUMBER){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": NaN" << endl;
	}
	newNode->nValue = atoi(token.tokenValue.c_str());
	newNode->nodeType = NUMBER;

	return newNode;

}

TreeNode* Parser::paramFunc(Token token) {
	//cout << "IN Parser::paramFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;

	if(token.tokenType == INT || token.tokenType == VOID){
		newNode->typeSpecifier = token.tokenType;
		newToken = scan->getToken();
		newNode->sValue = newToken.tokenValue;
		peekToken = scan->peek();

		if(peekToken.tokenType == LBRACKET){
			newToken = scan->getToken();
			newNode->nodeType = ARRAY;
			newToken = scan->getToken();
			if(newToken.tokenType != RBRACKET){
				//ERROR
				cout << "ERROR at line " << newNode->lineNumber << ": Broken array." << endl;
			}
		}else{
			newNode->nodeType = VARIABLE;
		}
		peekToken = scan->peek();

		if(peekToken.tokenType == COMMA){
			newToken = scan->getToken();
			newToken = scan->getToken();
			newNode->sibling = paramFunc(newToken);
		}else if(peekToken.tokenType == RPAREN){
			return newNode;
		}else{
			//ERROR
			cout << "ERROR at line " << newNode->lineNumber << ": Incorrect parameters" << endl;
		}
	}else{
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Parameter lacks a type specifier" << endl;
	}

	return newNode;
}

TreeNode* Parser::paramsListFunc(Token token) {
	//cout << "IN Parser::paramsListFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();

	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = STATEMENT_LIST;

	if(token.tokenType == VOID || token.tokenType == RPAREN){
		newNode->typeSpecifier = VOID;
	}else if(token.tokenType == INT){
		newNode->sibling = paramFunc(token);
	}else{
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Incorrect parameters." << endl;
	}

	return newNode;
}

TreeNode* Parser::programFunc(Token token) {
	//cout << "IN Parse::programFuc(Token token)" << endl;

	//init variables
	TreeNode* newNode = new TreeNode();
	Token peekToken = scan->peek();
	Token peekFurtherToken = scan->peekFurther();

	//create first node
	newNode->nodeType = 1;
	newNode->nodeType = PROGRAM;

	newNode->lineNumber = token.tokenLineNumber;

	if((token.tokenType == INT || token.tokenType == VOID) && (peekToken.tokenType == ID) && ((peekFurtherToken.tokenType == SEMI) || peekFurtherToken.tokenType == LBRACKET)){
		newNode->sibling = varDeclFunc(token);
	}else if((token.tokenType == INT || token.tokenType == VOID) && (peekToken.tokenType == ID) && (peekFurtherToken.tokenType == LPAREN)){
		newNode->sibling = funDeclFunc(token);
	}


	return newNode;
}

TreeNode* Parser::readStmtFunc(Token token) {
	//cout << "IN Parser::readStmtFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = READ;

	if(token.tokenType != READ){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": You shouldn't see this error" << endl;
	}
	newToken = scan->getToken();
	newNode->C1 = varFunc(newToken);
	newToken = scan->getToken();
	if(newToken.tokenType != SEMI){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Missing semicolon" << endl;
	}

	peekToken = scan->peek();
	if(peekToken.tokenType == RBRACE){
		return newNode;
	}

	newToken = scan->getToken();
	newNode->sibling = stmtFunc(newToken);

	return newNode;
}

TreeNode* Parser::returnStmtFunc(Token token) {
	//cout << "IN Parser::returnStmtFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = RETURN;

	if(token.tokenType != RETURN){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": You shouldn't see this error" << endl;
	}
	newToken = scan->getToken();
	newNode->C1 = expressionFunc(newToken);

	newToken = scan->getToken();
	if(newToken.tokenType != SEMI){
		//ERROR
		cout << "ERROR at line" << newNode->lineNumber << ": Missing semicolon" << endl;
	}

	peekToken = scan->peek();
	if(peekToken.tokenType == RBRACE){
		return newNode;
	}

	newToken = scan->getToken();
	newNode->sibling = stmtFunc(newToken);

	return newNode;
}

TreeNode* Parser::selectStmtFunc(Token token) {
	//cout << "IN Parser::selectStmtFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = STATEMENT;
	newNode->sValue = token.tokenValue;

	if(token.tokenType != IF){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": You probably shouldn't ever get this error" << endl;
	}
	newToken = scan->getToken();
	if(newToken.tokenType != LPAREN){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": IF statement but no Parenthesis" << endl;
	}
	newToken = scan->getToken();
	newNode->C1 = compareExprFunc(newToken);
	newToken = scan->getToken();
	if(newToken.tokenType != RPAREN){
		//ERROR
		cout << "ERROR at line" << newNode->lineNumber << ": IF statement not properly closed" << endl;
	}
	newToken = scan->getToken();
	newNode->C2 = compoundStmtFunc(newToken);
	peekToken = scan->peek();
	if(peekToken.tokenType == ELSE){
		newToken = scan->getToken();
		newToken = scan->getToken();
		newNode->C3 = compoundStmtFunc(newToken);
	}
	
	peekToken = scan->peek();
	if(peekToken.tokenType == RBRACE){
		return newNode;
	}
	
	newToken = scan->getToken();
	newNode->sibling = stmtFunc(newToken);


	return newNode;
}

TreeNode* Parser::stmtFunc(Token token) {
	//cout << "IN Parser::stmtFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	if(token.tokenType == ID){
		peekToken = scan->peek();
		if(peekToken.tokenType == LPAREN){
			return callStmtFunc(token);
		}else if(peekToken.tokenType == ASSIGN || peekToken.tokenType == LBRACKET){
			return gainFunc(token);
		}else{
			//ERROR
			cout << "ERROR at line " << newNode->lineNumber << ": Included ID, but is neither an assignment nor a function call" << endl;
		}
	}else if(token.tokenType == IF){
		return selectStmtFunc(token);
	}else if(token.tokenType == WHILE){
		return iterStmtFunc(token);
	}else if(token.tokenType == RETURN){
		return returnStmtFunc(token);
	}else if(token.tokenType == READ){
		return readStmtFunc(token);
	}else if(token.tokenType == WRITE){
		return writeStmtFunc(token);
	}else if(token.tokenType == CALL){
		return callFunc(token);
	}else if(token.tokenType == LBRACE){
		return compoundStmtFunc(token);
	}else{
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Invalid statement type" << endl;
	}

}

TreeNode* Parser::stmtListFunc(Token token) {
	//cout << "IN Parser::stmtListFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = STATEMENT_LIST;

	if(token.tokenType == ID){
		peekToken = scan->peek();
		if(peekToken.tokenType == LPAREN){
			newNode->sibling = callStmtFunc(token);
		}else if(peekToken.tokenType == ASSIGN || peekToken.tokenType == LBRACKET){
			newNode->sibling = gainFunc(token);
		}else{
			//ERROR
			cout << "ERROR at line " << newNode->lineNumber << ": Included ID, but is neither an assignment nor a function call" << endl;
		}
	}else if(token.tokenType == IF){
		newNode->sibling = selectStmtFunc(token);
	}else if(token.tokenType == WHILE){
		newNode->sibling = iterStmtFunc(token);
	}else if(token.tokenType == RETURN){
		newNode->sibling = returnStmtFunc(token);
	}else if(token.tokenType == READ){
		newNode->sibling = readStmtFunc(token);
	}else if(token.tokenType == WRITE){
		newNode->sibling = writeStmtFunc(token);
	}else if(token.tokenType == CALL){
		newNode->sibling = callFunc(token);
	}else if(token.tokenType == LBRACE){
		newNode->sibling = compoundStmtFunc(token);
	}else{
		//ERROR
		cout << "Line Number " << newNode->lineNumber << ": Invalid statement type" << endl;
	}

	return newNode;

}

TreeNode* Parser::varDeclFunc(Token token) {
	//cout << "IN Parser:varDeclFunc(Token token)" << endl;

	//declare variables
	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;
	Token peekFurtherToken;

	//copy values from token to new node
	newNode->lineNumber = token.tokenLineNumber;
	newNode->typeSpecifier = token.tokenType;

	//get the next token
	newToken = scan->getToken();

	newNode->sValue = token.tokenValue;

	newToken = scan->getToken();

	if(newToken.tokenType == LBRACKET){
		newNode->nodeType = ARRAY;
		newToken = scan->getToken();
		if(newToken.tokenType != NUMBER){
			//ERROR
			cout << "ERROR at line " << newNode->lineNumber << ": " << newToken.tokenValue.c_str() << " is expected to be a number." << endl;
		}
		newNode->nValue = atoi(newToken.tokenValue.c_str());
		newToken = scan->getToken();
		if(newToken.tokenType == RBRACKET){
			newToken = scan->getToken();
			if(newToken.tokenType != SEMI){
				//ERROR
				cout << "ERROR at line " << newNode->lineNumber << ": Missing a semicolon." << endl;
			}
		}else{
			//ERROR
			cout << "ERROR at line " << newNode->lineNumber << ": Expected a {." << endl;
		}
	}else if(newToken.tokenType == SEMI){
		newNode->nodeType = VARIABLE;
	}else{
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Expected { or ;" << endl;
	}

	newToken = scan->getToken();
	if(newToken.tokenType == END){
		return newNode;
	}

	peekToken = scan->peek();
	peekFurtherToken = scan->peekFurther();

	if((token.tokenType == INT || token.tokenType == VOID) && (peekToken.tokenType == ID) && ((peekFurtherToken.tokenType == SEMI) || peekFurtherToken.tokenType == LBRACKET))
		newNode->sibling = varDeclFunc(token);
	else if((token.tokenType == INT || token.tokenType == VOID) && (peekToken.tokenType == ID) && (peekFurtherToken.tokenType == LPAREN))
		newNode->sibling = funDeclFunc(token);

	return newNode;
}

TreeNode* Parser::varFunc(Token token) {
	//cout << "IN Parser::varFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;

	if(token.tokenType != ID){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Variable is not an ID" << endl;
	}
	newNode->sValue = token.tokenValue;
	peekToken = scan->peek();
	if(peekToken.tokenType == LBRACKET)
	{
		newToken = scan->getToken();
		newNode->nodeType = ARRAY;
		newToken = scan->getToken();
		newNode->C1 = expressionFunc(newToken);
		newToken = scan->getToken();
		if(newToken.tokenType != RBRACKET){
			//ERROR
			cout << "ERROR at line " << newNode->lineNumber << ": Improperly closed array." << endl;

		}
	}else{
		newNode->nodeType = VARIABLE;
	}

	return newNode;
}

TreeNode* Parser::writeStmtFunc(Token token) {
	//cout << "IN Parser::writeStmtFunc(Token token)" << endl;

	TreeNode* newNode = new TreeNode();
	Token newToken;
	Token peekToken;

	newNode->lineNumber = token.tokenLineNumber;
	newNode->nodeType = WRITE;

	if(token.tokenType != WRITE){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": You shouldn't see this error" << endl;
	}

	newToken = scan->getToken();
	if(newToken.tokenType != LPAREN){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Missing parenthesis" << endl;
	}

	newToken = scan->getToken();
	peekToken = scan->peek();

	newNode->C1 = expressionFunc(newToken);

	newToken = scan->getToken();
	if(newToken.tokenType != RPAREN){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Parenthesis not closed" << endl;
	}

	newToken = scan->getToken();
	if(newToken.tokenType != SEMI){
		//ERROR
		cout << "ERROR at line " << newNode->lineNumber << ": Missing semicolon" << endl;

	}

	peekToken = scan->peek();
	if(peekToken.tokenType == RBRACE){
		return newNode;
	}

	newToken = scan->getToken();
	newNode->sibling = stmtFunc(newToken);

	return newNode;
}

string Parser::enumToString(int enumValue) {
	string enumString[] = { "NOTHING", "EOF", "ERROR", "ELSE", "IF", "INT", "RETURN",	"VOID",	"WHILE",
				"PLUS", "MINUS", "MULT", "DIV",	"LS", "LEQ", "GT", "GEQ", "EQ", 
				"NEQ", "ASSIGN", "SEMI", "COMMA", "LPAREN", "RPAREN", "LBRACKET", 
				"RBRACKET", "LBRACE", "RBRACE",	"READ", "WRITE", "NUMBER", "ID",
				"PROGRAM", "DECLARATION", "VARIABLE", "ARRAY", "FUNCTION",
				"EXPRESSION", "CALL", "COMPOUND", "TYPE_SPECIFIER",	"PARAMETER_LIST",
				"PARAMETER", "STATEMENT_LIST", "STATEMENT",	"ARGUMENTS", "END" };

	return enumString[enumValue];

}

/* --------------------- END PART 2 ------------------------ */
