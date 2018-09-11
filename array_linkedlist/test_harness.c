//------------------------------------------------------------------------------
//- File:   test_harness.c
//- Author: Aaron Toney
//- Date:   August 27th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description: Test harness for array_list based linked list data structure. 
//-              Also tests using a free list. 
//-
//------------------------------------------------------------------------------

#include "../array_list/array_list.h"
#include "../array_list/array_list_state.h"
#include "test_harness_helper.h"

#include "array_freelist.h"
#include "array_linkedlist.h"

#include <stdio.h>

// Needed for rand...
#include <stdlib.h>
#include <time.h>

#define MAX_LIST_SIZE 6
#define BUFFER_LIST_MAXVAL 9

#define FREE_LIST_BUFF_SIZE 100

// Used for option_pop to select the option to take...
typedef enum { pop_front, pop_back} pop_op;

// Used for gs_op to select the option to take...
typedef enum { gs_get, gs_set } gs_op;

//--------------------------------------------------------------------
// option_clear
//--------------------------------------------------------------------
void option_clear( lmm_linkedlist *curList )
{
    lmmll_clear( curList );
}

//--------------------------------------------------------------------
// option_size
//--------------------------------------------------------------------
void option_size( lmm_linkedlist *curList )
{
    unsigned char sz = lmmll_size( curList );
    printf("\nList size is: %d\r\n", sz);
}

//--------------------------------------------------------------------
// option_isEmpty
//--------------------------------------------------------------------
void option_isEmpty( lmm_linkedlist *curList )
{
    if( lmmll_isEmpty( curList ) ){
	printf("\nLinkedlist is empty\r\n");
    }else{
	printf("\nLinkedlist is not empty\r\n");
    }
}

//--------------------------------------------------------------------
// option_isFull
//--------------------------------------------------------------------
void option_isFull( lmm_linkedlist *curList )
{
    if( lmmll_isFull( curList ) ){
	printf("\nLinkedlist is full\r\n");
    }else{
	printf("\nLinkedlist is not full\r\n");
    }
}

//--------------------------------------------------------------------
// option_peek_front
//--------------------------------------------------------------------

void option_peek_front( lmm_linkedlist *curList )
{
    lmm_llcell peekval;

    if( lmmll_peek_front( curList, &peekval )){
	printf("\nFront value is: %d\r\n", peekval.val );	
    }else{
	printf("\nFailed to peek at the front of the list.\r\n");
    }
}

//--------------------------------------------------------------------
// option_peek_back
//--------------------------------------------------------------------

void option_peek_back( lmm_linkedlist *curList )
{
    lmm_llcell peekval;

    if( lmmll_peek_back( curList, &peekval )){
	printf("\nBack value is: %d\r\n", peekval.val );	
    }else{
	printf("\nFailed to peek at the back of the list.\r\n");
    }
}

//--------------------------------------------------------------------
// option_push_front
//--------------------------------------------------------------------
void option_push_front( lmm_linkedlist *curLinkedList )
{
    int number;
    
    fflush(stdin);
    printf("\nPlease enter the number to push_front: ");
    scanf("%d", &number);
    
    // turn the number to 0..9
    number %= 10;

    // Add code pushing number to the back of the list here
    if( ! lmmll_push_front( curLinkedList, 0, ((short)number)) ){
	printf("Error pushing value to front of the list...\r\n");
    }
}

//--------------------------------------------------------------------
// option_push_back
//--------------------------------------------------------------------
void option_push_back( lmm_linkedlist *curLinkedList )
{
    int number;
    
    fflush(stdin);
    printf("\nPlease enter the number to push_back: ");
    scanf("%d", &number);
    
    // turn the number to 0..9
    number %= 10;

    // Add code pushing number to the back of the list here
    if( ! lmmll_push_back( curLinkedList, 0, ((short)number)) ){
	printf("Error pushing value to back of the list...\r\n");
    }
}

//--------------------------------------------------------------------
// option_contains
//--------------------------------------------------------------------
void option_contains( lmm_linkedlist *curList )
{
    int val;
    unsigned char pos;

    if( curList->size == 0 ){
	printf("\nError - list empty. \r\n");
	return;
    }

    printf("\nEnter a value to search the list for:  ");
    scanf("%d", &val);

    if( (val<0)||(val>FREE_LIST_BUFF_SIZE) ){
	printf("\nError - val to search for is out of range. \r\n");
	return;
    }

    if( lmmll_contains( curList, &pos, 0, (short)val ) ){
	printf( "Value %d found in list at postion %d. \r\n", val, pos );
    }else{
	printf( "Value not found in list. \r\n" );
    }
}



//--------------------------------------------------------------------
// option_pop
//
// used to implement code reuse for pop tests like pop_front, and pop_back
//--------------------------------------------------------------------

void option_pop( lmm_linkedlist *curLinkedList, pop_op op)
{
    lmm_llcell val;

    switch( op ){
    case pop_front:
	lmmll_pop_front(curLinkedList, &val);
	break;

//    case pop_back:
//	lmmll_pop_back(curLinkedList);
//	break;

    default:
	printf("Error in option_pop, invalid pop operation specified.\r\n");
	return;
	break;
    } 

}


//--------------------------------------------------------------------
// option_promote_head
//
// used to implement code reuse for pop tests like pop_front, and pop_back
//--------------------------------------------------------------------

// Comparison function used by partition to create partition
char cmp_altb( lmm_llcell *c1, lmm_llcell *c2 ){
    if( c1->val < c2->val)
     	return( -1 );

    if( c1->val == c2->val)
	return( 0 );

    return( 1 );
}

char option_promote_head( lmm_linkedlist *curLinkedList ) 
{
    if( ! lmmll_promote_head( curLinkedList, cmp_altb ) )
	return(false);

    return(true);
}

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------

int main()
{
    //--------------------------------------------------
    // Create a free list
    //--------------------------------------------------
    lmm_freelist myFreeList;
    lmm_flcell myFreeListBuff[FREE_LIST_BUFF_SIZE];

    lmmll_init_freelist( &myFreeList,
			 FREE_LIST_BUFF_SIZE, myFreeListBuff );

    //--------------------------------------------------
    // Create Linked List
    //--------------------------------------------------
    lmm_linkedlist curLinkedList;
    if(! lmmll_init( &curLinkedList, &myFreeList ) ){
	printf("Error initilizing the linked list.\r\n");
	printf("Exiting...\r\n");
	return(0);
    }

    //--------------------------------------------------
    // 
    //--------------------------------------------------

    lmm_flcell myListBuff[MAX_LIST_SIZE];

    lmm_linkedlist myLinkedList;
    long int choice;
    char loop = true;
    
    // Seed the random function
    srand(time(NULL));   
    
    lmmll_init_freelist( &myFreeList,
			 MAX_LIST_SIZE,
			 myListBuff );

    lmmll_init(&myLinkedList, &myFreeList);

    printf("\nStarting....\n");
    
    while(loop){
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
	       "\nPlease enter your selection \n",
	       "1. clear\n",
	       "2. size\n",
	       "3. isEmpty\n",
	       "4. isFull\n",

	       "5. push_front\n",
	       "6. push_back\n",
	       "7. pop_front\n",

	       "8. peek_front\n",
	       "9. peek_back\n",
	       "10. contains \n",
	       "11. promote head \n",

//  Operations on back of the list, and get/set at expensive for sll
//	       ". pop_back\n",
//	       ". lmmll_get at index\n",
//	       ". lmmll_set at index\n",
//	       ". option_peek_back",

	       "12. Exit...\n",

	       "Enter Choice: " );
	
	scanf("%ld",&choice);
	
	switch( choice)
	    {
	    case 1:
		option_clear( &myLinkedList );
		break;
		
	    case 2:
		option_size( &myLinkedList );
		break;
		
	    case 3:
		option_isEmpty( &myLinkedList );
		break;

	    case 4:
		option_isFull( &myLinkedList );
		break;

	    case 5:
		option_push_front( &myLinkedList );
		break;

	    case 6:
		option_push_back( &myLinkedList );
		break;

	    case 7:
		option_pop( &myLinkedList, pop_front );
		break;

	    case 8:
		option_peek_front( &myLinkedList );
		break;

	    case 9:
		option_peek_back( &myLinkedList );
		break;

//	    case :
//		option_gs( &myLinkedList, gs_get );
//		break;
//
//	    case :
//		option_gs( &myLinkedList, gs_set );
//		break;

	    case 10:
		option_contains( &myLinkedList );
		break;

	    case 11:
		option_promote_head( &myLinkedList );
		break;

	    case 12:
		loop = false;
		break;
		
	    default:
		printf("\nI am afraid that was not one of the listed choices.\n");
		break;
	    }
	
	print_state_from_ll_flags( &myLinkedList );
	
	print_ll_buffer( &myLinkedList );
	fflush(stdin);
    }

    return(1);
}
