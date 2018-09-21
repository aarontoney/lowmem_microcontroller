//------------------------------------------------------------------------------
//- File:   array_pqueue.c
//- Author: Aaron Toney
//- Date:   August 29th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Priority queue built atop the low memory microcontroller array_linkedlist
//- package. Insertion is sorted - so worst case O(N), while removing elemnts
//- O(1) as expected. 
//-
//------------------------------------------------------------------------------

#include "all_pqueue.h"

#define DEBUGGING_OUTPUT

#ifdef DEBUGGING_OUTPUT
#include "stdio.h" // remove post debugging - just needed for printf. 
#endif

// is_empty: check whether the queue has no elements.

// insert_with_priority: add an element to the queue with an associated priority.

// pull_highest_priority_element:

//------------------------------------------------------------------------------
// Private Functions
//------------------------------------------------------------------------------

//----------------------------------------------------------
// Function providing default sorting priority
//----------------------------------------------------------
// Comparison function used by partition to create partition
char default_cell_lt( lmm_llcell *c1, lmm_llcell *c2 ){
    if( c1->other < c2->other)
     	return( -1 );

    if( c1->other == c2->other)
	return( 0 );

    return( 1 );
}

char default_cell_gt( lmm_llcell *c1, lmm_llcell *c2 ){
    if( c1->other > c2->other)
     	return( -1 );

    if( c1->other == c2->other)
	return( 0 );

    return( 1 );
}

//------------------------------------------------------------------------------
// init
//------------------------------------------------------------------------------

char lmmpq_init( lmm_pqueue *curPQueue,
		 pqueue_type qtype,
		 pQueueCmpFn comparison_function,
		 lmm_freelist *curFreeList )
{
    if( (curPQueue == 0) || (curFreeList == 0) )
	return( false );

    switch( qtype ){

    case pqueue_other:
	curPQueue->cmpfn = comparison_function;
	break;

    case pqueue_max:
	curPQueue->cmpfn = default_cell_lt;
	break;

    case pqueue_min:
    default:
	curPQueue->cmpfn = default_cell_gt;
	break;
    }

    if(! lmmll_init( &(curPQueue->pqlist), curFreeList ) ){
	return( false );
    }

    return(true);
} 

//------------------------------------------------------------------------------
// size
//------------------------------------------------------------------------------

unsigned char lmmpq_size(lmm_pqueue  *curPQueue)
{
    if( curPQueue == (lmm_pqueue *)0 )
	return(0);

    return( (curPQueue->pqlist).size );
}

//------------------------------------------------------------------------------
// clear
//------------------------------------------------------------------------------

void lmmpq_clear( lmm_pqueue *curPQueue ){
    if( curPQueue == (lmm_pqueue *)0 )
	return;

    lmmll_clear( &(curPQueue->pqlist) );
}

//------------------------------------------------------------------------------
// isEmpty
//------------------------------------------------------------------------------

char lmmpq_isEmpty(lmm_pqueue  *curPQueue)
{
    if( curPQueue == (lmm_pqueue *)0 )
	return( true );

    if( (curPQueue->pqlist).size == 0 )
	return( true );
    return( false );
}

//------------------------------------------------------------------------------
// peek_front
//------------------------------------------------------------------------------

char lmmpq_peek( lmm_pqueue *curPQueue, lmm_llcell *retval )
{
    if( lmmll_peek_front( &(curPQueue->pqlist), retval ) )
	return(true);

    return(false);
}

//------------------------------------------------------------------------------
// contains
//------------------------------------------------------------------------------

char lmmpq_contains( lmm_pqueue *curPQueue, 
  		     unsigned char *pos, unsigned char oval, short sval ){

    if(curPQueue == (lmm_pqueue *)0)
    	return(false);

    if((curPQueue->pqlist).size == 0 ) 
    	return(false);
    
    if( lmmll_contains( &(curPQueue->pqlist), pos, oval, sval ) )
    	return(true);
    
    return( false );
}

//------------------------------------------------------------------------------
// pops with priority - relies on insertions being sorted by priority to maintain
//                      pop_front = pop min/max requirement.
//------------------------------------------------------------------------------

char lmmpq_pop( lmm_pqueue  *curPQueue, lmm_llcell *val ){
    if( curPQueue == (lmm_pqueue *)0 )
	return(false);

    if(!  lmmll_pop_front( &(curPQueue->pqlist)) )
	return(false);

    return( true);
}

//------------------------------------------------------------------------------
// push with priority
//
// Performs a sorted insert into the list based on priority function. More 
// computationally expensive than a min heap, with a tree structure but 
// will use less memory RAM/ROM overall either common code reuse. 
//
// Highest priority items are popped off queue fist, with increasing priority 
// value corresponding to lower queue priority. 0,1,2,...,n is in decreasing
// priority order. 
//
//------------------------------------------------------------------------------

char lmmpq_push( lmm_pqueue  *curPQueue, unsigned char priority, short sval ){
    if( curPQueue == (lmm_pqueue *)0 ){	return(false); }

    //--------------------------------------------------
    // Handle push on an full list
    //--------------------------------------------------

    // NOTE: Shared free list means a list can be both 
    //       empty and full. Empty as it contains no 
    //       nodes, and full as it can not request any 
    //       more nodes. 

    if( lmmll_isFull( &(curPQueue->pqlist)) )
	return(false);

    //--------------------------------------------------
    // Allocate new node to push onto list
    //--------------------------------------------------

// apt debugging .....
//    if(! lmmll_push_front( &(curPQueue->pqlist), priority, sval ) )
    if(! lmmll_push_front( &(curPQueue->pqlist), 1, 9 ) )
	return(false);


    // One element lists are sorted
    if( lmmll_size( &curPQueue->pqlist) == 1 ){
	return( true );
    }

// apt - debugging - with this out elements should post in order. 
//    if( ! lmmll_promote_head( &(curPQueue->pqlist), curPQueue->cmpfn ) )
//	return(false);

    printf("pushed (other: %d)(val: %d)...\r\n", priority, sval );

    return( true );
}


