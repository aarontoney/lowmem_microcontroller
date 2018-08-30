#ifndef __LMM_ARRAY_LINKED_LIST_H_
#define __LMM_ARRAY_LINKED_LIST_H_
//------------------------------------------------------------------------------
//- File:   array_linkedlist.h
//- Author: Aaron Toney
//- Date:   Aug 25nd, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Header for implementing an array based linked list.
//- 
//------------------------------------------------------------------------------

#include "../array_list/array_list_state.h"
#include "array_freelist.h"

#define true 1
#define false 0

//------------------------------------------------------------------
// Datastructures
//------------------------------------------------------------------

typedef struct lmm_linkedlist_cell_t {
    unsigned char next;
    unsigned char other; 
    short int val; 
} lmm_llcell;

typedef struct lmm_linkedlist_t {
    unsigned char size; 

    unsigned char head;

    unsigned char state;
    lmm_freelist *freelist;
    struct lmm_linkedlist_cell_t *buffer;
} lmm_linkedlist;

//------------------------------------------------------------------
// Prototypes - Common to both free an linked lists
//------------------------------------------------------------------

char lmmll_init( lmm_linkedlist *curLinkedList,
		 lmm_freelist *curFreeList );

void lmmll_clear( lmm_linkedlist *curLinkedList );
unsigned char lmmll_size(lmm_linkedlist  *curLinkedList );
char lmmll_isEmpty(lmm_linkedlist  *curLinkedList );

char lmmll_peek_front( lmm_linkedlist *curLinkedList, lmm_llcell *retval );

char lmmll_contains( lmm_linkedlist *curLinkedList, 
		     unsigned char *pos, char oval, short sval );

//------------------------------------------------------------------
// Prototypes - LinkedList
//------------------------------------------------------------------
char lmmll_push_front( lmm_linkedlist  *curLinkedList, char oval, short sval );

//  void lmmll_push_back( lmm_linkedlist  *curLinkedList, char newVal );
char lmmll_pop_front( lmm_linkedlist  *curLinkedList, lmm_llcell *val );

char lmmll_remove_at( lmm_linkedlist *curLinkedList, unsigned char pos );


//------------------------------------------------------------------------------
#endif
