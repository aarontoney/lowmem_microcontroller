//------------------------------------------------------------------------------
//- File:   array_freelist.c
//- Author: Aaron Toney
//- Date:   August 25th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Linked list based implementation of a free list. Using this free list 
//- to provides dynamic memory pool, for use on embedded systems without memory 
//- management kernel primitives like mallor/free. 
//- 
//------------------------------------------------------------------------------

#include "array_linkedlist.h"

// #define DEBUGGING_OUTPUT

#ifdef DEBUGGING_OUTPUT
#include "stdio.h" // remove post debugging - just needed for printf. 
#endif

//---------------------------------------------------------------
// init
//
// Note: Data buffer is supplied via init, since it is assumed 
//       that we dont ahve memory primaties such as malloc or 
//       free.
//---------------------------------------------------------------

void lmmll_init_freelist( lmm_freelist *curFreeList, 
			  unsigned short max_buff_size, 
			  lmm_flcell *buff )
{
    curFreeList->max_size = max_buff_size;

    curFreeList->size     = curFreeList->max_size;
    curFreeList->head     = 0;

    curFreeList->buffer   = buff;

    unsigned char i;  
    for( i=0; i<curFreeList->max_size; i++ ){
	(curFreeList->buffer[i]).next  = i+1;
	(curFreeList->buffer[i]).other  = 0;
	(curFreeList->buffer[i]).val = 0;
    }
    (curFreeList->buffer[ curFreeList->max_size-1 ]).next = FREE_LIST_SENTINEL;
} 

//---------------------------------------------------------------
// lmmll_alloc
//
// Requests a linked list cell from the free list. Notice we are
// being given an index into the free list, and not a pointer, 
// this is the whole point of this implementation.
//
//---------------------------------------------------------------

char lmmll_alloc( lmm_freelist *curFreeList,
		  unsigned char *retCellIndy )
{
    if( curFreeList == (lmm_freelist *)0 ){
	*retCellIndy = 0; 
	return( false );
    }

    if( curFreeList->size == 0){
	*retCellIndy = 0; 
	return( false );
    }

    // size check to implictly provides a ->next != 0 state
    (*retCellIndy) = curFreeList->head;
    curFreeList->head = (curFreeList->buffer[curFreeList->head]).next;
    curFreeList->size--;

    // Zero out the cell before we return it
    (curFreeList->buffer[(*retCellIndy)]).next = FREE_LIST_SENTINEL;
    (curFreeList->buffer[(*retCellIndy)]).other = 0;
    (curFreeList->buffer[(*retCellIndy)]).val = 0;
    
    return( true );
}


//---------------------------------------------------------------
// lmmll_return
//
// Returns an alloced linked list cell from the free list. Not 
// calling it free to avoid confusing people. 
//---------------------------------------------------------------

char lmmll_return( lmm_freelist *curFreeList, 
		   unsigned char retCellIndy )
{
    if( curFreeList == (lmm_freelist *)0 )
	return(false);

    if( curFreeList->size == curFreeList->max_size )  
	return(false);

    (curFreeList->buffer[retCellIndy]).next = curFreeList->head;
    curFreeList->head = retCellIndy;

    (curFreeList->buffer[retCellIndy]).other = 0;
    (curFreeList->buffer[retCellIndy]).val   = 0;

    curFreeList->size++;

    return(true);
}

//------------------------------------------------------------------------------
// size
//------------------------------------------------------------------------------

unsigned char lmmfl_size(lmm_freelist  *curFreeList)
{
    return( curFreeList->size );
}

//------------------------------------------------------------------------------
// isEmpty
//------------------------------------------------------------------------------

char lmmfl_isEmpty(lmm_freelist  *curFreeList)
{
    if( curFreeList->size == 0)
	return( true );
    return( false );
}

//------------------------------------------------------------------------------
// isFull
//------------------------------------------------------------------------------

char lmmfl_isFull(lmm_freelist  *curFreeList)
{
    if( curFreeList->size == curFreeList->max_size )
	return( true );

    return( false );
}

