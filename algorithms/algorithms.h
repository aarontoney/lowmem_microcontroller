#ifndef __LMM_ALGORITHMS_H_
#define __LMM_ALGORITHMS_H_
//------------------------------------------------------------------------------
//- File:   algorithms.h
//- Author: Aaron Toney
//- Date:   March 20th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Implements basic useful algorithms. Implementation assemes a low memeory 
//- microcontroller, with no underlying kernel support features like malloc or 
//- free.
//-
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define UNSIGNED_CHAR_MAX ((unsigned char)0xFF)

#include "../state.h"

// C does not have native boolean types - so we create them. 
typedef enum { false, true } bool;

//------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------

bool lmml_bubblesort_array( char ca[], 
			    unsigned char hi, 
			    unsigned char ti );

unsigned char lmml_partition_array( char ca[], 
				    unsigned char li, unsigned char ri );

bool lmml_sorted_array( char ca[], 
			unsigned char hi, unsigned char ti );

void lmml_quicksort_array_recursive( char * ca, 
  				     unsigned char hi, unsigned char ti );


//------------------------------------------------------------------------------
#endif
