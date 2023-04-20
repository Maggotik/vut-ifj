/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: generator.c - funkce pro generovani IFJcode20
* Autor: Jakub Vano, xvanoj00
         Zuzana Hrklova, xhrklo00
* ***************************************************************/

#include "generator.h"
#include "scanner.h"
#include "string.h"


void generate_inputf()
{
    fprintf(stdout, "LABEL $inputf\n"
                    "CREATEFRAME\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@return\n"
                    "READ LF@return float\n"
                    "JUMPIFEQ $err LF@return nil@nil\n"  
                    "PUSHS LF@return\n"
                    "POPFRAME\n"
                    "RETURN\n"
                    "LABEL $err\n"
                    "PUSHS float@\n"
                    "PUSHS int@1\n"
                    "POPFRAME\n"
                    "RETURN\n");
}

void generate_inputs()
{
    fprintf(stdout, "LABEL $inputs\n"
                    "CREATEFRAME\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@return\n"
                    "READ LF@return string\n"
                    "JUMPIFEQ $err LF@return nil@nil\n"
                    "PUSHS LF@return\n"
                    "POPFRAME\n"
                    "RETURN\n"
                    "LABEL $err\n"
                    "PUSHS string@\n"
                    "PUSHS int@1\n"
                    "POPFRAME\n"
                    "RETURN\n");
}

void generate_inputi()
{
    fprintf(stdout, "LABEL $inputi\n"
                    "CREATEFRAME\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@return\n"
                    "READ LF@return int\n"
                    "JUMPIFEQ $err LF@return nil@nil\n"
                    "PUSHS LF@return\n"
                    "POPFRAME\n"
                    "RETURN\n"
                    "LABEL $err\n"
                    "PUSHS int@\n"
                    "PUSHS int@1\n"
                    "POPFRAME\n"
                    "RETURN\n");
}

void generate_print()
{
    fprintf(stdout, "LABEL $print\n"
                    "CREATEFRAME\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@temp\n"
                    "DEFVAR LF@iterator\n"
                    "POPS LF@iterator\n"
                    "LABEL $cycle\n"
                    "JUMPIFEQ $cycle_end LF@iterator int@0\n"
                    "POPS LF@temp\n"
                    "WRITE LF@temp\n"
                    "SUB LF@iterator LF@iterator int@1\n"
                    "JUMP $cycle\n"
                    "LABEL $cycle_end\n"
                    "WRITE string@\010\n"
                    "POPFRAME\n"
                    "RETURN\n");
}

void generate_int2float()
{
    fprintf(stdout, "LABEL $int2float\n"
                    "CREATEFRAME\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@return\n"
                    "DEFVAR LF@int\n"
                    "POPS LF@int\n"
                    "INT2FLOAT LF@return LF@int\n"
                    "PUSHS LF@return\n"
                    "POPFRAME\n"
                    "RETURN\n");
}

void generate_float2int()
{
    fprintf(stdout, "LABEL $float2int\n"
                    "CREATEFRAME\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@return\n"
                    "DEFVAR LF@float\n"
                    "POPS LF@float\n"
                    "FLOAT2INT LF@return LF@float\n"
                    "PUSHS LF@return\n"
                    "POPFRAME\n"
                    "RETURN\n");
}

void generate_len()
{
    fprintf(stdout, "LABEL $len\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@return\n"
                    "DEFVAR LF@string\n"
                    "POPS LF@string\n"
                    "STRLEN LF@return LF@string\n"
                    "PUSHS LF@return\n"
                    "POPFRAME\n"
                    "RETURN\n");
}

void generate_substr()
{
    fprintf(stdout, "LABEL $substr\n"
                    "CREATEFRAME\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@string\n"
                    "DEFVAR LF@index\n"
                    "DEFVAR LF@length\n"
                    "POPS LF@length\n"
                    "POPS LF@index\n"
                    "POPS LF@string\n"
                    "DEFVAR LF@check\n"
                    "DEFVAR LF@str_length\n"
                    "STRLEN LF@str_length LF@string\n"
                    "SUB LF@str_length LF@str_length int@1\n"
                    "GT LF@check LF@index LF@str_length\n"
                    "JUMPIFEQ $err LF@check bool@true\n"
                    "LT LF@check LF@index int@0\n"
                    "JUMPIFEQ $err LF@check bool@true\n"
                    "LT LF@check LF@length int@0\n"
                    "JUMPIFEQ $err LF@check bool@true\n"
                    "DEFVAR LF@return\n"
                    "TYPE LF@return LF@return\n"
                    "DEFVAR LF@tmp\n"
                    "LABEL $cycle\n"
                    "GT LF@check LF@index LF@str_length\n"
                    "JUMPIFEQ $cycle_end LF@check bool@true\n"
                    "JUMPIFEQ $cycle_end LF@length int@0\n"
                    "STRI2INT LF@tmp LF@string LF@index\n"
                    "INT2CHAR LF@tmp LF@tmp\n"
                    "CONCAT LF@return LF@return LF@tmp\n"
                    "ADD LF@index LF@index int@1\n"
                    "SUB LF@length LF@length int@1\n"
                    "JUMP $cycle\n"
                    "LABEL $cycle_end\n"
                    "PUSHS LF@return\n"
                    "POPFRAME\n"
                    "RETURN\n"
                    "LABEL $err\n"
                    "PUSHS string@\n"
                    "PUSHS int@1\n"
                    "POPFRAME\n"
                    "RETURN\n");
}

void generate_ord()
{
    fprintf(stdout, "LABEL $ord\n"
                    "CREATEFRAME\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@return\n"
                    "DEFVAR LF@tmp\n"
                    "DEFVAR LF@check\n"
                    "DEFVAR LF@index\n"
                    "POPS LF@index\n"
                    "DEFVAR LF@string\n"
                    "POPS LF@string\n"
                    "STRLEN LF@tmp LF@string\n"
                    "SUB LF@tmp LF@tmp int@1\n"
                    "GT LF@chcek LF@index LF@tmp\n"
                    "JUMPIFEQ $err LF@check bool@true\n"
                    "LT LF@check LF@index int@0\n"
                    "JUMPIFEQ $err LF@check bool@true\n"
                    "STRI2INT LF@return LF@string LF@index\n"
                    "PUSHS LF@return\n"
                    "POPFRAME\n"
                    "RETURN\n"
                    "LABEL $err\n"
                    "PUSHS int@0\n"
                    "PUSHS int@1\n"
                    "POPFRAME\n"
                    "RETURN\n");
}

void generate_chr()
{
    fprintf(stdout, "LABEL $chr\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@tmp\n"
                    "DEFVAR LF@return\n"
                    "POPS LF@return\n"
                    "LT LF@tmp LF@return int@0\n"
                    "JUMPIFEQ $err LF@tmp bool@true\n"
                    "GT LF@tmp LF@return int@255\n"
                    "JUMPIFEQ $err LF@tmp bool@true\n"
                    "INT2CHAR LF@return LF@$return\n"
                    "PUSHS LF@return\n"
                    "POPFRAME\n"
                    "RETURN\n"
                    "LABEL $err\n"
                    "PUSHS string@\n"
                    "PUSHS int@1\n"
                    "POPFRAME\n"
                    "RETURN\n");
}



void generate_start()
{
    fprintf(stdout, ".IFJcode20\n"
                    "JUMP $$main\n");

    generate_inputs();
    generate_inputi();
    generate_inputf();
    generate_print();
    generate_int2float();
    generate_float2int();
    generate_len();
    generate_substr();
    generate_ord();
    generate_chr();
}

void generate_main_start()
{
    fprintf(stdout, "LABEL $$main\n"
                    "CREATEFRAME\n"
                    "PUSHFRAME\n");
}

void generate_main_end()
{
    fprintf(stdout, "POPFRAME\n");
}

void generate_var(char *var_name, bool global)
{
    if(global){
        fprintf(stdout, "DEFVAR GF@%s\n"
                        "MOVE GF@%s nil@nil\n", var_name, var_name);
    }
    else{
        fprintf(stdout, "DEFVAR LF@%s\n"
                        "MOVE LF@%s nil@nil\n", var_name, var_name);
    }
}

bool generate_assign_to_var(Token token, char *var_name, bool global)
{
    char *param;
    char *var;
    
    param = var_define(T_IDENTIFIER, var_name, global);
    var = var_define(token.token_type, token.token_attribute, global);

    if (param == NULL || var == NULL){
        return false;
    }

    fprintf(stdout, "MOVE %s %s\n", param, var);
    free(param);
    free(var);
    return true;
}

char *var_define(int type, char *attribute, bool global){
    char *tmp;
    char *ftype;

    switch(type){
        case T_IDENTIFIER:
            if (strcmp(attribute, "$return") == 0)
                ftype = "TF@";
            else if(!global){
                ftype = "LF@";
            }
            else{
                ftype = "GF@";
            }
            
            tmp = malloc(strlen(attribute) + 4);
            if(!tmp){
                return NULL;
            }

            strcpy(tmp, ftype);
            strcpy(tmp + 3, attribute);
            return tmp;
        case T_INTEGER:
            tmp = malloc(strlen(attribute) + 5);
            if(!tmp){
                return NULL;
            }
            strcpy(tmp, "int@");
            strcpy(tmp + 4, attribute);
            return tmp;
        case T_STRING_LITERAL:
            tmp = malloc(strlen(attribute) + 8);
            if(!tmp){
                return NULL;
            }
            strcpy(tmp, "string@");
            strcpy(tmp + 7, attribute);
            return tmp;
        case T_FLOATING_POINT_DOUBLE:
            tmp = malloc(strlen(attribute) + 7);
            if(!tmp){
                return NULL;
            }
            strcpy(tmp, "float@");
            strcpy(tmp + 6, attribute);
            return tmp;
        default:
            return NULL;

    }
}

bool generate_func_start(char *func_name)
{
    fprintf(stdout, "LABEL %s\n"
                    "PUSHFRAME\n"
                    "DEFVAR LF@return\n"
                    "MOVE LF@return nil@nil\n", func_name);
    return true;
}

bool generate_func_end()
{
    fprintf(stdout, "POPFRAME\n"
                    "RETURN\n");
    return true;
}

void generate_func_get_argument(char *var_name)
{
    fprintf(stdout, "POPS LF@%s\n", var_name);
}

void generate_func_return(Token token, char *var_name, bool global)
{
    char *var;
    var = var_define(token.token_type, token.token_attribute, global);
    fprintf(stdout, "MOVE LF@return %s\n", var);
    free(var);
}

void push_param(Token token, bool global){
    char *var;
    var = var_define(token.token_type, token.token_attribute, global);
    fprintf(stdout, "PUSHS %s\n", var);
    free(var);
}

bool generate_func_call(char *func_name, int argc)
{
    fprintf(stdout, "PUSHS int@%d\n"
                    "CREATEFRAME\n"
                    "CALL $%s\n", argc, func_name);
    return true;
}

void generate_if_start(int *if_count, bool glogal, Token token)
{
    static int count = 0;
    char *var = var_define(token.token_type, token.token_attribute, glogal);
    fprintf(stdout, "JUMPIFEQ $if_else%d %s bool@false\n", count, var);
    free(var);
    *if_count = count++;
}

void generate_else(int if_count)
{
    fprintf(stdout, "JUMP $if_end%d\n"
                    "LABEL $if_else%d\n", if_count, if_count);
}

void generate_if_end(int if_count)
{
    fprintf(stdout, "LABEL $if_end%d\n", if_count);
}

void generate_for_start(int *for_count, char *var_name, bool global)
{
    char *var;
    static int counter = 0;
    var = var_define(T_IDENTIFIER, var_name, global);
    fprintf(stdout, "LABEL $for%d\n"
                    "JUMPIFEQ $for_end%d %s bool@false\n", counter, counter, var);
    *for_count = counter++;
    free(var);
}

void generate_for_end(int for_count)
{
    fprintf(stdout, "JUMP $for%d\n"
                    "LABEL $for_end%d\n", for_count, for_count);
}

bool generate_operators(int type, Token var_dest, Token var_symb1, Token var_symb2, bool global)
{
    char *var;
    char *symb1;
    char *symb2;
    var = var_define(var_dest.token_type, var_dest.token_attribute, global);
    symb1 = var_define(var_symb1.token_type, var_symb1.token_attribute, global);
    symb2 = var_define(var_symb2.token_type, var_symb2.token_attribute, global);

    switch (type)
    {
    case T_ADDITION:
        fprintf(stdout, "ADD %s %s %s\n", var, symb1, symb2);
        break;
    case T_SUBTRACTION:
        fprintf(stdout, "SUB %s %s %s\n", var, symb1, symb2);
        break;
    case T_MULTIPLICATION:
        fprintf(stdout, "MUL %s %s %s\n", var, symb1, symb2);
        break;
    case T_DIVISION:
        if(var_symb1.token_type == T_INTEGER && var_symb2.token_type == T_INTEGER)
        {
            fprintf(stdout, "IDIV %s %s %s\n", var, symb1, symb2);
        }
        else {
            fprintf(stdout, "DIV %s %s %s\n", var, symb1, symb2);
        }
        break;
    case T_LESS_THAN:
        fprintf(stdout, "LT %s %s %s\n", var, symb1, symb2);
        break;
    case T_LESS_OR_EQUAL_TO:
        fprintf(stdout, "DEFVAR LF@tmp\n"
                        "LT %s %s %s\n"
                        "EQ LF@tmp %s %s\n"
                        "OR %s LF@tmp %s\n", var, symb1, symb2, symb1, symb2, var, var);
        break;
    case T_GREATER_THAN:
        fprintf(stdout, "GT %s %s %s\n", var, symb1, symb2);
        break;
    case T_GREATER_OR_EQUAL_TO:
        fprintf(stdout, "DEFVAR LF@tmp\n"
                        "GT %s %s %s\n"
                        "EQ LF@tmp %s %s\n"
                        "OR %s LF@tmp %s\n", var, symb1, symb2, symb1, symb2, var, var);
        break;
    case T_EQUAL_TO:
        fprintf(stdout, "EQ %s %s %s\n", var, symb1, symb2);
        break;
    case T_NOT_EQUAL_TO:
        fprintf(stdout, "EQ %s %s %s\n"
                        "NOT %s %s\n", var, symb1, symb2, var, var);
        break;
    default:
        return false;
    }
    return true;
}