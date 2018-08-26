//------------------------------------------------------------------------------
//- File:   test_harness.c
//- Author: Aaron Toney
//- Date:   August 19th, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description: Test harness for array_list data structure. .
//- 
//------------------------------------------------------------------------------

#include "algorithms.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BUFFER_ARRAY_SIZE 30
#define BUFFER_ARRAY_MAXVAL 9

// Number of tests we make against random generated buffers. Permutations are 
// exhaustive way to test, but only suitable for small search spaces. Random
// sampling enbles testing a larger space.
#define NUMB_SORT_TEST_LOOPS 1000

#define NUMB_PART_TEST_LOOPS  2000


char gBlist[BUFFER_ARRAY_SIZE];
char gBlist2[BUFFER_ARRAY_SIZE];

//--------------------------------------------------------------------
// 
//--------------------------------------------------------------------

void copy_buffer( ){
    for( int i=0; i<BUFFER_ARRAY_SIZE; i++ ){
	gBlist2[i] = gBlist[i];
    }
}

//--------------------------------------------------------------------
// Function: print_array
// Description: Just dumps the raw array to screen
//--------------------------------------------------------------------

void print_array( char *buff ){
    int i;

    for( i=0; i<BUFFER_ARRAY_SIZE; i++ ){
	printf("(%d)", buff[i] );
    }
    printf("\n");
}

//--------------------------------------------------------------------
// Function for loading the buffer with test data
//--------------------------------------------------------------------
void load_buffer_with_random_values(){
    do{
	for( unsigned char i = 0; i<BUFFER_ARRAY_SIZE; i++ ){
	    gBlist[i] = (rand()%(BUFFER_ARRAY_MAXVAL+1));
	}
    }while( lmml_sorted_array( gBlist, 0, (BUFFER_ARRAY_SIZE-1)) );
}

void load_buffer_with_0toN(){
    for( unsigned char i = 0; i<BUFFER_ARRAY_SIZE; i++ ){
	gBlist[i] = i;
    }
}

void load_buffer_with_Nto0(){
    for(int i=0; i<(BUFFER_ARRAY_SIZE); i++ ){
	gBlist[i] = (BUFFER_ARRAY_SIZE-i-1);
    }
}

//--------------------------------------------------------------------
// 
//--------------------------------------------------------------------
bool array_buffer_is_sorted(){
    for( unsigned char i = 1; i<BUFFER_ARRAY_SIZE; i++ ){
	if( gBlist[i-1] > gBlist[i] )
	    return( false );
    }
    return( true );
}

//------------------------------------------------------------------------------
// test_partitioning_array
//
// Tests if all the values in the array less than the value at index pi, have 
// indexes less than pi. 
//------------------------------------------------------------------------------

bool is_partitioned( char *ca, int pi ){
    if( ca == NULL )
	return( false );

    for( int i =0; i<=pi; i++ ){
	if( (ca[i] < ca[pi]) && i > pi )
	    return( false );
    }

    return( true );
}

void test_partitioning_array()
{
    int i;
    for( i=0; i<NUMB_PART_TEST_LOOPS; i++ ){
	load_buffer_with_random_values();  

	// Make sure we have a copy of the array before we sort
	copy_buffer();

	unsigned char pv = lmml_partition_array( gBlist, 0, (BUFFER_ARRAY_SIZE-1));
	if(! is_partitioned( gBlist, gBlist[pv]) ){
	    printf("(ERROR partitionin)\r\n");

	    printf("\t\tArray before: ");
	    print_array(gBlist);
	    
	    printf("\t\tArray after:  ");
	    print_array(gBlist2);
	    
	    printf("\r\n");
	    break; 
	}

    }

    if( i == NUMB_PART_TEST_LOOPS ){
	printf("Partition testing passed\r\n");
    }else{
	printf("Partition testing failed\r\n");
    }
}

//------------------------------------------------------------------------------
// test_bubblesort_array
//
//------------------------------------------------------------------------------

void test_bubblesort_array()
{
    int li = 0; 
    for( li = 0; li<NUMB_SORT_TEST_LOOPS; li++ ){
	
	load_buffer_with_random_values();  
	
	// Make sure we have a copy of the array before we sort
	copy_buffer();
	
	lmml_bubblesort_array( gBlist, 0, (BUFFER_ARRAY_SIZE-1) );
	
	if( ! array_buffer_is_sorted() ){
	    printf("(ERROR sorting)\r\n");
	    
	    printf("\t\tArray before: ");
	    print_array(gBlist);
	    
	    printf("\t\tArray after:  ");
	    print_array(gBlist2);
	    
	    printf("\r\n");
	    break; 
	}
    }
    
    if( li == NUMB_SORT_TEST_LOOPS ){
	printf("Testing passed\r\n");
    }else{
	printf("Testing failed\r\n");
    }

}


//------------------------------------------------------------------------------
// test_bubblesort_array
//
//------------------------------------------------------------------------------
void test_quicksort_array()
{
    load_buffer_with_random_values();
    // Make sure we have a copy of the array before we sort
    copy_buffer();
    
    lmml_quicksort_array_recursive( gBlist, 0, (BUFFER_ARRAY_SIZE-1) );
    
    //	  if( ! array_buffer_is_sorted() ){
    //	      printf("(ERROR sorting)\r\n");
    
    printf("\t\tArray before: ");
    print_array(gBlist);
    
    printf("\t\tArray after:  ");
    print_array(gBlist2);
    
    printf("\r\n");
    //	      break; 
    //	  }
    
    if( lmml_sorted_array( gBlist, 0, (BUFFER_ARRAY_SIZE-1) ) ){
	printf("Array is sorted...\r\n");
    }else{
	printf("Array is unsorted...\r\n");
    }
}

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------

int main()
{
    long int choice;
    int loop = TRUE;

    // Seed the random function
    srand(time(NULL));   

    printf("\nTesting algorithms....\n");

    while(loop){
	printf("%s%s%s%s%s%s%s%s",
	       "\nPlease enter your selection \n",
	       "1. load buffer with ((N-1)..0)\n",
	       "2. load buffer with random valuest\n",
	       "3. test bubble sort\n",
	       "4. test partition \n",
	       "5. test quick sort\n",
	       "6. quit testing programm\n",
	       "Enter Choice: " );

	scanf("%ld",&choice);
 
    switch( choice)
      {
	  //------------------------------------------------------------
	  //  Basics test loads on the buffer
	  //------------------------------------------------------------
      case 1:
	  printf("Loading buffer with ((N-1)..0) ...\r\n");
	  load_buffer_with_Nto0();
	  print_array(gBlist);
	  break;

      case 2:
	  printf("Loading buffer with random (unsorted) values....\r\n");
	  load_buffer_with_random_values();
	  print_array(gBlist);
	  break;

	  //------------------------------------------------------------
	  // Testing Bubblesort
	  //------------------------------------------------------------
      case 3:
	  printf("\r\nTesting Bubblesort...\r\n");
	  test_bubblesort_array();
	  break;

      case 4:
	  printf("Partitioning array...\r\n");
	  test_partitioning_array();
	  break;

	  //------------------------------------------------------------
	  // 
	  //------------------------------------------------------------
      case 5:
	  printf("\r\nTesting Quicksort...\r\n");	  
	  test_quicksort_array();
	break;

	  //------------------------------------------------------------
	  // Termination Condition
	  //------------------------------------------------------------
      case 6:
	loop = FALSE;
	break;

      default:
	printf("\nI am afraid that was not one of the listed choices.\n");
	break;
      }

    fflush(stdin);
    }

  return(1);
}



