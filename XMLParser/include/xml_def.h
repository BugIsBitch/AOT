/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml_def.h
*
* DESCRIPTION:
*   macro definitions
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


#ifndef __XML_DEF_H__
#define __XML_DEF_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include <windows.h>

/* ----------------------- MACRO DEFINITIONS ------------------------*/
#define PATH_OR	"|"
#define COND_OR	"or"
#define COND_AND	"and"

#define OPERATOR_OR	1
#define OPERATOR_AND	2
#define OPERATOR_EQU	3
#define OPERATOR_NONE -1


#define FUNC_STRCOMP	2
#define FUNC_NODE		3
#define FUNC_PI		4
#define FUNC_XPATH	 10
#define FUNC_NONE -1

#define ID_NONE -1
#define ID_CHILD		0
#define ID_DESC_O_SELF	1
#define ID_SELF		2
#define ID_PARENT		3
#define ID_ATTR		4
#define ID_DESC		5
#define ID_DESC_AND_ATTR 6
#define ID_CHILD_AND_ATTR 7


#define S_CHILD
#define S_SELF		"."
#define S_PARENT		".."
#define S_ATTR		"@"


#define PROCESS_SUCCESS 1

#define NODE_ERROR -2
#define HEAD_ERROR -3
#define FILE_OPEN_ERROR -4
#define UNKNOWN -5
#define  ATTRIBUTE_ERROR -6
#define  FILE_WRITE_ERROR -7
#define XPATH_ERROR -8
#define NAME_TOO_LON -9
#define VALUE_TOO_LON -10
#define  OUT_OF_MEMORY -11
#define  ADD_ELEM_FAILED -12
#define ADD_ATTR_FAILED -13
#define  SET_ATTR_FAILED -14


#define BULK_READ		4096		/* This is the internal buffer size for chunk of xml files */

#define LONG_LEN		512		/* This is the max size for XML objects (node name, attribute name and values...) 
* It is caused by the split of the XML file for parsing: 
* 512 int8s are reserved as security to handle splitting inside an XML object.
*/

#define BASE_LEN		256		/* this is the len of internal buffers. If a requested buffer is bigger, 
* then a malloc/free will occur and may slow down libroxml.
*/

/**
*
* 
* constant for argument node
*/
#define XML_FILE	0x01
/**
* 
* state for the state machine for init
*/
#define STATE_NODE_NONE		0

/**
* 
* state for the state machine for beginning of a node
*/
#define STATE_NODE_BEG		1

/**
* 
* state for the state machine for name read 
*/
#define STATE_NODE_NAME		2

/**
* state for the state machine for end of node
*/
#define STATE_NODE_END		3
/**
* 
* state for the state machine for separator reading
*/
#define STATE_NODE_PI		8

/**
* 
* state for the state machine for single nodes 
*/
#define STATE_NODE_SINGLE	9

/**
* 
* state for the state machine for attribut reading 
*/
#define STATE_NODE_ATTR		10

/**
* 
* state for the state machine for content read
*/
#define STATE_NODE_CONTENT	11
/**
* 
* state for the state machine for separator reading
*/
#define STATE_NODE_COMMENT		14
/**
* 
* state for the state machine for separator reading
*/
#define STATE_NODE_CDATA		22
/**
* 
* mode init in state machine 
*/
#define MODE_COMMENT_NONE  0

/**
* 
* mode quoted in state machine
*/
#define MODE_COMMENT_QUOTE	1

/**
* 
* mode double quoted in state machine
*/
#define MODE_COMMENT_DQUOTE	2

/**
* 
* inside node state begining (attribute declaration)
*/
#define STATE_INSIDE_ARG_BEG	0

/**
* 
* inside node state arg name
*/
#define STATE_INSIDE_ARG	1

/**
* 
* inside node state arg value
*/
#define STATE_INSIDE_VAL_BEG	2

/**
* 
* inside node state arg value
*/
#define STATE_INSIDE_VAL	3

/**
* 
* save current document position and recall to node
*/
#define WHITE(n) ((n==' ')||(n=='\t')||(n=='\n')||(n=='\r'))

/**
* 
* constant for attribute nodes
* \see add_node
*/
#define ATTR_NODE	0x008


/**
* constant for element nodes
*/
#define ELM_NODE	0x010

/**
* 
* constant for comment nodes
*/
#define CMT_NODE	0x040

/**
* 
* constant for processing_intruction nodes
*/
#define PI_NODE	0x080

/**
* 
* constant for cdata nodes
*/
#define CDATA_NODE	0x200

#define NONE_NODE 0x000
/**
* 
* constant for all types of nodes
*/
#define ALL_NODE	(PI_NODE | CMT_NODE  | ATTR_NODE | ELM_NODE)


#define NAME_LEN 33

#define VALUE_LEN 256

#define ATTR_COUNT 20

#define CHLDREN_COUNT 10

#define PARSE_ITM_DEF_COUNT 14

#define PARSE_ITEM_COUNT 13

#define NODE_ARRAY_COUNT 2000000

#define ATTR_ARR_CNT 3200000

#define ATTR_VAL_ATT_CNT 4000000*65

#define ES_ATTR_ARR_CNT 2000000

#define ES_NODE_ARR_CNT 200000

#define ES_ATTR_VAL_CNT 200000*10*65

#define MAX_COND_COUNT 10

#define MAX_NODE_PER_XPATH 10

#define TOTAL_XPATH 5

#define MAX_XPATH_RES_REC 70000

#define FIRST_XML 1

#define SECOND_XML 2

/* ----------------------- TYPE DECLARATIONS ------------------------*/

/*------------------------- VARIABLE DEFINITION ---------------------*/

/*------------------------- FUNCTION DECLARATIONS --------------------*/

#endif /* __XML_DEF_H__*/