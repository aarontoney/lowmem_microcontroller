//------------------------------------------------------------------------------
//- File:   array_queue.c
//- Author: Aaron Toney
//- Date:   Aug 24th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Queue overlay for aray_list data structure. Intended as a building block
//- for more complext algorithms on low memory systems without dynamic memory 
//- management tools like malloc. 
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

