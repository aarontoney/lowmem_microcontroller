//------------------------------------------------------------------------------
//- File:   array_linkedlist.c
//- Author: Aaron Toney
//- Date:   August 27th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Array based implementation of a linked list structure. Using an array enables
//- an implemention without pointers, which saves three bytes of RAM per element. 
//-
//- Two list structures are implemented with the same underlying structs. A free
//- list is used to provide dynamic cell allocation for one or more other lists. 
//- This use of a free use is to work arround not having memory primatives 
//- such as malloc / free when implenting dynamic algorithms. 
//- 
//------------------------------------------------------------------------------

#include "array_linkedlist.h"

// #define DEBUGGING_OUTPUT

#ifdef DEBUGGING_OUTPUT
#include "stdio.h" // remove post debugging - just needed for printf. 
#endif

//------------------------------------------------------------------------------
// init
//
// Note: Data buffer is supplied via init, since it is assumed that we dont ahve 
//       memory primaties such as malloc or free.
//------------------------------------------------------------------------------

char lmmll_init( lmm_linkedlist *curLinkedList,
		 lmm_freelist *curFreeList )
{
    if( (curLinkedList == (lmm_linkedlist *)0 ) || 
	(curFreeList == (lmm_freelist *)0 ) )
	return(false);

    curLinkedList->size = 0;
    curLinkedList->head = FREE_LIST_SENTINEL;
    curLinkedList->tail = FREE_LIST_SENTINEL;

    clrAllFlags( curLinkedList );

    curLinkedList->freelist = curFreeList;

    if(curFreeList->buffer == 0)
	return(false);

    // Buffer populated from free list during run time. 
    curLinkedList->buffer = (lmm_llcell *)(curFreeList->buffer);

    return(true);
} 

//------------------------------------------------------------------------------
// clear
//
// Clear walks the list freeing each element, as opposed to clearing the entire
// list in bulk, since a single free list could be used to simultaneously support
// multiple data structures. This way clear only frees up the cells associated 
// with a single of the lists using the free list. 
//------------------------------------------------------------------------------

void lmmll_clear( lmm_linkedlist *curLinkedList ){

    if( curLinkedList == (lmm_linkedlist *)0 )
	return;

    unsigned char curCellIndy;
    while( curLinkedList->size != 0 ){
	curCellIndy = curLinkedList->head;

	curLinkedList->head = (curLinkedList->buffer[curLinkedList->head]).next;

	lmmll_return( curLinkedList->freelist, curCellIndy );
	curLinkedList->size--;
    }

    curLinkedList->tail = FREE_LIST_SENTINEL;
}

//------------------------------------------------------------------------------
// size
//------------------------------------------------------------------------------

unsigned char lmmll_size(lmm_linkedlist  *curLinkedList)
{
    return( curLinkedList->size );
}

//------------------------------------------------------------------------------
// isEmpty
//------------------------------------------------------------------------------

char lmmll_isEmpty(lmm_linkedlist  *curLinkedList)
{
    if( curLinkedList->size == 0 )
	return( true );
    return( false );
}

//------------------------------------------------------------------------------
// isFull
//
// If there are no more additional free nodes in the freelist then the linked
// list is "full". 
//
// Warning: This definition of "empty" and "full" holds across multiple lists 
//          using the same free list so a list could be "empty" and full at the 
//          same time - corresponding to the list being "empty", but there being
//          no available memory in the free list. 
//
//------------------------------------------------------------------------------

char lmmll_isFull(lmm_linkedlist  *curLinkedList)
{
    if( lmmfl_isEmpty( curLinkedList->freelist ) )
	return( true );
    return( false );
}

//------------------------------------------------------------------------------
// peek_front
//------------------------------------------------------------------------------

char lmmll_peek_front( lmm_linkedlist *curLinkedList, lmm_llcell *retval )
{
    if(curLinkedList == (lmm_linkedlist *)0)
	return(false);

    if(curLinkedList->size == 0 ) 
	return(false);

    *retval = (curLinkedList->buffer[curLinkedList->head]);

    return(true);
}

//------------------------------------------------------------------------------
// peek_back
//------------------------------------------------------------------------------

char lmmll_peek_back( lmm_linkedlist *curLinkedList, lmm_llcell *retval )
{
    if(curLinkedList == (lmm_linkedlist *)0)
	return(false);

    if(curLinkedList->size == 0 )
	return(false);

    *retval = (curLinkedList->buffer[curLinkedList->tail]);

    return(true);
}

//------------------------------------------------------------------------------
// contains
//
// Walks list searching for a cell with the value matching sval. It if it 
// found the index of that cell is placed in pos and true is returned. 
// Otherwize false is returned.
//------------------------------------------------------------------------------

char lmmll_contains( lmm_linkedlist *curLinkedList, 
		     unsigned char *pos, char oval, short sval ){

    if(curLinkedList == (lmm_linkedlist *)0)
	return(false);

    if(curLinkedList->size == 0 ) 
	return(false);

    unsigned char curCell;
    unsigned char cnt = 1;

    curCell = curLinkedList->head; 
    do{
	if( ((curLinkedList->buffer[curCell]).val == sval ) &&
	    ((curLinkedList->buffer[curCell]).other == oval )    ){
	    *pos = curCell;
	    return(true);
	}
	curCell = (curLinkedList->buffer[curCell]).next;
    }while( cnt++ < curLinkedList->size );

    return( false );
}

//------------------------------------------------------------------------------
// swap
//
// Note this only swaps the values of the cells, not their relative ordering
// in the list. Its meant as a helper function to higher level sorting 
// algorithms.
//------------------------------------------------------------------------------

char lmmll_swap( lmm_linkedlist *curLinkedList, 
		 lmm_llcell *aPtr, lmm_llcell *bPtr )
{
    if( (curLinkedList == (lmm_linkedlist *)0 ) || 
	(aPtr == (lmm_llcell *)0) ||
	(bPtr   == (lmm_llcell *)0) ){
	return(false);
    }

    unsigned char tmpc;
    short tmps;
    tmpc = aPtr->other;
    aPtr->other = bPtr->other;
    bPtr->other = tmpc;

    tmps = aPtr->val;
    aPtr->val = bPtr->val;
    bPtr->val = tmps;

    return( true ); 
}

//------------------------------------------------------------------------------
// push_front
//
// Note: A push on empty list sets both head and tail. 
//------------------------------------------------------------------------------

char lmmll_push_front( lmm_linkedlist  *curLinkedList, unsigned char oval, short sval ){

    if( curLinkedList == (lmm_linkedlist *)0 ){
	return(false);
    }

    unsigned char newCellIndy;

    if(! lmmll_alloc( curLinkedList->freelist, &newCellIndy ) )
	return(false);

    (curLinkedList->buffer[newCellIndy]).next = curLinkedList->head;
    curLinkedList->head = newCellIndy;

    (curLinkedList->buffer[newCellIndy]).other = oval;
    (curLinkedList->buffer[newCellIndy]).val   = sval;

    if( curLinkedList->size == 0 ){
	curLinkedList->tail = newCellIndy;
    }

    curLinkedList->size++;

    return(true);
}

//------------------------------------------------------------------------------
// pop_front
//------------------------------------------------------------------------------

char lmmll_pop_front( lmm_linkedlist  *curLinkedList ){
    if( curLinkedList == (lmm_linkedlist *)0 )
	return(false);

    if( lmmll_isEmpty( curLinkedList ) )
	return(false);

    unsigned char curCellIndy = curLinkedList->head;
    curLinkedList->head = (curLinkedList->buffer[curLinkedList->head]).next;

    lmmll_return( curLinkedList->freelist, curCellIndy );
    curLinkedList->size--;

    if( curLinkedList->size == 0 ){
	curLinkedList->tail = FREE_LIST_SENTINEL;
    }

    return(true); 
}

//------------------------------------------------------------------------------
// push_back
//------------------------------------------------------------------------------
char lmmll_push_back( lmm_linkedlist  *curLinkedList, unsigned char oval, short sval ){
    if( curLinkedList == (lmm_linkedlist *)0 )
	return(false);

    unsigned char newCellIndy;

    if(! lmmll_alloc( curLinkedList->freelist, &newCellIndy ) )
	return(false);

    (curLinkedList->buffer[ newCellIndy ]).next = FREE_LIST_SENTINEL;
    (curLinkedList->buffer[newCellIndy]).other = oval;
    (curLinkedList->buffer[newCellIndy]).val   = sval;

    if( curLinkedList->size == 0 ){
	curLinkedList->head = newCellIndy;
	curLinkedList->tail = newCellIndy;
    }else{
	(curLinkedList->buffer[ curLinkedList->tail ]).next = newCellIndy;
	curLinkedList->tail = newCellIndy;
    }

    curLinkedList->size++;

    return(true); 
}


//------------------------------------------------------------------------------
// promote_head
//
// Uses the supplied comparison function to promotes the head value to a 
// new place where is is less than or equal to the elements that come before 
// it in the list. 
//
//------------------------------------------------------------------------------

char lmmll_promote_head( lmm_linkedlist *curLinkedList, 
			 lmm_linkedlistCmpFn cmpfn )
{
    if( (curLinkedList == (lmm_linkedlist *)0 ) ||
	( cmpfn == 0) )
	return( false );

    if( curLinkedList->size == 0 )
	return( false );

    if( curLinkedList->size == 1 )
	return( true );

    unsigned char promoteNodeIndy = curLinkedList->head;
    unsigned char curNodeIndy     = (curLinkedList->buffer[ promoteNodeIndy ]).next;
    unsigned char prevNodeIndy    = promoteNodeIndy;

    unsigned char cntdnSz = curLinkedList->size;
    while( ( cntdnSz-- > 1 ) && 
	   (cmpfn( &((curLinkedList->buffer)[ promoteNodeIndy ]), 
		   &((curLinkedList->buffer)[ curNodeIndy ])) <= 0 ) ){

	prevNodeIndy = curNodeIndy;
	curNodeIndy  = ((curLinkedList->buffer)[curNodeIndy]).next;
    }

    if( prevNodeIndy == promoteNodeIndy )
	return(true);

    curLinkedList->head = (curLinkedList->buffer[promoteNodeIndy]).next;
    (curLinkedList->buffer[promoteNodeIndy]).next = (curLinkedList->buffer[prevNodeIndy]).next;
    (curLinkedList->buffer[prevNodeIndy]).next = promoteNodeIndy;    

    return( true );
}


//   //------------------------------------------------------------------------------
//   // find_previous
//   //------------------------------------------------------------------------------
//   
//   char lmmll_find_previous( lmm_linkedlist *curLinkedList, 
//   			  unsigned char searchNodeIndy, 
//   			  unsigned char *prevNodeIndy )
//   {
//       if( curLInkedList == 0 || searchNodeIndy == FREE_LIST_SENTINEL )
//   	return( false ); 
//   
//       *prevNodeInd = prevLinkedList->head;
//       while( (prevNodeIndy != FREE_LIST_SENTINEL)  && 
//   	   ((prevLinkedList->buffer)[prevNodeIndy].next != searchNodeIndy ) ){
//   	prevNodeIndy = (prevLinkedList->buffer)[prevNodeIndy].next;
//       }
//   
//       return( prevNodeIndy );
//   }

//********************************************************************************
//**************************      Stuff to Add      ******************************
//********************************************************************************

//   //------------------------------------------------------------------------------
//   // remove_at
//   //------------------------------------------------------------------------------
//   
//   bool lmmll_remove_at( lmm_linkedlist *curLinkedList, unsigned char pos );
//   
//   //------------------------------------------------------------------------------
//   // get - gets the element at index i, placing its value in ret. If a match cant 
//   // be made it returns false. 
//   //------------------------------------------------------------------------------
//   char lmmll_get( lmm_linkedlist *curLinkedList unsigned char indy, char *ret ){
//   }
//   
//   //------------------------------------------------------------------------------
//   // set - setss the element at index i
//   //------------------------------------------------------------------------------
//   char lmmll_set(lmm_linkedlist *curLinkedList unsigned char indy, char newVal ){
//   }
