#include <iostream>  
#include <fstream>   
#include <cctype>    
#include <string>    

using namespace std;

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define END_OF_FILE -1

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

int charClass;
string lexeme;
char nextChar;
int nextToken;
ifstream in_fp;

// Adds current character to the lexeme
void addChar() {
    lexeme += nextChar;
}

// Reads the next character and classifies it
void getChar() {
    if (in_fp.get(nextChar)) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = END_OF_FILE;
    }
}

// Skips whitespace characters
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

// Looks up operators and parentheses and sets the token
int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    default:
        addChar();
        nextToken = END_OF_FILE;
        break;
    }
    return nextToken;
}

// Lexical analyzer that returns the next token
int lex() {
    lexeme = "";
    getNonBlank();

    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;

    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;

    case END_OF_FILE:
        nextToken = END_OF_FILE;
        lexeme = "EOF";
        break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;

    return nextToken;
}

// Main function: opens file, runs lexer, and closes file
int main() {
    in_fp.open("front.in");

    if (!in_fp) {
        cerr << "ERROR - cannot open front.in" << endl;
        return 1;
    }

    getChar();

    do {
        lex();
    } while (nextToken != END_OF_FILE);

    in_fp.close();
    return 0;
}
