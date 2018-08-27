#ifndef __LMM_ARRAY_LIST_STATE_H_
#define __LMM_ARRAY_LIST_STATE_H_
//------------------------------------------------------------------------------
//- File:   state.h
//- Author: Aaron Toney
//- Date:   March 22nd, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Header for implementing a commong bit state buffer interface for 
//- contained data structures. 
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
