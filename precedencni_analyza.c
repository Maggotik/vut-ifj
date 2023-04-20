/*****************************************************************
* Projekt: Implementace prekladace imperativniho jazyka IFJ20
* Varianta: II
* Tym: 
*
* Soubor: precedencni_analyza.c - zpracovani vyrazu - parser
* Autor: Jiří Václavič, xvacla31
* ***************************************************************/
#include "precedencni_analyza.h"


// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct Stack* firstPush() 
{ 
    struct Stack (*stack) = (struct Stack*)malloc(sizeof(struct Stack));
    if ( stack == NULL ) {
        fprintf( stderr, "Chyba [INTERN]> Chyba alokace paměti! \n" );
        exit( INTERN_ERR );
    }        
    stack->array[0] = (struct Item*)malloc(sizeof(struct Item));
    if ( stack->array[0] == NULL ) {
        fprintf( stderr, "Chyba [INTERN]> Chyba alokace paměti! \n" );
        exit( INTERN_ERR );
    }
    //stack->array[stack->top+1] = (struct Item*)malloc(sizeof(struct Item));
    /*for(int i = 10; i < 10; i++) {
        stack->array[i]->attrib_string = malloc(10*sizeof(char));
    }*/
    stack->capacity = 1;
    stack->top = -1;
    stack->array[++stack->top]->item = STOP;
    //stack->array[0]->item = STOP;    
    //stack->array[0];
    //printf("%c\n", stack->array[0]);
    return stack; 
} 
  

void SInit(struct Stack* stack)
{
    stack->top = -1; 
    stack->capacity = 0;   
} 
// Stack is full when top is equal to the last index 
int Full(struct Stack* stack) 
{     
    return stack->top == stack->capacity - 1; 
} 
  
// Stack is empty when top is equal to -1
int Empty(struct Stack* stack) 
{ 
    return stack->top == -1; 
} 

bool isInteger(double val)
{
    int truncated = (int)val;
    return (val == truncated);
} 
// Function to add an item to stack.  It increases top by 1 
void push(struct Stack* stack, int item, char* item_attrib) 
{ 
    //printf("stack->top %i\n",stack->top);            printf("Stack2: ");
    //struct Item* pom = stack->array[0];
    //realloc(stack->array[stack->top+1],sizeof)
    //printf("POM ITEM1: %i\n",pom->item);
    stack->array[stack->top+1] = (struct Item*)malloc(sizeof(struct Item));
    if(stack->array[stack->top+1] == NULL){
        fprintf( stderr, "Malloc problem!\n");
        exit(INTERN_ERR);
    }
    //stack->array[0]->item = STOP;
    //printf("POM ITEM: %i\n",pom->item);
    //if (Full(stack)) 
        //TODO realokace stacku na stack o +10 kapacite
        //return; 
    stack->array[stack->top+1]->item = item;
    fprintf(stderr,"item-%d\n",item);
    stack->top +=1;
    switch (item)
    {
    case T_INTEGER:
        stack->array[stack->top]->attrib_int = atoi(item_attrib);
        break;
    case T_FLOATING_POINT_DOUBLE:
    case T_FLOATING_POINT_EXPONENT_DOUBLE:
        stack->array[stack->top]->attrib_float = atof(item_attrib);
        break;
    case T_STRING_LITERAL:
        strcpy(stack->array[stack->top]->attrib_string,item_attrib);
        break; 
    case T_IDENTIFIER:
        //KIKI
        if(atof(item_attrib)){
            stack->array[stack->top]->attrib_int = atof(item_attrib);
            stack->array[stack->top]->item = T_FLOATING_POINT_DOUBLE;
        } else if(atoi(item_attrib)){
            stack->array[stack->top]->attrib_float = atoi(item_attrib); 
            stack->array[stack->top]->item = T_INTEGER; 
        } else {
            strcpy(stack->array[stack->top]->attrib_string,item_attrib);
            stack->array[stack->top]->item = T_STRING_LITERAL;
        }
        break;
    default:        
        break;
    }        
    fprintf(stderr,"%i pushed to stack\n", item); 
} 
  
// Function to remove an item from stack.  It decreases top by 1 
//returns next stack item
int pop(struct Stack* stack) 
{ 
    if (!Empty(stack))
        free(stack->array[stack->top]);
        stack->top--;        
        if(stack->top > 0){            
            return stack->array[stack->top]->item; 
        }else{            
            return STOP;
        }

} 
  
// Function to return the top from stack without removing it 
int top(struct Stack* stack) 
{  
    return stack->array[stack->top]->item; 
} 

char precedence_table[7][7] = {
/*                +-   /x  ==  (   )  var  $     */
/*  +-   */      {'>','<','>','<','>','<','>'},
/*  /x   */      {'>','>','>','<','>','<','>'},
/*  ==   */      {'<','<','X','<','>','<','>'},
/*  (    */      {'<','<','<','<','=','<','X'}, //k
/*  )    */      {'>','>','>','X','>','X','>'},
/*  var  */      {'>','>','>','X','>','X','>'}, //k
/*  $    */      {'<','<','<','<','X','<','K'}
};

int get_index( int token_type )
{
 int index;
 //int stack_index;
 switch (token_type)
 {
    case T_ADDITION:
    case T_SUBTRACTION:
        index = 0;
        break;
    case T_MULTIPLICATION:
    case T_DIVISION:
        index = 1;
        break;
    case T_EQUAL_TO:
    case T_NOT_EQUAL_TO:
    case T_GREATER_THAN:
    case T_LESS_THAN:
    case T_GREATER_OR_EQUAL_TO:
    case T_LESS_OR_EQUAL_TO:
        index = 2;
        break;
    case T_LEFT_PARENTHESIS:
        index = 3;
        break;
    case T_RIGHT_PARENTHESIS:
        index = 4;
        break;
    case T_IDENTIFIER:   
    case T_INTEGER:
    case T_FLOATING_POINT_DOUBLE:
    case T_FLOATING_POINT_EXPONENT_DOUBLE:
    case T_STRING_LITERAL:
        index = 5;
        break;
    case T_END_OF_LINE:
    case T_END_OF_FILE:
    case T_LEFT_CURLY_BRACKET:
    case T_SEMICOLON:
    case STOP:
        index = 6;
        break; 
    case E:
        index = 7;
        break;       
    default:
        //CHYBA pri precedencni analyze        
        fprintf( stderr, "ERROR ve funkci get_index!\n");
        exit(SYNTAX_ERR); //doplnit chybovy kod
        break;
 }
 return index;
}

/* Getting indexes into precedence table from stack and input token */
void get_table_index(Token* token, struct Stack* stack, int* input_index, int* stack_index,int* left_shift){

    *input_index = get_index(token->token_type);
    *stack_index = get_index(stack->array[stack->top]->item);
    if(*input_index == 7){
        fprintf( stderr, "Chyba ve funkci get_table_index\n");
        exit(SYNTAX_ERR);
    }
    if(*stack_index == 7){
        *left_shift +=1;
        *stack_index = get_index(stack->array[stack->top-1]->item);
    }
}

char table_value_search(int input_index, int stack_index)
{
    fprintf(stderr,"\ninput-%i stack-%i \n", input_index,stack_index);
    char value = precedence_table[stack_index][input_index];
    if(value == 'X'){
        fprintf( stderr, "Error ve funkci table_value_search\n");
        exit(SYNTAX_ERR);
    }
    fprintf(stderr,"VALUEE: %c\n",value);
    return value;
}

void sub_expr_process( struct Stack* stack, symtable * table, char * key )
{
    for(int i = stack->top; i > 0; i--)
    {
        if(stack->array[i]->item == LEFT_OP)
        {      
            int sub_expr_len = stack->top - i; // zjisteni delky podvyrazu            
            switch (sub_expr_len)
            {
                case 1:
                    // zjisteni zda se jedna o int/double/string
                    if(stack->array[i+1]->item >= 20 && stack->array[i+1]->item <=24 || stack->array[i+1]->item==T_IDENTIFIER){
                        stack->array[i]->type = stack->array[i+1]->item;
                        switch (stack->array[i]->type)
                        {
                            /*case T_IDENTIFIER:
                            ; // debilita jazyka -> deklarace neni statement, ktery zde musi byt jako prvni 
                                item_data * variable;
                                variable = search_item( table, key );
                                if ( variable == NULL && strcmp(key,"")) {
                                    exit(SYNTAX_ERR);
                                } 
                            
                                switch (variable->t_data)
                                {
                                case T_INTEGER:
                                    stack->array[i]->attrib_int = variable->values.integer;
                                    stack->array[i]->type = T_INTEGER;
                                    break;
                                case T_FLOATING_POINT_DOUBLE:
                                case T_FLOATING_POINT_EXPONENT_DOUBLE:
                                    stack->array[i]->attrib_float = variable->values.float_64;
                                    stack->array[i]->type = T_FLOATING_POINT_DOUBLE;
                                    break;
                                case T_STRING_LITERAL:                                 
                                    strcpy(stack->array[i]->attrib_string,variable->values.string);
                                    stack->array[i]->type = T_STRING_LITERAL;
                                    break; 
                                // TODO BOOL                               
                                default:
                                    // ERROR -> neznámý datový typ
                                    break;
                                }
                            

                            break;*/
                        case T_INTEGER:
                            stack->array[i]->attrib_int = stack->array[i+1]->attrib_int;                        
                            break;
                        case T_FLOATING_POINT_DOUBLE:
                        case T_FLOATING_POINT_EXPONENT_DOUBLE:
                            stack->array[i]->attrib_float = stack->array[i+1]->attrib_float;
                            break;
                        default:                    
                            break;
                        }
                    }
                    stack->array[i]->item = E; // E->a vyhodnoceni promenne
                    pop(stack); // pop <
                    //printf("POPPPP\n");
                    break;
                
                case 3:                
                    //char expr_val[] = 
                    expr_eval(stack,i); // a + a , a - a, a * a, a > a
                    break;
                default:
                    fprintf( stderr, "Chyba ve funkci sub_expr_process\n");
                    exit(SYNTAX_ERR);
                    break;
            }
            break;
        }
    }
}

bool check_set_int(int type, int* stack_type){
    if(type == T_INTEGER){
        *stack_type = T_INTEGER;
        return true;
    }else{
        return false;
    }

}
bool check_set_float(int type, int* stack_type){
    if(type == T_FLOATING_POINT_DOUBLE || type == T_FLOATING_POINT_EXPONENT_DOUBLE){
        *stack_type = T_FLOATING_POINT_DOUBLE;
        return true;
    }else{
                fprintf(stderr,"\nTU???\n");
        fprintf(stderr,"\nTU???\n");
        fprintf(stderr,"\nTU???\n");
        fprintf(stderr,"\nTU???\n");
        fprintf(stderr,"\nTU???\n");
        return false;
    }

}
/*
void get_char_value(int operator)
{
    switch (operator)
    {
    case T:
        
        break;
    
    default:
        break;
    }
}*/

void expr_eval(struct Stack* stack,int i)
{    
    struct Item* operand1 = stack->array[i+1];
    struct Item* operand2 = stack->array[i+3];
    struct Item* operator = stack->array[i+2];
    if((operand1->type != operand2->type) || (operand1->type != T_FLOATING_POINT_EXPONENT_DOUBLE && operand2->type == T_FLOATING_POINT_DOUBLE)
        &&(operand2->type != T_FLOATING_POINT_EXPONENT_DOUBLE && operand1->type == T_FLOATING_POINT_DOUBLE)){
        fprintf( stderr, "Error ve funkci expr_eval\n");
        exit(SEM_TYPE_ERR);
        
    }

    switch (operator->item)
    {
    case T_EQUAL_TO:
        if(operand1->attrib_bool == operand2->attrib_bool){            
            stack->array[i]->attrib_bool = true;
        }
        else{
            stack->array[i]->attrib_bool = false;
        }
        stack->array[i]->type = BOOL;
        break;
    case T_NOT_EQUAL_TO:
        if(operand1->attrib_bool != operand2->attrib_bool){            
            stack->array[i]->attrib_bool = true;
        }
        else{
            stack->array[i]->attrib_bool = false;
        }
        stack->array[i]->type = BOOL;
        break;
    case T_GREATER_THAN:
        if(operand1->attrib_bool > operand2->attrib_bool){            
            stack->array[i]->attrib_bool = true;
        }
        else{
            stack->array[i]->attrib_bool = false;
        }
        stack->array[i]->type = BOOL;
        break;  
    case T_LESS_THAN:
        if(operand1->attrib_bool < operand2->attrib_bool){
            stack->array[i]->type = BOOL;
            stack->array[i]->attrib_bool = true;
        }
        else{
            stack->array[i]->attrib_bool = false;
        }
        stack->array[i]->type = BOOL;
        break;
    case T_GREATER_OR_EQUAL_TO:
        if(operand1->attrib_bool >= operand2->attrib_bool){
            stack->array[i]->type = BOOL;
            stack->array[i]->attrib_bool = true;
        }
        else{
            stack->array[i]->attrib_bool = false;
        }
        stack->array[i]->type = BOOL;
        break;                      
    case T_LESS_OR_EQUAL_TO:
        if(operand1->attrib_bool <= operand2->attrib_bool){            
            stack->array[i]->attrib_bool = true;
        }
        else{
            stack->array[i]->attrib_bool = false;
        }
        stack->array[i]->type = BOOL;
        break;
    case T_ADDITION:
        if(operand1->type == T_INTEGER)
        {            
            stack->array[i]->attrib_int = operand1->attrib_int + operand2->attrib_int;
            stack->array[i]->type = T_INTEGER;
        }
        else if (operand1->type == T_FLOATING_POINT_DOUBLE || operand1->type == T_FLOATING_POINT_EXPONENT_DOUBLE)
        {
            stack->array[i]->attrib_float = operand1->attrib_float + operand2->attrib_float;
            stack->array[i]->type = T_FLOATING_POINT_DOUBLE;        
        }
        else if(operand1->type == T_STRING_LITERAL)
        {            
            strcpy(stack->array[i]->attrib_string,operand1->attrib_string);
            strcat(stack->array[i]->attrib_string,operand2->attrib_string);
            stack->array[i]->type = T_STRING_LITERAL;
        }
        else
        {
            printf("typek: %i\n",operand1->type);
            fprintf( stderr, "Error ve funkci expr_eval\n");
            exit(SEM_TYPE_ERR);            
        }
        break;
    case T_SUBTRACTION:
        if(operand1->type == T_INTEGER)
        {
            stack->array[i]->attrib_int = operand1->attrib_int - operand2->attrib_int;
            stack->array[i]->type = T_INTEGER;
        }
        else if (operand1->type == T_FLOATING_POINT_DOUBLE || operand1->type == T_FLOATING_POINT_EXPONENT_DOUBLE)
        {
            stack->array[i]->attrib_float = operand1->attrib_float - operand2->attrib_float;
            stack->array[i]->type = T_FLOATING_POINT_DOUBLE;        
        }
        else
        {
            fprintf( stderr, "Error ve funkci expr_eval\n");
            exit(SEM_TYPE_ERR);            
        } 
        break;
    case T_MULTIPLICATION:       
        if(check_set_int(operand1->type,&(stack->array[i]->type)))
        {
            stack->array[i]->attrib_int = operand1->attrib_int * operand2->attrib_int;
            //stack->array[i]->type = T_INTEGER;
        }
        else if (check_set_float(operand1->type,&(stack->array[i]->type)))
        {
            stack->array[i]->attrib_float = operand1->attrib_float * operand2->attrib_float;
            //stack->array[i]->type = T_FLOATING_POINT_DOUBLE;        
        }
        else
        {
            fprintf( stderr, "Error ve funkci expr_eval\n");
            exit(SEM_TYPE_ERR);           
        } 
        break;
    case T_DIVISION:       
        if(operand1->type == T_INTEGER)
        {
            stack->array[i]->attrib_int = operand1->attrib_int / operand2->attrib_int;
            stack->array[i]->type = T_INTEGER;
        }
        else if (operand1->type == T_FLOATING_POINT_DOUBLE || operand1->type == T_FLOATING_POINT_EXPONENT_DOUBLE)
        {
            stack->array[i]->attrib_float = operand1->attrib_float / operand2->attrib_float;
            stack->array[i]->type = T_FLOATING_POINT_DOUBLE;        
        }
        else
        {
            fprintf( stderr, "Error ve funkci expr_eval\n");
            exit(SEM_TYPE_ERR);           
        } 
        break;        
    default:
        fprintf( stderr, "Error ve funkci expr_eval\n");
        exit(SYNTAX_ERR);
        break;
    }
    stack->array[i]->item = E;
    pop(stack); // pop a
    pop(stack); // pop +
    pop(stack); // pop a
}

void remove_left_OP(struct Stack* stack){
    for(int i = stack->top;i > 0;i--){
        if(stack->array[i]->item == LEFT_OP && stack->array[i+1]->item == T_LEFT_PARENTHESIS){
            free(stack->array[i]);
            free(stack->array[i+1]);
            for(int i2 = i; i < stack->top; i++){
                stack->array[i2] = stack->array[i2+2];
            }
            stack->top -= 2;
            break;
        }
    }
}

bool token_check(Token* token){
    if( (token->token_type == T_END_OF_FILE) || 
        (token->token_type == T_END_OF_LINE) ||
        (token->token_type == T_LEFT_CURLY_BRACKET) ||
        (token->token_type == T_SEMICOLON)
    ){
        return false;
    }
    else{
        return true;
    }
}
bool first_token_check(Token *token){

}
// Main expression-processing function
int precedence_processing( Token * token, symtable * table, char * key ) 
{ 
    fprintf( stderr, "[[%s]]", token->token_attribute );

    // PRIDAL OS
    /*item_data * variable;
    variable = search_item( table, token->token_attribute );
    if ( variable != NULL ) {
        fprintf( stderr, "[[<%d>]]", variable->t_data );
    }

    //insert_data_type( table, key, DATOVY_TYP );
    //set_already_defined( table, key );
    //variable->values.float_64 = vysledek
    
    // PRIDAL OS
    */
    // nacteni zarazky na stack
    struct Stack* stack = firstPush();
    //push(stack,'M');    
    //printf("%d\n", token->token_type);
    int left_shift = 0;
    printf("\nNA VSTUPU JE %i\n",token->token_type);
    if(!token_check(token)){
        printf("\nNA VSTUPU JE EOL\n");
    }
    while(token_check(token))
    {
        // && (stack->top > 0)
        printf("\nKlic1: %s\n",key);
        fprintf(stderr,"Stack: ");
        for(int i = 0;i <= stack->top;i++)
        {
            fprintf(stderr,"%i ",stack->array[i]->item);
        }

        int input_index, stack_index;

        get_table_index(token, stack, &input_index, &stack_index,&left_shift);
        char operation = table_value_search(input_index,stack_index);
        fprintf(stderr,"\n%c\n", operation);
        
        if(operation == '<')
        {
            push(stack, LEFT_OP,"");
            struct Item* pom =  stack->array[stack->top-left_shift];
            stack->array[stack->top-left_shift] = stack->array[stack->top];
            stack->array[stack->top] = pom;
            
            //-----------
            
            if(token->token_type == T_IDENTIFIER){
                //printf("jsem tu doufam\n");
                item_data * variable;
                variable = search_item( table, token->token_attribute );
                if ( variable == NULL && strcmp(key,"")) {
                    exit(SYNTAX_ERR);
                } 
                printf("\nKlic2: %s\n",key);
                char pom_string[99];
                switch (variable->t_data)
                {
                case T_INTEGER:
                    sprintf(pom_string,"%i",variable->values.integer);                     
                    token->token_type = T_INTEGER;
                    break;
                case T_FLOATING_POINT_DOUBLE:
                case T_FLOATING_POINT_EXPONENT_DOUBLE:                    
                    sprintf(pom_string,"%f",variable->values.float_64);
                    token->token_type = T_FLOATING_POINT_DOUBLE;
                    break;
                case T_STRING_LITERAL:                                 
                    strcpy(pom_string,variable->values.string);
                    token->token_type = T_STRING_LITERAL;
                    break; 
                // TODO BOOL                               
                default:
                    printf("jsem tu doufam\n"); 
                    printf("atribut:%s\n",token->token_attribute);
                    // ERROR -> neznámý datový typ proměnné
                    break;
                }
                push(stack,token->token_type,pom_string);                    
            }else{
                printf("ATRIBUT TOKENU: %s\n",token->token_attribute);
                push(stack,token->token_type,token->token_attribute);
            }

            // -----------------------
    
            for(int i = 0;i <= stack->top;i++)
            {
                fprintf(stderr,"%i ",stack->array[i]->item);
            }
            fprintf(stderr,"\n");
            if(token_check(token)){
               get_next_token( token );
               fprintf(stderr, "[[%s]]", token->token_attribute);
           }                        
        }
        else if(operation == '>')
        {                       
            sub_expr_process(stack,table,key); // vyhodnoceni podvyrazu
        }
        else if(operation == '=')
        {
            remove_left_OP(stack);
            if(token_check(token)){
               get_next_token( token );
               fprintf(stderr, "[[%s]]", token->token_attribute);
           } 
        }
        else if(operation == 'K'){
            // OO  
            
            item_data * variable;
            
            variable = search_item( table, key );
            
            if ( variable == NULL && strcmp(key,"")) {                
                exit(SYNTAX_ERR);
            } 
            // OO
            
            switch (stack->array[1]->type)
            {
            case T_INTEGER:                           
                insert_data_type( table, key, T_INTEGER );
                set_already_defined( table, key );
                variable->values.integer = stack->array[1]->attrib_int;
                // OO
                fprintf(stderr,"VYSLEDEK: %i %i\n",variable->values.integer,variable->t_data);
                // OO
                break;
            case T_FLOATING_POINT_DOUBLE:
                insert_data_type( table, key, T_FLOATING_POINT_DOUBLE );
                set_already_defined( table, key );
                variable->values.float_64 = stack->array[1]->attrib_float;
                fprintf(stderr,"VYSLEDEK: %f\n",stack->array[1]->attrib_float);
                break;
            case T_STRING_LITERAL:
                insert_data_type( table, key, T_STRING_LITERAL );
                set_already_defined( table, key );
                variable->values.string = stack->array[1]->attrib_string;
                break;
            case BOOL:
                fprintf(stderr,stack->array[1]->attrib_bool ? "true\n" : "false\n");
                return stack->array[1]->attrib_bool; 
                break;                           
            default:
                break;
            }
            break;
        }
        left_shift = 0;
    }

    return 0; 
}