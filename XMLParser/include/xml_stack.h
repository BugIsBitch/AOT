/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml_stack.h
*
* DESCRIPTION:
*    implementation of stack and useful API
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

#ifndef __XML_STACK_H__
#define __XML_STACK_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include "xml_types.h"
#include "assert.h"
/* ----------------------- MACRO DEFINITIONS ------------------------*/
#define STACK_MAX_SIZE 70000
/* ----------------------- TYPE DECLARATIONS ------------------------*/
typedef struct stack  
{  
	node_t* (*head)[STACK_MAX_SIZE];
	int top;  
}stack_t; 

/*------------------------- VARIABLE DEFINITION ---------------------*/

/*------------------------- FUNCTION DECLARATIONS --------------------*/
/**********************************************************************
* FUNCTION NAME:
*   push
*
* DESCRIPTION:
*   This function push a new element to stack
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     data--pushed element
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     g_stack --stack pointer
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* return PROCESS_SUCCESS if push element succeed.
*
* NOTES:
*
*********************************************************************/
int push(stack_t* g_stack,node_t* data);  
/**********************************************************************
* FUNCTION NAME:
*   pop
*
* DESCRIPTION:
*   This function pop up an element from stack
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     g_stack --stack pointer
*     data-- popped element
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* return PROCESS_SUCCESS if pop up element succeed.
*
* NOTES:
*
*********************************************************************/
int pop(stack_t*g_stack,node_t** data);  
/**********************************************************************
* FUNCTION NAME:
*   init_stack
*
* DESCRIPTION:
*   This function initial the stack
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     None
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     g_stack --stack pointer
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
*  if initial the stack success return PROCESS_SUCCESS else return 0
*
* NOTES:
*
*********************************************************************/
int init_stack(stack_t* g_stack);  

int init_scnd_stk(stack_t* g_stack);
/**********************************************************************
* FUNCTION NAME:
*   stack_empty
*
* DESCRIPTION:
*   This function judge whether the stack is full.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*      g_stack --stack pointer
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*    None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* return 1 if the stack is empty else return 0
*
* NOTES:
*
*********************************************************************/
int stack_empty(stack_t* g_stack);
/**********************************************************************
* FUNCTION NAME:
*   stack_elem_in
*
* DESCRIPTION:
*   This function judge whether the stack has the given element.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*      g_stack --stack pointer
*      nd -- judge element
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*    None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* return 1 if the stack has the element else return 0
*
* NOTES:
*
*********************************************************************/
int stack_elem_in(stack_t* g_stack,node_t* nd);

#endif/****__XML_STACK_H__ ****/