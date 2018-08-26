#ifndef __LMM_STATE_H_
#define __LMM_STATE_H_
//------------------------------------------------------------------------------
//- File:   state.h
//- Author: Aaron Toney
//- Date:   March 18th, 2018
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

#define STATE_FULL      0x01
#define STATE_EMPTY     0x02
#define STATE_ERROR     0x04

#define STATE_OVERFLOW  0x10
#define STATE_UNDERFLOW 0x20

//------------------------------------------------------------------------------
// Macros assume a struct for data structure with an int field for 
// common bit flags. 
//------------------------------------------------------------------------------
#define noFlags(curBuffer) ((curBuffer->state == 0 ) ? (TRUE) : (FALSE))

#define isSet(curBuffer, flags) ((curBuffer->state & flags ) ? (TRUE) : (FALSE))
#define isOtherFlgsSet(curBuffer, flags) ((curBuffer->state & ~flags ) ? (TRUE) : (FALSE))

#define isFull(  curBuffer ) ((curBuffer->state & STATE_FULL ) ? (TRUE) : (FALSE))
#define isEmpty( curBuffer ) ((curBuffer->state & STATE_EMPTY) ? (TRUE) : (FALSE))
#define isError( curBuffer ) ((curBuffer->state & STATE_ERROR) ? (TRUE) : (FALSE))
#define isOverflow( curBuffer ) ((curBuffer->state & STATE_OVERFLOW) ? (TRUE) : (FALSE))
#define isUnderflow( curBuffer ) ((curBuffer->state & STATE_UNDERFLOW) ? (TRUE) : (FALSE))

//------------------------------------------------------------------
// Note: With this type of #defined bit flag implementation it is
// possible to have contradicting flags like full and empty set at 
// the same time - if this needs to be protected against its easy to 
// swap the #define for a function with compatable signature that
// adds error checks. 
//------------------------------------------------------------------
#define setFull(curBuffer)      (curBuffer->state |= STATE_FULL)
#define setEmpty(curBuffer)     (curBuffer->state |= STATE_EMPTY)
#define setError(curBuffer)     (curBuffer->state |= STATE_ERROR)
#define setOverflow(curBuffer)  (curBuffer->state |= STATE_OVERFLOW)
#define setUnderflow(curBuffer) (curBuffer->state |= STATE_UNDERFLOW)

#define clrAllFlags(curBuffer)  (curBuffer->state = 0x00)

#define clrFull(curBuffer)      (curBuffer->state &= ~STATE_FULL)
#define clrEmpty(curBuffer)     (curBuffer->state &= ~STATE_EMPTY)
#define clrError(curBuffer)     (curBuffer->state &= ~STATE_ERROR)
#define clrOverflow(curBuffer)  (curBuffer->state &= ~STATE_OVERFLOW)
#define clrUnderflow(curBuffer) (curBuffer->state &= ~STATE_UNDERFLOW)

//------------------------------------------------------------------------------
#endif
