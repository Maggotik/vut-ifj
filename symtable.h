/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: symtable.c -tabulka symbolov
* Autor: Jakub Vano, xvanoj00
         Zuzana Hrklova, xhrklo00
* ***************************************************************/

#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdbool.h>
#include "string.h"

#define SYMTABLE_MAX_SIZE 27487 //setting to prime no.

typedef struct {
    int integer;
    float float_64;
    char * string;
} values ;

typedef struct {
    int inputs_no;
    int outputs_no;
    values in_params[100];
    values out_params[100];
} func_data;

typedef struct
{
    bool global; //global/local variable
    values values;
    int t_data; //data type of a variable
    bool already_defined;
} item_data;

typedef struct list_item
{
    char *key; // identifier
	item_data data; // data
    func_data fdata; // function data
	struct list_item *next; // ptr to next item in the list
} table_item; 

typedef table_item* symtable[SYMTABLE_MAX_SIZE];


int hash_function(const char *key); //returns index

void initialize_symtable(symtable *table); //initialization of a symbol table

bool insert_symbol(symtable *table, const char *key); //returns true if symbol inserted into the table successfully

bool insert_data_type (symtable *table, const char *key, int data_type); //inserts type of a symbol's data into the table

bool set_already_defined(symtable *table, const char *key); //returns true when ended successfully

item_data *search_item(symtable *table, const char *key); //looks for the item in the table, if found returns its data else returns NULL 

bool remove_symbol (symtable *table, const char *key); //removes symbol from the symbol table, returns true if ended successfully

void free_symtable(symtable *table); //deletion of a symbol table

#endif