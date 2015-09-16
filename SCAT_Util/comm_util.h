/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   scat_comm_util.h
*
* FILE DESCRIPTION:
*  Common Util function
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

#ifndef __SCAT_COMM_UTIL_H__
#define __SCAT_COMM_UTIL_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include "comm_defs.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/
#define PRJ_PATH_LEN 260
/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DECLARATIONS ---------------------*/


/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/
/**********************************************************************
* FUNCTION NAME:
*   init_project_path
*
* DESCRIPTION:
*  initial the project path
*
*
* INTERFACE:
*   GLOBAL DATA:
*     dir_path-- project path
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
extern void init_project_path();
/**********************************************************************
* FUNCTION NAME:
*   get_project_path
*
* DESCRIPTION:
*  get path of current project
*
*
* INTERFACE:
*   GLOBAL DATA:
*     dir_path-- project path
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
extern char*  get_project_path();
/**********************************************************************
* FUNCTION NAME:
*   get_file_name
*
* DESCRIPTION:
*  get file name of given path
*
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*   INPUT:
*      filepath--file path
*
*   OUTPUT:
*     file_name--file name
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
extern void get_file_name(char *filepath,char *file_name);
/**********************************************************************
* FUNCTION NAME:
*   htoi
*
* DESCRIPTION:
*  convert string to hexadecimal integer
*
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*   INPUT:
*      s--hexadecimal string 
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
* the converted integer
*
* NOTES:
*
*********************************************************************/
extern  uint32_t htoi(char *s);
/**********************************************************************
* FUNCTION NAME:
*   str_to_db
*
* DESCRIPTION:
*  convert string to double
*
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*   INPUT:
*      str-- string 
*      
*   OUTPUT:
*     ret_value--double value
*
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* if convert succeed return true , else return false.
*
* NOTES:
*
*********************************************************************/
extern bool_t str_to_db(char str[],double *ret_value);
/**********************************************************************
* FUNCTION NAME:
*   str_to_int
*
* DESCRIPTION:
*  convert string to integer
*
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*   INPUT:
*      str-- string 
*      
*   OUTPUT:
*     ret_value--integer value
*
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
*
* if convert succeed return true , else return false.
*
* NOTES:
*
*********************************************************************/
extern bool_t str_to_int( char *ptr,int *ret_value);
/**********************************************************************
* FUNCTION NAME:
*   is_relative_path
*
* DESCRIPTION:
*  is given path a relative path
*
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*   INPUT:
*      path-- given file path
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
* if it is relative path return true ,else return false.
*
* NOTES:
*
*********************************************************************/
extern bool_t is_relative_path(char *path);
/**********************************************************************
* FUNCTION NAME:
*   cnst_full_path
*
* DESCRIPTION:
*  construct full file path according file relative path
*
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*   INPUT:
*      relative_path--relative path of file
*   OUTPUT:
*     full_path-- full file path
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
extern void cnst_full_path(char* full_path,char* relative_path);
/**********************************************************************
* FUNCTION NAME:
*   check_folder_exist
*
* DESCRIPTION:
*  check if folder exist
*
*
* INTERFACE:
*   GLOBAL DATA:
*    None
*   INPUT:
*      path--given path
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
* If folder exist return true, else return false.
*
* NOTES:
*
*********************************************************************/
extern bool_t check_folder_exist(char *path);


#endif/*__SCAT_COMM_UTIL_H__*/