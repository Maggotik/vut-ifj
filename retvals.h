/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: retvals.h - navratove hodnoty
* Autor: Ondrej Sebesta, xsebes22
* ***************************************************************/

// Uspech - vse probehlo v poradku
#define OK 0

// Chyba lexikalni analyzy - chybna struktura lexemu
#define LEX_ERR 1

// Chyba syntakticke analyzy - chybna syntaxe programu, neocekavane odradkovani
#define SYNTAX_ERR 2

// Chyba semanticke analyzy - nedefinovana funkce/promenna, pokus o redefinici funkce/promenne
#define SEM_NAME_ERR 3

// Chyba semanticke analyzy - chyba pri odvozovani datoveho typu nove definovane promenne
#define SEM_DERIV_ERR 4

// Chyba semanticke analyzy - chyba typove kompatibility v aritmetickych, retezcovych a relacnich vyrazech
#define SEM_TYPE_ERR 5

// Chyba semanticke analyzy - spatny pocet/typ parametru nebo navratovych hodnot u volani fce / navratu z fce 
#define SEM_PARAM_ERR 6

// Chyba semanticke analyzy - ostatni semanticke chyby
#define SEM_OTHER_ERR 7

// Chyba semanticke analyzy - deleni 0
#define SEM_ZERO_ERR 9

// Interni chyba prekladace - alokace, realokace pameti, ...
#define INTERN_ERR 99