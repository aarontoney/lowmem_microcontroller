//------------------------------------------------------------------------------
//- File:   array_linkedlist.c
//- Author: Aaron Toney
//- Date:   March 25th, 2018
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

#define DEBUGGING_OUTPUT

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
    curLinkedList->head = 0;

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
// push_front
//------------------------------------------------------------------------------

char lmmll_push_front( lmm_linkedlist  *curLinkedList, char oval, short sval ){

    if( curLinkedList == (lmm_linkedlist *)0 ){
	return(false);
    }

    unsigned char newCellIndy;

    if(! lmmll_alloc( curLinkedList->freelist, &newCellIndy ) )
	return(false);

    // only if there is already data in the list...
    (curLinkedList->buffer[newCellIndy]).next = curLinkedList->head;
    curLinkedList->head = newCellIndy;

    (curLinkedList->buffer[newCellIndy]).other = oval;
    (curLinkedList->buffer[newCellIndy]).val   = sval;

    curLinkedList->size++;

    return(true);
}

//------------------------------------------------------------------------------
// pop_front
//
// Warning - popping clears underflow as well as full flags. 
//------------------------------------------------------------------------------

char lmmll_pop_front( lmm_linkedlist  *curLinkedList, lmm_llcell *val ){
    if( curLinkedList == (lmm_linkedlist *)0 )
	return(false);

    if( lmmll_isEmpty( curLinkedList ) )
	return(false);

    unsigned char curCellIndy = curLinkedList->head;
    curLinkedList->head = (curLinkedList->buffer[curLinkedList->head]).next;
    (*val) = (curLinkedList->buffer[curCellIndy]);

    lmmll_return( curLinkedList->freelist, curCellIndy );
    curLinkedList->size--;
    return(true); 
}

//********************************************************************************
//**************************      Stuff to Add      ******************************
//********************************************************************************

//   //------------------------------------------------------------------------------
//   // push_back
//   //------------------------------------------------------------------------------
//   void lmmll_push_back( lmm_linkedlist  *curLinkedList, char newVal ){ 
//     return(false); 
//   }
//
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
