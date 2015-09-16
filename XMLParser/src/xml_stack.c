/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml_stack.c
*
* FILE DESCRIPTION:
*   implementation of stack and useful API
*
* DEFINED FUNCTION:
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
/*------------------------- FILE INCLUSION --------------------------*/
#include "../include/xml_stack.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DECLARATIONS ---------------------*/
static node_t* data_array[STACK_MAX_SIZE];
static node_t* second_data_arr[STACK_MAX_SIZE];
/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/
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
* if initial the stack success return PROCESS_SUCCESS else return 0
*
* NOTES:
*
*********************************************************************/	 
int init_stack(stack_t* g_stack)  
{  
	int ret = 0;
	if (NULL != g_stack )
	{
		int i = 0;
		g_stack->head = &data_array;
		g_stack->top = -1;
		for ( ; i < STACK_MAX_SIZE ; i++)
		{
			(*(g_stack->head))[i] = NULL;
		}
		ret = PROCESS_SUCCESS;
	}
	
	return ret;  
}  

int init_scnd_stk(stack_t* g_stack)  
{  
	int ret = 0;
	if (NULL != g_stack )
	{
		int i = 0;
		g_stack->head = &second_data_arr;
		g_stack->top = -1;
		for ( ; i < STACK_MAX_SIZE ; i++)
		{
			(*(g_stack->head))[i] = NULL;
		}
		ret = PROCESS_SUCCESS;
	}

	return ret;  
} 
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
int push(stack_t* g_stack,node_t* data)  
 {  
	/*find unused data in array*/
    ++(g_stack->top);
	/*is stack full*/
	assert(g_stack->top < (STACK_MAX_SIZE-1));
	(*(g_stack->head))[g_stack->top] = data;
	 
	 return PROCESS_SUCCESS;  
}   
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
int pop(stack_t* g_stack,node_t** data)  
{  
	assert(g_stack->top >= 0);

	/*get element*/
	 *data = (*(g_stack->head))[g_stack->top];

	 (*(g_stack->head))[g_stack->top] = NULL;

	 /*set stack top*/
	 --(g_stack->top);

	  return PROCESS_SUCCESS;  
}    
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
int stack_empty(stack_t* g_stack)
{
	int ret = 0;
	if (g_stack->top == -1)
	{
		ret = PROCESS_SUCCESS;
	}
	return ret;
}
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
int stack_elem_in(stack_t* g_stack,node_t* nd)
{
	int ret = 0;
	/*stack  isn't empty*/
    if (!stack_empty(g_stack))
	{
		int i = 0;
		/*find element in stack*/
		for ( ; i <= g_stack->top ; i++)
		{
			if ((*(g_stack->head))[i] == nd)
			{
				ret = PROCESS_SUCCESS;
				break;
			}
		}
	}
	return ret;
}
