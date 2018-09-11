#ifndef __LMM_ARRAY_FREE_LIST_H_
#define __LMM_ARRAY_FREE_LIST_H_
//------------------------------------------------------------------------------
//- File:   array_freelist.h
//- Author: Aaron Toney
//- Date:   Aug 25nd, 2018
//- Verion: 0.1
//- Revions:
//- 
//- Description:
//- 
//- Header for implementing an array based free list.
//- 
//------------------------------------------------------------------------------

// Maximum size of the free list is 0XFF, but it is zero based so the maximum
// range for valid indexes is 0x00 to 0xFE. The value of 0xFFFF is reserved
// as a sentinel value. 
#define FREE_LIST_SENTINEL ((unsigned char)0xFF)

//------------------------------------------------------------------
// Datastructures
//------------------------------------------------------------------

typedef struct lmm_freelist_cell_t{    
    unsigned char next;
    unsigned char other;
    short  val; 
} lmm_flcell;

typedef struct lmm_freelist_t{
    unsigned char max_size;
    unsigned char size; 

    unsigned char head;

    lmm_flcell *buffer;
} lmm_freelist;

//------------------------------------------------------------------
// Prototypes - FreeList
//------------------------------------------------------------------

void lmmll_init_freelist( lmm_freelist *curFreeList,
			  unsigned short max_buff_size, 
			  lmm_flcell *buff );

char lmmll_alloc( lmm_freelist *curFreeList,
		  unsigned char *retCellIndy );


char lmmll_return( lmm_freelist *curFreeList, 
		   unsigned char retCellIndy );


//------------------------------------------------------------------
// Prototypes - Common to both free an linked lists
//------------------------------------------------------------------

unsigned char lmmfl_size(lmm_freelist  *curLinkedList );
char lmmfl_isEmpty(lmm_freelist  *curLinkedList );

//------------------------------------------------------------------------------
#endif
