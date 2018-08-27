//------------------------------------------------------------------------------
//- File:   algorithms.c
//- Author: Aaron Toney
//- Date:   August 26th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Implements simple algorithms. Intended for low memory systems without 
//- dynamic memory management tools like malloc.
//- 
//------------------------------------------------------------------------------

#include "algorithms.h"

//------------------------------------------------------------------------------
// Tests if a range in an array is in sorted order. 
//------------------------------------------------------------------------------

bool lmml_sorted_array( char* ca, 
			unsigned char hi, unsigned char ti )
{
    if( ca == NULL)
	return(false);

    if( ti==hi )
	return(true);

    unsigned char i;
    for( i=(hi+1); i<=ti; i++){
	if( ca[i-1] > ca[i] )
	    return(false);
    }

    return(true);
}

//------------------------------------------------------------------------------
// partion_array
//
// Partitions the array arround a pivot value, such that all values less than 
// the pivot value end up with indexes less than the pivot index. Array values 
// with an index greater than the returned pivot index have a value that is 
// greater than or equal to the pivot value. 
//
// Implementation uses the right most value in range as the pivot. This avoids 
// division needed in mid point pivot, or random operation in random pivot. 
//
// If the pivot value is not unique - the duplicate pivot values will occur 
// with indexes greater than the pivot index. 
//
//------------------------------------------------------------------------------

unsigned char lmml_partition_array( char * ca, 
				    unsigned char li, unsigned char ri )
{
    unsigned char pi = ri;
    char pv = ca[pi]; // pv = Pivot value

    // Find the pivot index, pushing all values less than
    // the pivot value to the left of the pivot. 
    while( li < ri ){
	// Extra checks needed to prevent roll over error - since
	// the li and ri indexes are of an unsigned type.
	while( (ca[li] < pv) && (li<(UNSIGNED_CHAR_MAX-1)) ){ li++; }
	while( (ca[ri] > pv) && (ri>0)){ ri--; }

	if( li < ri ){
	    char tmp = ca[li];
	    ca[li] = ca[ri];
	    ca[ri] = tmp;

	    li++;
	    ri--;
	}
    }

    // Push the pivot value into the pivot index - we found
    // the indext for the pivot if the array was sorted so
    // now put it here. 
    char tmp = ca[li];
    ca[li] = ca[pi];
    ca[pi] = tmp;

    return(li);
}

//------------------------------------------------------------------------------
// quicksort
//
// The array is assumed to be zero based. The head value, hi, is the index of
// the first element and the tail value, ti, is the index of the element after
// last element. 
//
// So (hi == ti) represents either an empty list, or a list full to the point 
// that it entirely fills without overflowing the underlying buffer. 
//
//------------------------------------------------------------------------------

void lmml_quicksort_array_recursive( char * ca, 
  				     unsigned char hi, unsigned char ti )
{
    if( (ca == NULL) || (ti<=hi) )
  	return;
        

    fflush(stdout);

    unsigned char pivot_indy = lmml_partition_array( ca, hi, ti );

    lmml_quicksort_array_recursive( ca, hi, pivot_indy-1 ); 

    lmml_quicksort_array_recursive( ca, pivot_indy, ti ); 
}


//------------------------------------------------------------------------------
// Bubble Sort
//
// WARNING!!! Bubble sort is an O(N^2) sort, never actually use it. It is just
//            included here as its useful for making performance comparisons
//            with better algorithms. 
//------------------------------------------------------------------------------

bool lmml_bubblesort_array( char * ca, 
			    unsigned char hi, 
			    unsigned char ti ) 
{
    if( ca == NULL )
	return(false);

    for( int i = hi; i<ti; i++ ){
	for( int j = i+1; j<=ti; j++ ){
	    
	    if( ca[i] > ca[j] ){
		char tmp = ca[i];
		ca[i] = ca[j];
		ca[j] = tmp;
	    }
	    
	}
    }

    return(true);
}

