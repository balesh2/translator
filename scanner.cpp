#include "scanner.h"

/* ----------------------- PART 1 --------------------------
 * Title: Scanner and Tokens
 * Description: The Scanner is Part 1 of the Translator. It
 *    will take a file and tokenize it.
 * Input: A C-File (.cm) filename as input from the user.
 * Output: Tokens, printed to the screen.
 * --------------------------------------------------------- */


//Constructor
Scanner::Scanner(char* myFile) {
	this->sourceFile.open(myFile);
	ignorePeek = 0;
	lineNumber = 0;
}

//Destructor
Scanner::~Scanner() {
	if(this->sourceFile.is_open()) {
		this->sourceFile.close();
	}
}

//Check for brackets and parens that should be in a seperate token
Token Scanner::checkOverflow(char *token) {
	char newToken[100];
	int i = 0;
	int j = 0;

	if((token[i] == '[') || (token[i] == ']') || (token[i] == '(') || (token[i] == ')') || (token[i] == '{') || (token[i] == '}') || (token[i] == ',') || (token[i] == ';')){
		strncpy(newToken, token, 1);
		newToken[i+1] = '\0';
		overflow = 1;
		while(token[i+1] != '\0'){
			overflowToken[j] = token[i+1];
			i++;
			j++;
		}
		overflowToken[i] = '\0';

	}else{
		while((token[i] != '[') && (token[i] != ']') && (token[i] != '(') && (token[i] != ')') && (token[i] != '{') && (token[i] != '}') && (token[i] != ',') && (token[i] != ';')){
			i++;
		}
		strncpy(newToken, token, i);
		newToken[i] = '\0';
		
		overflow = 1;	
		while(token[i] != '\0'){
			overflowToken[j] = token[i];
			i++;
			j++;
		}
		overflowToken[j] = '\0';
	}

	return createNewToken(newToken);
}

//Create each type of token
Token Scanner::createNewToken(char *token)
{
	Token newToken;
	int i = 0;

	if(!strcmp(token, "eof")){
		newToken.tokenType = _EOF; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "error")){
		newToken.tokenType = ERROR; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "else")){
		newToken.tokenType = ELSE; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "if")){
		newToken.tokenType = IF; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "int")){
		newToken.tokenType = INT; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "return")){
		newToken.tokenType = RETURN; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "void")){
		newToken.tokenType = VOID; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "while")){
		newToken.tokenType = WHILE; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "read")){
		newToken.tokenType = READ; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "write")){
		newToken.tokenType = WRITE; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "call")){
		newToken.tokenType = CALL; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "+")){
		newToken.tokenType = PLUS; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "-")){
		newToken.tokenType = MINUS; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "*")){
		newToken.tokenType = MULT; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "/")){
		newToken.tokenType = DIV; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "<")){
		newToken.tokenType = LS; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "<=")){
		newToken.tokenType = LEQ; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, ">")){
		newToken.tokenType = GT; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, ">=")){
		newToken.tokenType = GEQ; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "==")){
		newToken.tokenType = EQ; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "!=")){
		newToken.tokenType = NEQ; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "=")){
		newToken.tokenType = ASSIGN; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, ";")){
		newToken.tokenType = SEMI; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, ",")){
		newToken.tokenType = COMMA; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "(")){
		newToken.tokenType = LPAREN; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, ")")){
		newToken.tokenType = RPAREN; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 		  
	}else if(!strcmp(token, "[")){
		newToken.tokenType = LBRACKET; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "]")){
		newToken.tokenType = RBRACKET; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1;
	}else if(!strcmp(token, "{")){
		newToken.tokenType = LBRACE; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else if(!strcmp(token, "}")){
		newToken.tokenType = RBRACE; newToken.tokenValue = token; newToken.tokenLineNumber = lineNumber-1; 
	}else{	
		i = 0;
		if((token[i] >= 'A' && token[i] <= 'Z') || (token[i] >= 'a' && token[i] <= 'z')){
			while(token[i] != '\0'){
				if((token[i] >= 'A' && token[i] <= 'Z') || (token[i] >= 'a' && token[i] <= 'z')){
					i++;
				}else{
					newToken = checkOverflow(token);
					return newToken;
				}
			}
			newToken.tokenType = ID;
			newToken.tokenValue = token;
			newToken.tokenLineNumber = lineNumber-1;
		}else if(token[i] >= '0' && token[i] <= '9'){
			while(token[i] != '\0'){
				if(token[i] >= '0' && token[i] <= '9'){
					i++;
				}else{
					newToken = checkOverflow(token);
					return newToken;
				}
			}
			newToken.tokenType = NUMBER;
			newToken.tokenValue = token;
			newToken.tokenLineNumber = lineNumber-1;
		}else{
			newToken = checkOverflow(token);
			return newToken;
		}
	}

	return newToken;
}

Token Scanner::getToken() {
	string line;
	char *token;
	Token newToken;
	int i;

	if(peeked == 1 && ignorePeek != 1) {
		peeked = 0;
		newToken = peekToken;
	} else if(peekedFurther == 1 && ignorePeek != 1) {
		peekedFurther = 0;
		newToken = peekFurtherToken;
	}else if(overflow == 1){
		overflow = 0;
		newToken = createNewToken(overflowToken);
	} else{
		token = strtok(NULL, " \t\r\a\n");
		while(token == NULL) {
			if(sourceFile.eof()) {
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

Token Scanner::peek() {
	peekToken = getToken();
	peeked = 1;

	return peekToken;
}

Token Scanner::peekFurther() {
	ignorePeek = 1;
	peekFurtherToken = getToken();
	peekedFurther = 1;
	ignorePeek = 0;

	return peekFurtherToken;
}

int Scanner::checkSourceFile() {
	if(!sourceFile.eof()){
		return 1;
	}else{
		cout << "End of File" << endl;
		return 0;
	}
}

