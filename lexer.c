#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "lexer.h"

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