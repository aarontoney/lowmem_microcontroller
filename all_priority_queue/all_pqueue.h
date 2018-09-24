#ifndef __LMM_ARRAY_PRIORITY_QUEUE_H_
#define __LMM_ARRAY_PRIORITY_QUEUE_H_
//------------------------------------------------------------------------------
//- File:   all_pqueue.h
//- Author: Aaron Toney
//- Date:   September 3rd, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Header for implementing an array_list based priority queue.
//- 
//------------------------------------------------------------------------------

#include "../array_linkedlist/array_linkedlist.h"
#include "../array_linkedlist/array_freelist.h"

#define true 1
#define false 0

// Used for pqueue_type to select the option to take...
typedef enum { pqueue_min, pqueue_max, pqueue_other } pqueue_type;

//------------------------------------------------------------------
// Datastructures
//------------------------------------------------------------------
typedef char (*pQueueCmpFn)(lmm_llcell *, lmm_llcell *); 

typedef struct lmm_pqueue_t {
    lmm_linkedlist pqlist;

    pQueueCmpFn cmpfn;
} lmm_pqueue;

//------------------------------------------------------------------
// Prototypes - Common to both free an linked lists
//------------------------------------------------------------------

char lmmpq_init( lmm_pqueue *curPQueue,
		 pqueue_type qtype,
		 pQueueCmpFn comparison_function,
		 lmm_freelist *curFreeList );

void lmmpq_clear( lmm_pqueue *curPQueue );

unsigned char lmmpq_size(lmm_pqueue  *curPQueue);

char lmmpq_isEmpty(lmm_pqueue  *curPQueue);

char lmmpq_peek( lmm_pqueue *curPQueue, lmm_llcell *retval );

char lmmpq_contains( lmm_pqueue *curPQueue, 
  		     unsigned char *pos, unsigned char oval, short sval );

char lmmpq_push( lmm_pqueue  *curPQueue, unsigned char priority, short sval );

char lmmpq_pop( lmm_pqueue  *curPQueue, lmm_llcell *val );

//------------------------------------------------------------------------------
#endif
