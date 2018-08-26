#ifndef __LMM_ARRAY_STACK_H_
#define __LMM_ARRAY_STACK_H_
//------------------------------------------------------------------------------
//- File:   al_queue.h
//- Author: Aaron Toney
//- Date:   Aug 25th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Header for implementing a queue interface on top of the array_listd list
//- data structure. 
//- 
//------------------------------------------------------------------------------

#include "../array_list/array_list.h"

#define true  1
#define false 0

#define MAX_STACK_SIZE 6

// Note: doubble wrapping, as opposed to just redefining, to avoid 
//       scoping and namespace conflict issues. 

typedef lmm_list lmm_queue;

//------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------

void alq_init( lmm_queue *curStack, unsigned char max_buff_size, char *buff );
void alq_clear( lmm_queue *curStack );
void alq_sec_clear( lmm_queue *curStack );
unsigned char alq_size(lmm_queue  *curStack);

void alq_push_back( lmm_queue  *curStack, char newVal );
char alq_pop_front( lmm_queue  *curStack );

char alq_top( lmm_queue  *curStack );

char alq_isEmpty(lmm_queue  *curStack);

//------------------------------------------------------------------------------
#endif
