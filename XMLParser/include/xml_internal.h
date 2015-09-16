/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml_internal.h
*
* DESCRIPTION:
*   internal function using by xml parsing engine
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

#ifndef __XML_INTERNAL_H__
#define __XML_INTERNAL_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "xml_stack.h"
#include "xml_def.h"
#include "xml_types.h"

/* ----------------------- MACRO DEFINITIONS ------------------------*/

/* ----------------------- TYPE DECLARATIONS ------------------------*/

/*------------------------- VARIABLE DEFINITION ---------------------*/

/*------------------------- FUNCTION DECLARATIONS --------------------*/

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
extern void  create_node(node_t* n,int pos, FILE * src, int type);

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
extern attribute_t* malloc_attribute(node_t *n,int type);
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
extern void initial_attr(attribute_t *attr);

/**********************************************************************
* FUNCTION NAME:
*   initial_attr
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
extern void 	 close_node(node_t *n, node_t *close);

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
*   OUTPUT:
*     None
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
extern int  load(FILE *file,node_t** root,int type);

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
*     None
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
extern node_t *  parent_node(node_t *parent, node_t * n,int xml_type,int *error_code);

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
extern void  set_type(node_t * n, int type);

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
extern int  is_separator(char sep);
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
extern void copy_string(char* dest ,char* src,const int src_len);
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
extern void copy_node_data(node_t* dest_node,node_t* src_node);
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
extern void init_node_arry(node_t node_arr[],int count);
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
extern void init_node(node_t* n);
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
extern int  get_type(node_t *n);

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
extern int malloc_fst_arr_node(int node_count,node_t** head);
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
extern int malloc_scd_arr_node(int node_count,node_t** head);
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
extern int malloc_node(int node_count,node_t** head,int type);
/**********************************************************************
* FUNCTION NAME:
*   print_declaration
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
extern void   print_format(FILE *file,node_t* nd);
/**********************************************************************
* FUNCTION NAME:
*   print_format
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
extern void  print_declaration(FILE *file,node_t* root);
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
extern void print_attribute(FILE *file,char*name,char*value);
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
extern void write_node_begin(FILE *file,node_t* nd);
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
extern void write_node_end(FILE *file,node_t* nd,stack_t* p_stk);

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
extern xpath_node_t  *set_axes(xpath_node_t *node, char *axes, int *offset);
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
extern int  parse_xpath(char *path);
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
extern int exec_xpath(node_t *root, node_t * n, int max_xp_count, int *count);
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
extern void init_xpath_array();
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
extern void clear_array_data(node_t* nd_array[],const int count);
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
extern int  check_node(xpath_node_t * xp, node_t * root,node_t* input_arr_array[],node_t* output_arr_array[],
				                  const int input_arr_count,int* output_arr_count);

/**********************************************************************
* FUNCTION NAME:
*   validate_axes
*
* DESCRIPTION:
*  This function validate if an axe is matching the current node
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
extern int  validate_axes(node_t *root, node_t * candidat,xpath_node_t *xn);
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
*       None
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
extern void copy_array_data(node_t* dest_array[],node_t* src_array[],const int start,const int count);
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
extern  int process_desc_self(node_t* root,node_t* context,xpath_node_t* xp,node_t* output_arr_array[],int* output_index);
/**********************************************************************
* FUNCTION NAME:
*   validate_predicat
*
* DESCRIPTION:
*  This function check for predicate validity. predicate is part between brackets
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
extern int  validate_predicat(xpath_node_t *xn, node_t * candidat);

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
extern int is_cur_nd_valid(node_t* cur_node);
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
extern int malloc_fst_arr_attr(node_t *n,attribute_t **ret_attr);
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
extern int malloc_scd_arr_attr(node_t* n,attribute_t **ret_attr);
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
extern void init_attr_arry(attribute_t attr_arr[],int count);
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
extern int is_head_correct(node_t* head);
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
*      fsrt_index - current unused index in array
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
extern int malloc_fst_arr_val_attr(attribute_t* attr,int count);
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
extern int malloc_scd_arr_val_attr(attribute_t* attr,int count);
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
extern int malloc_attr_value(attribute_t *attr,int count,int type);

#endif /* __XML_INTERNAL_H__ */

