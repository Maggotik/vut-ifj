/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 094
*
* Soubor: symtable.c -tabulka symbolov
* Autor: Jakub Vano, xvanoj00
         Zuzana Hrklova, xhrklo00
* ***************************************************************/

#include <stdlib.h>
#include <string.h>
#include "symtable.h"

int hash_function(const char *key)
{
  int length = (int)strlen(key);
  int sum = 0;
  for (int i = 0; i < length; i++){
    sum += key[i];
  }
  int hash = sum % SYMTABLE_MAX_SIZE;
  return hash;
}

void initialize_symtable(symtable *table)
{
  if (table == NULL)
		return;
  for(int i = 0; i < SYMTABLE_MAX_SIZE; i++){
		(*table)[i] = NULL;
	}
}

bool insert_symbol(symtable *table, const char *key)
{
  if (table == NULL || key == NULL) {
    return false;
  }

  int index = hash_function(key);

  table_item *new_item = (table_item*)malloc(sizeof(table_item));
  
  if (!new_item){
    return false;
  }

  item_data *searched_item = search_item(table, key);

  if (searched_item != NULL){
    free(new_item);
    return false;
  }

  initialize_string(&new_item->key);
  initialize_string(&new_item->data.values.string);
  // initialize_string(&new_item->data.params);

  if ((*table)[index] == NULL) {

    (*table)[index] = new_item;
    new_item->next = NULL;

  } else {

    new_item->next = (*table)[index];

  }
  
  int length = (int)strlen(key);
  for (int i = 0; i < length; i++){
    append_string( &new_item->key, key[i]);
  }

  new_item->data.global = false;
  new_item->data.already_defined = false;
  new_item->data.t_data = -1;
  return true;
}

bool insert_data_type (symtable *table, const char *key, int data_type)
{
  if(table == NULL || key == NULL){
    return false;
  }

  int index = hash_function(key);
  item_data *item_modified = search_item(table, key);
  item_modified->t_data = data_type;
  return true;
}

bool set_already_defined(symtable *table, const char *key)
{
  if(table == NULL || key == NULL){
    return false;
  }

  int index = hash_function(key);
  item_data *item_modified = search_item(table, key);
  item_modified->already_defined = true;
  return true;
}

item_data *search_item(symtable *table, const char *key)
{
  if (table == NULL || key == NULL){
    return NULL;
  }

  int index = hash_function(key);

  table_item *item = (*table)[index];

  for (; item != NULL ; item = item->next) {

    if ( !strcmp(item->key, key ) ){

      return &item->data;

    }

  }

  return NULL;

}

bool remove_symbol (symtable *table, const char *key)
{
  if (table == NULL || key == NULL){
    return false;
  }
  item_data *searched_item = search_item(table, key);
  if (searched_item == NULL){
    return false;
  }

  int index = hash_function(key);
  table_item *item = (*table)[index];
  table_item * tmp_ptr = NULL; // = (table_item*)malloc(sizeof(table_item));

  for (; item; item = item->next ){
    if( !strcmp(item->key, key ) ){

      tmp_ptr = item->next;

      if ( tmp_ptr == NULL ) {

        (*table)[index] = (*table)[index]->next;

      } else {

        tmp_ptr->next = item->next;

      }

      // free_string(&item->data.params);
      free_string(&item->data.values.string);
      free_string(&item->key);
      free(item);

      return true;

    }
    tmp_ptr = item;
  }

  return false;

}

void free_symtable(symtable *table)
{
  if (table == NULL){
    return;
  }

  for(int i = 0; i < SYMTABLE_MAX_SIZE; i++){

		table_item * item = (*table)[i];
    table_item * tmp_ptr = NULL;

		for ( ; item != NULL; item = tmp_ptr ) {

        tmp_ptr = item->next;

        if ( item != NULL ) {
          //free_string( &item->key );        
          free( item );
        }
        

		}

		(*table)[i] = NULL;

	}

  return;

}

