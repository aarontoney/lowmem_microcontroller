#ifndef __LMM_ARRAY_LIST_STATE_H_
#define __LMM_ARRAY_LIST_STATE_H_
//------------------------------------------------------------------------------
//- File:   state.h
//- Author: Aaron Toney
//- Date:   August 26th, 2018
//-
//- git repositor: https://github.com/aarontoney/lowmem_microcontroller.git
//-
//- Description:
//- 
//- Header for implementing a commong bit state buffer interface for 
//- contained data structures. 
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

#define TRUE  1
#define FALSE 0

#define AL_STATE_ERROR     0x1
#define AL_STATE_OVERFLOW  0x2
#define AL_STATE_UNDERFLOW 0x4

//------------------------------------------------------------------------------
// Macros assume a struct for data structure with an int field for 
// common bit flags. 
//------------------------------------------------------------------------------
#define noFlags(curBuffer) ((curBuffer->state == 0 ) ? (TRUE) : (FALSE))

#define isError( curBuffer ) ((curBuffer->state & AL_STATE_ERROR) ? (TRUE) : (FALSE))
#define isOverflow( curBuffer ) ((curBuffer->state & AL_STATE_OVERFLOW) ? (TRUE) : (FALSE))
#define isUnderflow( curBuffer ) ((curBuffer->state & AL_STATE_UNDERFLOW) ? (TRUE) : (FALSE))

//------------------------------------------------------------------
// Note: With this type of #defined bit flag implementation it is
// possible to have contradicting flags like full and empty set at 
// the same time - if this needs to be protected against its easy to 
// swap the #define for a function with compatable signature that
// adds error checks. 
//------------------------------------------------------------------
#define setError(curBuffer)     (curBuffer->state |= AL_STATE_ERROR)
#define setOverflow(curBuffer)  (curBuffer->state |= AL_STATE_OVERFLOW)
#define setUnderflow(curBuffer) (curBuffer->state |= AL_STATE_UNDERFLOW)

#define clrAllFlags(curBuffer)  (curBuffer->state = 0x00)

#define clrError(curBuffer)     (curBuffer->state &= ~AL_STATE_ERROR)
#define clrOverflow(curBuffer)  (curBuffer->state &= ~AL_STATE_OVERFLOW)
#define clrUnderflow(curBuffer) (curBuffer->state &= ~AL_STATE_UNDERFLOW)

//------------------------------------------------------------------------------
#endif
