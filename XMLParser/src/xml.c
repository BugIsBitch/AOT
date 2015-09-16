/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml.c
*
* FILE DESCRIPTION:
*   API
*
* DEFINED FUNCTION:
*   load_doc
*   get_root
*   get_name
*   get_element
*   get_attribute
*   set_attr_value
*   save_file
*   xpath
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
#include "../include/xml.h"
#include "../include/xml_stack.h"
#include "assert.h"
#include "../include/xml_global.h"
#include <stdlib.h>
#include <stdio.h>
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DECLARATIONS ---------------------*/

/*the node pointer array which satisfy the xpath condition*/
extern node_t* res_node_array[MAX_XPATH_RES_REC];
/*store all the xml node info*/
extern node_t xml_node_array[NODE_ARRAY_COUNT];
/*store all the second XML node info*/
extern node_t scnd_xml_node_arr[ES_NODE_ARR_CNT];
extern attribute_t xml_attr_array[ATTR_ARR_CNT];/*store all XML attribute*/
extern attribute_t scd_attr_array[ES_ATTR_ARR_CNT];/*store all XML attribute*/
extern char xml_attr_value_arr[ATTR_VAL_ATT_CNT];/*attribute value array*/
char scd_attr_value_arr[ES_ATTR_VAL_CNT];/*attribute value array*/
extern cur_arr_index_t scd_index;/*second DOM used array index*/
extern cur_arr_index_t fsrt_index;/*first DOM used array index*/
/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/

/**********************************************************************
* FUNCTION NAME:
*   load_doc
*   
* DESCRIPTION:
*    This function load a file document by parsing all the corresponding nodes
*
* INTERFACE:
*   GLOBAL DATA:
*     
*
*   INPUT:
*     filename --file name the XML document to load
*     
*
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     root--point to the root pointer
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*  if it parses xml failed return error type otherwise return PROCESS_SUCCESS
*
* NOTES:
*
*********************************************************************/
int  load_doc(char *filename,node_t** root)
{
	int error_code = PROCESS_SUCCESS;
	FILE* file = NULL;
	fsrt_index.attr_unused_index = 0;
	fsrt_index.node_unused_index =0;
	fsrt_index.unused_attr_value_index = 0;
	/*whether the file is a xml file*/
	if(is_xml_file(filename) == 1)
	{
       file = fopen(filename, "r");
	}
   /* initial the xml node array*/
	init_node_arry(xml_node_array,NODE_ARRAY_COUNT);
	init_attr_arry(xml_attr_array,ATTR_ARR_CNT);
	memset(xml_attr_value_arr,0,ATTR_VAL_ATT_CNT);
	
	if(file != NULL)	
	{
		error_code  =  load(file,root,FIRST_XML);
		fclose(file);
	}
	else
	{
         error_code = FILE_OPEN_ERROR;
	}
	
	return error_code;
}
/**********************************************************************
* FUNCTION NAME:
*   load_second_doc
*   
* DESCRIPTION:
*    This function load a file document by parsing all the corresponding nodes
*
* INTERFACE:
*   GLOBAL DATA:
*     
*
*   INPUT:
*     filename --file name the XML document to load
*     
*
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     root--point to the root pointer
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*  if it parses xml failed return error type otherwise return PROCESS_SUCCESS
*
* NOTES:
*
*********************************************************************/
int  load_second_doc(char *filename,node_t** root)
{
	int error_code = PROCESS_SUCCESS;
	FILE* file = NULL;
	scd_index.attr_unused_index = 0;
	scd_index.node_unused_index =0;
	scd_index.unused_attr_value_index = 0;
	/*whether the file is a XML file*/
	if(is_xml_file(filename) == 1)
	{
       file = fopen(filename, "r");
	}
   /* initial the xml node array*/
	init_node_arry(scnd_xml_node_arr,ES_NODE_ARR_CNT);
	init_attr_arry(scd_attr_array,ES_ATTR_ARR_CNT);
	memset(scd_attr_value_arr,0,ES_ATTR_VAL_CNT);
	if(file != NULL)	
	{
		error_code  =  load(file,root,SECOND_XML);
		fclose(file);
	}
	else
	{
         error_code = FILE_OPEN_ERROR;
	}

	return error_code;
}
/**********************************************************************
* FUNCTION NAME:
*   is_xml_file
*   
* DESCRIPTION:
*    This function judge whether the file ext is ".xml"
*
* INTERFACE:
*   GLOBAL DATA:
*     
*
*   INPUT:
*     file_path --file path the XML document to load
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
*  if it the file is a xml file return 1 else return 0
*
* NOTES:
*
*********************************************************************/
static int is_xml_file(char* file_path)
{
	int ret = 0;
	if (file_path != NULL)
	{
		char ext[_MAX_EXT];  
		_splitpath( file_path, NULL, NULL, NULL, ext ); 
		if (strcmp(ext,".xml") == 0)
		{
			ret = 1;
		}
	}
     return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   get_root
*
* DESCRIPTION:
*    This function returns the root of a tree containing the given node
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*
*   INPUT:
*     n --given node pointer
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
*  the root node pointer of tree
*
* NOTES:
*
*********************************************************************/
node_t *  get_root(node_t *n)
{
	node_t* ret_node = NULL;
	if(n)	
	{
		node_t * root = NULL;
		root = n;
		while(root->prnt) root = root->prnt;

		if(root && get_type(root) == PI_NODE) 
		{
			char root_name[16];
			node_t * lone_elm_node = 0;
			get_name(root,root_name,16);
			if(strcmp(root_name, "xml") == 0) 
			{
			    ret_node =  root;
			}
		}
	}
	return ret_node;
}

/*********************************************************************
* FUNCTION NAME:
*   get_name
*
* DESCRIPTION:
*   This function get the name with a given node
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     n --given node pointer 
*     size--the size of buffer pointed by buffer
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     buffer --preserve the node name
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* ret--if the function successfully executed return PROCESS_SUCCESS else return error type
*
* NOTES:
*
*********************************************************************/
int  get_name(node_t *n, char * buffer, int size)
{
	int ret =PROCESS_SUCCESS;
	if (NULL != n)
	{
		int name_len = (int)strlen(n->node_name);
		if ((name_len+1) <= size)
		{
			copy_string(buffer,n->node_name,name_len+1);
		}
		else
		{
			ret = OUT_OF_MEMORY;
		}
	}
	else
	{
		ret = NODE_ERROR;
	}
	return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   get_element
*
* DESCRIPTION:
*   This function get node matching the given name 
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     n --find node with a given node
*     name--matching name
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
* the matching node pointer
*
* NOTES:
*
*********************************************************************/
node_t* get_element(node_t* n, char* name)
{
	stack_t stk;
	node_t *child = NULL;
	node_t* nd = NULL;
	node_t* find_node = NULL;
	assert(n != NULL);
	/*create stack*/
	init_stack(&stk);
	if(n != NULL)
	{
		child = n->child;
	}
	/*push all children of the node to stack*/
	while(child)
	{
		/*push data to stack*/
		push(&stk,child);

		child =  child->sibl;
	}
	/*is stack empty*/
	while (!stack_empty(&stk))
	{ 
		node_t* nd_child = NULL;
		/*get node from the stack*/
		pop(&stk,&nd);
		if (nd != NULL && 0 == strcmp(nd->node_name,name))
		{
			find_node =  nd;
			break;
		}
		/*nd node has child*/
		if(nd != NULL && nd->child != NULL)
		{
			nd_child = nd->child;
			/*push all nd_child to stack*/
			while (nd_child)
			{
				push(&stk,nd_child);
				nd_child = nd_child->sibl;
			}
		}	
	}/*end while*/
	
	return find_node;
}
/**********************************************************************
* FUNCTION NAME:
*   get_attribute
*
* DESCRIPTION:
*   This function get node attribute matching the given attribute name 
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     n --find attribute in the given node
*     name--matching attribute name
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
* the matching attribute pointer
* 
* NOTES:
*
*********************************************************************/
attribute_t* get_attribute(node_t* n,char* attr_name)
{
	attribute_t* p_attr = NULL;
	/*preserve the matching attribute pointer*/
	attribute_t* find_attr = NULL;
	int attr_index = 0;
	if (n != NULL)
	{
		p_attr = n->attr;
		attr_index = n->cur_attr_index;
	     /*node attributes*/
		while (p_attr != NULL)
		{
			if (0 == strcmp(p_attr->name,attr_name))
			{
				find_attr = p_attr;
				break;
			}
			p_attr = p_attr->next;
		}
	}
	return find_attr;
}
/**********************************************************************
* FUNCTION NAME:
*   get_attr_value
*
* DESCRIPTION:
*   This function get attribute value with a given attribute
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     attr --given attribute pointer 
*     size--the size of buffer
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     buffer--preserve the attribute value
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* if execute succeed return PROCESS_SUCCESS
* else return error type
*
* NOTES:
*
*********************************************************************/
int  get_attr_value(attribute_t *attr,char* buffer, int size)
{
	int ret = PROCESS_SUCCESS;
	assert(attr != NULL);
   /* is the buffer has enough space*/
	if(attr != NULL && ((strlen(attr->value)+1) < (unsigned int)size)) 
	{
		size= ((int)strlen(attr->value)) + 1;

		strncpy(buffer, attr->value, size);
	}
	else
	{
		ret = OUT_OF_MEMORY;
	}
		
	return ret;
}


/**********************************************************************
* FUNCTION NAME:
*   add_node
*
* DESCRIPTION:
*   This function add node to the tree
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     parent --parent node pointer 
*     new_node--node which want to be added
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
* if add node failed return the error type otherwise return PROCESS_SUCCESS
*
* NOTES:
*
*********************************************************************/
int add_element(node_t* parent,node_t* new_node)
{
	int ret = PROCESS_SUCCESS;
	int type = 0;
    node_t *root = NULL;
	node_t* chld = NULL;

    if ((NULL == parent) || (NULL == new_node))
    {
         ret = ADD_ELEM_FAILED;
    }
	/*get root element*/
	root = get_root(parent);
	if (root == &(xml_node_array[0]))
	{
		type = FIRST_XML;
	}
	else
	{
		type = SECOND_XML;
	}
	/*doesn't have child*/
	if (parent->child == NULL)
	{
		/*alloc memory*/
		ret = malloc_node(1,&(parent->child),type);
		/*can we add node to tree*/
		if ((ret != ADD_ELEM_FAILED) &&
			(ret != OUT_OF_MEMORY) )
		{
			parent->child->state = ALLOCTE;
			copy_node_data(parent->child,new_node);
		}
	}
	else
	{
		/*get last children*/
		node_t* last_child = parent->child;
		while (last_child)
		{
			last_child = last_child->sibl;
		}
		/*alloc memory*/
		ret = malloc_node(1,&(last_child),type);
		/*can we add node to tree*/
		if ((ret != ADD_ELEM_FAILED) &&
			(ret != OUT_OF_MEMORY) )
		{
			last_child->state = ALLOCTE;
			copy_node_data(last_child,new_node);
		}
	}
	
    return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   add_attribute
*
* DESCRIPTION:
*   This function add attribute to the given node
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     node -- given node pointer 
*     name--attribute name
*    value --attribute value
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
* if add attribute failed return error type otherwise return 
* PROCESS_SUCCESS
*
* NOTES:
*
*********************************************************************/
int add_attribute(node_t* node,char* name,char* value)
{
	int ret = PROCESS_SUCCESS;
	int name_len = 0;
	int value_len = 0;
	int type = 0;
	attribute_t *p_attr = NULL;
	node_t *root = NULL;
	if ((NULL != name) && (NULL != value))
	{
		name_len = (int)strlen(name);
		value_len = (int)strlen(value);
	}
	/* node invalid*/
	if (NULL == node)
	{
		ret = ADD_ATTR_FAILED;
	}
	/*node valid*/
	else
	{
		/*get root element*/
		root = get_root(node);
		if (root == &(xml_node_array[0]))
		{
			type = FIRST_XML;
		}
		else
		{
			type = SECOND_XML;
		}
		p_attr = malloc_attribute(node,type);
		if (p_attr != NULL)
		{
			if ((name_len < NAME_LEN) && (value_len < VALUE_LEN))
			{
				int is_alloc_suc = PROCESS_SUCCESS;
				copy_string(p_attr->name,name,name_len);
				is_alloc_suc = malloc_attr_value(p_attr,value_len,type);
				if (is_alloc_suc == PROCESS_SUCCESS)
				{
					copy_string(p_attr->value,value,value_len);
				}
				else
				{
					ret = is_alloc_suc;
				}
			}
			else
			{
				ret = ADD_ATTR_FAILED;
			}
		}
		else
		{
			ret = ADD_ATTR_FAILED;
		}
	}	
	return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   set_attr_value
*
* DESCRIPTION:
*   This function set attribute value with given attribute name
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     n --given node 
*     attr_name--attribute name pointer
*     attr_value--attribute value pointer
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
* if set attribute value failed return the error type otherwise return
* PROCESS_SUCCESS
*
* NOTES:
*
*********************************************************************/
int set_attr_value(node_t* n,char* attr_name,char* attr_value)
{
	int  ret = PROCESS_SUCCESS;
	attribute_t* p_attr = NULL;
	int attr_index = 0;
    node_t* root = NULL;
	int value_len = 0; 
	int type = 0;
	if (attr_value != NULL)
	{
		value_len	= (int)strlen(attr_value);
	}
    /*is parameter valid*/
    if ((NULL == n) ||(attr_name == NULL) || (attr_value == NULL))
    {
		ret =  SET_ATTR_FAILED;
    }
	else
	{
		/*get root element*/
		root = get_root(n);
		if (root == &(xml_node_array[0]))
		{
			type = FIRST_XML;
		}
		else
		{
			type = SECOND_XML;
		}
		attr_index = n->cur_attr_index;
		p_attr = n->attr;
		/*find attribute name in the node*/
		while (p_attr != NULL)
		{
			if ((0 ==strcmp(p_attr->name,attr_name)) &&(value_len < VALUE_LEN))
			{
				int is_alloc_suc = malloc_attr_value(p_attr,value_len+1,type);
				if (is_alloc_suc == PROCESS_SUCCESS)
				{
					copy_string(p_attr->value,attr_value,value_len);
				}
				else
				{
					ret = is_alloc_suc;
				}
			}
			if (value_len > VALUE_LEN)
			{
				ret = VALUE_TOO_LON;
				break;
			}
			p_attr = p_attr->next;
		}
	}
	return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   save_file
*
* DESCRIPTION:
*   This function save the RAM tree info to the given file
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     file_name-- given file name
*     root --root of the tree 
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
* if save file failed return the error type otherwise return PROCESS_SUCCESS
*
*
* NOTES:
*
*********************************************************************/
int save_file(char *file_name,node_t* root)
{
	int ret = PROCESS_SUCCESS;
	FILE* file;
    stack_t stk;
	node_t *child = NULL;
	node_t* nd = NULL;
	if (file_name)
	{
		file = fopen( file_name, "w" );
	}	
	/*file open failed*/
	if ((NULL == file) ||(NULL == root) )
	{
		ret = FILE_WRITE_ERROR;
	}
	if (ret >= 0)
	{
		/*print head of xml*/
		print_declaration(file,root);
		/*create stack*/
		init_stack(&stk);
		/*push all children of the node to stack*/
		child = root->child;
		while(child)
		{
			/*push data to stack*/
			push(&stk,child);
			child = child->sibl;
		}
		/*is stack empty*/
		while (!stack_empty(&stk))
		{ 
			node_t* nd_child = NULL;
			int nd_chld_index = 0;
			/*get node from the stack*/
			pop(&stk,&nd);
			/*write node to xml file*/
			write_node_begin(file,nd);
			/*last leaf node of the tree with nd as its root*/
			write_node_end(file,nd,&stk);
			/*does nd node have child*/
			nd_child = nd->child;
			/*push all nd_child to stack*/
			while (nd_child)
			{
				push(&stk,nd_child);
				
				nd_child = nd_child->sibl;
			}/*end while*/
		}/*end while*/
		fclose(file);
	}
	
	  return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   xpath
*
* DESCRIPTION:
*   This function return a node set (table of nodes) corresponding to a given xpath.
*
* INTERFACE:
*   GLOBAL DATA:
*     res_node_array--preserve the result node set
*
*   INPUT:
*     n-- current node
*     path --the xpath to use  
*     
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     node_set--the node table pointer
*     nb_node --the number of results
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* if execute xpath failed return the error type otherwise 
*  return PROCESS_SUCCESS
*
*
* NOTES:
*
*********************************************************************/
int   xpath(node_t *n, char *path,node_t* ((**node_set)[MAX_XPATH_RES_REC]),  int *nb_node)
{
	int ret = PROCESS_SUCCESS;
	int max_xp_count = 0;
	int count = 0;
	node_t *root = n;
	char *full_path_to_find;
	/*clear res_node_array data*/
	clear_array_data(res_node_array,MAX_XPATH_RES_REC);
	/*point to the array which satisfy the given condition*/
    *node_set = &res_node_array;
	if (n == NULL)
	{
		ret= XPATH_ERROR;
	}
    if (ret != XPATH_ERROR)
    {
	   root = get_root(n);

	   full_path_to_find = strdup(path);
	   /*initial the xpath array*/
       init_xpath_array();
	   /*parse the given xpath */
	   max_xp_count = parse_xpath(full_path_to_find);

	   if (max_xp_count >= 0) 
	   {
		   /*handled xpath*/
		   ret = exec_xpath(root, n, max_xp_count, &count);
	   }
	   else
	   {
		   ret = XPATH_ERROR;
	   }
	   if (ret != XPATH_ERROR) 
	   {
		   *nb_node = count;
	   }
   }
	return ret;
}
/**********************************************************************
* FUNCTION NAME:
*   get_cal_crc_value
*
* DESCRIPTION:
*   This function return crc value.
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
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* return calculated crc value.
*
*
* NOTES:
*
*********************************************************************/
unsigned int get_cal_crc_value()
{
	unsigned int crc = 0;
	crc = get_output_crc();
	return crc;
}