//------------------------------------------------------------------------------
//- File:   array_list.c
//- Author: Aaron Toney
//- Date:   August 22nd, 2018
//-
//- git repositor: https://github.com/aarontoney/lowmem_microcontroller.git
//- 
//- Description:
//- ------------
//- 
//- Common building blocks for more complex algorithms on low memory 
//- systems management tools like malloc.
//-
//- An array based implementation enables heap or stack based allocation. 
//- Main drawback is that it has array O(n) times for deletion, insertion,
//- and search. 
//-
//- Implementation:
//- ---------------
//-
//- The list uses zero based indexing. The internal head and tail values 
//- correspond to indexes for the first element, and one past the last 
//- element respectivly. 
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

#include "array_list.h"

//------------------------------------------------------------------------------
// "Private" Functions
//
// While C does not support private scoping, by having the private functions
// declared at the top of this file, and not prototyped in the header file the
// functions only have local scope. This is intentional. DO NOT ADD ANY OF THE 
// _private_ named functions to the header file prototypes. 
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// private_getindex
// 
// A "private" helper function that takes a list index and fetches the underlying
// array buffer element index. Returns true if a sucessfull mapping was able to
// be made and a valid value returned, false otherwise. 
//
// NOTE: This function is implicitly checkign validity of index value
//------------------------------------------------------------------------------

char lmml_private_getindex( lmm_list *curList, 
 			    unsigned char indy, unsigned char *bindy )
{
    if( (curList->size == 0 ) || (curList->size > curList->max_size ))
 	return(false);
    
    *bindy = (curList->head + indy);
    if( *bindy > curList->max_size ){
	*bindy = (*bindy % (curList->max_size));
    }

    return(true);
}

//------------------------------------------------------------------------------
// "Private" Functions
//
// Back to "public" functions - everthing below this point should be prototyped
// in the header file. 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// init
//
// Note: Data buffer is supplied via init, since it is assumed that we dont ahve 
//       memory primaties such as malloc or free.
//------------------------------------------------------------------------------

void lmml_init( lmm_list *curList, unsigned char max_buff_size, char *buff )
{
    curList->buffer = buff;
    curList->max_size = max_buff_size;

    // The list is empty on startup
    lmml_clear( curList );
} 

//------------------------------------------------------------------------------
// clear
//
// Warning: Clear resets all flags, so after it is called any previous error
//          infomation is lost. 
//------------------------------------------------------------------------------

void lmml_clear( lmm_list *curList ){
    curList->head = 0;
    curList->tail = 0;
    curList->size = 0;

    clrAllFlags(curList);
}

//------------------------------------------------------------------------------
// lmml_sec_clear
//
// Clears the list, then overwrites the underlying buffer sure data is no longer
// in memory.  
// 
//------------------------------------------------------------------------------

void lmml_sec_clear( lmm_list *curList ) 
{
    lmml_clear( curList );

    for( int i=0; i<curList->max_size; i++ ){
	curList->buffer[i] = 0;
    }
}

//------------------------------------------------------------------------------
// push_back
//------------------------------------------------------------------------------

void lmml_push_back( lmm_list  *curList, char newVal )
{

    if( curList->size == curList->max_size ){
	setOverflow( curList );
	return;
    }

    curList->buffer[curList->tail] = newVal;
    (curList->tail)++;

    if( curList->tail == curList->max_size ){
	(curList->tail) = 0; 
    }

    curList->size++;
}


//------------------------------------------------------------------------------
// pop_back
//
// Warning - popping clears underflow as well as full flags. 
//
// Currently working here - adding so array_list can be efficently used to
// implement both stacks and queues. 
//
//------------------------------------------------------------------------------

char lmml_pop_back(lmm_list  *curList){
  char retChar = 0;

  clrOverflow(curList);

  if(curList->size == 0){
      setUnderflow(curList);
      return(retChar);
  }

  if( curList->tail == 0 ){
      curList->tail = (curList->max_size-1);
  }else{
      curList->tail--;
  }
  retChar = curList->buffer[curList->tail];

  curList->size--;
  return(retChar);
}

//------------------------------------------------------------------------------
// pop_front
//
// Warning - popping clears underflow as well as full flags. 
//------------------------------------------------------------------------------

char lmml_pop_front(lmm_list  *curList){
  char retChar = 0;

  clrOverflow(curList);

  if(curList->size == 0){
      setUnderflow(curList);
      return(retChar);
  }

  retChar = curList->buffer[curList->head];

  curList->head++;
  if( curList->head == curList->max_size ) {
      curList->head = 0;
  }

  curList->size--;
  return(retChar);
}

//------------------------------------------------------------------------------
// size
//------------------------------------------------------------------------------

unsigned char lmml_size(lmm_list  *curList)
{
    return( curList->size );
}

//------------------------------------------------------------------------------
// isEmpty
//------------------------------------------------------------------------------

char lmml_isEmpty(lmm_list  *curList)
{
    if( curList->size == 0)
	return( true );
    return( false );
}

//------------------------------------------------------------------------------
// peek_back
//------------------------------------------------------------------------------

char lmml_peek_back( lmm_list *curList )
{
    if( curList->tail == 0 ){
	return(  curList->buffer[(curList->max_size-1)] );
    }else{
	return(  curList->buffer[(curList->tail-1)] );
    }
}

//------------------------------------------------------------------------------
// peek_front
//------------------------------------------------------------------------------

char lmml_peek_front( lmm_list *curList )
{
    return( curList->buffer[curList->head] );
}


//  //-------------------------------------------------------------------------
//  // Tests if an index is in range for the list
//  //-------------------------------------------------------------------------
//  bool lmml_index_valid(lmm_list *curList, unsigned char indy){
//      if( curList->size == 0  )
//  	return(false);
//  
//      unsigned char cs = lmml_size(curList);
//      if( (cs < (a-1)) || (cs < (b-1)) ){
//  	return(false);
//      } 
//  
//      return(true);
//  }

//------------------------------------------------------------------------------
// get - gets the element at index i, placing its value in ret. If a match cant 
// be made it returns false. 
//------------------------------------------------------------------------------

char lmml_get( lmm_list *curList, unsigned char indy, char *ret ){
     unsigned char elementIndy; 
     if(! lmml_private_getindex( curList, indy, &elementIndy ) ){
 	return(false);
     }
     
     *ret = curList->buffer[elementIndy];
     return(true); 
 }

//------------------------------------------------------------------------------
// set - setss the element at index i
//------------------------------------------------------------------------------

char lmml_set(lmm_list *curList, unsigned char indy, char newVal ){
    unsigned char elementIndy; 
    if(! lmml_private_getindex( curList, indy, &elementIndy ) ){
 	return(false);
    }
    
    curList->buffer[elementIndy] = newVal;
    return(true); 
}

//------------------------------------------------------------------------------
// lmml_wap 
//
// Swaps values at index a and b. If indexes a or b dont exsist in the list
// return is false. 
//
// WARNING: This implemnation is slow requiring two function calls. If 
//          developing an algorithm using swap frequently this sould be 
//          optimized. 
//------------------------------------------------------------------------------

void lmml_swap( lmm_list *curList, unsigned char a, unsigned char b ){
    unsigned char ai;
    unsigned char bi;
    
    if(! lmml_private_getindex( curList, a, &ai ) ){
 	return;
    }
    
    if(! lmml_private_getindex( curList, b, &bi ) ){
 	return;
    }
    
    char tmp = curList->buffer[ai];
    curList->buffer[ai] = curList->buffer[bi];
    curList->buffer[bi] = tmp; 
    
    return;
}

//------------------------------------------------------------------------------
// contains
//
// Returns true if the list contains the value val, false otherwise. If the 
// value exsists in the list pos is set to the index of its first occurance. 
// The index is the list index, not the index in the underlying buffer. 
//------------------------------------------------------------------------------

// Meant as a private function - if the value is present in the list it returns 
// the index in the underlying buffer holding the value. 

char lmml_contains_at( lmm_list *curList, unsigned char *pos, char val ){
     if( curList->size == 0 ) {
 	return( false );
     }
 
     unsigned char i;
 
     if( curList->head < curList->tail ){
 	for( i=curList->head; (i<curList->tail); i++ ){	
 	    if( curList->buffer[i] == val ){
 		*pos = i;
 		return( true );
 	    }
 	}
     }else{
 	for( i=curList->head; (i<curList->max_size); i++ ){	
 	    if( curList->buffer[i] == val ){
 		*pos = i;
 		return( true );
 	    }
 	}

 	for( i=0; (i<curList->tail); i++ ){	
 	    if( curList->buffer[i] == val ){
 		*pos = i;
 		return( true );
 	    }
 	}
     }

     return( false );
}

char lmml_contains( lmm_list *curList, char val ){
    unsigned char pos;
    return( lmml_contains_at( curList, &pos, val ) );
}

