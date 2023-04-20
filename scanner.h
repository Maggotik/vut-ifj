/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: scanner.h - lexikalni analyza
* Autor: Ondrej Sebesta, xsebes22
* ***************************************************************/

#ifndef SCANNER_H
#define SCANNER_H

#include "string.h"
#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Zakladni stavy konecneho automatu
enum States {
    S_START,
    S_DIV,
    S_LESS,
    S_GREAT,
    S_ASSIGN,
    S_NEQ,
    S_DEF
};

// Typy tokenu
enum TokenTypes {
    T_ADDITION,
    T_SUBTRACTION,
    T_MULTIPLICATION,
    T_DIVISION,
    T_LEFT_CURLY_BRACKET,
    T_RIGHT_CURLY_BRACKET,
    T_LEFT_PARENTHESIS,
    T_RIGHT_PARENTHESIS,
    T_COMA,
    T_SEMICOLON,
    T_IDENTIFIER,
    T_KEYWORD,
    T_LESS_THAN,
    T_LESS_OR_EQUAL_TO,
    T_GREATER_THAN,
    T_GREATER_OR_EQUAL_TO,
    T_ASSIGNMENT,
    T_EQUAL_TO,
    T_NOT_EQUAL_TO,
    T_DEFINITION,
    T_INTEGER,
    T_FLOATING_POINT_DOUBLE,
    T_EXPONENT_DOUBLE,
    T_FLOATING_POINT_EXPONENT_DOUBLE,
    T_STRING_LITERAL,
    T_END_OF_LINE,
    T_END_OF_FILE
};

// Struktura pro token
typedef struct Tokens {
    int token_type;
    char * token_attribute;
    bool returned;
} Token;

// Pomocna funkce pro nastaveni typu tokenu
// Operator scitani +
void addition( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Operator odcitani -
void subtraction( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Operator nasobeni *
void multiplication( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Operator deleni /
void division( Token * token );

// Funkce odstrani komentar zacinajici "//" a koncici '\n'
char comment_1( char character );

// Funkce odstrani komentar zacinajici "/*" a koncici "*/"
void comment_2( char character );

// Pomocna funkce pro nastaveni typu tokenu
// Leva slozena zavorka {
void left_curly_bracket( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Prava slozena zavorka }
void right_curly_bracket( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Leva kulata zavorka (
void left_parenthesis( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Prava kulata zavorka {
void right_parenthesis( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Carka ,
void coma( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Strednik ;
void semicolon( Token * token );

// Funkce nacita znak po znaku retezec ktery odpovida pravidlum pro identifikator
// Znaky jsou ukladany do dynamickeho retezce token_attribute (soucast struktury token)
void identifier( Token * token, char character );

// Funkce porovna identifikator s klicovymi slovy
// Je-li shoda, je typ tokenu zmenen na 'klicove slovo'
bool keyword( char * token_attribute );

// Pomocna funkce pro nastaveni typu tokenu
// Mensi <
void less_than( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Mensi rovno <=
void less_equal_to( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Vetsi >
void greater_than( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Vetsi rovno >=
void greater_or_equal_to( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Prirazeni =
void assignment( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Rovnost ==
void equal_to( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Nerovnost !=
void not_equal_to( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Definice :=
void definition( Token * token );

// Funkce nacte cele nezaporne cislo a nastavi typ tokenu
// Napr. 123 nebo 14238749478
char integer( Token * token, char character );

// Funkce nacte desetinne cislo s exponentem a nastavi typ tokenu
// Napr. 123.34e123 nebo 0.33E-22
char floating_point_exponent_double( Token * token, char character );

// Funkce nacte desetinne cislo a nastavi typ tokenu
// Napr. 0.123 nebo 12345.2
char floating_point_double( Token * token, char character );

// Funkce nacte cislo s exponentem
// Napr. 1431e123 nebo 123E+44
char exponent_double( Token * token, char character );

// Ridici funkce pro nacitani a zpracovani ciselnych posloupnosti
void number( Token * token, char character );

// Funkce pro nacitani retezcovych literalu (bez uvozovek)
// Nacita vcetne escape sekvenci a nijak je neupravuje
void string_literal( Token * token, char character );

// Pomocna funkce pro nastaveni typu tokenu
// Novy radek \n
void eol( Token * token );

// Pomocna funkce pro nastaveni typu tokenu
// Konec zdrojoveho souboru EOF
void eof( Token * token );

// Funkce pro ziskani tokenu ze souboru se zdrojovym kodem
void get_next_token( Token *token );

// Funkce vrati aktualni token zpet na vstup
void put_token_back( Token * token );

#endif