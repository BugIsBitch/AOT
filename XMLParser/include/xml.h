/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml.h
*
* DESCRIPTION:
*   API defination
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

#ifndef __XML_H__
#define __XML_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include "../include/xml_types.h"

/* ----------------------- MACRO DEFINITIONS ------------------------*/

/* ----------------------- TYPE DECLARATIONS ------------------------*/

/*------------------------- VARIABLE DEFINITION ---------------------*/

/*------------------------- FUNCTION DECLARATIONS --------------------*/

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
* if it parses xml failed return error type otherwise return PROCESS_SUCCESS
*
* NOTES:
*
*********************************************************************/
extern int  load_doc(char *filename,node_t** root);
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
extern int  load_second_doc(char *filename,node_t** root);
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
extern int is_xml_file(char* file_path);
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
extern node_t*	 get_root(node_t *n);

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
extern int   xpath(node_t *n, char *path,node_t* ((**node_set)[MAX_XPATH_RES_REC]),  int *nb_node);

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
*
* NOTES:
*
*********************************************************************/
extern int  get_name(node_t *n,char * buffer, int size);
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
extern node_t* get_element(node_t* n, char* name);
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
extern attribute_t* get_attribute(node_t* n,char* attr_name);
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
* return a successful code if no error occurs during the function performing
* else return error type
*
* NOTES:
*
*********************************************************************/
extern int  get_attr_value(attribute_t *attr, char * buffer, int size);
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
extern int add_element(node_t* parent,node_t* new_node);
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
extern int add_attribute(node_t* node,char* name,char* value);
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
extern int set_attr_value(node_t* n,char* attr_name,char* attr_value);

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
extern int save_file(char *file_name,node_t* root);
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
extern unsigned int get_cal_crc_value();

#endif /* __XML_H__ */