/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: string.h - dynamicky retezec
* Autor: Ondrej Sebesta, xsebes22
* ***************************************************************/

#include "retvals.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Funkce alokuje pamet pro retezec - pro 1 znak \0
void initialize_string( char ** string );

// Funkce prida na konec retezce novy znak
void append_string( char ** string, char character );

// Funkce uvolni pamet retezce
void free_string( char ** string );