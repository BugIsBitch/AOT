/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   scat_log_types.h
*
* FILE DESCRIPTION:
*   Data structure for log file
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

#ifndef __SCAT_LOG_TYPES_H__
#define __SCAT_LOG_TYPES_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include "scat_log_def.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DECLARATIONS ---------------------*/


/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/
/*********************************************************************/
/*  Definitions for log item data structure.            */
/*********************************************************************/
typedef struct Log_Item
{
	char *file_name;/*input file name*/

	int error_id;/*XML error id*/

    char *node_xpath;/*node xpath*/

	char *log_type;/*log type*/

	char *msg;/*log description*/
} Log_Item_Tag;
/*********************************************************************/
/*  Definitions for every type log count data structure.            */
/*********************************************************************/
typedef struct Log_Item_Num
{
	int log_err_num;/*the number of error type item */
	int log_war_num;/*the number of warning type item */
	int log_crt_num;/*the number of critical type item */
	int log_info_num;/*the number of information type item */
}Log_Item_Num_Tag;

/*********************************************************************/
/*  Definitions for relationship between path and log count data structure.            */
/*********************************************************************/
typedef struct Map_Path_Itm_Num
{
    char log_path[PATH_LEN];

	Log_Item_Num_Tag num_itm;

}Map_Path_Itm_Num_Tag;

#endif/*__SCAT_LOG_TYPES_H__*/