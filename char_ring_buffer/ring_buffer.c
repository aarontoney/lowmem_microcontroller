//------------------------------------------------------------------------------
//-
//- Copyright (c) 2016                                                         
//-      Aaron P Toney.  All rights reserved.                                  
//-                                                                            
//- Redistribution and use in source and binary forms, with or without         
//- modification, are permitted provided that the following conditions         
//- are met:                                                                   
//- 1. Redistributions of source code must retain the above copyright          
//-    notice, this list of conditions and the following disclaimer.           
//- 2. Redistributions in binary form must reproduce the above copyright       
//-    notice, this list of conditions and the following disclaimer in the     
//-    documentation and/or other materials provided with the distribution.    
//- 3. All advertising materials mentioning features or use of this software   
//-    must display the following acknowledgement:                             
//-      This product includes software developed by Aaron P Toney.            
//- 4. The name of Aaron P Toney man not be used to endorse or promote         
//-    products derived from this software without specific prior written      
//-    permission.                                                             
//-                                                                            
//- THIS SOFTWARE IS PROVIDED BY AARON P TONEY ``AS IS'' AND ANY EXPRESS       
//- OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED          
//- WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE     
//- DISCLAIMED.  IN NO EVENT SHALL AARON P TONEY BE LIABLE                     
//- FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
//- DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS    
//- OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)      
//- HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
//- LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY  
//- OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF     
//- SUCH DAMAGE.                                                               
//-
//------------------------------------------------------------------------------
//-
//- File:   ring_buffer.c
//- Author: Aaron Toney
//- Date:   April 22nd, 2016
//- Verion: 1.0
//- Revions:
//- 
//- Description:
//- 
//- This header file defines a very simple fifo ring buffer. Its written
//- for micro-controllers where there is very limited memory. It also assumes
//- only straight C is available. 
//-
//- The buffer size is set with the MAX_CSBUFFER_SIZE #define in the 
//- ring_buffer.h file. 
//- 
//- The buffer uses a head chasing tail implementation. Data is stored in an 
//- array where head and tail are indexes into that array. Pushing advances 
//- tail, popping advances the head. Equality of indexes indicates full / empty condition. 
//- 
//- An empty or full list has the head and tail parked with an equal value. 
//-
//- Empty:  1,2,3,4,5,6,7,8,9,10 = Push => 1,2,3,4,5,6,7,8,9,10
//-         ^                              ^ ^
//-         |                              | |
//-        h,t                             h t
//- 
//- To illustrate wrapping a single element list has head just behind tail. 
//- 
//- Wrapping push
//-
//-      Starts as             Push(es) to Full            Pop
//- --------------------     --------------------   --------------------
//- 1,2,3,4,5,6,7,8,9,10     1,2,3,4,5,6,7,8,9,10   1,2,3,4,5,6,7,8,9,10
//-                 ^  ^                        ^   ^                  ^
//-                 |  |                        |   |                  |
//-                 h  t                       h,t  t                  h
//- 
//- Wrapping pop
//- 
//-            Starts as             Push to Wrap              Pop
//-       --------------------   --------------------   --------------------
//- or:   1,2,3,4,5,6,7,8,9,10   1,2,3,4,5,6,7,8,9,10   1,2,3,4,5,6,7,8,9,10
//-                     ^    ^   ^             ^                      ^    ^
//-                     |    |   |             |                      |    |
//-                     h    t   t             h                      h    t
//- 
//------------------------------------------------------------------------------

#include "ring_buffer.h"

//------------------------------------------------------------------------------
// Init Char Buffer
//------------------------------------------------------------------------------
void init_cs_fifo_char_buffer(cs_fifo_char_buffer *curBuffer)
{
  curBuffer->head = 0;
  curBuffer->tail = 0;

  // Clear all flags. 
  curBuffer->buffer_state = 0;

  // The buffer is empty on startup
  setEmpty(curBuffer);
} 

//------------------------------------------------------------------------------
// function: get_size
//
// Note: As this is intended for an embedded context where we have a lot more ROM 
//       then RAM I am not just keeping a byte of ram for the storage of buffer 
//       size. Every byte counts.
//------------------------------------------------------------------------------
int get_size(cs_fifo_char_buffer *curBuffer){

    if(curBuffer->head == curBuffer->tail){
      return( 0 );
    }else if(curBuffer->head > curBuffer->tail){
      // We return the buffer size minus the unused distance between
      // head and tail.
      return(MAX_CSBUFFER_SIZE - (curBuffer->head - (curBuffer->tail)) );
    }else{
      // We know that head must be less then tail so our total size is now
      return( curBuffer->tail - curBuffer->head );
    }
}

//------------------------------------------------------------------------------
// function: push
//
// Note: I talk about changes I would make here to have this code be usable in 
//       a multi-threaded context at the top of ring_buffer.h.
//
//------------------------------------------------------------------------------
void push( cs_fifo_char_buffer *curBuffer, 
	   char newVal)
{
  if(isFull(curBuffer)){
    setOverflow(curBuffer);
    return;
  }

  clrEmpty(curBuffer);

  curBuffer->buffer[curBuffer->tail] = newVal;

  if( ++(curBuffer->tail) == MAX_CSBUFFER_SIZE ){
    curBuffer->tail = 0;
  }
  
  // Test for being full. 
  if( curBuffer->tail == curBuffer->head )
    {
      // Signal that we are now full
      setFull(curBuffer);
    }
}

//------------------------------------------------------------------------------
// function: pop
//
// Note: I talk about changes I would make here to have this code be usable in 
//       a multi-threaded context at the top of ring_buffer.h.
//
//------------------------------------------------------------------------------

char pop(cs_fifo_char_buffer *curBuffer){
  char retChar;

  if( isEmpty(curBuffer) ){
    // Error flag, needs to be cleared by user. 
    setUnderflow(curBuffer);
    return((char)0);
  }

  clrFull(curBuffer);

  retChar = curBuffer->buffer[curBuffer->head];

  // Then advance the head. 
  curBuffer->head++;
  if( curBuffer->head  == MAX_CSBUFFER_SIZE ){
    curBuffer->head = 0;
  }

  // Signal if we are now empty
  if( curBuffer->head == curBuffer->tail ){
    setEmpty(curBuffer);
  }

  return(retChar);
}


