/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2013-2014  
*   
*   All Rights Reserved
*
* FILE NAME:
*   mem_pool.h
*
* FILE DESCRIPTION:
*   Allocate memory and manage memory
*
* DEFINED FUNCTION:
*  
*
* DESIGN NOTES:
*   None.
* 
* VERSION:
*   V1.00   
* 
* CHANGE HISTORY:
*
* AUTHOR:
*   Fu Pei 
*
*********************************************************************/
#ifndef __MEM_POOL_H__
#define __MEM_POOL_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include "mem_pool_type.h"
#include "mem_pool_def.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DECLARATIONS ---------------------*/


/* ---------------------- FUNCTION DECLARATIONS ---------------------*/
/**********************************************************************
* FUNCTION NAME:
*   round_up
*   
* DESCRIPTION:
*     
*
* INTERFACE:
*   GLOBAL DATA:
*     
*
*   INPUT:
*     bytes-- number of bytes
*
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*  None
*
* NOTES:
*
*********************************************************************/
extern size_t round_up(size_t bytes);

extern size_t freelist_index(size_t bytes);

extern void *mem_malloc(size_t nbytes);

extern void mem_free(void *p, size_t nbytes);

extern void *refill(size_t n);

extern char *chunk_alloc(size_t bytes, size_t *nobjs);

extern void reset_freelist_state(mem_state_t *ptr_state);

extern bool_t search_cntn_unit(mem_state_t *ptr_state,size_t nbytes,size_t ncount);

extern char* freelist_unit_merge(size_t need_bytes, size_t *nobjs,size_t cur_list_bytes,mem_state_t* p_state);

extern char* merge_chunk_alloc(size_t need_bytes, size_t *nobjs);

extern void update_state(mem_state_t* ptr_state,obj* cntn_head,obj* pre_head,size_t ncount);

extern void init_mem_pool();

#endif/*__MEM_POOL_H__*/