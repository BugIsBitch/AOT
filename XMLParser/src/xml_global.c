/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   global.c
*
* FILE DESCRIPTION:
*   global variable definition
*
* DEFINED FUNCTION:
*  none
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
#include "../include/xml_def.h"
#include "../include/xml_types.h"
#include "../include/xml_global.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/
/*------------------------- TYPE DECLARATIONS -----------------------*/
/*------------------------- VARIABLE DEFINITION ---------------------*/
xml_parser_item_t parser_itm_arry[PARSE_ITM_DEF_COUNT];/*xml parse item array*/
xpath_parser_item_t xpath_parser_arry[PARSE_ITM_DEF_COUNT];/*xpath parse item array*/
node_t xml_node_array[NODE_ARRAY_COUNT];/*store all the xml node info*/
attribute_t xml_attr_array[ATTR_ARR_CNT];/*store all XML attribute*/
char xml_attr_value_arr[ATTR_VAL_ATT_CNT];/*attribute value array*/
xpath_node_t xpath_nd_array[TOTAL_XPATH][MAX_NODE_PER_XPATH];/*total xpath node array*/
node_t* res_node_array[MAX_XPATH_RES_REC];/*the node pointer array which satisfy the xpath condition*/
cur_arr_index_t fsrt_index;/*first DOM used array index*/

node_t scnd_xml_node_arr[ES_NODE_ARR_CNT];
attribute_t scd_attr_array[ES_ATTR_ARR_CNT];/*store all XML attribute*/
char scd_attr_value_arr[ES_ATTR_VAL_CNT];/*attribute value array*/
cur_arr_index_t scd_index;/*second DOM used array index*/
static unsigned int output_crc32;

/* ---------------------- FUNCTION DECLARATIONS ---------------------*/
/**********************************************************************
* FUNCTION NAME:
*   get_output_crc
*
* DESCRIPTION:
*   This function get crc value.
*
* INTERFACE:
*   GLOBAL DATA:
*     output_crc32-- crc value
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
* return  crc value.
*
*
* NOTES:
*
*********************************************************************/
unsigned int get_output_crc()
{
	return output_crc32;
}
/**********************************************************************
* FUNCTION NAME:
*   get_output_crc
*
* DESCRIPTION:
*   This function set crc value.
*
* INTERFACE:
*   GLOBAL DATA:
*     output_crc32-- crc value
*
*   INPUT:
*     crc32 - crc value
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
*
* NOTES:
*
*********************************************************************/
void set_output_crc(unsigned int crc32)
{
	output_crc32 = crc32;
}