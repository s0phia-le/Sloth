#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdbool.h>

typedef enum {
    IDENTIFIER, // variable or function names
    NUMBER,     // numberic constants
    STRING,     // string literals
    KEYWORD,    // keywords
    OPERATOR,   // operators
    SEPARATOR,  // punctuation
    END,        // end of file
    INVALID     // invalid token
} TokenType;

typedef struct {
    TokenType type; // type of the token
    char * token;   // actual text of the token
    int line;       // line number where token was found
    int column;     // column number for error reporting
} Token;

typedef struct {
    FILE * input;       // input file
    int current_line;   // current line in the input file
    int current_column; // current column in the input file
    char current_char;  // current character being processed
    bool end_of_file;   // end of file indicator
} Lexer;

Lexer * init(const char * filename);
void destroy_lexer(Lexer * lexer);
Token * get_next(Lexer * lexer);
void destroy_token(Token * token);

bool is_whitespace(char c);
bool is_digit(char c);
bool is_letter(char c);
bool is_operator(char c);
bool is_keyword(const char * token);

#endif // LEXER_H