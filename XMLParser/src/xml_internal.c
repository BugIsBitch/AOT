/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml_internal.c
*
* FILE DESCRIPTION:
*   The file define internal function used for parsing xml and handle xpath.
*
* DEFINED FUNCTION:
*  create_node
*  create_attribute
*  close_node
*  initial_attr
*  load
*  parent_node
*  set_type
*  copy_string
*  copy_node_data
*  init_node_arry
*  init_node
*  get_type
*  malloc_node
*  print_format
*  print_declaration
*  print_attribute
*  write_node_begin
*  write_node_end
*  write_last_node_end
*  is_separator
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
#include "../include/xml_internal.h"
#include "../include/xml_parse_engine.h"
#include "../include/xml_stack.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../include/xml_global.h"
#include "../include/xml.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/
/*xml parse item array*/
extern xml_parser_item_t parser_itm_arry[PARSE_ITEM_COUNT];
extern node_t xml_node_array[NODE_ARRAY_COUNT];
/*xpath parse item array*/
extern xpath_parser_item_t xpath_parser_arry[PARSE_ITM_DEF_COUNT];
/*xml_node_array index of first unused node */
extern int first_unused_index;
/*total xpath node array*/
extern xpath_node_t xpath_nd_array[TOTAL_XPATH][MAX_NODE_PER_XPATH];
/*the node pointer array which satisfy the xpath condition*/
extern node_t* res_node_array[MAX_XPATH_RES_REC];
/*store all the second XML node info*/
extern node_t scnd_xml_node_arr[ES_NODE_ARR_CNT];
/*index of first unused node of scnd_xml_node_arr*/
extern int second_unused_index;

extern attribute_t xml_attr_array[ATTR_ARR_CNT];/*store all XML attribute*/
extern attribute_t scd_attr_array[ES_ATTR_ARR_CNT];/*store all XML attribute*/
extern cur_arr_index_t scd_index;
extern cur_arr_index_t fsrt_index;/*used array index*/
extern char xml_attr_value_arr[ATTR_VAL_ATT_CNT];/*attribute value array*/
extern char scd_attr_value_arr[ES_ATTR_VAL_CNT];/*attribute value array*/
/*------------------------- VARIABLE DECLARATIONS ---------------------*/
static node_t* tmp_input__array[MAX_XPATH_RES_REC];
static node_t* tmp_output_arry[MAX_XPATH_RES_REC];
/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/

/**********************************************************************
* FUNCTION NAME:
*   create_node
*
* DESCRIPTION:
*   This function create a new node and set its value
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     n --create node pointer
*     pos --is the beginning offset of the node in the file
*     src -- is the pointer to the file
*     type-- node type
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
* 
* None
*
* NOTES:
*
*********************************************************************/
void  create_node(node_t* n,int pos, FILE *src, int type)
{
	n->type = type;
	n->pos = pos;
	n->end = pos;
	n->child = NULL;
	n->sibl = NULL;
	n->prnt = NULL;
	n->cur_attr_index = -1;
	n->is_nd_closed = 0;
	n->attr = NULL;
	copy_string(n->node_name,"",1);
    n->depth = -1;
}
/**********************************************************************
* FUNCTION NAME:
*   get_type
*
* DESCRIPTION:
*   This function get the node type
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     n --given node 
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
*
* if successfully executed return node type otherwise return error type
*
* NOTES:
*
*********************************************************************/
int  get_type(node_t *n)
{
	int ret = NONE_NODE;
	/*node is not null*/
	if(n) 
	{
		ret = (n->type & ( ELM_NODE | CMT_NODE |PI_NODE ));
	}
	return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   initial_attr
*
* DESCRIPTION:
*   This function initial attribute array data
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     attr_array --attribute array
*     size --array size
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
*
* None
*
* NOTES:
*
*********************************************************************/
void initial_attr(attribute_t *attr)
{
	int i = 0;
	copy_string(attr->name,"",1);
	attr->value = NULL;
	attr->next = NULL;
	attr->state = UNALLOCTE;
}

/**********************************************************************
* FUNCTION NAME:
*   malloc_fst_arr_attr
*
* DESCRIPTION:
*   This function malloc attribute for given node
*
* INTERFACE:
*   GLOBAL DATA:
*     xml_attr_array - first attribute array
*     fsrt_index - unused index in array
*   INPUT:
*     n --given node
*     ret_attr - allocate attribute
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
*
* This function return PROCESS_SUCCESS malloc attribute successful, else return error code.
*
* NOTES:
*
*********************************************************************/
int malloc_fst_arr_attr(node_t *n,attribute_t **ret_attr)
{
	int error_code = PROCESS_SUCCESS;
    if (n != NULL)
    {
		if ((fsrt_index.attr_unused_index+1) < ATTR_ARR_CNT)
		{
			xml_attr_array[fsrt_index.attr_unused_index].state = ALLOCTE;
			/*first time allocate attribute*/
			if (n->attr == NULL)
			{
				n->attr = &(xml_attr_array[fsrt_index.attr_unused_index]);
				n->attr->next = NULL;
				*ret_attr = n->attr;
			}
			else
			{
				attribute_t *attr = n->attr;
				/*get last attribute*/
				while (attr != NULL && attr->next != NULL)
				{
					attr = attr->next;
				}
				attr->next = &(xml_attr_array[fsrt_index.attr_unused_index]);
				attr->next->next = NULL;
				*ret_attr = attr->next;
			}
			n->cur_attr_index++;
			fsrt_index.attr_unused_index += 1;
		}
		else
		{
			error_code = OUT_OF_MEMORY;
		}
    }
	return error_code;
}
/**********************************************************************
* FUNCTION NAME:
*   malloc_scd_arr_attr
*
* DESCRIPTION:
*   This function malloc attribute for given node
*
* INTERFACE:
*   GLOBAL DATA:
*     scd_attr_array - second attribute array
*     scd_index - unused index in array
*   INPUT:
*     n --given node
*     ret_attr - allocate attribute
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
*
* This function return PROCESS_SUCCESS malloc attribute successful, else return error code.
*
* NOTES:
*
*********************************************************************/
int malloc_scd_arr_attr(node_t* n,attribute_t **ret_attr)
{
	int error_code = PROCESS_SUCCESS;
	if (n != NULL)
	{
		if ((scd_index.attr_unused_index+1) < ES_ATTR_ARR_CNT)
		{
			scd_attr_array[scd_index.attr_unused_index].state = ALLOCTE;
			/*first time allocate attribute*/
			if (n->attr == NULL)
			{
				n->attr = &(scd_attr_array[scd_index.attr_unused_index]);
				n->attr->next = NULL;
				*ret_attr = n->attr;
			}
			else
			{
				attribute_t *attr = n->attr;
				/*get last attribute*/
				while (attr != NULL && attr->next != NULL)
				{
					attr = attr->next;
				}
				attr->next = &(scd_attr_array[scd_index.attr_unused_index]);
				attr->next->next = NULL;
				*ret_attr = attr->next;
			}
			n->cur_attr_index++;
			scd_index.attr_unused_index += 1;
		}
		else
		{
			error_code = OUT_OF_MEMORY;
		}
	}
	return error_code;
}
/**********************************************************************
* FUNCTION NAME:
*   malloc_fst_arr_val_attr
*
* DESCRIPTION:
*   This function malloc value for attribute
*
* INTERFACE:
*   GLOBAL DATA:
*     xml_attr_value_arr - first attribute value array
*     fsrt_index - current unused index in array
*   INPUT:
*     count - malloc character count
*   OUTPUT:
*     attr - given attribute
*
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* This function return PROCESS_SUCCESS malloc value successful, else return error code.
*
* NOTES:
*
*********************************************************************/
int malloc_fst_arr_val_attr(attribute_t* attr,int count)
{
	int error_code = PROCESS_SUCCESS;
	if (attr != NULL)
	{
		if ((fsrt_index.unused_attr_value_index+count) < ATTR_VAL_ATT_CNT)
		{
			attr->value = &(xml_attr_value_arr[fsrt_index.unused_attr_value_index]);
			fsrt_index.unused_attr_value_index += count+1;
		}
		else
		{
			error_code = OUT_OF_MEMORY;
		}
	}
	return error_code;
}
/**********************************************************************
* FUNCTION NAME:
*   malloc_scd_arr_val_attr
*
* DESCRIPTION:
*   This function malloc value for attribute
*
* INTERFACE:
*   GLOBAL DATA:
*     scd_attr_value_arr - second attribute value array
*     scd_index - current unused index in array
*   INPUT:
*     count - malloc character count
*   OUTPUT:
*     attr - given attribute
*
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* This function return PROCESS_SUCCESS malloc value successful, else return error code.
*
* NOTES:
*
*********************************************************************/
int malloc_scd_arr_val_attr(attribute_t* attr,int count)
{
	int error_code = PROCESS_SUCCESS;
	if (attr != NULL)
	{
		if ((scd_index.unused_attr_value_index+count) < ES_ATTR_VAL_CNT)
		{
			attr->value = &(scd_attr_value_arr[scd_index.unused_attr_value_index]);
			scd_index.unused_attr_value_index += count+1;
		}
		else
		{
			error_code = OUT_OF_MEMORY;
		}
	}
	return error_code;
}
/**********************************************************************
* FUNCTION NAME:
*   close_node
*
* DESCRIPTION:
*   This function close the node (add the end offset)
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     node --is the node set the node end offset
*     close--is the node to close
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
*
* None
*
* NOTES:
*
*********************************************************************/
void  close_node(node_t *n, node_t *close)
{
	if (NULL != n && NULL != close)
	{
		n->end = close->pos;
		n->is_nd_closed = close->is_nd_closed;
		/*reset attributes */
		close->attr = NULL;
		close->cur_attr_index = -1;
		close->depth = -1;
		close->end = -1;
		close->child = NULL;
		close->sibl = NULL;
        close->is_nd_closed = 0;
		strcpy(close->node_name,"");
		close->pos = -1;
		close->prnt = NULL;
		close->type = NONE_NODE;
        close->state = UNALLOCTE;
	}
}
/**********************************************************************
* FUNCTION NAME:
*   is_separator
*
* DESCRIPTION:
*   This function tells if a char is a string separator
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     sep --char to test
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
*
* return 1 if the char was a separator else 0
*
* NOTES:
*
*********************************************************************/
int  is_separator(char sep)
{
	int ret = 0;
	int i = 0;
	char separators[32] = "\t\n ";
	while(separators[i] != 0)
	{
		if(sep == separators[i])
		{
			ret = 1;
			break;
		}
		i++;
	}
	return ret;
}

/**********************************************************************
* FUNCTION NAME:
*   load
*
* DESCRIPTION:
*   This function load a document and all the corresponding nodes
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     file --file descriptor of document
*     type-- load to first array or second array
*    
*   OUTPUT:
*      None
*
*   INPUT/OUTPUT:
*      root--the xml root node pointer
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* return PROCESS_SUCCESS if parse xml succeed else return the error type
*
* NOTES:
*
*********************************************************************/
int  load(FILE *file,node_t** root,int type)
{
	int ret = PROCESS_SUCCESS;
	int error = 0;
	char buffer[BULK_READ+1];
	xml_load_ctx_t context;
	xml_parser_item_t *item = &(parser_itm_arry[0]);
	memset(&context, 0, sizeof(xml_load_ctx_t));
	
	/*append parse element to parse item array */
	append_parser_item(item++, " ", _func_load_white);
	append_parser_item(item++, "<", _func_load_open_node);
	append_parser_item(item++, ">", _func_load_close_node);
	append_parser_item(item++, "/", _func_load_end_node);
	append_parser_item(item++, "'", _func_load_quoted);
	append_parser_item(item++, "\"", _func_load_dquoted);
	append_parser_item(item++, "\t", _func_load_white);
	append_parser_item(item++, "\n", _func_load_white);
	append_parser_item(item++, "\r", _func_load_white);
	append_parser_item(item++, "!", _func_load_open_spec_node);
	append_parser_item(item++, "]", _func_load_close_cdata);
	append_parser_item(item++, "-", _func_load_close_comment);
	append_parser_item(item++, "?", _func_load_close_pi);
	append_parser_item(item, NULL, _func_load_default);
	if(file)	
	{ 
		int circle = 0;
		size_t data_len = 0;
		context.type = XML_FILE;
		context.src =file;
		context.pos = 0;
		context.fisrt_or_second = type;
		do 
		{	
			int chunk_len = 0;
			/*read file*/
			data_len = fread(buffer+circle, 1, BULK_READ-circle, file) + circle;
			buffer[data_len] = '\0';

			if(data_len == BULK_READ) 
			{
				chunk_len = (int)(data_len - LONG_LEN);
			} 
			else 
			{
				chunk_len = (int)data_len;
			}
            /*parsing given string*/
			ret = parse_line(parser_itm_arry, buffer, chunk_len, &context);
			circle = (int)(data_len-ret);
			if((ret < 0)||(circle < 0))
			{
				error = 1;
				break;
			}
			memmove(buffer, buffer+ret, circle);
		} while(data_len == BULK_READ);
	} 

	if(!error) 
	{
		*root = get_root(context.current_node);
		 ret = PROCESS_SUCCESS;
	} 
	return ret;
}

/**********************************************************************
* FUNCTION NAME:
*   set_type
*
* DESCRIPTION:
*   This function change the type of a node
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     n --the node to modify
*     type--the new type to set
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
*
* None
*
* NOTES:
*
*********************************************************************/
void  set_type(node_t * n, int type)
{
	n->type &= ~(ELM_NODE|CMT_NODE|PI_NODE);
	n->type |= type;
}

/**********************************************************************
* FUNCTION NAME:
*   parent_node
*
* DESCRIPTION:
*  This function change the position of a node in its parent list and allocate 
*   memory for its children
*
* INTERFACE:
*   GLOBAL DATA:
*     xml_node_array
*
*   INPUT:
*     parent --the parent node
*     n--the node to parent
*     xml_type-- XML type
*   OUTPUT:
*      error_code-- succeeded or failed type
*
*   INPUT/OUTPUT:
*      None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* the node to parent
*
* NOTES:
*
*********************************************************************/
node_t *  parent_node(node_t *parent, node_t * n,int xml_type,int *error_code)
{
    node_t* nd = n;
	*error_code = PROCESS_SUCCESS;
	if (nd != NULL)
	{
		/*root node*/
		if(parent == NULL) 
		{
			*error_code = malloc_node(1,&nd,xml_type);
			if (*error_code == PROCESS_SUCCESS)
			{
				/*alloc memory for root node*/
				copy_node_data(nd,n);
                nd->is_nd_closed = 1;
			}
		}
		/*other node*/
		else
		{
			n->prnt = parent;
			/*set node depth*/
			n->depth = n->prnt->depth + 1;
			/*doesn't alloc memory for children node*/
			if (parent->child == NULL)
			{
				/*alloc memory*/
				*error_code = malloc_node(1,&(parent->child),xml_type);
                if (*error_code == PROCESS_SUCCESS)
                {
					copy_node_data(parent->child,n);

					nd = parent->child;
                }	
			}	
			else
			{
				node_t* first_child = parent->child;
				/*alloc memory*/
				*error_code = malloc_node(1,&(parent->child),xml_type);
				if (*error_code == PROCESS_SUCCESS)
				{
					copy_node_data(parent->child,n);
					/*add brother to child node*/
					parent->child->sibl = first_child;
					
					nd = parent->child;
				}		
			}
		}
	}
	return nd;
}

/**********************************************************************
* FUNCTION NAME:
*   copy_node_data
*
* DESCRIPTION:
*  This function copy the source node data to destination node.
*   
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     dest_node --destination node
*     src_node--source node
*
*   OUTPUT:
*      None
*
*   INPUT/OUTPUT:
*       None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* None
*
* NOTES:
*
*********************************************************************/
void copy_node_data(node_t* dest_node,node_t* src_node)
{
	if ((dest_node != NULL) && (src_node !=NULL))
	{
		int i = 0 ;
		dest_node->cur_attr_index = src_node->cur_attr_index;
		dest_node->depth = src_node->depth;
		dest_node->end = src_node->end;
		dest_node->child = src_node->child;
		dest_node->sibl = src_node->sibl;
		dest_node->is_nd_closed = src_node->is_nd_closed;
		strcpy(dest_node->node_name,src_node->node_name);
		dest_node->pos = src_node->pos;
		dest_node->prnt = src_node->prnt;
		dest_node->type = src_node->type;
		dest_node->attr = src_node->attr;
	}
}
/**********************************************************************
* FUNCTION NAME:
*   init_node_arry
*
* DESCRIPTION:
*  This function initial the node array
*   
*
* INTERFACE:
*   GLOBAL DATA:
*     xml_node_array
*
*   INPUT:
*     node_arr-- node array
*     count -- number of nodes
*
*   OUTPUT:
*      None
*
*   INPUT/OUTPUT:
*       None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* None
*
* NOTES:
*
*********************************************************************/
void init_node_arry(node_t node_arr[],int count)
{
	int i = 0;
	for ( ; i < count ; i++)
	{
		/*init node*/
		init_node(&(node_arr[i]));
	}
}
/**********************************************************************
* FUNCTION NAME:
*   init_attr_arry
*
* DESCRIPTION:
*  This function initial the attributes array
*   
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     count -- number of attributes
*
*   OUTPUT:
*      attr_arr-- attributes array
*
*   INPUT/OUTPUT:
*       None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* None
*
* NOTES:
*
*********************************************************************/
void init_attr_arry(attribute_t attr_arr[],int count)
{
	int i = 0;
	for ( ; i < count ; i++)
	{
		/*init node*/
		initial_attr(&(attr_arr[i]));
	}
}
/**********************************************************************
* FUNCTION NAME:
*   malloc_node
*
* DESCRIPTION:
*  This function malloc nodes with specified count. 
*   
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     node_count -- number of nodes
*     type - XML type
*   OUTPUT:
*      head-- point to malloc node
*
*   INPUT/OUTPUT:
*       None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* If malloc node succeed return PROCESS_SUCCESS, else return error code.
*
* NOTES:
*
*********************************************************************/
int malloc_node(int node_count,node_t** head,int type)
{
	int ret = PROCESS_SUCCESS;
	/*malloc first array node*/
	if (type == 1)
	{
		ret = malloc_fst_arr_node(node_count,head);
	}
	/*malloc second array node*/
	else
	{
		ret = malloc_scd_arr_node(node_count,head);
	}
	return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   malloc_attribute
*
* DESCRIPTION:
*   This function malloc attribute for node
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     n --given node
*     type - FIRST_XML or SECOND_XML
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
*
* This function return allocated attribute pointer
*
* NOTES:
*
*********************************************************************/
attribute_t* malloc_attribute(node_t *n,int type)
{
    attribute_t* attr = NULL;
	int ret = PROCESS_SUCCESS;
	/*malloc first array node*/
	if (type == FIRST_XML)
	{
		ret =malloc_fst_arr_attr(n,&attr);
	}
	/*malloc second array node*/
	else
	{
		ret = malloc_scd_arr_attr(n,&attr);
	}
	if (ret == OUT_OF_MEMORY)
	{
		attr = NULL;
	}
	return attr;
}
/**********************************************************************
* FUNCTION NAME:
*   malloc_attr_value
*
* DESCRIPTION:
*   This function malloc attribute value for given attribute
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     attr --given attribute
*     type - FIRST_XML or SECOND_XML
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
*
* This function PROCESS_SUCCESS if malloc successful. else return error code.
*
* NOTES:
*
*********************************************************************/
int malloc_attr_value(attribute_t *attr,int count,int type)
{
	int ret = PROCESS_SUCCESS;
	/*malloc first array node*/
	if (type == FIRST_XML)
	{
		ret =malloc_fst_arr_val_attr(attr,count);
	}
	/*malloc second array node*/
	else
	{
		ret = malloc_scd_arr_val_attr(attr,count);
	}
	return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   malloc_fst_arr_node
*
* DESCRIPTION:
*  This function allocate a set of nodes.
*   
*
* INTERFACE:
*   GLOBAL DATA:
*     xml_node_array
*
* INPUT:
*     node_count--request node count
*     
* OUTPUT:
*      None
*
* INPUT/OUTPUT:
*      head--a pointer point to the allocated node pointer
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* if allocate succeed return the PROCESS_SUCCESS otherwise return error type
*
* NOTES:
*
*********************************************************************/
int malloc_fst_arr_node(int node_count,node_t** head)
{
	int error_code = PROCESS_SUCCESS;
	int i = 0;
	if ((fsrt_index.node_unused_index+node_count) < NODE_ARRAY_COUNT)
	{
        *head = &(xml_node_array[fsrt_index.node_unused_index]);
		i = fsrt_index.node_unused_index;
		for (; i < (fsrt_index.node_unused_index+node_count); i++)
		{
			/*init node*/
			init_node(&xml_node_array[i]);
			xml_node_array[i].state = ALLOCTE;
		}
		fsrt_index.node_unused_index += node_count;
	}
	else
	{
		error_code = OUT_OF_MEMORY;
	}
	return error_code;
}
/**********************************************************************
* FUNCTION NAME:
*   malloc_scd_arr_node
*
* DESCRIPTION:
*  This function allocate a set of nodes.
*   
*
* INTERFACE:
*   GLOBAL DATA:
*     scnd_xml_node_arr
*
* INPUT:
*     node_count--request node count
*     
* OUTPUT:
*      None
*
* INPUT/OUTPUT:
*      head--a pointer point to the allocated node pointer
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* if allocate succeed return the PROCESS_SUCCESS otherwise return error type
*
* NOTES:
*
*********************************************************************/
int malloc_scd_arr_node(int node_count,node_t** head)
{
	int error_code = PROCESS_SUCCESS;
	int i = 0;
	if ((scd_index.node_unused_index+node_count) < ES_NODE_ARR_CNT)
	{
        *head = &(scnd_xml_node_arr[scd_index.node_unused_index]);
		i = scd_index.node_unused_index;
		for (; i < (scd_index.node_unused_index+node_count); i++)
		{
			/*init node*/
			init_node(&scnd_xml_node_arr[i]);
			scnd_xml_node_arr[i].state = ALLOCTE;
		}
		scd_index.node_unused_index += node_count;
	}
	else
	{
		error_code = OUT_OF_MEMORY;
	}
	return error_code;
}

/**********************************************************************
* FUNCTION NAME:
*   init_node
*
* DESCRIPTION:
*  This function initial a given node.
*   
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
* INPUT:
*     n--given node
*    
* OUTPUT:
*      None
*
* INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* None
*
* NOTES:
*
*********************************************************************/
void init_node(node_t* n)
{
	int j = 0;
	n->cur_attr_index = -1;
	n->depth = -1;
	n->end = -1;
	n->child = NULL;
	n->sibl = NULL;
	strcpy(n->node_name,"");
	n->pos = -1;
	n->prnt = NULL;
	n->type = NONE_NODE;
	n->state = UNALLOCTE;
	n->attr = NULL;
}

/**********************************************************************
* FUNCTION NAME:
*   copy_string
*
* DESCRIPTION:
*   This function copy source string to destination string
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     dest --destination string
*     src--source string
*     src_len --length of source string
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
*
* None
*
* NOTES:
*
*********************************************************************/
void copy_string(char* dest,char* src,const int src_len)
{
	strncpy(dest,src,src_len);
	dest[src_len] = '\0';
}
/**********************************************************************
* FUNCTION NAME:
*   write_node_begin
*
* DESCRIPTION:
*   This function write the begin of the node to xml file.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     file --source xml file
*     nd-- node pointer
*   
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
*
* None
*
* NOTES:
*
*********************************************************************/
void write_node_begin(FILE *file,node_t* nd)
{
	attribute_t* p_attr = NULL;
	int attr_index = 0;
	int len = 0;
	/*format*/
	print_format(file,nd);
	/*start of the node*/
	/*write node name*/
	fprintf(file,"<%s",nd->node_name);
	len = (int)strlen(nd->node_name);
	/*node has attribute*/
	if(nd->cur_attr_index >= 0)
	{
		/*write attributes*/
		p_attr = nd->attr;
		while (p_attr != NULL)
		{
			print_attribute(file,p_attr->name,p_attr->value);
			p_attr = p_attr->next;
		}
	}

	/*node single*/
	if (nd->child == NULL)
	{
		fprintf(file,"/>");
	}
	else
	{
		fprintf(file,">");
	}
	fprintf(file,"\n");
	
}
/**********************************************************************
* FUNCTION NAME:
*   write_node_end
*
* DESCRIPTION:
*   This function write the end of the node to xml file.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     file --source xml file
*     nd-- node pointer
*     p_stk--stack store unwritten node pointer
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
*
* None
*
* NOTES:
*
*********************************************************************/
void write_node_end(FILE *file,node_t* nd,stack_t* p_stk)
{
    node_t*	prnt = nd->prnt;
   
	/*the leaf node of the tree and the last leaf node*/
	if ((nd->child == NULL )&& 
		(nd == prnt->child))
	{
		/*if has been written the parent node in xml file*/ 
		while(prnt && 
			(0 != strncmp(prnt->node_name,"xml",3))&&
			(0 == stack_elem_in(p_stk,prnt->child)) &&
			 (NULL != prnt->child))
		{
			int len = 0;
			/*format*/
			print_format(file,prnt);
			fprintf(file,"</%s>",prnt->node_name);
			fprintf(file,"\n");
            len = (int)strlen(prnt->node_name);
			prnt = prnt->prnt;
		}
	}
}

/**********************************************************************
* FUNCTION NAME:
*   print_attribute
*
* DESCRIPTION:
*   This function write the given attribute name and value to xml file.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     file --source xml file
*     name-- attribute name pointer
*     value--attribute value pointer
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
*
* None
*
* NOTES:
*
*********************************************************************/
void print_attribute(FILE *file,char*name,char*value)
{
	/*get output CRC value*/
	int len = 0;
	/*doesn't consider dquoted and quoted*/
	fprintf (file, " %s=", name);
	fprintf(file,"\"%s\"",value);
	len = (int)strlen(name);
	len = (int)strlen(value);
	
}
/**********************************************************************
* FUNCTION NAME:
*   print_format
*
* DESCRIPTION:
*   This function write white space to xml file and make it easy to read.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     file --source xml file
*     nd-- write white space in the given node
*
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
*
* None
*
* NOTES:
*
*********************************************************************/
void  print_format(FILE *file,node_t* nd)
{
	if (-1 != nd->depth)
	{
		int i = 0;
		for (; i < nd->depth; i++)
		{
			fprintf( file, "    " );
		}
	}
}

/**********************************************************************
* FUNCTION NAME:
*   print_declaration
*
* DESCRIPTION:
*   This function write the head of xml file
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     file --xml file
*     root-- root node pointer
*
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
*
* None
*
* NOTES:
*
*********************************************************************/
void  print_declaration(FILE *file,node_t* root)
{
	int len = 0;
	/*get xml version and encoding */
	fprintf( file, "<?xml " );
	fprintf (file, "version=\"%s\"", root->attr->value);
	fprintf (file, " encoding=\"%s\"", root->attr->next->value);
	fprintf( file, "?>" );
	/*line end*/
	fprintf(file,"\n");
	len = (int)strlen(root->attr->value);
	len = (int)strlen(root->attr->next->value);
	
}
/**********************************************************************
* FUNCTION NAME:
*   set_axes
*
* DESCRIPTION:
*   this function set the axes to a xpath node from xpath string
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     node -- the xpath node to fill
*     axes--  the string where axes is extracted from
*     offset--the detected offset in axes string
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
*
* return the filled xpath_node
*
* NOTES:
*
*********************************************************************/
xpath_node_t  *set_axes(xpath_node_t *node, char *axes, int *offset)
{
	struct _xpath_axes 
	{
		char id;
		char *name;
	};

	struct _xpath_axes xpath_axes[3] = 
	{
		{ID_PARENT, S_PARENT},
		{ID_SELF, S_SELF},
		{ID_ATTR, S_ATTR},
	};

	if (axes[0] == '/') 
	{
		axes[0] = '\0';
		*offset += 1;
		axes++;
	}
	if (axes[0] == '/') 
	{
		(*offset)++;
		axes++;
		/*S_DESC_O_SELF*/
		node->axes = ID_DESC_O_SELF;
		node->axes_name = axes;
		/*is search attribute*/
		if (axes[0] == '@')
		{
			(*offset)++;
			node->axes = ID_DESC_AND_ATTR;
			node->axes_name = axes+1;
		}
	}
	/*is attribute */
	else if (axes[0] == '@')
	{
		(*offset)++;
		node->axes = ID_CHILD_AND_ATTR;
		node->axes_name = axes+1;
	}
	else
	{
		int i = 0;
		/*S_CHILD is default*/
		node->axes = ID_CHILD;
		node->axes_name = axes;
		for (i = 0; i < 3; i++) 
		{
			int len = (int)strlen(xpath_axes[i].name);
			if (strncmp(xpath_axes[i].name, axes, len) == 0) 
			{
				node->axes = xpath_axes[i].id;
				node->axes_name = axes + len;
				break;
			}
		}
	}
	return node;
}

/**********************************************************************
* FUNCTION NAME:
*   parse_xpath
*
* DESCRIPTION:
*   This function convert an xpath string to a table of list of xpath_node_t
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     path -- the xpath string
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
*
* return the filled xpath_node
*
* NOTES:
*
*********************************************************************/
int  parse_xpath(char *path)
{
	int ret = 0;
	xpath_ctx_t ctx;
	xpath_parser_item_t *parser = &(xpath_parser_arry[0]);
	ctx.pos = 0;
	ctx.row = 0;
	ctx.col = 0;
	ctx.bracket = 0;
	ctx.quoted = 0;
	ctx.dquoted = 0;
	ctx.content_quoted = 0;
	ctx.is_first_node = 1;
	ctx.is_next_or_path_node = 0;
	ctx.first_node = &(xpath_nd_array[ctx.row][ctx.col]);
	ctx.new_node = ctx.first_node;
	ctx.new_cond = NULL;
	ctx.first_node->rel = OPERATOR_OR;

	append_xpath_parser_item(parser++, " ", _func_xpath_ignore);
	append_xpath_parser_item(parser++, "\t", _func_xpath_ignore);
	append_xpath_parser_item(parser++, "\n", _func_xpath_ignore);
	append_xpath_parser_item(parser++, "\r", _func_xpath_ignore);
	append_xpath_parser_item(parser++, "\"", _func_xpath_dquote);
	append_xpath_parser_item(parser++, "\'", _func_xpath_quote);
	append_xpath_parser_item(parser++, "/", _func_xpath_new_node);
	append_xpath_parser_item(parser++, "[", _func_xpath_open_brackets);
	append_xpath_parser_item(parser++, "]", _func_xpath_close_brackets);
	append_xpath_parser_item(parser++, "=", _func_xpath_operator_equal);
	append_xpath_parser_item(parser++, PATH_OR, _func_xpath_path_or);
	append_xpath_parser_item(parser++, COND_OR, _func_xpath_condition_or);
	append_xpath_parser_item(parser++, COND_AND, _func_xpath_condition_and);
	append_xpath_parser_item(parser, NULL, _func_xpath_default);
   /* parsing xpath*/
	ret = parse_xpath_line(xpath_parser_arry, path, 0, &ctx);

	if (ret >= 0) 
	{
		/*number of xpath*/
		ret =  ctx.row+ 1;
	}

	return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   init_xpath_array
*
* DESCRIPTION:
*   This function initial the xpath array
*
* INTERFACE:
*   GLOBAL DATA:
*     xpath_nd_array --xpath node array
*
*   INPUT:
*     None
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
*
* None
*
* NOTES:
*
*********************************************************************/
void init_xpath_array()
{
	int indx_i = 0;
	int indx_j = 0;
	/*initial all '|' xpath*/
	for(indx_i = 0 ; indx_i < TOTAL_XPATH ; indx_i++)
	{
	   /* initial per xpath node*/
		for (indx_j = 0 ; indx_j < MAX_NODE_PER_XPATH; indx_j++)
		{
			int k = 0;
			xpath_cond_t *cond_array = NULL;
			xpath_nd_array[indx_i][indx_j].abs = 0;
			xpath_nd_array[indx_i][indx_j].axes =ID_NONE;
			xpath_nd_array[indx_i][indx_j].cur_cond_index = -1;
			xpath_nd_array[indx_i][indx_j].axes_name = NULL;
			xpath_nd_array[indx_i][indx_j].rel = OPERATOR_NONE;
			cond_array = xpath_nd_array[indx_i][indx_j].cond_array;
			/*initial xpath node condition*/
			for (k = 0; k < MAX_COND_COUNT ; k++)
			{
				cond_array[k].arg1 = NULL;
				cond_array[k].arg2 = NULL;
				cond_array[k].axes = ' ';
				cond_array[k].func = FUNC_NONE;
				cond_array[k].op = ' ';
				cond_array[k].rel = ' ';
				cond_array[k].xp = NULL;
			}
		}	
	}
}
/**********************************************************************
* FUNCTION NAME:
*   exec_xpath
*
* DESCRIPTION:
*  This function exec a decoded xpath structure
*
* INTERFACE:
*   GLOBAL DATA:
*    xpath_nd_array-- xpath node array
*
*   INPUT:
*     root--the root of the  tree
*      n--the context node
*		max_xp_count--max numbers of '|' xpath
*		
*
*   OUTPUT:
*     count--node set numbers
*
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* if successfully executed return PROCESS_SUCCESS otherwise return the error type.
*
* NOTES:
*
*********************************************************************/
int exec_xpath(node_t *root, node_t * n, int max_xp_count, int *count)
{
	int ret = PROCESS_SUCCESS;
	int index_i = 0;
	int index_j = 0;
	int input_arr_count = 0;
	int output_arr_count = 0;
	int start = 0;
	int per_path_count = 0;
	clear_array_data(tmp_input__array,MAX_XPATH_RES_REC);
	clear_array_data(tmp_output_arry,MAX_XPATH_RES_REC);
	/* process all '|' xpath*/
	for (index_i = 0; index_i < max_xp_count; index_i++) 
	{
		if (ret == XPATH_ERROR)
		{
			break;
		}
		/*first time add node to input_arr_count array*/
		if (input_arr_count == 0)
		{
			tmp_input__array[input_arr_count] = n;
			input_arr_count++;
		}
		/*process per xpath node*/
         for (index_j = 0; index_j < MAX_NODE_PER_XPATH; index_j++)
         {

			 if ((ret == XPATH_ERROR) || 
				 (xpath_nd_array[index_i][index_j].axes_name == NULL))
			 {
				 break;
			 }
			 else
			 {
				 if (output_arr_count != 0)
				 {
					 start = 0;
					 /*clear input array data*/
					 clear_array_data(tmp_input__array,input_arr_count);
					 /*set tmp_input__array validate element count*/
					 input_arr_count = output_arr_count;
					 copy_array_data(tmp_input__array,tmp_output_arry,start,output_arr_count);
				 }
				 ret =check_node(&(xpath_nd_array[index_i][index_j]),root,tmp_input__array,tmp_output_arry,input_arr_count,&output_arr_count);
			 }
         }
		 start += per_path_count;
		 per_path_count = output_arr_count;
		  /*add validate node to result array*/
		 copy_array_data(res_node_array,tmp_output_arry,start,per_path_count);
		/* reset the tmp_output_arry and tmp_input_array data and useful data count*/
		 clear_array_data(tmp_output_arry,output_arr_count);
		 output_arr_count = 0;
         clear_array_data(tmp_input__array,input_arr_count);
		 input_arr_count = 0;
		 *count += per_path_count;
	}
	return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   copy_array_data
*
* DESCRIPTION:
*  This function copy the source array data to destination array
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*
*   INPUT:
*      src_array--source array
*		start--array index to start copying 
*		count--copy node numbers
*
*   OUTPUT:
*      None
*
*   INPUT/OUTPUT:
*      dest_array--destination array
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* None
*
* NOTES:
*
*********************************************************************/
 void copy_array_data(node_t* dest_array[],node_t* src_array[],const int start,const int count)
 {
	 int i = start ;
	 for (; i < (start+count) ; i++)
	 {
		 dest_array[i] = src_array[i-start];
	 }
 }
 /**********************************************************************
 * FUNCTION NAME:
 *   clear_array_data
 *
 * DESCRIPTION:
 *  This function clear array data.
 *
 * INTERFACE:
 *   GLOBAL DATA:
 *    None
 *
 *   INPUT:
 *      count--array node numbers
 *		
 *
 *   OUTPUT:
 *      None
 *
 *   INPUT/OUTPUT:
 *      nd_array--node array
 *
 * AUTHOR:
 *   Fu Pei
 *
 * RETURN VALUE:
 *
 * None
 *
 * NOTES:
 *
 *********************************************************************/
 void clear_array_data(node_t* nd_array[],const int count)
 {
	 int i = 0;
     for ( ; i < count; i++)
     {
		 nd_array[i] = NULL;
     }  
 }

 /**********************************************************************
 * FUNCTION NAME:
 *   check_node
 *
 * DESCRIPTION:
 *  This function perform the xpath test on a tree.
 *
 * INTERFACE:
 *   GLOBAL DATA:
 *    None
 *
 *   INPUT:
 *     xp--the xpath nodes to test
 *     root--the root node
 *		input_arr_array--input node array
 *     input_arr_count--numbers of input node
 *    
 *   OUTPUT:
 *      None
 *   INPUT/OUTPUT:
 *      output_arr_array--satisfy xpath node array
 *      output_arr_count--numbers of output node
 *
 * AUTHOR:
 *   Fu Pei
 *
 * RETURN VALUE:
 *
 * if test xpath node success return PROCESS_SUCCESS otherwise return error type.
 *
 * NOTES:
 *
 *********************************************************************/
int  check_node(xpath_node_t * xp, node_t * root,node_t* input_arr_array[],node_t* output_arr_array[],
				        const int input_arr_count,int* output_arr_count)
{
	int ret = PROCESS_SUCCESS;
	int index = 0;
	int output_index = 0;
	xpath_node_t *temp_xp = xp;
	node_t* context = NULL;
	int validate = 0;
	/*process all xpath node*/
	for (;index < input_arr_count; index++)
	{
		context = input_arr_array[index];

		switch (temp_xp->axes) 
		{
		case ID_CHILD:
		case ID_CHILD_AND_ATTR:
			/*if it's absolute path set root node*/
			if (temp_xp->abs == 1)
			{
				context = root;
			}
			
			/*has child*/
			if (context->child == NULL)
			{
				validate = 0;
			}
			else
			{
				/*find child which is named as xp->name*/
				int i = 0;
				node_t* current = context->child;
				/*search for child*/
				while(current)
				{
					/*confirm whether node is validate*/
					validate =  validate_axes(root, current, temp_xp);
					if (validate == 1)
					{
						/*add validate node to output_arr_array array*/
						output_arr_array[output_index] = current;
						output_index++;
					}
					current = current->sibl;
				}
			}		
			break;
		case ID_DESC_O_SELF:
		case ID_DESC_AND_ATTR:
			if (xp->abs == 1)
			{
				context = root;
			}
			validate = process_desc_self(root,context,temp_xp,output_arr_array,&output_index);
			break;
		case ID_SELF:
			/*is node validate */
			validate =  validate_axes(root, context, temp_xp);
			if (validate == 1)
			{
				/*add validate node to output node array*/
				output_arr_array[output_index] = context;
				output_index++;
			}
			break;
		case ID_PARENT:
			if (context->prnt) 
			{
				validate =  validate_axes(root, context->prnt, temp_xp);
				if (validate == 1)
				{
					output_arr_array[output_index] = context->prnt;
					output_index++;
				}
			} 
			else
			{
				validate = 0;
			}
			break;
		case ID_ATTR:
			validate =  validate_axes(root, context, temp_xp);
			if (validate == 1)
			{
				output_arr_array[output_index] = context;
				output_index++;
			}
			break;
		default:
			ret = XPATH_ERROR;
			break;
		}
	}
	*output_arr_count = output_index;
	return ret;
}

/**********************************************************************
* FUNCTION NAME:
*   process_desc_self
*
* DESCRIPTION:
*  This function handle the xpath node and its type id is ID_DESC_O_SELF 
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*
*   INPUT:
*     root--the root node
*     context--the context node
*     xp--the xpath nodes to test 
*     
*   OUTPUT:
*      None
*   INPUT/OUTPUT:
*      output_arr_array--satisfy xpath node array
*      output_arr_count--numbers of output node
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* if test xpath node success return PROCESS_SUCCESS otherwise return error type.
*
* NOTES:
*
*********************************************************************/
static int process_desc_self(node_t* root,node_t* context,xpath_node_t* xp,
					           node_t* output_arr_array[],int* output_index)
{
	int ret = PROCESS_SUCCESS;

	int validate = 0;
	/*get all children node  of current node*/
	/*create stack*/
	stack_t stk;
	node_t* child = context->child;
	init_stack(&stk);
	/*push all child of the node to stack*/
	while(child)
	{
		/*push data to stack*/
		push(&stk,child);
		child =  child->sibl;
	}
	/*is stack empty*/
	while (!stack_empty(&stk))
	{ 
		node_t* nd = NULL;
		node_t* nd_child = NULL;
		/*get node from the stack*/
		pop(&stk,&nd);
		/*node validate*/
		validate =  validate_axes(root, nd, xp);
		if (validate == 1)
		{
			ret = 1;
			output_arr_array[*output_index] = nd;
			(*output_index)++;
		}
		if (validate == XPATH_ERROR)
		{
			ret = validate;
			break;
		}
		/*does nd node have child*/
		nd_child = nd->child;
		/*push all nd_child to stack*/
		while (nd_child)
		{
			push(&stk,nd_child);

			nd_child = nd_child->sibl;
		}/*end while*/
	}/*end while*/
	return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   validate_axes
*
* DESCRIPTION:
*  This function validate if an axes is matching the current node
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*
*   INPUT:
*     root--the root node
*	   candidat--the node to test
*     xn--the xpath node to test
*   
*   OUTPUT:
*      None
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* if test node success return PROCESS_SUCCESS otherwise return error type.
*
* NOTES:
*
*********************************************************************/
int  validate_axes(node_t *root, node_t * candidat,xpath_node_t *xn)
{
	int valid = 0;
	char *axes = NULL;
	if (xn == NULL) 
	{
		valid = XPATH_ERROR;
	} 
	else 
	{
		axes = xn->axes_name;
		/*wildcard for all nodes*/
		if (strcmp("*", axes) == 0) 
		{
			valid = PROCESS_SUCCESS;
		} 
		/*isn't error node*/
		else if (valid != XPATH_ERROR)
		{
			if ((xn->axes == ID_SELF) || (xn->axes == ID_PARENT))
			{
				valid = PROCESS_SUCCESS;
			}
		}
	}
    /*isn't error xpath*/
	if ((!valid) && (valid != XPATH_ERROR)) 
	{
		/*search for node attribute*/
		if ((xn->axes == ID_ATTR) ||  (xn->axes == ID_DESC_AND_ATTR) || 
			(xn->axes == ID_CHILD_AND_ATTR))
		{
			int attr_index = 0;
			while(attr_index <= candidat->cur_attr_index)
			{
				if (strcmp(candidat->attr[attr_index].name, axes) == 0)
				{
					valid = PROCESS_SUCCESS;
					break;
				}
				attr_index++;
			}
		}
		else if (xn->axes == ID_CHILD)
		{
			/*find child by its name*/
			if ( strcmp(candidat->node_name, axes) == 0) 
			{
				valid = PROCESS_SUCCESS;
			}
		}
		else if (xn->axes == ID_DESC_O_SELF)
		{
			if (strcmp(candidat->node_name, axes) == 0) 
			{
				valid = PROCESS_SUCCESS;
			}
		}
		else
		{
			valid = XPATH_ERROR;
		}
	}
	if (valid == PROCESS_SUCCESS)
	{
		valid = validate_predicat(xn, candidat);
	}

	return valid;
}
/**********************************************************************
* FUNCTION NAME:
*   validate_predicat
*
* DESCRIPTION:
*  This function check for predicate validity, predicate is part between brackets
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*
*   INPUT:
*     xn--the xpath node containing the predicate to test
*     candidat--the node to test
*	
*   OUTPUT:
*      None
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
*return 1 if predicate is validated, else 0
*
* NOTES:
*
*********************************************************************/
int  validate_predicat(xpath_node_t *xn, node_t* candidat)
{
	int valid = 0;
	xpath_cond_t *condition;

	if ((xn == NULL))
	{
		valid = XPATH_ERROR;
	}
    if (xn->cur_cond_index == -1)
    {
		valid = 1;
    }
	else
	{
		int index = 0;
		
		while (index <= xn->cur_cond_index) 
		{
			int status = 0;
			char *sarg1 = NULL;
			char *sarg2 = NULL;
			condition = &(xn->cond_array[index]);
			/*string compare*/
			if (condition->func == FUNC_STRCOMP) 
		    {
				attribute_t  *attr = get_attribute(candidat, condition->arg1);
				 status = 0;
				 if (attr != NULL)
				 {
					  sarg1 = attr->value;
				 }
				 sarg2 = condition->arg2;
				 if ((condition->op == OPERATOR_EQU) &&
					 sarg1 != NULL &&
					 (strcmp(sarg1, sarg2) == 0))
				 {
					  status = 1;
				 }
			} 
			else
			{
				 valid = XPATH_ERROR;
			}
			/*valid xpath*/
			if (valid != XPATH_ERROR)
			{
				/*"or" condition*/
				if (condition->rel == OPERATOR_OR) 
				{
					valid = valid || status;
				} 
				/*"and" condition*/
				else if (condition->rel == OPERATOR_AND)
				{
					valid = valid && status;
				}
				else
				{
					valid = status;
				}
			}
			index++;
		}
	}
	return valid;
}
/**********************************************************************
* FUNCTION NAME:
*   is_cur_nd_valid
*
* DESCRIPTION:
*  This function check current node
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*
*   INPUT:
*     cur_node--the current node test
*	
*   OUTPUT:
*      None
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
*return PROCESS_SUCCESS node is valid, else NODE_ERROR
*
* NOTES:
*
*********************************************************************/
int is_cur_nd_valid(node_t* cur_node)
{
	int ret_value = PROCESS_SUCCESS;
	/*is current node valid*/
	node_t* prnt = cur_node->prnt;
	while ( (prnt != NULL) && (prnt->prnt != NULL))
	{
		/*is node name equal*/
		if (strcmp(prnt->node_name,cur_node->node_name) == 0)
		{
			ret_value = NODE_ERROR;
			break;
		}
		prnt = prnt->prnt;
	}
	return ret_value;
}
/**********************************************************************
* FUNCTION NAME:
*   is_head_correct
*
* DESCRIPTION:
*  This function check is XML head valid.
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*
*   INPUT:
*     head--head node
*	
*   OUTPUT:
*      None
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
*return PROCESS_SUCCESS if head node is valid, else HEAD_ERROR
*
* NOTES:
*
*********************************************************************/
int is_head_correct(node_t* head)
{
	int head_correct = PROCESS_SUCCESS;
	/*check head attribute*/
	if (head != NULL)
	{
		attribute_t *attr = NULL;
		attr = get_attribute(head,"version");
		if (attr == NULL)
		{
			head_correct = HEAD_ERROR;
		}
		else
		{
			if (strcmp(attr->value,"1.0") != 0)
			{
				head_correct = HEAD_ERROR;
			}
		}
		attr = get_attribute(head,"encoding");
		if (attr == NULL)
		{
			head_correct = HEAD_ERROR;
		}
		else
		{
			if (stricmp(attr->value,"UTF-8") != 0)
			{
				head_correct = HEAD_ERROR;
			}
		}
	}
	/*has more than 2 attributes*/
	if (head->cur_attr_index > 1)
	{
		head_correct = HEAD_ERROR;
	}
	return head_correct;
}