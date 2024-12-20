/**
 * This file contains the implementation of the lexical analyzer (lexer) which
 * processes an input file and generates tokens representing meaningful units
 * (e.g., keywords, identifiers, operators, numbers, etc.). The lexer returns
 * the tokens to a parser or higher-level compiler module.
 * 
 * The lexer supports:
 * - Keywords (e.g., 'if', 'else', etc.)
 * - Identifiers (variable names, function names)
 * - Numeric constants (integers)
 * - Operators ('+', '-', '*', '/', etc.)
 * - Disregarding whitespace
 * - Error handling for invalid tokens
 * 
 * Usage:
 *  - Initializes the lexer with 'init_lexer()'
 *  - Usage 'get_next_token()' to extract tokens 
 *  - Free resources with 'destroy_lexer()' and 'destroy_token()'
 * 
 * @file    lexer.c
 * @author  Sophia Le (s0phia-le)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "lexer.h"

#define BUFFER 256

/**
 * Initializes the lexical analyzer by opening a source file,
 * initializing the current character, and setting the line and column
 * counters.
 * 
 * @param filename: The source file to be analyzed
 * @return: A pointer to the new 'Lexer' structure
 */
Lexer * init(const char * filename) {
    Lexer * lexer = (Lexer *)malloc(sizeof(Lexer));
    assert(lexer);

    lexer->input = fopen(filename, "r");
    assert(lexer->input);

    lexer->current_line = 1;
    lexer->current_column = 0;
    lexer->end_of_file = false;

    lexer->current_char = fgetc(lexer->input);
    return lexer;
}

/**
 * Destroys the given lexer and frees all resources associated
 * with it.
 * 
 * @param lexer: A pointer to the lexer
 */
void destroy_lexer(Lexer * lexer) {
    if(lexer->input) {
        fclose(lexer->input);
    }
    free(lexer);
}

/**
 * Advances the lexer to the next character in the source file.
 * Updates the current character and adjusts the line and column counters.
 * 
 * @param lexer: A pointer to the lexer
 */
static void advance(Lexer * lexer) {
    if(lexer->current_char == '\n') {
        lexer->current_line++;
        lexer->current_column = 0;
    } else {
        lexer->current_column++;
    }

    lexer->current_char = fgetc(lexer->input);
    if(lexer->current_char = END) {
        lexer->end_of_file = true;
    }
}

/**
 * Skips whitespace in the file
 * 
 * @param lexer: A pointer to the lexer
 */
static void skip(Lexer * lexer) {
    while(isspace(lexer->current_char) && !lexer->end_of_file) {
        advance(lexer);
    }
}

/**
 * Check if a character is valid in an identifier.
 * An identifier can contain letters, digits, and underscores.
 * 
 * @param c: The character to check
 * @return: 'true' if the character is valid in an identifier, 'false'
 * otherwise
 */
static bool is_valid_identifier_char(char c) {
    return isalnum(c) || c == '_';
}

/**
 * Gets the next token from the source file. Reads the input file,
 * skipping whitespace, and generates a token based on the current
 * character. Supports identifiers, keywords, numbers, operators,
 * and handles invalid tokens.
 * 
 * @param lexer: A pointer to the lexer
 * @return: A pointer to the next 'Token' structure
 */
Token * get_next(Lexer * lexer) {
    skip(lexer);

    if(lexer->end_of_file) {
        Token * token = (Token *)malloc(sizeof(Token));
        token->type = END;
        token->token = strdup("EOF");
        token->line = lexer->current_line;
        token->column = lexer->current_column;
        return token;
    }

    if(isalpha(lexer->current_char) || lexer->current_char == '_') {
        int start = lexer->current_column;
        char buf[BUFFER];
        int index = 0;

        while(is_valid_identifier_char(lexer->current_char)) {
            if(index < sizeof(buf) - 1) {
                buf[index++] = lexer->current_char;
            }
            advance(lexer);
        }
        buf[index] = '\0';

        Token * token = (Token *)malloc(sizeof(Token));
        token->token = strdup(buf);
        token->line = lexer->current_line;
        token->column = start;

        if(is_keyword(buf)) token->type = KEYWORD;
        else token->type = IDENTIFIER;

        return token;
    }

    if(isdigit(lexer->current_char)) {
        int start = lexer->current_column;
        char buf[BUFFER];
        int index = 0;

        while(isdigit(lexer->current_char)) {
            if(index < sizeof(buf) - 1) buf[index++] = lexer->current_char;
            advance(lexer);
        }
        buf[index] = '\0';

        Token * token = (Token *)malloc(sizeof(Token));
        token->token = strdup(buf);
        token->line = lexer->current_line;
        token->column = start;

        if(is_keyword(buf)) token->type = KEYWORD;
        else token->type = IDENTIFIER;

        return token;
    }

    if(is_operator(lexer->current_char)) {
        char op = lexer->current_char;
        int start = lexer->current_column;

        advance(lexer);

        Token * token = (Token *)malloc(sizeof(Token));
        token->type = OPERATOR;
        token->token = (char *)malloc(2);
        token->token[0] = op;
        token->token[1] = '\0';
        token->line = lexer->current_line;
        token->column = start;

        return token;
    }

    Token * token = (Token *)malloc(sizeof(Token));
        token->type = INVALID;
        token->token = (char *)malloc(2);
        token->token[0] = lexer->current_char;
        token->token[1] = '\0';
        token->line = lexer->current_line;
        token->column = lexer->current_column;

        advance(lexer);
        return token;
}

/**
 * Destroys the token and all memory resources associated
 * with it.
 * 
 * @param token: A pointer to the token to be destroyed
 */
void destroy_token(Token * token) {
    if(token->token) free(token->token);
    free(token);
}

/**
 * Checks if a character is whitespace
 * 
 * @param c: The character to be checked
 * @return: 'true' if the character is whitespace, 'false' otherwise
 */
bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

/**
 * Checks if a character is a digit
 * 
 * @param c: The character to be checked
 * @return: 'true' if the character is a digit, 'false' otherwise
 */
bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

/**
 * Checks if a character is a letter of the alphabet.
 * 
 * @param c: The character to be checked
 * @return: 'true' if the character is a letter, 'false' otherwise
 */
bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 * Checks if a character is a mathematical operator
 * 
 * @param c: The character to be checked
 * @return: 'true' if the character is an operator, 'false' otherwise
 */
bool is_operator(char c) {
    return strchr("+-*/=<>!&|", c) != NULL;
}

/**
 * Checks if a token is a valid keyword. Valid keywords include:
 * - "if"
 * - "else"
 * - "while"
 * - "return"
 * - "int"
 * - "float"
 * - NULL
 * 
 * @param token: A pointer to the token to be checked
 * @return: 'true' if the token is a valid keyword, 'false' otherwise
 */
bool is_keyword(const char * token) {
    const char * keywords[] = { "if", "else", "while", "return", "int", "float", NULL };
    for(int i = 0; keywords[i]; i++) {
        if(strcmp(token, keywords[i]) == 0) return true;
    }
    return false;
}