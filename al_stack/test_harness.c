//------------------------------------------------------------------------------
//- File:   test_harness.c
//- Author: Aaron Toney
//- Date:   August 24th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description: Test harness for stack overlay for array_list data structure. 
//- 
//------------------------------------------------------------------------------

#include "../array_list/array_list.h"
#include "../array_list/test_harness_helper.h"

#include "al_stack.h"

#include <stdio.h>

// Needed for rand...
#include <stdlib.h>
#include <time.h>

#define BUFFER_STACK_MAXVAL 9

//--------------------------------------------------------------------
// option_clear
//--------------------------------------------------------------------
void option_clear( lmm_stack *curStack )
{
    lmml_clear( (lmm_list *)curStack );
}

//--------------------------------------------------------------------
// option_clear
//--------------------------------------------------------------------
void option_sec_clear( lmm_stack *curStack )
{
    lmml_sec_clear( (lmm_list *)curStack );
}

//--------------------------------------------------------------------
// option_size
//--------------------------------------------------------------------
void option_size( lmm_stack *curStack )
{
    unsigned char sz = lmml_size( (lmm_list *)curStack );
    printf("\nList size is: %d\r\n", sz);
}

//--------------------------------------------------------------------
// option_size
//--------------------------------------------------------------------
void option_top( lmm_stack *curStack )
{
    if( curStack->size == 0 ){
	printf("Error peeking top of list - list empty.\r\n");
	return;
    }

    char val = lmml_peek_back( (lmm_list *)curStack );

    printf("\nTop of list has value: %d\r\n", val);
}

//--------------------------------------------------------------------
// option_isEmpty
//--------------------------------------------------------------------
void option_isEmpty( lmm_stack *curStack )
{
    if( lmml_isEmpty(curStack) ){
	printf("List is empty\r\n");
    }else{
	printf("List is not empty\r\n");
    }
}

//--------------------------------------------------------------------
// option_push_back
//--------------------------------------------------------------------
void option_push( lmm_stack *curStack )
{
    int number;

    fflush(stdin);
    printf("\nPlease enter the number to push_back: ");
    scanf("%d", &number);
    
    // turn the number to 0..9
    number %= 10;
    lmml_push_back( (lmm_list *)curStack, number);
}

//--------------------------------------------------------------------
// option_pop 
//--------------------------------------------------------------------

char option_pop( lmm_stack *curStack )
{
    char val = 0;

    // Note: real code would use isEmpty, but that is tested 
    //       elsewhere - so using primitives here. 
    if( curStack->size == 0 ){
	printf("Error in pop - list empty\r\n");

    }else{
	val = als_pop( (lmm_list *) curStack );
    }

    fflush(stdin);
    return(val);
}

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
int main()
{
    char myListBuff[MAX_STACK_SIZE];

    lmm_stack myStack;
    long int choice;
    char loop = true;
    
    // Seed the random function
    srand(time(NULL));   
    
    lmml_init((lmm_list *)&myStack, MAX_STACK_SIZE, myListBuff);
    
    printf("\nStarting....\n");
    
    while(loop){
	printf("%s%s%s%s%s%s%s%s%s%s",
	       "\nPlease enter your selection \n",
	       "1. clear\n",
	       "2. sec clear\n",
	       "3. size\n",

	       "4. push\n",
	       "5. pop\n",

	       "6. top\n",

	       "7. isEmpty\n",

	       "8. quit testing programm\n",
	       "Enter Choice: " );
	
	scanf("%ld",&choice);
	
	switch( choice)
	    {
	    case 1:
		option_clear( &myStack );
		break;
		
	    case 2:
		option_sec_clear( &myStack );
		break;
		
	    case 3:
		option_size( &myStack );
		break;
		
	    case 4:
		option_push( &myStack );
		break;
		
	    case 5:
		option_pop( &myStack );
		break;

	    case 6:
		option_top( &myStack );
		break;
		
	    case 7:
		option_isEmpty( &myStack );
		break;

	    case 8:
		loop = false;
		break;
		
	    default:
		printf("\nI am afraid that was not one of the listed choices.\n");
		break;
	    }
	
	print_state_from_flags( (lmm_list *)&myStack );
	
	print_buffer( (lmm_list *) &myStack );
	fflush(stdin);
    }
    
    return(1);
}
