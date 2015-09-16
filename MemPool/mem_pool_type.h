/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2013-2014  
*   
*   All Rights Reserved
*
* FILE NAME:
*   mem_pool_type.h
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
#ifndef __MEM_POOL_TYPE_H__
#define __MEM_POOL_TYPE_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include <stdio.h>
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/
typedef union obj
{
	union obj *free_list_link;
	char client_data[1];
}obj;

typedef struct mem_state
{
	size_t cntn_chunk_num;/*�����ڴ��ĸ���*/
	obj* cntn_chunk_head;/*��һ����¼�Ŀ����������׵�ַ*/
    size_t cntn_unit_num;/*��һ���������е�Ԫ�ڴ�����*/
	obj* pre_cntn_head;/*�������ǰһ����Ԫָ��*/

}mem_state_t;
/*------------------------- VARIABLE DECLARATIONS ---------------------*/


/* ---------------------- FUNCTION DECLARATIONS ---------------------*/

#endif/*__MEM_POOL_TYPE_H__*/