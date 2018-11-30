//------------------------------------------------------------------------------
//- File:   array_queue.c
//- Author: Aaron Toney
//- Date:   Aug 24th, 2018
//- 
//- git repositor: https://github.com/aarontoney/lowmem_microcontroller.git
//- 
//- Description:
//- 
//- Queue overlay for aray_list data structure. Intended as a building block
//- for more complext algorithms on low memory systems without dynamic memory 
//- management tools like malloc. 
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

#include "al_queue.h"
#include "../array_list/array_list.h"

//------------------------------------------------------------------------------
// init
//------------------------------------------------------------------------------

void alq_init( lmm_queue *curStack, unsigned char max_buff_size, char *buff )
{
    lmml_init( (lmm_list *)curStack, max_buff_size, buff );
} 

//------------------------------------------------------------------------------
// clear
//
// Warning: Clear resets all flags, so after it is called any previous error
//          infomation is lost. 
//------------------------------------------------------------------------------

void alq_clear( lmm_queue *curStack ){
    lmml_clear((lmm_list *)curStack );
}

//------------------------------------------------------------------------------
// sec_clear
//
// Clears the stack, including overwriting the underlying buffer sure data is 
// no longer in memory.  
// 
//------------------------------------------------------------------------------

void alq_sec_clear( lmm_queue *curStack ){
    lmml_sec_clear((lmm_list *)curStack );
}

//------------------------------------------------
// push
//------------------------------------------------

void alq_push_back( lmm_queue  *curStack, char newVal ){
    lmml_push_back((lmm_list *)curStack, newVal);
}

//------------------------------------------------
// pop
//------------------------------------------------

char alq_pop_front( lmm_queue  *curStack ){
    return( lmml_pop_front((lmm_list *)curStack) );
}

//------------------------------------------------
// top
//------------------------------------------------

char alq_top( lmm_queue  *curStack ){
    return( lmml_peek_front((lmm_list *)curStack) );
}

//------------------------------------------------
// size
//------------------------------------------------

unsigned char alq_size(lmm_queue  *curStack){
    return( lmml_size((lmm_list *)curStack) );
}

//------------------------------------------------
// isEmpty
//------------------------------------------------

char alq_isEmpty(lmm_queue  *curStack){
    if(lmml_size((lmm_list *)curStack) == 0)
	return(true);
    return(false);
}

