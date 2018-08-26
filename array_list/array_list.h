#ifndef __LMM_ARRAY_LIST_H_
#define __LMM_ARRAY_LIST_H_
//------------------------------------------------------------------------------
//- File:   array_list.h
//- Author: Aaron Toney
//- Date:   Aug 22nd, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Header for implementing an array based list interface. 
//- 
//------------------------------------------------------------------------------

#include "array_list_state.h"

#define true 1
#define false 0

typedef struct lmm_list_t{
    unsigned char max_size;

    unsigned int head;
    unsigned int tail; 

    unsigned char size; 
    unsigned char state;

    char *buffer;
} lmm_list;

//------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------

void lmml_init( lmm_list *curList, unsigned char max_size, char *buffer );
void lmml_clear( lmm_list *curList );
void lmml_sec_clear( lmm_list *curList );

void lmml_push_back( lmm_list  *curList, char newVal );
char lmml_pop_front(lmm_list  *curList); 
char lmml_pop_back(lmm_list  *curList); 

unsigned char lmml_size(lmm_list  *curList);
char lmml_isEmpty(lmm_list  *curList);
char lmml_peek_back( lmm_list *curList );
char lmml_peek_front( lmm_list *curList );


char lmml_get(lmm_list *curList, unsigned char indy, char *ret);
char lmml_set(lmm_list *curList, unsigned char indy, char newVal);

void lmml_swap( lmm_list *curList, unsigned char a, unsigned char b );

char lmml_contains( lmm_list *curList, char val );

// bool lmml_remove_at( lmm_list *curList, unsigned char pos );
// bool lmml_remove_if

// bool lmml_unique   (is unique)
// void lmml_unique   (make unique)

// lmml_sort


//------------------------------------------------------------------------------
#endif
