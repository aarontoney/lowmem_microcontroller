//------------------------------------------------------------------------------
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

#ifndef __APT_RINGBUFF_H_
#define __APT_RINGBUFF_H_
//------------------------------------------------------------------------------
//- 
//- File:   ring_buffer.h
//- Author: Aaron Toney
//- Date:   April 22nd, 2016
//- Verion: 0.1
//- Revions: None
//- 
//- Description:
//- 
//- This header file defines a very simple character fifo ring buffer. 
//-
//- Comment about multi-threading
//- -----------------------------
//- I added no multi-threading support since it was a simple pre-screen quesiton
//- but there are three stragagies that you could use to make this thread safe. 
//- 
//- 1. Use an atomic swap lock on the push / pop operations. This would be my  
//-    prefered implementaiton. 
//- 
//- 2. Add explicit Mutextes. Problem here is no bounded response. Someone can 
//-    grab and hold the mutex for an unknown ammount of time. This is a problem
//-    if we are servicing something time sensative like an UART ISR with the 
//-    buffer. Mutexes can be the cleaner implementation - over atomic swaps - 
//-    but you need to know a lot more about the embedded context the code is being
//-    run it. 
//-
//- 3. Use no wait locking - no wait locks require maintaining extra buffers and are 
//-    typically way to heavyweigh for what I think I am being asked for here. 
//- 
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TRUE  1
#define FALSE 0

// #define CSBUFFER_ERROR    0x01 // Saving the generic error flag
#define CSBUFFER_FULL     0x02
#define CSBUFFER_EMPTY    0x04

#define CSBUFFER_UNDERFLOW 0x08
#define CSBUFFER_OVERFLOW  0x10

#define MAX_CSBUFFER_SIZE 10

typedef struct cs_fifo_char_buffer_struct{
  char  buffer[MAX_CSBUFFER_SIZE];
  unsigned char   head;
  unsigned char   tail;
  unsigned char   buffer_state;
} cs_fifo_char_buffer;

//------------------------------------------------------------------------------
// Macros.
//
// We track under and overflow conditions, but the user is responsible for
// clearing and responding to the flags once set. 
//------------------------------------------------------------------------------

#define isFull(curBuffer) (curBuffer->buffer_state & CSBUFFER_FULL)
#define isEmpty(curBuffer) (curBuffer->buffer_state & CSBUFFER_EMPTY)
// #define isError(curBuffer) (curBuffer->buffer_state & CSBUFFER_ERROR)

#define isUnderflow(curBuffer) (curBuffer->buffer_state & CSBUFFER_UNDERFLOW)
#define isOverflow(curBuffer) (curBuffer->buffer_state & CSBUFFER_OVERFLOW)

//------------------------------------------------------------------
// Note: With this type of #defined bit flag implementation it is
// possible to have contradicting flags like full and empty set at 
// the same time - if this needs to be protected against its easy to 
// swap the #define for a function with compatable signature that
// adds error checks. 
//------------------------------------------------------------------
// #define setError(curBuffer) (curBuffer->buffer_state |= CSBUFFER_ERROR);
#define setFull(curBuffer)  (curBuffer->buffer_state |= CSBUFFER_FULL);
#define setEmpty(curBuffer) (curBuffer->buffer_state |= CSBUFFER_EMPTY);
#define setUnderflow(curBuffer) (curBuffer->buffer_state |= CSBUFFER_UNDERFLOW)
#define setOverflow(curBuffer) (curBuffer->buffer_state |= CSBUFFER_OVERFLOW)


// #define clrError(curBuffer) (curBuffer->buffer_state &= ~CSBUFFER_ERROR);
#define clrFull(curBuffer)  (curBuffer->buffer_state &= ~CSBUFFER_FULL);
#define clrEmpty(curBuffer) (curBuffer->buffer_state &= ~CSBUFFER_EMPTY);
#define clrUnderflow(curBuffer) (curBuffer->buffer_state &= ~CSBUFFER_UNDERFLOW)
#define clrOverflow(curBuffer) (curBuffer->buffer_state &= ~CSBUFFER_OVERFLOW)

//------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------

void init_cs_fifo_char_buffer( cs_fifo_char_buffer *);
int  get_size(cs_fifo_char_buffer *);
void push( cs_fifo_char_buffer *, char);
char pop(cs_fifo_char_buffer *);

//------------------------------------------------------------------------------
#endif // Closes the #ifndef 


