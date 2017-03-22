#include "scanner.h"

/* ----------------------- PART 1 --------------------------
 * Title: Scanner and Tokens
 * Description: The Scanner is Part 1 of the Translator. It
 *    will take a file and tokenize it.
 * Input: A C-File (.cm) filename as input from the user.
 * Output: Tokens, printed to the screen.
 * --------------------------------------------------------- */


/* ***************************************************************************
 * Function: Scanner
 * Description: Scanner class constructor
 * Parameters: char* myFile - the name of the file to scan
 * Returns: None
 * *************************************************************************** */

Scanner::Scanner(char* myFile) {
	this->sourceFile.open(myFile);
	ignorePeek = 0;
	lineNumber = 0;
}

/* ***************************************************************************
 * Function: ~Scanner
 * Description: Scanner class destructor
 * Parameters: void
 * Returns: None
 * *************************************************************************** */

Scanner::~Scanner() {
	if(this->sourceFile.is_open()) {
		this->sourceFile.close();
	}
}

/* ***************************************************************************
 * Function: checkSourceFile
 * Description: checks if EOF has been reached
 * Parameters: void
 * Returns: 1 - EOF reached
 * 	0 - EOF not reached
 * *************************************************************************** */

int Scanner::checkSourceFile() {
	if(!sourceFile.eof()){
		return 1;
	}else{
		cout << "End of File" << endl;
		return 0;
	}
}

/* ***************************************************************************
 * Function: checkOverflow
 * Description: checks future tokens in case brackets and parens and semi-colons
 * 	were not preceded by a space.
 * Parameters: char *token - the token to inspect
 * Returns: Token newToken - the newly created token
 * *************************************************************************** */

Token Scanner::checkOverflow(char *token) {
	int i = 0;
	int j = 0;

	char newToken[100];

	if(
		(token[i] == '[') || 
		(token[i] == ']') || 
		(token[i] == '(') ||
	       	(token[i] == ')') || 
		(token[i] == '{') || 
		(token[i] == '}') || 
		(token[i] == ',') || 
		(token[i] == ';')	) {

		strncpy(newToken, token, 1);
		newToken[i+1] = '\0';
		overflow = 1;

		while(token[i+1] != '\0'){
			overflowToken[j] = token[i+1];
			i++;
			j++;
		}

		overflowToken[i] = '\0';

	} else {
		while(
			(token[i] != '[') && (token[i] != ']') && (token[i] != '(') && 
			(token[i] != ')') && (token[i] != '{') && (token[i] != '}') && 
			(token[i] != ',') && (token[i] != ';')				){

			i++;

		}

		strncpy(newToken, token, i);
		newToken[i] = '\0';
		overflow = 1;	
		
		while(token[i] != '\0') {
			overflowToken[j] = token[i];
			i++;
			j++;
		}

		overflowToken[j] = '\0';
	}

	return createNewToken(newToken);
}

/* ***************************************************************************
 * Function: createNewToken
 * Description: creates a new token based on the token parameter
 * Parameters: char* token - the token read from the file
 * Returns: Token newToken - the new token create from the token parameter
 * *************************************************************************** */

Token Scanner::createNewToken(char *token) {
	int i = 0;

	Token newToken;

	if(!strcmp(token, "eof")) {
		newToken.tokenType = _EOF; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "error")) {
		newToken.tokenType = ERROR; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "else")) {
		newToken.tokenType = ELSE; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "if")) {
		newToken.tokenType = IF; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "int")) {
		newToken.tokenType = INT; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;
		
	} else if(!strcmp(token, "return")) {
		newToken.tokenType = RETURN; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;

	} else if(!strcmp(token, "void")) {
		newToken.tokenType = VOID; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "while")) {
		newToken.tokenType = WHILE; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;

	} else if(!strcmp(token, "read")) {
		newToken.tokenType = READ; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;
		
	} else if(!strcmp(token, "write")) {
		newToken.tokenType = WRITE; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;

	} else if(!strcmp(token, "call")) {
		newToken.tokenType = CALL; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;

	} else if(!strcmp(token, "+")) {
		newToken.tokenType = PLUS; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "-")) {
		newToken.tokenType = MINUS; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;

	} else if(!strcmp(token, "*")) {
		newToken.tokenType = MULT; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "/")) {
		newToken.tokenType = DIV; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;

	} else if(!strcmp(token, "<")) {
		newToken.tokenType = LS; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "<=")) {
		newToken.tokenType = LEQ; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;

	} else if(!strcmp(token, ">")) {
		newToken.tokenType = GT; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, ">=")) {
		newToken.tokenType = GEQ; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;

	} else if(!strcmp(token, "==")) {
		newToken.tokenType = EQ; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "!=")) {
		newToken.tokenType = NEQ; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "=")) {
		newToken.tokenType = ASSIGN; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, ";")) {
		newToken.tokenType = SEMI; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, ",")) {
		newToken.tokenType = COMMA; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "(")) {
		newToken.tokenType = LPAREN; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 
		
	} else if(!strcmp(token, ")")) {
		newToken.tokenType = RPAREN; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 		  

	} else if(!strcmp(token, "[")) {
		newToken.tokenType = LBRACKET; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;

	} else if(!strcmp(token, "]")) {
		newToken.tokenType = RBRACKET; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1;

	} else if(!strcmp(token, "{")) {
		newToken.tokenType = LBRACE; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else if(!strcmp(token, "}")) {
		newToken.tokenType = RBRACE; 
		newToken.tokenValue = token; 
		newToken.tokenLineNumber = lineNumber-1; 

	} else {	
		i = 0;

		if(
			(token[i] >= 'A' && token[i] <= 'Z') || 
			(token[i] >= 'a' && token[i] <= 'z')	) {

			while(token[i] != '\0') {
				if(
					(token[i] >= 'A' && token[i] <= 'Z') || 
					(token[i] >= 'a' && token[i] <= 'z')	) {

					i++;

				} else {
					newToken = checkOverflow(token);

					return newToken;
				}
			}

			newToken.tokenType = ID;
			newToken.tokenValue = token;
			newToken.tokenLineNumber = lineNumber-1;

		} else if(token[i] >= '0' && token[i] <= '9') {
			while(token[i] != '\0') {
				if(token[i] >= '0' && token[i] <= '9') {
					i++;
				} else {
					newToken = checkOverflow(token);
					return newToken;
				}
			}

			newToken.tokenType = NUMBER;
			newToken.tokenValue = token;
			newToken.tokenLineNumber = lineNumber-1;

		} else {
			newToken = checkOverflow(token);

			return newToken;
		}
	}

	return newToken;
}

/* ***************************************************************************
 * Function: getToken
 * Description: creates a new token for the token read from the open file
 * Parameters: void
 * Returns: Token newToken - the new token create from the token parameter
 * *************************************************************************** */

Token Scanner::getToken() {
	int i;
	char *token;

	string line;
	Token newToken;

	//check to see if we have a peeked token to create
	if(peeked == 1 && ignorePeek != 1) {
		peeked = 0;
		newToken = peekToken;
	//check to see if we have peeked further token to create
	} else if(peekedFurther == 1 && ignorePeek != 1) {
		peekedFurther = 0;
		newToken = peekFurtherToken;
	//check to see if we have an overflow token to create
	}else if(overflow == 1){
		overflow = 0;
		newToken = createNewToken(overflowToken);
	//create a new token
	} else{
		token = strtok(NULL, " \t\r\a\n");

		while(token == NULL) {
			//check to make sure we haven't reached the end of the file
			if(sourceFile.eof()) {
				//create the END token if we have reached EOF
				newToken.tokenType = END;
				return newToken;
			}

			getline(sourceFile, line);
			lineNumber++;

			strcpy(cline, line.c_str());
			token = strtok(cline, " \t\r\a\n");
		}	

		newToken = createNewToken(token);
	}

	return newToken;
}

/* ***************************************************************************
 * Function: peek
 * Description: creates a token of the next thing in the file
 * Parameters: void
 * Returns: Token newToken - the new token create from the token parameter
 * *************************************************************************** */

Token Scanner::peek() {
	peekToken = getToken();
	peeked = 1;

	return peekToken;
}

/* ***************************************************************************
 * Function: peekFurther
 * Description: creates a new token for the next thing in the file
 * Parameters: void
 * Returns: Token newToken - the new token create from the token parameter
 * *************************************************************************** */

Token Scanner::peekFurther() {
	ignorePeek = 1;

	peekFurtherToken = getToken();

	peekedFurther = 1;
	ignorePeek = 0;

	return peekFurtherToken;
}

