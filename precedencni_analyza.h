/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 
*
* Soubor: precedencni_analyza.c - zpracovani vyrazu - parser
* Autor: Jiří Václavič, xvacla31
* ***************************************************************/
#ifndef _SCANNER_H
#define _SCANNER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"


struct Item{
    int item; //nazev
    int type; //typ, pokud je

    int attrib_int;
    float attrib_float;
    bool attrib_bool;
    char attrib_string[99]; // hodnota promenne
};

struct Stack{

    int top; 
    unsigned capacity; 
    struct Item *array[99]; 
};


int precedence_processing( Token * token, symtable * table, char * key );
int top(struct Stack* stack);
int pop(struct Stack* stack);
void push(struct Stack* stack, int item, char* item_attrib);
int Empty(struct Stack* stack); 
int Full(struct Stack* stack);
void SInit(struct Stack* stack);
struct Stack* firstPush();
void get_table_index(Token* token, struct Stack* stack, int* input_index, int* stack_index,int* left_shift);
int get_index( int token_type );
char table_value_search(int input_index, int stack_index);
void expr_eval(struct Stack* stack,int i);
void sub_expr_process( struct Stack* stack, symtable * table, char * key );

#define STOP -1 // zarazka $
#define LEFT_OP 30 // <
#define EQ_OP 31

#define TRUE 32
#define FALSE 33

#define E 34
#define BOOL 35

#endif