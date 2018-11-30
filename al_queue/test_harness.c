//------------------------------------------------------------------------------
//- File:   test_harness.c
//- Author: Aaron Toney
//- Date:   August 24th, 2018
//- 
//- git repositor: https://github.com/aarontoney/lowmem_microcontroller.git
//- 
//- Description: Test harness for stack overlay for array_list data structure. 
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

#include "../array_list/array_list.h"
#include "../array_list/test_harness_helper.h"

#include "al_queue.h"

#include <stdio.h>

// Needed for rand...
#include <stdlib.h>
#include <time.h>

#define BUFFER_STACK_MAXVAL 9

//--------------------------------------------------------------------
// option_clear
//--------------------------------------------------------------------
void option_clear( lmm_queue *curQueue )
{
    lmml_clear( (lmm_list *)curQueue );
}

//--------------------------------------------------------------------
// option_clear
//--------------------------------------------------------------------
void option_sec_clear( lmm_queue *curQueue )
{
    lmml_sec_clear( (lmm_list *)curQueue );
}

//--------------------------------------------------------------------
// option_size
//--------------------------------------------------------------------
void option_size( lmm_queue *curQueue )
{
    unsigned char sz = lmml_size( (lmm_list *)curQueue );
    printf("\nList size is: %d\r\n", sz);
}

//--------------------------------------------------------------------
// option_size
//--------------------------------------------------------------------
void option_top( lmm_queue *curQueue )
{
    if( curQueue->size == 0 ){
	printf("Error peeking top of list - list empty.\r\n");
	return;
    }

    char val = alq_top((lmm_list *)curQueue );

    printf("\nTop of list has value: %d\r\n", val);
}

//--------------------------------------------------------------------
// option_isEmpty
//--------------------------------------------------------------------
void option_isEmpty( lmm_queue *curQueue )
{
    if( lmml_isEmpty(curQueue) ){
	printf("List is empty\r\n");
    }else{
	printf("List is not empty\r\n");
    }
}

//--------------------------------------------------------------------
// option_push_back
//--------------------------------------------------------------------
void option_push( lmm_queue *curQueue )
{
    int number;

    fflush(stdin);
    printf("\nPlease enter the number to push_back: ");
    scanf("%d", &number);
    
    // turn the number to 0..9
    number %= 10;
    lmml_push_back( (lmm_list *)curQueue, number);
}

//--------------------------------------------------------------------
// option_pop 
//--------------------------------------------------------------------

char option_pop( lmm_queue *curQueue )
{
    char val = 0;

    // Note: real code would use isEmpty, but that is tested 
    //       elsewhere - so using primitives here. 
    if( curQueue->size == 0 ){
	printf("Error in pop - list empty\r\n");

    }else{
	val = alq_pop_front( (lmm_list *) curQueue );
    }

    fflush(stdin);
    return(val);
}

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
int main()
{
    char myListBuff[MAX_STACK_SIZE];

    lmm_queue myQueue;
    long int choice;
    char loop = true;
    
    // Seed the random function
    srand(time(NULL));   
    
    lmml_init((lmm_list *)&myQueue, MAX_STACK_SIZE, myListBuff);
    
    printf("\nStarting....\n");
    
    while(loop){
	printf("%s%s%s%s%s%s%s%s%s%s",
	       "\nPlease enter your selection \n",
	       "1. clear\n",
	       "2. sec clear\n",
	       "3. size\n",

	       "4. push\n",
	       "5. pop\n",

	       "6. top\n",

	       "7. isEmpty\n",

	       "8. quit testing programm\n",
	       "Enter Choice: " );
	
	scanf("%ld",&choice);
	
	switch( choice)
	    {
	    case 1:
		option_clear( &myQueue );
		break;
		
	    case 2:
		option_sec_clear( &myQueue );
		break;
		
	    case 3:
		option_size( &myQueue );
		break;
		
	    case 4:
		option_push( &myQueue );
		break;
		
	    case 5:
		option_pop( &myQueue );
		break;

	    case 6:
		option_top( &myQueue );
		break;
		
	    case 7:
		option_isEmpty( &myQueue );
		break;

	    case 8:
		loop = false;
		break;
		
	    default:
		printf("\nI am afraid that was not one of the listed choices.\n");
		break;
	    }
	
	print_state_from_flags( (lmm_list *)&myQueue );
	
	print_buffer( (lmm_list *) &myQueue );
	fflush(stdin);
    }
    
    return(1);
}
