//------------------------------------------------------------------------------
//- File:   array_list.c
//- Author: Aaron Toney
//- Date:   Aug 24th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Stack overlay for aray_list data structure. Intended as a building block
//- for more complext algorithms on low memory systems without dynamic memory 
//- management tools like malloc. 
//-
//------------------------------------------------------------------------------

#include "al_stack.h"
#include "../array_list/array_list.h"

//------------------------------------------------------------------------------
// init
//------------------------------------------------------------------------------

void als_init( lmm_stack *curStack, unsigned char max_buff_size, char *buff )
{
    lmml_init( (lmm_list *)curStack, max_buff_size, buff );
} 

//------------------------------------------------------------------------------
// clear
//
// Warning: Clear resets all flags, so after it is called any previous error
//          infomation is lost. 
//------------------------------------------------------------------------------

void als_clear( lmm_stack *curStack ){
    lmml_clear((lmm_list *)curStack );
}

//------------------------------------------------------------------------------
// sec_clear
//
// Clears the stack, including overwriting the underlying buffer sure data is 
// no longer in memory.  
// 
//------------------------------------------------------------------------------

void als_sec_clear( lmm_stack *curStack ){
    lmml_sec_clear((lmm_list *)curStack );
}

//------------------------------------------------
// push
//------------------------------------------------

void als_push( lmm_stack  *curStack, char newVal ){
    lmml_push_back((lmm_list *)curStack, newVal);
}

//------------------------------------------------
// pop
//------------------------------------------------

char als_pop( lmm_stack  *curStack ){
    return( lmml_pop_back((lmm_list *)curStack) );
}

//------------------------------------------------
// top
//------------------------------------------------

char als_top( lmm_stack  *curStack ){
    return( lmml_peek_back((lmm_list *)curStack) );
}

//------------------------------------------------
// size
//------------------------------------------------

unsigned char als_size(lmm_stack  *curStack)
{
    return( lmml_size((lmm_list *)curStack) );
}

//------------------------------------------------
// isEmpty
//------------------------------------------------

char als_isEmpty(lmm_stack  *curStack)
{
    if(lmml_size((lmm_list *)curStack) == 0)
	return(true);
    return(false);
}

