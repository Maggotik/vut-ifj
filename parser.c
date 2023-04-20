/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: parser.c - SA implementovana rekurzivnim sestupem
* Autor: Ondrej Sebesta, xsebes22
* ***************************************************************/

#include "parser.h"

// Lexikalni analyza - tisk tokenu
void lex_debug( int token_type, char * token_attribute )
{
    fprintf( stderr, "[ %d|%s ]\n" , token_type, token_attribute );
}

// EOLy
bool multi_eol( Token * token )
{
    while ( token->token_type == T_END_OF_LINE ) {
        get_next_token( token );
    }

    put_token_back( token );
    return true;

}

// $ TERM -> string_val
// $ TERM -> int_val
// $ TERM -> float64
// $ TERM -> id
bool NT_term( Token * token )
{

    switch ( token->token_type ) {
        case T_STRING_LITERAL:
        case T_INTEGER:
        case T_FLOATING_POINT_DOUBLE:
        case T_FLOATING_POINT_EXPONENT_DOUBLE:
        case T_EXPONENT_DOUBLE:
        case T_IDENTIFIER:
            return true;
            break;
        default:
            return false;
    }

}

// TODO EXPRESSION_LIST -> EXPRESSION NEXT_EXPRESSION
bool NT_expression_list( Token * token )
{

    fprintf(stderr, "AA%d", token->token_type );
    if ( token->token_type == T_RIGHT_CURLY_BRACKET ) {
        exit( SYNTAX_ERR );
    }

    char * key = token->token_attribute;

    // PRECEDENCE
    int navrat = precedence_processing( token, &table, key );
    // PRECEDENCE

    fprintf(stderr, "%s", token->token_attribute );

    return true;

}

// $ RET_VALS -> EXPRESSION_LIST
// $ RET_VALS -> TERM
// $ RET_VALS -> ε
bool NT_ret_vals( Token * token )
{

    if ( NT_expression_list( token ) ) {

        put_token_back( token );
        return true;

    } else if ( NT_term( token ) ) {

        return true;

    } 

    put_token_back( token );
    return true;

}

// $ OPT_EOL -> eol
// $ OPT_EOL -> ε
bool NT_opt_eol( Token * token )
{

    if ( token->token_type == T_END_OF_LINE ) {

        return multi_eol( token );

    }
        
    put_token_back( token );
    return true;

}

// $ ID_LIST -> , id ID_LIST
// $ ID_LIST -> ε
bool NT_id_list( Token * token )
{

    if ( token->token_type == T_COMA ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( token->token_type == T_IDENTIFIER ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );
            return NT_id_list( token );
            
        } else { return false; }

    }

    put_token_back( token );
    return true;

}

// $ NEXT_ARG -> , TERM NEXT_ARG
// $ NEXT_ARG -> ε
bool NT_next_arg( Token * token )
{

    if ( token->token_type == T_COMA ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( NT_term( token ) ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );
            return NT_next_arg( token );

        } else { return false; }

    }
    
    put_token_back( token );
    return true;

}

// $ FUNC_ARGS -> TERM NEXT_ARG
// $ FUNC_ARGS -> ε
bool NT_func_args( Token * token )
{

    if ( NT_term( token ) ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );
        return NT_next_arg( token );

    } 

    put_token_back( token );
    return true;

}

// FUNC_CALL -> id ( FUNC_ARGS )
bool NT_func_call( Token * token )
{
    
    if ( token->token_type == T_IDENTIFIER ) {

        Token * tmp = (Token *) malloc(sizeof(Token));
        if ( tmp == NULL ) {
            fprintf( stderr, "Chyba [INTERN]> Chyba alokace paměti! \n" );
            exit( INTERN_ERR );
        }

        tmp->token_attribute = token->token_attribute;
        tmp->token_type = token->token_type;

        get_next_token( token );
        fprintf( stderr, "ˆoˆ%s", token->token_attribute);
        //lex_debug( token->token_type, token->token_attribute );
        //fprintf( stderr, "*%s* A\n", token->token_attribute );

        if ( token->token_type == T_LEFT_PARENTHESIS ) {
            fprintf( stderr, "Leva zavorka! \n" );
            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );

            if ( NT_func_args( token ) ) {
                fprintf( stderr, "Leva ! \n" );
                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );

                if ( token->token_type == T_RIGHT_PARENTHESIS ) {
                    
                    return true;

                } else { fprintf( stderr, "%s", "L"); put_token_back( token ); return false; }

            } else { put_token_back( token ); return false; }

        } else {

            fprintf( stderr, "ˆbˆ%s", tmp->token_attribute);
            
            //put_token_back( token ); return false; 
            for (int i = 0; i < strlen(token->token_attribute); i++)
            {
                ungetc(token->token_attribute[i],stdin);
            }

            token->token_attribute = tmp->token_attribute;
            token->token_type = tmp->token_type;
            fprintf( stderr, "ˆˆ%s", tmp->token_attribute);
            //put_token_back( token ); return false;
            return false;
        }

    } 

    put_token_back( token );
    return false;

}

// R_ASSIGN -> FUNC_CALL
// R_ASSIGN -> EXPRESSION_LIST
bool NT_r_assign( Token * token )
{

    if ( NT_func_call( token ) ) {
        fprintf( stderr, "ˆbˆ%s", "xxxxxx");
        get_next_token( token );
        return true;

    } else if ( NT_expression_list( token ) ) { // Tu dorazi uz BCKO
        
        fprintf( stderr, "ˆbˆ%s", "xxxxxx");
        put_token_back( token );
        return true;

    }

    fprintf( stderr, "ˆbˆ%s", "xxxxxx");
    return false;

}

// ASSIGN -> id ID_LIST = OPT_EOL R_ASSIGN
bool NT_assign( Token * token )
{
    
    if ( token->token_type == T_IDENTIFIER ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( NT_id_list( token ) ) {
            
            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );

            if ( token->token_type == T_ASSIGNMENT ) {

                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );

                if ( NT_opt_eol( token ) ) {

                    get_next_token( token );
                    lex_debug( token->token_type, token->token_attribute );
                    return NT_r_assign( token );

                } else { return false; }

            } else { return false; }

        } else { return false; }

    }

    return false;

}

// ID_DEF -> id := EXPRESSION
bool NT_id_def( Token * token )
{

    bool id_def = false;

    if ( token->token_type == T_IDENTIFIER ) {

        insert_symbol(&table, token->token_attribute);
        char * key = token->token_attribute;

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( token->token_type == T_DEFINITION ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );

            if ( token->token_type == T_IDENTIFIER ) {

                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );

                if ( token->token_type == T_LEFT_PARENTHESIS ) {
                    // Je to funkce, zpracovani v rekurzi
                } else {

                    // PRECEDENCE
                    int navrat = precedence_processing( token, &table, key );
                    // PRECEDENCE

                }

            } else {

            }
            // EXPRESSION - Zavolat precedencni analyzu

        }

    }

    return id_def;

}

// OPT_ID_DEF -> ID_DEF
// OPT_ID_DEF -> ε
bool NT_opt_id_def( Token * token )
{

    if ( NT_id_def( token ) ) {

        return true;

    }

    put_token_back( token );
    return true;

}

// COMMAND_CONTINUE -> := EXPRESSION
// COMMAND_CONTINUE -> ID_LIST = OPT_EOL R_ASSIGN
// COMMAND_CONTINUE -> ( FUNC_ARGS )
bool NT_command_continue( Token * token, char * key )
{

    bool command_continue = false;
    get_next_token( token );
    lex_debug( token->token_type, token->token_attribute );

    // COMMAND_CONTINUE -> := EXPRESSION
    if ( token->token_type == T_DEFINITION ) {

        insert_symbol( &table, key );
        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( token->token_type == T_IDENTIFIER ) {

            Token * tmp = (Token *) malloc(sizeof(Token));
            if ( tmp == NULL ) {
                fprintf( stderr, "Chyba [INTERN]> Chyba alokace paměti! \n" );
                exit( INTERN_ERR );
            }

            get_next_token( tmp );
            for (int i = 0; i < strlen(tmp->token_attribute); i++)
            {
                ungetc(tmp->token_attribute[i],stdin);
            }
            
            lex_debug( token->token_type, token->token_attribute );

            if ( tmp->token_type == T_LEFT_PARENTHESIS ) {
                
                put_token_back(tmp);
                token = tmp;
                return NT_command_continue(token, key );
                
            } else {

                // PRECEDENCE
                // TU TO JE
                int navrat = precedence_processing( token, &table, key );
                return true;
                // PRECEDENCE

            }

        } else {

            // PRECEDENCE
            int navrat = precedence_processing( token, &table, key );
            // PRECEDENCE
            
            return true;

        }

    // COMMAND_CONTINUE -> ( FUNC_ARGS )
    } else if ( token->token_type == T_LEFT_PARENTHESIS ) {
        
        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( NT_func_args( token ) ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );

            if ( token->token_type == T_RIGHT_PARENTHESIS ) {

                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );
                return true;

            }

        }

    // COMMAND_CONTINUE -> ID_LIST = OPT_EOL R_ASSIGN
    } else if ( NT_id_list( token ) ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( token->token_type == T_ASSIGNMENT ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );

            if ( NT_opt_eol( token ) ) {

                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );
                
                return NT_r_assign( token );

            }

        }

    } 

    return false;

}

// COMMANDS -> COMMAND COMMANDS
// COMMANDS -> ε
bool NT_commands( Token * token )
{

    if ( NT_command( token ) ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );
        return NT_commands( token );

    }

    put_token_back( token );
    return true;

}

// COMMAND -> if EXPRESSION { eol COMMANDS } else { eol COMMANDS } eol
// COMMAND -> for OPT_ID_DEF ; EXPRESSION ; ID_ASSIGN { eol COMMANDS } eol
// COMMAND -> return RET_VALS eol
// COMMAND -> id COMMAND_CONTINUE eol
bool NT_command( Token * token )
{

    // if, for, return
    if ( token->token_type == T_KEYWORD ) {

        // COMMAND -> if EXPRESSION { eol COMMANDS } else { eol COMMANDS }
        if ( !strcmp( token->token_attribute, "if" ) ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );

            // PRECEDENCE
            int navrat = precedence_processing( token, &table, "" );
            // PRECEDENCE

            if ( token->token_type == T_LEFT_CURLY_BRACKET ) {

                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );

                if ( token->token_type == T_END_OF_LINE ) {
                    multi_eol( token );

                    get_next_token( token );
                    lex_debug( token->token_type, token->token_attribute );

                    if ( NT_commands( token ) ) {
                    
                        get_next_token( token );
                        lex_debug( token->token_type, token->token_attribute );

                        if ( token->token_type == T_RIGHT_CURLY_BRACKET ) {

                            get_next_token( token );
                            lex_debug( token->token_type, token->token_attribute );

                            if ( token->token_type == T_KEYWORD ) {
                                if ( !strcmp( token->token_attribute, "else" ) ) {

                                    get_next_token( token );
                                    lex_debug( token->token_type, token->token_attribute );

                                    if ( token->token_type == T_LEFT_CURLY_BRACKET ) {

                                        get_next_token( token );
                                        lex_debug( token->token_type, token->token_attribute );

                                        if ( token->token_type == T_END_OF_LINE ) {

                                            multi_eol( token );
                                            get_next_token( token );
                                            lex_debug( token->token_type, token->token_attribute );

                                            if ( NT_commands( token ) ) {

                                                get_next_token( token );
                                                lex_debug( token->token_type, token->token_attribute );

                                                if ( token->token_type == T_RIGHT_CURLY_BRACKET ) {

                                                    get_next_token( token );
                                                    lex_debug( token->token_type, token->token_attribute );

                                                    if ( token->token_type == T_END_OF_LINE ) {

                                                        multi_eol( token );
                                                        return true;

                                                    }
                                                    
                                                }

                                            }

                                        }

                                    }

                                }
                            }

                        }

                    }

                }

            }

        // COMMAND -> for OPT_ID_DEF ; EXPRESSION ; ID_ASSIGN { eol COMMANDS }
        } else if ( !strcmp( token->token_attribute, "for" ) ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );

            if ( NT_opt_id_def( token ) ) {

                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );
                
                if ( token->token_type == T_SEMICOLON ) {
                    
                    get_next_token( token );
                    lex_debug( token->token_type, token->token_attribute );

                    // PRECEDENCE
                    int navrat = precedence_processing( token, &table, "" );
                    // PRECEDENCE
                    
                    if ( token->token_type == T_SEMICOLON ) {

                        get_next_token( token );
                        lex_debug( token->token_type, token->token_attribute );

                        if ( NT_assign( token ) ) {

                            get_next_token( token );
                            lex_debug( token->token_type, token->token_attribute );

                            if ( token->token_type == T_LEFT_CURLY_BRACKET ) {

                                get_next_token( token );
                                lex_debug( token->token_type, token->token_attribute );

                                if ( token->token_type == T_END_OF_LINE ) {

                                    multi_eol( token );
                                    get_next_token( token );
                                    lex_debug( token->token_type, token->token_attribute );

                                    if ( NT_commands( token ) ) {

                                        get_next_token( token );
                                        lex_debug( token->token_type, token->token_attribute );

                                        if ( token->token_type == T_RIGHT_CURLY_BRACKET ) {

                                            get_next_token( token );
                                            lex_debug( token->token_type, token->token_attribute );

                                            if ( token->token_type == T_END_OF_LINE ) {

                                                return multi_eol( token );

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        // COMMAND -> return RET_VALS
        } else if ( !strcmp( token->token_attribute, "return" ) ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );

            if ( NT_ret_vals( token ) ) {

                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );

                if ( token->token_type == T_END_OF_LINE ) {

                    return multi_eol( token );

                }

            }

        }

    // COMMAND -> id COMMAND_CONTINUE
    } else if ( token->token_type == T_IDENTIFIER ) {
        
        char * key = token->token_attribute;

        if ( NT_command_continue( token, key ) ) {

            if ( token->token_type == T_END_OF_LINE ) {

                return multi_eol( token );

            }

        }
                

    } 

    return false;

}

// TYPE -> int
// TYPE -> float64
// TYPE -> string
bool NT_type( Token * token )
{

    if ( token->token_type == T_KEYWORD ) {

        if ( !strcmp( token->token_attribute, "int" ) ) {

            return true;

        } else if ( !strcmp( token->token_attribute, "float64" ) ) {

            return true;

        } else if ( !strcmp( token->token_attribute, "string" ) ) {

            return true;

        }

    }

    return false;

}

// NEXT_RET_TYPE -> , TYPE NEXT_RET_TYPE
// NEXT_RET_TYPE -> ε
bool NT_next_ret_type( Token * token )
{

    if ( token->token_type == T_COMA ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( NT_type( token ) ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );
            return NT_next_ret_type( token );

        } else { return false; }

    }

    put_token_back( token );
    return true;

}

// RET_TYPES -> ( TYPE NEXT_RET_TYPE )
// RET_TYPES -> ε
bool NT_ret_types( Token * token )
{

    if ( token->token_type == T_LEFT_PARENTHESIS ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( NT_type( token ) ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );
            
            if ( NT_next_ret_type( token ) ) {

                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );

                if ( token->token_type == T_RIGHT_PARENTHESIS ) {

                    return true;

                } else { return false; }

            } else { return false; }

        } else { return false; }

    } 
    
    put_token_back( token );
    return true;

}

// $ PARAM -> id TYPE
bool NT_param( Token * token )
{

    if ( token->token_type == T_IDENTIFIER ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );
        return NT_type( token );

    }

    return false;

}

// $ NEXT_PARAM -> , OPT_EOL PARAM NEXT_PARAM
// $ NEXT_PARAM -> ε
bool NT_next_param( Token * token )
{

    if ( token->token_type == T_COMA ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( NT_opt_eol( token ) ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );

            if ( NT_param( token ) ) {

                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );
                return NT_next_param( token );

            } else { return false; }

        } else { return false; }

    }

    put_token_back( token );
    return true;

}

// FUNC_PARAMS -> PARAM NEXT_PARAM
// FUNC_PARAMS -> ε
bool NT_func_params( Token * token )
{

    if ( NT_param( token ) ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );
        return NT_next_param( token );

    } 

    put_token_back( token );
    return true;

}

// FUNC_DEF -> func id ( OPT_EOL FUNC_PARAMS ) RET_TYPES { eol COMMANDS }
bool NT_func_def( Token * token )
{
    bool func_def = false;

    if ( !strcmp( token->token_attribute, "func" ) ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( token->token_type == T_IDENTIFIER ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );

            if ( token->token_type == T_LEFT_PARENTHESIS ) {
                
                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );

                if ( NT_opt_eol( token ) ) {
                    
                    get_next_token( token );
                    lex_debug( token->token_type, token->token_attribute );

                    if ( NT_func_params( token ) ) {

                        get_next_token( token );
                        lex_debug( token->token_type, token->token_attribute );

                        if ( token->token_type == T_RIGHT_PARENTHESIS ) {

                            get_next_token( token ); // RET_TYPES
                            lex_debug( token->token_type, token->token_attribute );

                            if ( NT_ret_types( token ) ) {

                                get_next_token( token ); // [ { ]
                                lex_debug( token->token_type, token->token_attribute );

                                if ( token->token_type == T_LEFT_CURLY_BRACKET ) {

                                    get_next_token( token ); // [ eol ]
                                    lex_debug( token->token_type, token->token_attribute );

                                    if ( token->token_type == T_END_OF_LINE ) {

                                        multi_eol( token );
                                        get_next_token( token ); // NT_COMMANDS
                                        lex_debug( token->token_type, token->token_attribute );

                                        if ( NT_commands( token ) ) {

                                            get_next_token( token ); // [ } ]
                                            lex_debug( token->token_type, token->token_attribute );

                                            if ( token->token_type == T_RIGHT_CURLY_BRACKET ) {

                                                func_def = true;

                                            }


                                        }


                                    }


                                }

                            }


                        }

                    }

                }


            }


        }

    }

    return func_def;

}

// NEXT_FUNC_DEFS -> eol FUNC_DEF NEXT_FUNC_DEFS
// NEXT_FUNC_DEFS -> ε
bool NT_next_func_defs( Token * token )
{

    if ( token->token_type == T_END_OF_LINE ) {

        multi_eol( token );
        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( NT_func_def( token ) ) {

            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );
            return NT_next_func_defs( token );

        } else if ( token->token_type == T_END_OF_FILE ) {

            put_token_back( token );
            return true;

        }

    }

    put_token_back( token );
    return true;

}

// FUNC_DEFS -> FUNC_DEF NEXT_FUNC_DEFS
bool NT_func_defs( Token * token )
{

    if ( NT_func_def( token ) ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );
        return NT_next_func_defs( token );

    }

    return false;

}

// PROGRAM -> OPT_EOL package main eol FUNC_DEFS OPT_EOL eof
bool NT_program( Token * token )
{

    if ( NT_opt_eol( token ) ) {

        get_next_token( token );
        lex_debug( token->token_type, token->token_attribute );

        if ( !strcmp( token->token_attribute, "package" ) ) {
        
            get_next_token( token );
            lex_debug( token->token_type, token->token_attribute );
            
            if ( !strcmp( token->token_attribute, "main" ) ) {

                get_next_token( token );
                lex_debug( token->token_type, token->token_attribute );

                if ( token->token_type == T_END_OF_LINE ) {

                    multi_eol( token );
                    get_next_token( token );
                    lex_debug( token->token_type, token->token_attribute );

                    if ( NT_func_defs( token ) ) {

                        get_next_token( token );
                        lex_debug( token->token_type, token->token_attribute );
                        
                        if ( token->token_type == T_END_OF_FILE ) {

                            return true;

                        } else { return false; }

                    } else { return false; }

                } else { return false; }

            } else { return false; }

        } else { return false; }

    }

    return false;

}

int main( int argc, char *argv[] )
{

    Token * token = (Token *) malloc(sizeof(Token));

    if ( token == NULL ) {
        fprintf( stderr, "Chyba [INTERN]> Chyba alokace paměti! \n" );
        exit( INTERN_ERR );
    }

    token->returned = false;

    initialize_symtable( &table );

    /*** Syntakticka analyza ***/

    get_next_token( token );

    if ( NT_program( token ) ) {
        exit( 0 );
    } else {
        exit( SYNTAX_ERR );
    }

    /*** Debug lexikalni analyzy ***/
    /*** Vypise tokeny, ktere jsou predavany parseru ***/

    // while( true ) {

    //     get_next_token( token );
    //     lex_debug( token->token_type, token->token_attribute );

    //     if ( token->token_type == T_END_OF_FILE ) {
    //         exit(0);
    //     }
        
    // }

    /*** Debug Tabulky symbolu ***/
    /*** Testovani funkci pro vlozeni, odstraneni, hledani ***/

    // symtable local_table;
    // initialize_symtable( &local_table );
    // item_data * found;
    // insert_symbol( &local_table, "klic" );
    // insert_symbol( &local_table, "bic" );
    // insert_symbol( &local_table, "bind" );

    // found = search_item( &local_table, "klic" );
    // set_already_defined( &local_table, "klic" );
    // fprintf( stderr, "%d", found->already_defined ); // 1
    // found = search_item( &local_table, "bic" );
    // fprintf( stderr, "%d", found->already_defined ); // 0
    // set_already_defined( &local_table, "bic" );
    // found = search_item( &local_table, "bic" );
    // fprintf( stderr, "%d", found->already_defined ); // 1
    // remove_symbol( &local_table, "klic" );
    // remove_symbol( &local_table, "bic" );
    // if ( (found = search_item( &local_table, "bic" )) == NULL ) {
    //     fprintf( stderr, "\n%s", "BIC_NULL" );
    // }
    // found = search_item( &local_table, "bind" );
    // set_already_defined( &local_table, "bind" );
    // fprintf( stderr, "%d", found->already_defined );
    // insert_symbol( &local_table, "klic" );
    // set_already_defined( &local_table, "klic" );
    // fprintf( stderr, "%d", found->already_defined );
    // fprintf( stderr, "%d", found->t_data );
    // insert_data_type( &local_table, "klic", T_DIVISION ); 
    // fprintf( stderr, "<%d>", found->t_data );
    // remove_symbol( &local_table, "klic" );
    // remove_symbol( &local_table, "klic" );
    // found = search_item( &local_table, "klic" );
    // insert_symbol( &local_table, "klic" );
    // found = search_item( &local_table, "klic" );
    // set_already_defined( &local_table, "klic" );
    // fprintf( stderr, "%d", found->already_defined );
    // free_symtable( &local_table );

    return 0;
    
}