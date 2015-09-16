/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2013-2014  
*   All Rights Reserved
*
* FILE NAME:
*   mem_pool_def.h
*
* FILE DESCRIPTION:
*   allocate memory and manage memory
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
#ifndef __MEM_POOL_DEF_H__
#define __MEM_POOL_DEF_H__
/*------------------------- FILE INCLUSION --------------------------*/

/*------------------------- MACRO DEFINITIONS -----------------------*/
#define __ALIGN 8    //小型区块上调边界
#define __MAX_BYTES 256    //小型区块大小的上限
#define __NFREELISTS (__MAX_BYTES/__ALIGN)    //free-lists的个数
#define __POOL_SIZE  512/*内存池的大小*/
#define SIZE_OF_POINTER 4/*定义指针占用字节数*/

#define true 1
#define TRUE 1
#define false 0
#define FALSE 0
/*------------------------- TYPE DECLARATIONS -----------------------*/
typedef size_t            bool_t;         /* declaration for bool type */
/*------------------------- VARIABLE DECLARATIONS ---------------------*/

/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/
#endif /*__MEM_POOL_DEF_H__*/