#ifndef __LMM_ARRAY_STACK_H_
#define __LMM_ARRAY_STACK_H_
//------------------------------------------------------------------------------
//- File:   al_queue.h
//- Author: Aaron Toney
//- Date:   Aug 25th, 2018
//- 
//- git repositor: https://github.com/aarontoney/lowmem_microcontroller.git
//- 
//- Description:
//- 
//- Header for implementing a queue interface on top of the array_listd list
//- data structure. 
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
