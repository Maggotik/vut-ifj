/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: string.c - dynamicky retezec
* Autor: Ondrej Sebesta, xsebes22
* ***************************************************************/

#include "string.h"

void initialize_string( char ** string )
{

    // Alokace pameti pro 1 znak
    char * tmp_string = malloc( 2 * sizeof( char ) );

    // Osetreni alokace pameti
    if ( tmp_string == NULL ) {
        fprintf( stderr, "Chyba > Alokace pameti pro dynamicky string selhala!" );
        exit( INTERN_ERR );
    }

    // Nastaveni adresy retezce na nove alokovanou pamet
    *string = tmp_string;

}

void append_string( char ** string, char character )
{

    // Zjisteni a inkrementace delky aktualniho retezce
    int new_string_length = strlen( *string );
    ++new_string_length;

    // Realokace pameti pro novou delku retezce (+1 znak)
    *string = realloc( *string, new_string_length * sizeof( char ) );

    // Osetreni realokace pameti
    if ( *string == NULL ) {
        fprintf( stderr, "Chyba > Realokace pameti pro dynamicky string selhala!" );
        exit( INTERN_ERR );
    }

    // Vlozeni znaku na konec retezce
    strncat( *string, &character, 1 );

}

void free_string( char ** string )
{
    
    // Uvolneni pameti retezce
    free( *string );

}