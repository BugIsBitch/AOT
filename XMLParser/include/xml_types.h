/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml_types.h
*
* DESCRIPTION:
*   data structure for xml parsing
*
* VERSION:
*   V1.00   
*
* CHANGE HISTORY:
*
* AUTHOR:
*   Fupei 
*
*********************************************************************/


#ifndef __XML_TYPES_H__
#define __XML_TYPES_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include "xml_def.h"
#include "stdio.h"
/* ----------------------- MACRO DEFINITIONS ------------------------*/

/* ----------------------- TYPE DECLARATIONS ------------------------*/
extern struct xml_load_ctx;
extern struct _xpath_ctx;
/*********************************************************************/
/*This is the prototype for a parser callback function. It receive as argument
the chunk that matched the key, and the context as a void. It should return the 
number of handled int8s or error code if doesn't want to handle this key*/
/*********************************************************************/
typedef int(*xml_parse_func)(char *chunk, struct xml_load_ctx * data);
typedef int(*xpath_parser_func)(char *chunk, struct _xpath_ctx * data);

/*********************************************************************/
/*   Memory is allocated or unallocated.                         */
/*********************************************************************/
enum MEMORY_TYPE
{
	UNALLOCTE = 0,
	ALLOCTE = 1
} ;
/*********************************************************************/
/*  Definitions for attribute data structure.            */
/*********************************************************************/
typedef struct attribute
{
	char name[NAME_LEN]; /*name of the attribute*/
	char* value; /*value of the attribute*/
	struct attribute *next;/*next attribute*/
	enum MEMORY_TYPE state;/*alloc or unalloc*/
} attribute_t;
/*********************************************************************/
/*  This is the structure for a node. This struct is very little as it only contains 
      offset for node in file and tree links.            */
/*********************************************************************/
typedef struct node
{
	unsigned short type;		/*document or buffer */
	unsigned long pos;		/*offset of beginning of opening node in file */
	unsigned long end;		/*offset of beginning of closing node in file */
	struct node *child;		/*point to children*/
	struct node *sibl; /*point to brother*/
	struct node *prnt;		/*ref to parent */
	struct attribute *attr;		/* attribute  array*/
    int cur_attr_index;/*current index of attribute*/
	char node_name[NAME_LEN];/*name of the node*/
	int depth;//depth of the tree
	int is_nd_closed;/*is node correctly closed*/
	enum MEMORY_TYPE state;/*alloc or unalloc*/
} node_t;

/*********************************************************************/
/*  obscure structure that contains all the XML parsing variables          */
/*********************************************************************/
typedef struct xml_load_ctx
{
	int pos;				/* position in file */
	int state;				/* state (state machine main var) */
	int previous_state;			/* previous state */
	int mode;				/*mode quoted or normal */
	int inside_node_state;			/* sub state for attributes*/
	int content_quoted;			/* content of attribute was quoted */
	int type;				/* source type (file or buffer) */
	FILE * src;				/* source file */
	node_t candidat_node;			/* node being processed */
	attribute_t *candidat_arg;			/*attr node being processed */
	node_t *current_node;			/*current node */
	char curr_name[NAME_LEN];			/*current node name */
	int fisrt_or_second;                         /*load first XML or second XML*/
} xml_load_ctx_t;
/*********************************************************************/
/*  this struct contains the key and callback and use for XML parsing.         */
/*********************************************************************/
typedef struct xml_parser_item 
{
	int count;				/*number of parser item with non null key (only for head) */
	int def_count;				/*total number of parser item (only for head) */
	char chunk;				/* key to match */
	xml_parse_func func;			/*callback function */
} xml_parser_item_t;
/*********************************************************************/
/*  this struct contains the key and callback and use for xpath parsing.         */
/*********************************************************************/
typedef struct xpath_parser_item 
{
	int count;				/*number of parser item with non null key (only for head) */
	int def_count;				/*total number of parser item (only for head) */
	char chunk;				/* key to match */
	xpath_parser_func func;			/*callback function */
} xpath_parser_item_t;

/** \struct xpath_cond_t
*
* \brief xpath cond structure
* 
* This is the structure for a xpath cond. It contains the
* node condition
*/
typedef struct _xpath_cond
{
	int rel;		/*relation with previous */
	char axes;		/* axes for operator */
	char op;		/*operator used */
	int func;		/* function to process */
	char *arg1;		/*condition arg1 as string */
	char *arg2;		/*condition arg2 as string */
	struct _xpath_node *xp;	/*xpath that have to be resolved for condition */
} xpath_cond_t;

/** \struct xpath_node_t
*
* \brief xpath node structure
* 
* This is the structure for a xpath node. It contains the
* node axes and conditions
*/
typedef struct _xpath_node
{
	char abs;		/* first node: is path absolute */
	char rel;		/*relation with previous */
	int axes;		/*axes type */
	char *axes_name;		/*axes string */
	struct _xpath_cond cond_array[MAX_COND_COUNT];	/*condition list */
	int cur_cond_index;
} xpath_node_t;


/** \struct xpath_ctx_t
* \brief xpath parsing context
* 
* obscure structure that contains all the xpath
* parsing variables
*/
typedef struct _xpath_ctx
{
	int pos;		/*position in string */
	int is_first_node;	/*is it the first node of xpath */
	int is_next_or_path_node;	/*are we waiting for the first node of a xpath */
	int row;		/*xpath per path */
	int col;   /*node of xpath*/
	int bracket;		/*are we inside two brackets */
	int quoted;		/*are we quoted (') */
	int dquoted;		/*are we double quoted (") */
	int content_quoted;	/*content of val was quoted */
	xpath_node_t *first_node;	/*the very first node of xpath string */
	xpath_node_t *new_node;	/*current xpath node */
	xpath_cond_t *new_cond;	/*current xpath cond */
} xpath_ctx_t;

typedef struct cur_arr_index
{
	int attr_unused_index;/*index of first unused node of xml_node_array*/
	int node_unused_index;/*index of first unused node of xml_attr_array*/
	int unused_attr_value_index;/*index of xml_attr_value_arr */
}cur_arr_index_t;
/*------------------------- VARIABLE DEFINITION ---------------------*/

/*------------------------- FUNCTION DECLARATIONS --------------------*/

#endif /* __XML_TYPES_H__*/