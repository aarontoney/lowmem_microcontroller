#ifndef __LMM_ARRAY_STACK_H_
#define __LMM_ARRAY_STACK_H_
//------------------------------------------------------------------------------
//- File:   al_stack.h
//- Author: Aaron Toney
//- Date:   Aug 24nd, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Header for implementing a stack interface on top of the array_listd list
//- data structure. 
//- 
//------------------------------------------------------------------------------

#include "../array_list/array_list.h"

#define true  1
#define false 0

#define MAX_STACK_SIZE 6

// Note: doubble wrapping, as opposed to just redefining, to avoid 
//       scoping and namespace conflict issues. 

typedef lmm_list lmm_stack;

//------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------

void als_init( lmm_stack *curStack, unsigned char max_buff_size, char *buff );
void als_clear( lmm_stack *curStack );
void als_sec_clear( lmm_stack *curStack );
unsigned char als_size(lmm_stack  *curStack);

void als_push( lmm_stack  *curStack, char newVal );
char als_pop( lmm_stack  *curStack );

char als_top( lmm_stack  *curStack );

char als_isEmpty(lmm_stack  *curStack);

//------------------------------------------------------------------------------
#endif
