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
//- 
//- Copyright 2018 Aaron Toney
//- 
//- Redistribution and use in source  and binary forms, with or without
//- modification, are permitted provided  that the following conditions
//- are met:
//- 
//- 1. Redistributions of  source code must retain  the above copyright
//- notice, this list of conditions and the following disclaimer.
//- 
//- 2.  Redistributions  in  binary   form  must  reproduce  the  above
//- copyright  notice,  this  list  of  conditions  and  the  following
//- disclaimer  in the  documentation and/or  other materials  provided
//- with the distribution.
//- 
//- 3. Neither  the name of the  copyright holder nor the  names of its
//- contributors may  be used  to endorse  or promote  products derived
//- from this software without specific prior written permission.
//- 
//- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//- "AS IS" AND  ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING, BUT NOT
//- LIMITED TO,  THE IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS
//- FOR  A PARTICULAR  PURPOSE ARE  DISCLAIMED. IN  NO EVENT  SHALL THE
//- COPYRIGHT  HOLDER  OR  CONTRIBUTORS   BE  LIABLE  FOR  ANY  DIRECT,
//- INDIRECT, INCIDENTAL, SPECIAL,  EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//- (INCLUDING, BUT NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE GOODS OR
//- SERVICES; LOSS OF USE, DATA,  OR PROFITS; OR BUSINESS INTERRUPTION)
//- HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
//- STRICT  LIABILITY,  OR  TORT (INCLUDING  NEGLIGENCE  OR  OTHERWISE)
//- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
//- OF THE POSSIBILITY OF SUCH DAMAGE.
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
