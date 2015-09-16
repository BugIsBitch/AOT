/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   scat_log.h
*
* FILE DESCRIPTION:
*   Test and verify every attribute of xml file
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

#ifndef __SCAT_LOG_H__
#define __SCAT_LOG_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include "scat_log_types.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DECLARATIONS ---------------------*/


/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/
/**********************************************************************
* FUNCTION NAME:
*   log_head
*
* DESCRIPTION:
*  The function write the head of log file 
*
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     fp--file pointer 
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
extern void log_head(FILE *fp);
/**********************************************************************
* FUNCTION NAME:
*   log_init
*
* DESCRIPTION:
*  The function initial log file 
*
*
* INTERFACE:
*   GLOBAL DATA:
*      file_path--log file path
*     item_num--each item count
*
*   INPUT:
*     path--path of log file 
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
extern void log_init(char *path);
/**********************************************************************
* FUNCTION NAME:
*   log_entry
*
* DESCRIPTION:
*  The function write log item to log file 
*
*
* INTERFACE:
*   GLOBAL DATA:
*     file_path-- log file path
*
*   INPUT:
*     log_item-- struct Log_Item_Tag pointer
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
extern void log_entry(char*file_path, Log_Item_Tag *log_item);
/**********************************************************************
* FUNCTION NAME:
*   stc_item_num
*
* DESCRIPTION:
*  The function shall statistic the number of log item with each type.
*
*
* INTERFACE:
*   GLOBAL DATA:
*     item_num--each item count
*
*   INPUT:
*     log_item-- struct Log_Item_Tag pointer
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
extern void stc_item_num(char*file_path,Log_Item_Tag *log_item);
/**********************************************************************
* FUNCTION NAME:
*   log_end
*
* DESCRIPTION:
*  The function write the number of log item of each type to log file 
*
*
* INTERFACE:
*   GLOBAL DATA:
*     file_path--log file path
*     item_num--each item count
*   INPUT:
*     None
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
extern void log_end(char*file_path);
/**********************************************************************
* FUNCTION NAME:
*   log_comment
*
* DESCRIPTION:
*  The function write comment to log file 
*
*
* INTERFACE:
*   GLOBAL DATA:
*     file_path-- log file path
*
*   INPUT:
*     comment-- character pointer
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
extern void log_comment(char*file_path,const char *comment);

extern Log_Item_Num_Tag *get_log_itm(char *path);

extern void clear_map_data(char *path);

extern void add_data(char *path);

extern void set_itm_num(char* file_path,FILE *fp);

#endif/*__SCAT_LOG_H__*/