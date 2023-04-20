/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: scanner.c - lexikalni analyza
* Autor: Ondrej Sebesta, xsebes22
* ***************************************************************/
  
#include "scanner.h"

// Token: +
void addition( Token * token )
{
    token->token_type = T_ADDITION;
    append_string( &token->token_attribute, '+' );
    return;
}

// Token: -
void subtraction( Token * token )
{
    token->token_type = T_SUBTRACTION;
    append_string( &token->token_attribute, '-' );
    return;
}

// Token: *
void multiplication( Token * token )
{
    token->token_type = T_MULTIPLICATION;
    append_string( &token->token_attribute, '*' );
    return;
}

// Token: /
void division( Token * token )
{
    token->token_type = T_DIVISION;
    append_string( &token->token_attribute, '/' );
    return;
}

// Token: // text (ignoruje se)
char comment_1( char character )
{

    while ( true ) {

        character = fgetc( stdin );

        if ( character == '\n' ) {
            break;
        } else if ( character == EOF ) {
            break;
        }

        
    }

    return character;

}

// Token: /* text */ (ignoruje se)
void comment_2( char character )
{

    while ( true ) {
        character = fgetc( stdin );
        if ( character == '*' ) {
            character = fgetc( stdin );
            if ( character == '/' ) {
                return;
            } else {
                continue;
            }

        } else if ( character == EOF ) {
            fprintf( stderr, "Chyba [LEX] > Viceradkovy komentar nebyl radne ukoncen!\n" );
            exit( LEX_ERR );
        }
    }

}

// Token: {
void left_curly_bracket( Token * token )
{
    token->token_type = T_LEFT_CURLY_BRACKET;
    append_string( &token->token_attribute, '{' );
    return;
}

// Token: }
void right_curly_bracket( Token * token )
{
    token->token_type = T_RIGHT_CURLY_BRACKET;
    append_string( &token->token_attribute, '}' );
    return;
}

// Token: (
void left_parenthesis( Token * token )
{
    token->token_type = T_LEFT_PARENTHESIS;
    append_string( &token->token_attribute, '(' );
    return;
}

// Token: )
void right_parenthesis( Token * token )
{
    token->token_type = T_RIGHT_PARENTHESIS;
    append_string( &token->token_attribute, ')' );
    return;
}

// Token: ,
void coma( Token * token )
{
    token->token_type = T_COMA;
    append_string( &token->token_attribute, ',' );
    return;
}

// Token: ;
void semicolon( Token * token )
{
    token->token_type = T_SEMICOLON;
    append_string( &token->token_attribute, ';' );
    return;
}

// Token: identifier
void identifier( Token * token, char character )
{

    token->token_type = T_IDENTIFIER;
    while( (( character >= 'A' ) && ( character <= 'Z' )) ||
           (( character >= 'a' ) && ( character <= 'z')) || 
           ( character == '_' ) || isdigit( character ) ) {
        append_string( &token->token_attribute, character );
        character = fgetc( stdin );
    }
    ungetc( character, stdin );
    return;
    

}

// Token: keyword
bool keyword( char * token_attribute )
{

    if ( strcmp( token_attribute, "package" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "if" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "else" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "for" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "func" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "return" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "int" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "float64" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "string" ) == 0 ) {
        return true;
    } else {
        return false;
    }
    /*
    else if ( strcmp( token_attribute, "inputs" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "inputi" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "inputf" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "print" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "int2float" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "float2int" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "len" ) == 0 ) {
        return true;
    }else if ( strcmp( token_attribute, "substr" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "ord" ) == 0 ) {
        return true;
    } else if ( strcmp( token_attribute, "chr" ) == 0 ) {
        return true;
    } else {
        return false;
    }
    */
}

// Token: <
void less_than( Token * token ) {
    token->token_type = T_LESS_THAN;
    append_string( &token->token_attribute, '<' );
    return;
}

// Token: <=
void less_equal_to( Token * token )
{
    token->token_type = T_LESS_OR_EQUAL_TO;
    append_string( &token->token_attribute, '<' );
    append_string( &token->token_attribute, '=' );
    return;
}

// Token: >
void greater_than( Token * token )
{
    token->token_type = T_GREATER_THAN;
    append_string( &token->token_attribute, '>' );
    return;
}

// Token: >=
void greater_or_equal_to( Token * token )
{
    token->token_type = T_GREATER_OR_EQUAL_TO;
    append_string( &token->token_attribute, '>' );
    append_string( &token->token_attribute, '=' );
    return;
}

// Token: =
void assignment( Token * token )
{
    token->token_type = T_ASSIGNMENT;
    append_string( &token->token_attribute, '=' );
    return;
}

// Token: ==
void equal_to( Token * token )
{
    token->token_type = T_EQUAL_TO;
    append_string( &token->token_attribute, '=' );
    append_string( &token->token_attribute, '=' );
    return;
}

// Token: !=
void not_equal_to( Token * token )
{
    token->token_type = T_NOT_EQUAL_TO;
    append_string( &token->token_attribute, '!' );
    append_string( &token->token_attribute, '=' );
    return;
}

// Token: :=
void definition( Token * token )
{
    token->token_type = T_DEFINITION;
    append_string( &token->token_attribute, ':' );
    append_string( &token->token_attribute, '=' );
    return;
}

void extra_zero_check( char * token_attribute )
{

    if ( token_attribute[0] == '0' && strlen(token_attribute) > 1 ) {
        fprintf( stderr, "Chyba [LEX] > Prebytecna pocatecni cislice 0!\n" );
        exit( LEX_ERR );
    }

}

// Token: 12342
char integer( Token * token, char character )
{

    token->token_type = T_INTEGER;

    while ( isdigit( character ) ) {
        append_string( &token->token_attribute, character );
        character = fgetc( stdin );
    }
    ungetc( character, stdin );
    return character;

}

// Token: 123.123e+123
char floating_point_exponent_double( Token * token, char character )
{
    token->token_type = T_FLOATING_POINT_EXPONENT_DOUBLE;
    append_string( &token->token_attribute, character ); // eE

    character = fgetc( stdin );
    character = fgetc( stdin );

    if ( character == '+' || character == '-' ) {
        append_string( &token->token_attribute, character ); // +-
        character = fgetc( stdin );
    }

    if ( isdigit( character ) ) {

        //ungetc( character, stdin );

        while( isdigit( character ) ) {
            append_string( &token->token_attribute, character );
            character = fgetc( stdin );
        }

        return character;

    } else {
        fprintf( stderr, "Chyba [LEX] > Za exponentem [Ee][+-]? musi nasledovat cislice!\n" );
        exit( LEX_ERR );
    }

}

// Token: 1234.123
char floating_point_double( Token * token, char character )
{

    token->token_type = T_FLOATING_POINT_DOUBLE;
    append_string( &token->token_attribute, character ); // .
    character = fgetc( stdin );

    if ( isdigit( character ) ) {

        //ungetc( character, stdin );
        while( isdigit( character ) ) {
            append_string( &token->token_attribute, character );
            character = fgetc( stdin );
        }
        if ( character == 'e' || character == 'E' ) {
            character = floating_point_exponent_double( token, character );
        } 
        ungetc( character, stdin );


        return character;

    } else {
        fprintf( stderr, "Chyba [LEX] > Za desetinnou '.' musi nasledovat cislice!\n" );
        exit( LEX_ERR );
    }
    
}

// Token: 1234e123
char exponent_double( Token * token, char character )
{

    token->token_type = T_EXPONENT_DOUBLE;
    append_string( &token->token_attribute, character ); // eE
    character = fgetc( stdin );

    if ( character == '+' || character == '-' ) {
        append_string( &token->token_attribute, character ); // +-
        character = fgetc( stdin );
    }

    if ( isdigit( character ) ) {

        //ungetc( character, stdin );
        while( isdigit( character ) ) {
            append_string( &token->token_attribute, character );
            character = fgetc( stdin );
        }

        ungetc( character, stdin );
        return character;

    } else {
        fprintf( stderr, "Chyba [LEX] > Za exponentem [Ee][+-]? musi nasledovat cislice!\n" );
        exit( LEX_ERR );
    }

}

// Token: 12342 | 1234.123 | 1234e123 | 123.123e+123
void number( Token * token, char character )
{

    character = integer( token, character );
    extra_zero_check( token->token_attribute );
    character = getc( stdin );

    if ( character == '.' ) {

        character = floating_point_double( token, character );

    } else if ( character == 'e' || character == 'E' ) {

        character = exponent_double( token, character );

    } else {

        ungetc( character, stdin );
        return;

    }

    // if ( character == '\n' ) {
    //     ungetc( character, stdin );
    // }

    // if ( isspace( character ) ) {
    //     return;
    // } else if ( character == ')' ) {
    //     return;
    // } else if ( character == EOF ) {
    //     return;
    // } else if ( character == ';' ) {
    //     return;
    // } else {
    //     fprintf( stderr, "Chyba [LEX] > Neplatny ciselny literal! : %c\n", character );
    //     exit( LEX_ERR );
    // }

    return;

}

// Token: " toto je nejaky texttt\" "
void string_literal( Token * token, char character )
{

    char before_character;

    while ( true ) {
        
        before_character = character;
        character = fgetc( stdin );

        // Nacteny znak je '\'
        if ( character == '\\' ) {

            char hex_to_ascii[3];
            long int number;
            character = fgetc( stdin );

            // Znak musi by nasledovan t, n, ", \, x
            switch( character ) {

                case 't':
                    append_string(&token->token_attribute, '\t');
                    break;

                case 'n':
                    append_string(&token->token_attribute, '\n');
                    break;

                case '\"':
                    append_string(&token->token_attribute, '\"');
                    break;

                case '\\':
                    append_string(&token->token_attribute, '\\');
                    break;

                case 'x':

                    character = fgetc( stdin );

                    if ( ((character >= '0') && (character <= '9')) 
                        || ((character >= 'A') && (character <= 'F')) ) {

                            hex_to_ascii[0] = character;
                            character = fgetc( stdin );

                            if ( ((character >= '0') && (character <= '9')) 
                                || ((character >= 'A') && (character <= 'F')) ) {

                                    hex_to_ascii[1] = character;
                                    number = strtol( hex_to_ascii, 0, 16 );
                                    char hex = (char) number;
                                    append_string(&token->token_attribute, hex);

                            } else {

                                fprintf( stderr, "Chyba [LEX] > Neznama escape sekvence!\n" );
                                exit( LEX_ERR );

                            }

                    } else {

                        fprintf( stderr, "Chyba [LEX] > Neznama escape sekvence!\n" );
                        exit( LEX_ERR );

                    }
                    break;
                
                default:

                    fprintf( stderr, "Chyba [LEX] > Neznama escape sekvence!\n" );
                    exit( LEX_ERR );

            }

            continue;

        }
        
        if ( character == '\"' ) {

            break;

        } else if ( character == EOF ) {
            fprintf( stderr, "Chyba [LEX] > Retezcovy literal neni radne ukoncen!\n" );
            exit( LEX_ERR );
        }

        append_string(&token->token_attribute, character);

    }

    token->token_type = T_STRING_LITERAL;
    return;

}

// Token: \n
void eol( Token * token )
{
    token->token_type = T_END_OF_LINE;
    return;
}

// Token: Konec zdrojoveho souboru
void eof( Token * token )
{
    token->token_type = T_END_OF_FILE;
    return;
}

// Ziskani 1ks tokenu
void get_next_token( Token *token )
{

    int state = S_START;
    char character;

    if ( token->returned ) {

        token->returned = false;
        return;

    } 

    initialize_string( &token->token_attribute );

    while ( true ) {

        character = fgetc( stdin );
        printf("AKTUALNI TOKEN: %c\n",character);
        switch ( state ) {

            case S_START:

                if ( character == '+' ) {
                    addition( token );
                    return;

                } else if ( character == '-' ) {
                    subtraction( token );
                    return;

                } else if ( character == '*' ) {
                    multiplication( token );
                    return;

                } else if ( character == '/' ) {
                    state = S_DIV;
                    break;

                } else if ( character == '{' ) {
                    left_curly_bracket( token );
                    return;

                } else if ( character == '}' ) {
                    right_curly_bracket( token );
                    return;

                } else if ( character == '(' ) {
                    left_parenthesis( token );
                    return;

                } else if ( character == ')' ) {
                    right_parenthesis( token );
                    return;

                } else if ( character == ',' ) {
                    coma( token );
                    return;

                } else if ( character == ';' ) {
                    semicolon( token );
                    return;

                } else if ( (( character >= 'A' ) && ( character <= 'Z' )) ||
                            (( character >= 'a' ) && ( character <= 'z' )) || 
                            ( character == '_' ) ) {
                    
                    identifier( token, character );

                    if ( keyword( token->token_attribute ) ) {
                        token->token_type = T_KEYWORD;
                    } 
                    
                    return;

                } else if ( character == '<' ) {
                    state = S_LESS;
                    break;

                } else if ( character == '>' ) {
                    state = S_GREAT;
                    break;

                } else if ( character == '=' ) {
                    state = S_ASSIGN;
                    break;

                } else if ( character == '!' ) {
                    state = S_NEQ;
                    break;

                } else if ( character == ':' ) {
                    state = S_DEF;
                    break;
                
                } else if ( isdigit( character ) ) {
                    number( token, character );
                    return;

                } else if ( character == '"' ) {
                    string_literal( token, character );
                    return;

                } else if ( character == ' ' || character == '\t' ) {
                    break;

                } else if ( character == '\n' ) {
                    eol( token );
                    return;

                } else if ( character == EOF ) {
                    eof( token );
                    return;

                } else {
                    fprintf( stderr, "Chyba [LEX]> Neznamy lexem na vstupu: %c\n", character );
                    exit( LEX_ERR );
                }

            case S_DIV:
                
                if ( character == '/' ) {
                    character = comment_1( character );
                    state = S_START;
                    break;

                } else if ( character == '*') {
                    comment_2( character );
                    state = S_START;
                    break;

                } else {
                    division( token );
                    ungetc( character, stdin );
                    state = S_START;
                    return;
                }

                break;

            case S_LESS:

                if ( character == '=' ) {
                    less_equal_to( token );
                    state = S_START;
                    return;

                } else {
                    less_than( token );
                    ungetc( character, stdin );
                    state = S_START;
                    return;
                }

                break;

            case S_GREAT:

                if ( character == '=' ) {
                    greater_or_equal_to( token );
                    state = S_START;
                    return;

                } else {
                    greater_than( token );
                    ungetc( character, stdin );
                    state = S_START;
                    return;
                }

                break;

            case S_ASSIGN:

                if ( character == '=' ) {
                    equal_to( token );
                    state = S_START;
                    return;

                } else {
                    assignment( token );
                    ungetc( character, stdin );
                    state = S_START;
                    return;
                }

                break;

            case S_NEQ:

                if ( character == '=' ) {
                    not_equal_to( token );
                    state = S_START;
                    return;

                } else {
                    fprintf( stderr, "Chyba [LEX] > Za znakem '!' musi nasledovat znak '='\n" );
                    exit( LEX_ERR );
                }

                break;

            case S_DEF:

                if ( character == '=' ) {
                    definition( token );
                    state = S_START;
                    return;

                } else {
                    fprintf( stderr, "Chyba [LEX] > Za znakem ':' musi nasledovat znak '='!\n" );
                    exit( LEX_ERR );
                }

                break;

            default:

                fprintf( stderr, "Chyba [INTERN] > Neznamy stav konecneho automatu!\n" );
                exit( INTERN_ERR );

                break;
        }

    }

}

void put_token_back( Token * token )
{

    token->returned = true;
    return;

}