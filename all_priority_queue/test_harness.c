//------------------------------------------------------------------------------
//- File:   test_harness.c
//- Author: Aaron Toney
//- Date:   September 3rd, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description: Test harness for array_list based priority queue.
//-
//------------------------------------------------------------------------------

#include "../array_list/array_list.h"
#include "../array_list/array_list_state.h"
#include "test_harness_helper.h"

#include "../array_linkedlist/array_freelist.h"
#include "../array_linkedlist/array_linkedlist.h"

#include "all_pqueue.h"

#include <stdio.h>

// Needed for rand...
#include <stdlib.h>
#include <time.h>

#define MAX_LIST_SIZE 9
#define BUFFER_LIST_MAXVAL 9

#define FREE_LIST_BUFF_SIZE 100

// Used for option_pop to select the option to take...
typedef enum { pop_front, pop_back} pop_op;

// Used for gs_op to select the option to take...
typedef enum { gs_get, gs_set } gs_op;

//--------------------------------------------------------------------
// option_clear
//--------------------------------------------------------------------
void option_clear( lmm_pqueue *curPQueue )
{
    lmmpq_clear( curPQueue );
}

//--------------------------------------------------------------------
// option_size
//--------------------------------------------------------------------
void option_size( lmm_pqueue *curPQueue )
{
    unsigned char sz = lmmpq_size( curPQueue );
    printf("\nList size is: %d\r\n", sz);
}

//--------------------------------------------------------------------
// option_isEmpty
//--------------------------------------------------------------------
void option_isEmpty( lmm_pqueue *curPQueue )
{
    if( lmmpq_isEmpty( curPQueue ) ){
	printf("\npriority queue is empty\r\n");
    }else{
	printf("\npriority queue is not empty\r\n");
    }
}

//--------------------------------------------------------------------
// option_peek_front
//--------------------------------------------------------------------

void option_peek_front( lmm_pqueue *curPQueue )
{
    lmm_llcell peekval;

    if( lmmpq_peek( curPQueue, &peekval )){
	printf("\nFront value is: %d\r\n", peekval.val );	
    }else{
	printf("\nFailed to peek at the front of the pqueue.\r\n");
    }
}

//--------------------------------------------------------------------
// option_push
//--------------------------------------------------------------------
void option_push( lmm_pqueue *curLinkedList )
{
    int number;
    
    fflush(stdin);
    printf("\nPlease enter the number to push: ");
    scanf("%d", &number);
    
    // turn the number to 0..9
    number %= 10;

    // Add code pushing number to the back of the list here
    if( ! lmmpq_push( curLinkedList, ((short)number), ((short)number)) ){
	printf("Error pushing value to front of the queue...\r\n");
    }
}

//--------------------------------------------------------------------
// option_contains
//--------------------------------------------------------------------
void option_contains( lmm_pqueue *curPQueue )
{
    int val;
    unsigned char pos;

    if( lmmpq_isEmpty(curPQueue) ){
	printf("\nError - pqueue empty. \r\n");
	return;
    }

    printf("\nEnter a value to search the queue for:  ");
    scanf("%d", &val);

    if( (val<0)||(val>FREE_LIST_BUFF_SIZE) ){
	printf("\nError - val to search for is out of range. \r\n");
	return;
    }

    if( lmmpq_contains( curPQueue, &pos, 0, (short)val ) ){
	// Should always be at the head - doing it this way for debugging. 
	printf( "Value %d found in queue at postion %d. \r\n", val, pos );
    }else{
	printf( "Value not found in priority queue. \r\n" );
    }
}

//--------------------------------------------------------------------
// option_pop
//
// used to implement code reuse for pop tests like pop_front, and 
// pop_back
//--------------------------------------------------------------------

void option_pop( lmm_pqueue *curPQueue, pop_op op)
{
    lmm_llcell val;

    switch( op ){
    case pop_front:
	lmmpq_pop(curPQueue, &val);
	break;

//    case pop_back:
//	lmmll_pop_back(curPQueue);
//	break;

    default:
	printf("Error in option_pop, invalid pop operation specified.\r\n");
	return;
	break;
    } 

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
    // Create priority queue
    //--------------------------------------------------
    lmm_pqueue myPQueue;

    if(! lmmpq_init( &myPQueue, pqueue_max, ((pQueueCmpFn) 0), &myFreeList ) ){
	printf("Error initilizing the priority queue.\r\n");
	printf("Exiting...\r\n");
	return(0);
    }

    //--------------------------------------------------
    // 
    //--------------------------------------------------
    lmm_flcell myListBuff[MAX_LIST_SIZE];

    long int choice;
    char loop = true;
    
    // Seed the random function
    srand(time(NULL));   
    
    lmmll_init_freelist( &myFreeList,
			 MAX_LIST_SIZE,
			 myListBuff );

    printf("\nStarting....\n");
    
    while(loop){
	printf("%s%s%s%s%s%s%s%s%s%s",
	       "\nPlease enter your selection \n",
	       "1. clear\n",
	       "2. size\n",
	       "3. isEmpty\n",

	       "4. push_front\n",
	       "5. pop_front\n",

	       "6. peek_front\n",

	       "7. contains \n",

	       "8. Exit...\n",

	       "Enter Choice: " );
	
	scanf("%ld",&choice);
	
	switch( choice)
	    {
	    case 1:
		option_clear( &myPQueue );
		break;
		
	    case 2:
		option_size( &myPQueue );
		break;
		
	    case 3:
		option_isEmpty( &myPQueue );
		break;

	    case 4:
		option_push( &myPQueue );
		break;

	    case 5:
		option_pop( &myPQueue, pop_front );
		break;

	    case 6:
		option_peek_front( &myPQueue );
		break;

//	    case :
//		option_gs( &myPQueue, gs_get );
//		break;
//
//	    case :
//		option_gs( &myPQueue, gs_set );
//		break;

	    case 7:
		option_contains( &myPQueue );
		break;

	    case 8:
		loop = false;
		break;
		
	    default:
		printf("\nI am afraid that was not one of the listed choices.\n");
		break;
	    }
	
	print_state_from_ll_flags( &(myPQueue.pqlist) );
	
	print_ll_buffer( &(myPQueue.pqlist) );
	fflush(stdin);
    }

    return(1);
}
