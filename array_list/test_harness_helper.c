//------------------------------------------------------------------------------
//- File:   test_harness_helper.c
//- Author: Aaron Toney
//- Date:   August 24th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description: Test harness helper functions for testing data structures 
//               derived from the array_list data structure. 
//- 
//------------------------------------------------------------------------------
#include "test_harness_helper.h"

//--------------------------------------------------------------------
// Function: print_buffer
// Description: takes in an index i for the underlying raw buffer and
//              returns true if that index is withing a valid range 
//              of values for the current ring buffer state. 
//
// Becuase we want to check against the ring buffer's underlying 
// buffer there are a bunch of cases to check. So this is a bit 
// ugly since we are deliberatly breaking the data structures
// abstraction for testing. 
//
// index: (0)(1)(2)(3)(4)(5)(6)(7)(8)(9)   check
//        ( )( )( )(0)(1)(2)(3)( )( )( )
// t1:              h           t
//        (2)(3)( )( )( )( )( )( )(0)(1)   check
// t2:           t                 h
//        ( )( )( )( )( )( )(0)(1)(2)(3)   check
// t3:     t                 h        
//        (0)(1)(2)(3)(4)(5)(6)(7)(8)(9)   check
// t4:    t,h                          
//        ( )( )( )( )( )( )( )( )( )( )   check
// t5:    t,h                          
//
//--------------------------------------------------------------------

char inRange( lmm_list *curList, unsigned char i ){
    if( (curList->size == 0) ||	(i >= curList->max_size) )
	return(false);
    
    if( curList->head == curList->tail){
	if(curList->size != curList->max_size)
	    return(false);
	return(true);
    }
    
    if( curList->head < curList->tail ){
	if( (curList->head <=i) && (i < curList->tail) )
	    return(true);
	return(false);
    }
    
    // We know curList->head > curList->tail below here
    
    if( (i >= curList->head ) || (i < curList->tail) )
	return(true);
    return(false);
}

//--------------------------------------------------------------------
// Function: print_buffer
// Description: Just dumps the raw buffer to screen for comparison
//--------------------------------------------------------------------

void print_buffer( lmm_list *curList ){
    int i;
    
    printf("\nList: ");
    for( i=0; i<curList->max_size; i++ ){
	
	if( inRange( curList, i) ){
	    printf( "->%d<- ", curList->buffer[i] );
	}else{
	    printf( "-><- " );
	}
    }
    
    printf("\nHead: %d, Tail: %d", curList->head, curList->tail);
    printf("\n");
}

//--------------------------------------------------------------------
// print_state_from_flags
//
// Used to print out the current state of the list flags
//--------------------------------------------------------------------

void print_state_from_flags( lmm_list *curList )
{
    if( isOverflow(curList)  ) { printf("Overflow flag set.\r\n");  }
    if( isUnderflow(curList) ) { printf("Underflow flag set.\r\n"); }
}

//--------------------------------------------------------------------
// fill_list_with_rand_values
//--------------------------------------------------------------------

 void fill_buffer_with_rand_values( lmm_list *curList, unsigned char bmaxval ){
    for( int i=0; (i<curList->max_size); i++ ){
	lmml_push_back( curList, 
			((unsigned char) (rand()%(bmaxval+1)) ) );
    }
}

