//------------------------------------------------------------------------------
//- File:   test_harness.c
//- Author: Aaron Toney
//- Date:   April 21st, 2016
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- This is a test harness for a very simple fifo ring buffer.
//- 
//------------------------------------------------------------------------------

#include "ring_buffer.h"

char *gLetterLUT = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
size_t gLetterLUTLen = 62;

//--------------------------------------------------
// Prototypes...
//--------------------------------------------------
void print_buffer( cs_fifo_char_buffer *curBuffer );
void test_deliberate_overflow( cs_fifo_char_buffer *curBuffer );
void test_deliberate_underflow( cs_fifo_char_buffer *curBuffer );


void test_basic( cs_fifo_char_buffer *curBuffer );
void test_bulkpushpop( cs_fifo_char_buffer *curBuffer );

void test_pops( cs_fifo_char_buffer *curBuffer );
void test_pushes( cs_fifo_char_buffer *curBuffer );

//--------------------------------------------------
// Main
//--------------------------------------------------
int main()
{
  time_t t; // Need it for Rand

  cs_fifo_char_buffer myBuffer;
  long int choice;
  int loop = TRUE;
  char c;

  // Init the random number generator...
  srand((unsigned) time(&t));

  init_cs_fifo_char_buffer(&myBuffer);

  printf("\nStarting....\n");

  while(loop){
    printf("%s%d%s%s%s%s%s%s%s%s%s",
	   "\nBuffer size: ", get_size( &myBuffer ),
	   "\nPlease enter your selection \n",
	   "1. test bulk pushes and pops\n",
	   "2. bulk tests\n",
	   "3. test single push\n",
	   "4. test single pop\n",
	   "5. test overflow\n",
	   "6. test underflow\n",
	   "7. quit testing programm\n",
 	   "Choice: ");
   scanf("%ld",&choice);
 
    switch( choice)
      {
	//-------------------------------------
	// Basic Pushes and Pops
	//-------------------------------------
      case 1:
	test_bulkpushpop( &myBuffer );
	loop = FALSE;
	break;

	//-------------------------------------
	// Test with Over / Underflow
	//-------------------------------------
      case 2:
	test_basic( &myBuffer );
	loop = FALSE;
	break;

	//-------------------------------------
	// Test Pushes
	//-------------------------------------
      case 3:
	c = gLetterLUT[rand() % gLetterLUTLen];    
	printf("\nPushing char %c:", c);
	push( &myBuffer, c);

	print_buffer(&myBuffer);

	if(isOverflow((&myBuffer))){
	  // Flag persistent until user clears it.
	  printf("\nThe buffer has been overflown"); 
	}
	break;

	//-------------------------------------
	// Test Pop
	//-------------------------------------
      case 4:
	if(isEmpty((&myBuffer))){
	  printf("\nThe queue was empty.\n");
	}else{
	  c = pop(&myBuffer);
	  printf("\nThe number %c was dequeued.\n", c);
	}

	if(isUnderflow((&myBuffer))){
	  // Flag persistent until user clears it.
	  printf("\nThe buffer has been underflown"); 
	}
	break;

	//-------------------------------------
	// Test Overflow
	//-------------------------------------
      case 5:
	test_deliberate_overflow( &myBuffer );
	loop = FALSE;
	break;

	//-------------------------------------
	// Test underflow
	//-------------------------------------
      case 6:
	test_deliberate_underflow( &myBuffer );
	loop = FALSE;
	break;

	//-------------------------------------
	// Done testing
	//-------------------------------------
      case 7:
	loop = FALSE;
	break;

      default:
	printf("\nI am afraid that was not one of the listed choices.\n");
	loop = FALSE;
	break;
      }
    fflush(stdin);
  }
  return(1);
}

//--------------------------------------------------------------------
// Function: print_buffer
// Description: Just dumps the raw buffer to screen for comparison
//--------------------------------------------------------------------
void print_buffer( cs_fifo_char_buffer *curBuffer ){
  int i;

  printf("\nBuffer: ");
  for( i=0; i<MAX_CSBUFFER_SIZE; i++ ){
    printf("->%c<- ", curBuffer->buffer[i] );
  }
  printf("\nHead: %d, Tail: %d", curBuffer->head, curBuffer->tail);
  printf("\n");
}

//--------------------------------------------------------------------
// Function: test_bulkpushpop
// Description: 
//--------------------------------------------------------------------

void test_bulkpushpop( cs_fifo_char_buffer *curBuffer ){
  char c;
  int i;

  //----------------------------------------
  // Test pushes
  //----------------------------------------
  printf("\nTest of Pushing buffer\n");
  printf("--------------------------\n");

  printf("\nPushing chars to buffer: ");
  for( i = 0; i<(MAX_CSBUFFER_SIZE-2); i++ ){
    c = gLetterLUT[rand() % gLetterLUTLen];    
    printf("%c ", c);
    push( curBuffer, c);
  }
  printf("\n");
  print_buffer(curBuffer);

  //----------------------------------------
  // Rest pops removing half the chars
  //----------------------------------------
  printf("\nTest of Popping from the buffer\n");
  printf("-----------------------------------\n");

  printf("Buffer size: %d\n", get_size( curBuffer ) );
  printf("Poping half the chars we just added from the buffer\n");
  printf("Poping chars to buffer: ");
  for( i=0; i<((MAX_CSBUFFER_SIZE-2)/2); i++ ){
    c = pop(curBuffer);
    printf("%c ", c);
  }
  printf("\n");
  print_buffer(curBuffer);
}

//--------------------------------------------------------------------
// Function: test_basic
// Description: 
//--------------------------------------------------------------------

void test_basic( cs_fifo_char_buffer *curBuffer ){
  char c;

  //----------------------------------------
  // Load the buffer with data, then remove
  // some but without triggering and over /
  // under flow error. 
  //----------------------------------------
  test_bulkpushpop(curBuffer);

  //----------------------------------------
  // Deliberatly overflow the buffer
  //----------------------------------------
  test_deliberate_overflow(curBuffer);
  clrOverflow(curBuffer);

  //----------------------------------------
  // Make sure we recover from an overflow
  //----------------------------------------

  printf("Poping two chars off buffer to test function after overflow\n");

  c = pop(curBuffer);
  printf("Popped: %c \n", c);
  print_buffer(curBuffer);

  c = pop(curBuffer);
  printf("Popped: %c \n", c);
  print_buffer(curBuffer);

  //----------------------------------------
  // Deliberatly underflow the buffer
  //----------------------------------------
  test_deliberate_underflow(curBuffer);
  clrOverflow(curBuffer);

  //----------------------------------------
  // Make sure we recover from an underflow
  //----------------------------------------

  clrUnderflow(curBuffer);

  printf("Pushing two chars into buffer to test funciton after underflow\n");

  c = gLetterLUT[rand() % gLetterLUTLen];    
  push(curBuffer,c );
  printf("Pushed: %c \n", c);
  print_buffer(curBuffer);

  c = gLetterLUT[rand() % gLetterLUTLen];    
  push(curBuffer,c );
  printf("Pushed: %c \n", c);
  print_buffer(curBuffer);

}

//--------------------------------------------------------------------
// Function: test_deliberate_overflow
//--------------------------------------------------------------------

void test_deliberate_overflow( cs_fifo_char_buffer *curBuffer ){
  int i;
  char c;

  printf("\nTest of overflowing the buffer\n");
  printf("-----------------------------------\n");
  print_buffer(curBuffer);

  printf("Pushing chars to buffer: ");
  for( i = 0; ((i<=MAX_CSBUFFER_SIZE) && !isOverflow(curBuffer)); i++ ){
    c = gLetterLUT[rand() % gLetterLUTLen];    
    printf("%c ", c);
    push( curBuffer, c);
  }
  printf("\n");

  if( isOverflow(curBuffer) ){
    printf("Overflow of buffer detected.\n");
  }else{
    printf("Error: Overflow of buffer was not detected.\n");
  }

  print_buffer(curBuffer);
}

//--------------------------------------------------------------------
// Function: test_deliberate_underflow
//--------------------------------------------------------------------

void test_deliberate_underflow( cs_fifo_char_buffer *curBuffer ){
  int i;
  char c;

  printf("\nTest of underflowing the buffer\n");
  printf("-----------------------------------\n");
  print_buffer(curBuffer);

  printf("Popping chars from buffer: ");
  for( i = 0; ((i<=MAX_CSBUFFER_SIZE) && !isUnderflow(curBuffer)); i++ ){
    c = pop( curBuffer);
    printf("%c ",c);
  }
  printf("\n");

  if( isUnderflow(curBuffer) ){
    printf("Underflow of buffer detected.\n");
  }else{
    printf("Error: Underflow of buffer was not detected.\n");
  }

  print_buffer(curBuffer);
}


