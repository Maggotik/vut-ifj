/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: generator.h - funkce pro generovani IFJcode20
* Autor: Jakub Vano, xvanoj00
         Zuzana Hrklova, xhrklo00
* ***************************************************************/

#ifndef GENERATOR_H
#define GENERATOR_H


#include <stdio.h>
#include <stdbool.h>
#include "symtable.h"
#include "scanner.h"
#include "precedencni_analyza.h"

void generate_inputf();
void generate_inputs();
void generate_inputi();
void generate_print();
void generate_int2float();
void generate_float2int();
void generate_len();
void generate_substr();
void generate_ord();
void generate_chr();

void generate_start();
void generate_main_start();
void generate_main_end();
void generate_var(char *var_name, bool global);
bool generate_assign_to_var(Token token, char *var_name, bool global);
char *var_define(int type, char *attribute, bool global);
bool generate_func_start(char *func_name);
bool generate_func_end();
void generate_func_get_argument(char *var_name);
void generate_func_return(Token token, char *var_name, bool global);
void push_param(Token token, bool global);
bool generate_func_call(char *func_name, int argc);
void generate_if_start(int *if_count, bool global, Token token);
void generate_else(int if_count);
void generate_if_end(int if_count);
void generate_for_start(int *for_count, char *var_name, bool global);
void generate_for_end();
bool generate_operators(int type, Token var_dest, Token var_symb1, Token var_symb2, bool global);


#endif