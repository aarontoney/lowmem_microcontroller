//------------------------------------------------------------------------------
//- File:   test_harness.c
//- Author: Aaron Toney
//- Date:   August 19th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description: Test harness for array_list data structure. .
//- 
//------------------------------------------------------------------------------

#include "array_list.h"
#include "array_list_state.h"
#include "test_harness_helper.h"

#include <stdio.h>

// Needed for rand...
#include <stdlib.h>
#include <time.h>

#define MAX_LIST_SIZE 6
#define BUFFER_LIST_MAXVAL 9

// Used for option_pop to select the option to take...
typedef enum { pop_front, pop_back} pop_op;

// Used for gs_op to select the option to take...
typedef enum { gs_get, gs_set } gs_op;

//--------------------------------------------------------------------
// option_clear
//--------------------------------------------------------------------
void option_clear( lmm_list *curList )
{
    lmml_clear( curList );
}

//--------------------------------------------------------------------
// option_clear
//--------------------------------------------------------------------
void option_sec_clear( lmm_list *curList )
{
    lmml_sec_clear( curList );
}

//--------------------------------------------------------------------
// option_size
//--------------------------------------------------------------------
void option_size( lmm_list *curList )
{
    unsigned char sz = lmml_size( curList );
    printf("\nList size is: %d\r\n", sz);
}

//--------------------------------------------------------------------
// option_peek_front
//--------------------------------------------------------------------

void option_peek_front( lmm_list *curList )
{
    char val = lmml_peek_front( curList );
    printf("\nFront value is: %d\r\n", val);
}

//--------------------------------------------------------------------
// option_peek_back
//--------------------------------------------------------------------

void option_peek_back( lmm_list *curList )
{
    char val = lmml_peek_back( curList );
    printf("\nBack value is: %d\r\n", val);
}



//--------------------------------------------------------------------
// option_push_back
//--------------------------------------------------------------------
void option_push_back( lmm_list *curList )
{
    int number;

    fflush(stdin);
    printf("\nPlease enter the number to push_back: ");
    scanf("%d", &number);
    
    // turn the number to 0..9
    number %= 10;
    lmml_push_back( curList, number);
}

//--------------------------------------------------------------------
// option_gs - tests get set at index
//--------------------------------------------------------------------

void option_gs( lmm_list *curList, gs_op gsoption )
{
    char val;
    int  tmpv;

    unsigned int i;

    printf("\nEnter an index to ");
    switch( gsoption ){
    case gs_get: 
	printf("get: ");
	break;

    case gs_set:
	printf("set: ");
	break;

    default:
	printf("Error in option_gs, invalid get / set operation specified.\r\n");
	return;
	break;
    }
    scanf("%d", &i);

    if( ! inRange( curList, i ) ){
	printf("error - index %d was out of range.\r\n", i );
	return;
    }

    switch( gsoption ){
    case gs_get: 
	if( lmml_get( curList, i, &val ) ){
	    printf("get[%d] has value %d\r\n", (unsigned char)i, val );
	}else{
	    printf("lmml_get failed\r\n");
	}
	break;

    case gs_set:
	printf("\nEnter value to set: ");
	scanf("%d", &tmpv);
	val = (tmpv % 0x1FF);

	if( lmml_set( curList, i, val ) ){
	    printf("set[%d] has value %d\r\n", (unsigned char)i, (unsigned char)val );
	}else{
	    printf("lmml_get failed\r\n");
	}
	break;
    } 

    fflush(stdin);
}

//--------------------------------------------------------------------
// option_swap
//--------------------------------------------------------------------
void option_swap( lmm_list *curList )
{
    unsigned int ta;
    unsigned int tb;

    printf("\nEnter an index to swap from: ");
    scanf("%d", &ta);

    if( ! inRange( curList, ta ) ){
	printf("error - index %d was out of range.\r\n", ta );
	return;
    }

    printf("\nEnter an index to swap from: ");
    scanf("%d", &tb);

    if( ! inRange( curList, tb ) ){
	printf("error - index %d was out of range.\r\n", tb );
	return;
    }

    lmml_swap( curList, 
	       (unsigned char)(ta % 0x1FF), (unsigned char)(tb % 0x1FF) );

}

//--------------------------------------------------------------------
// option_contains
//--------------------------------------------------------------------
void option_contains( lmm_list *curList )
{
    int val;

    if( curList->size == 0 ){
	printf("\nError - list empty. \r\n");
	return;
    }

    printf("\nEnter a value to search the list for:  ");
    scanf("%d", &val);

    if( (val<0)||(val>BUFFER_LIST_MAXVAL) ){
	printf("\nError - val to search for is out of range. \r\n");
	return;
    }

    if( lmml_contains( curList, val ) ){
	printf( "Value %d found in list. \r\n", val );
    }else{
	printf( "Value not found in list. \r\n" );
    }
}


//--------------------------------------------------------------------
// option_pop
//
// used to implement code reuse for pop tests like pop_front, and pop_back
//--------------------------------------------------------------------

void option_pop( lmm_list *curList, pop_op op)
{
    unsigned char oldsz;
    unsigned char sz;

    oldsz = lmml_size( curList );

    switch( op ){
    case pop_front:
	lmml_pop_front(curList);
	break;

    case pop_back:
	lmml_pop_back(curList);
	break;

    default:
	printf("Error in option_pop, invalid pop operation specified.\r\n");
	return;
	break;
    } 

    sz    = lmml_size( curList );

    if( (oldsz == 0 ) && ( oldsz != sz ) ){
	printf("Failed size check after pop on empty list\r\n");
	return;
    }else{
	if( (sz+1) != oldsz ){
	    printf("Failed size check after pop. (%d,%d)\r\n", oldsz, sz);
	    return;
	}
    }

    if( curList->size == 0 ){
	printf("The list is empty.\n");
    }
    
    // No flags should be set if everything is working properly
    print_state_from_flags( curList );
}

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
int main()
{
    char myListBuff[MAX_LIST_SIZE];
    lmm_list myList;
    long int choice;
    char loop = true;
    
    // Seed the random function
    srand(time(NULL));   
    
    lmml_init(&myList, MAX_LIST_SIZE, myListBuff );
    
    printf("\nStarting....\n");
    
    while(loop){
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
	       "\nPlease enter your selection \n",
	       "1. clear\n",
	       "2. sec clear\n",
	       "3. size\n",

	       "4. push_back\n",

	       "5. pop_front\n",
	       "6. pop_back\n",

	       "7. peek_front\n",
	       "8. peek_back\n",

	       "9. lmml_get at index\n",
	       "10. lmml_set at index\n",

	       "11. swap \n",
	       "12. contains \n",

	       "13. quit testing programm\n",
	       "Enter Choice: " );
	
	scanf("%ld",&choice);
	
	switch( choice)
	    {
	    case 1:
		option_clear( &myList );
		break;
		
	    case 2:
		option_sec_clear( &myList );
		break;
		
	    case 3:
		option_size( &myList );
		break;
		
	    case 4:
		option_push_back( &myList );
		break;
		
	    case 5:
		option_pop( &myList, pop_front );
		break;

	    case 6:
		option_pop( &myList, pop_back );
		break;

	    case 7:
		option_peek_front( &myList );
		break;

	    case 8:
		option_peek_back( &myList );
		break;
		
	    case 9:
		option_gs( &myList, gs_get );
		break;

	    case 10:
		option_gs( &myList, gs_set );
		break;

	    case 11:
		option_swap( &myList );
		break;

	    case 12:
		option_contains( &myList );
		break;

	    case 13:
		loop = false;
		break;
		
	    default:
		printf("\nI am afraid that was not one of the listed choices.\n");
		break;
	    }
	
	print_state_from_flags( &myList );
	
	print_buffer( &myList );
	fflush(stdin);
    }

    return(1);
}
