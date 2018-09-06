#ifndef __LMM_TESTHARNESS_HELPER_H_
#define __LMM_TESTHARNESS_HELPER_H_
//------------------------------------------------------------------------------
//- File:   array_list.h
//- Author: Aaron Toney
//- Date:   Aug 24nd, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Header for helper functions implementing a test harness for data structures
//- derived from array list data sructure. 
//- 
//------------------------------------------------------------------------------

#include "../array_list/array_list.h"
#include "../array_list/array_list_state.h"

#include "../array_linkedlist/array_linkedlist.h"

#include <stdio.h>

// Needed for rand...
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------

char inRange( lmm_list *curList, unsigned char i );

void print_buffer( lmm_list *curList );
void print_ll_buffer( lmm_linkedlist *curList );

void print_state_from_flags( lmm_list *curList );
void print_state_from_ll_flags( lmm_linkedlist *curList );
void fill_buffer_with_rand_values( lmm_list *curList, unsigned char bmaxval );

//------------------------------------------------------------------------------
#endif
