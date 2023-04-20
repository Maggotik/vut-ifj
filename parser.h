/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: parser.h - SA implementovana rekurzivnim sestupem
* Autor: Ondrej Sebesta, xsebes22
* ***************************************************************/

#include "scanner.h"
#include "string.h"
#include "symtable.h"
#include "precedencni_analyza.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

symtable table;

bool NT_term( Token * token );

bool NT_expression_list( Token * token );

bool NT_ret_vals( Token * token );

bool NT_opt_eol( Token * token );

bool NT_id_list( Token * token );

bool NT_next_arg( Token * token );

bool NT_func_args( Token * token );

bool NT_func_call( Token * token );

bool NT_r_assign( Token * token );

bool NT_assign( Token * token );

bool NT_id_def( Token * token );

bool NT_opt_id_def( Token * token );

bool NT_command_continue( Token * token, char * key );

bool NT_commands( Token * token );

bool NT_command( Token * token );

bool NT_type( Token * token );

bool NT_next_ret_type( Token * token );

bool NT_ret_types( Token * token );

bool NT_param( Token * token );

bool NT_next_param( Token * token );

bool NT_func_params( Token * token );

bool NT_func_def( Token * token );

bool NT_next_func_defs( Token * token );

bool NT_func_defs( Token * token );

bool NT_program( Token * token );