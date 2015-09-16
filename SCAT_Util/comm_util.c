/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   scat_comm_util.c
*
* FILE DESCRIPTION:
*   common tool function
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
/*------------------------- FILE INCLUSION --------------------------*/
#include <stdio.h>
#include "comm_util.h"
#include <windows.h>  
#include <math.h>
#include <stdlib.h>
#include <io.h>
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DECLARATIONS ---------------------*/
static char dir_path[PRJ_PATH_LEN] = "";

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
void init_project_path()
{
	char szPath[PRJ_PATH_LEN]=""; 
	char cDir[PRJ_PATH_LEN] = "";  
	char cDrive[10] = "";  
	char cf[64] = "";  
	char cExt[10] = "";  
	GetModuleFileNameA(NULL, szPath,PRJ_PATH_LEN);  
	_splitpath(szPath, cDrive, cDir, cf, cExt);  
	_makepath_s(dir_path, PRJ_PATH_LEN, cDrive, cDir, NULL, NULL); 
}
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
char*  get_project_path()
{ 
	return dir_path;
}
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
void get_file_name(char *filepath,char *file_name)
{
	char ext[64] = "";
	int len = 0;
	_splitpath(filepath, NULL, NULL, file_name, ext); 
	len = ((int)strlen(file_name))+ ((int)strlen(ext));
	if (len < 64)
	{
		strcat(file_name,ext);
	}
	
}
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
uint32_t htoi(char *s)
{
	int i; 
	int n = 0; 
	/*0x or 0X*/
	if (s[0] == '0' && (s[1]=='x' || s[1]=='X')) 
	{ 
		i = 2; 
	} 
	else 
	{ 
		i = 0; 
	} 
	for (; (s[i] >= '0' && s[i] <= '9') 
		|| (s[i] >= 'a' && s[i] <= 'f') || (s[i] >='A' && s[i] <= 'F');++i) 
	{   
		if (tolower(s[i]) > '9') 
		{ 
			n = 16 * n + (10 + tolower(s[i]) - 'a'); 
		} 
		else 
		{ 
			n = 16 * n + (tolower(s[i]) - '0'); 
		} 
	} 
	return n; 
}
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
bool_t str_to_db(char str[],double *ret_value)
{
	int is_cnv_suc = true;
	int i=0;
	int  sign = 1;
	double integer=0.0;/*integer portion*/
	double decimal=0.0;/*decimal portion*/
	/*get length of the string */
	int len= 0;
	int dot = 0;
	if (str != NULL)
	{
		len = ((int)strlen(str));
	}
	/*positive or negative*/
	if(str[i]=='-')
	{
		sign=-1;
		i++;
	}
	else 
	{
		sign = 1;
	}

	for( ;i < len && (is_cnv_suc == true);i++)
	{
		/*48 is ASSCI value of zero*/
		unsigned number = 0;
		number = str[i] - 48;
		/*current character is a numeral*/
		if( number>= 0 && number <= 9)
		{
			/*integer numbers*/
			if (dot == 0)
			{
				integer=number+integer*10;
			}
			else
			{
				if(i > dot)
				{
					decimal=decimal+number/pow(10,i-dot);
				}
			}
		}
		else
		{
			if(str[i] == '.')
			{
				/*get position of decimal point*/
				dot = i;
			}
			else
			{
				is_cnv_suc = false;
			}
		}		
	}
	*ret_value = sign*(integer+decimal);

	return is_cnv_suc;
}

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
bool_t str_to_int( char *ptr,int *ret_value)
{
	bool_t is_data_valid = true;
	int sign = 1;/*positive or negative*/

	if (ptr == NULL)
	{
		is_data_valid = false;
	}
	if (is_data_valid)
	{
		char c = *ptr;
		/*first character is '-'*/
		if (c == '-')
		{
			/*the number is a negative*/
			sign = -1;
			/*get next character*/
			c = *(++ptr);
		}
		while (c != '\0')
		{
			/*positive number*/
			if ( c >= '0' && c <= '9')
			{
				*ret_value = (c - '0')*sign + (*ret_value)*10;
			}
			else
			{
				is_data_valid = false;
				break;
			}
			/*get next character*/
			c = *(++ptr);
		}/*end while*/
	}/*end if*/

	return is_data_valid;
}
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
bool_t is_relative_path(char *path)
{
	bool_t is_relative = true;
	char szPath[PRJ_PATH_LEN]=""; 
	char cDir[256] = "";  
	char cDrive[256] = "";  
	char cf[256] = "";  
	char cExt[256] = "";  
	_splitpath(path, cDrive, cDir, cf, cExt);  
	if(strcmp(cDrive,"") == 0)
	{
		is_relative = true;
	}
	else
	{
		is_relative = false;
	}
	return is_relative;
}
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
void cnst_full_path(char* full_path,char* relative_path)
{
    if(full_path != NULL && relative_path != NULL)
	{
		char *prj_path = get_project_path();
		strcpy(full_path,"");
		strcat(full_path,prj_path);
		strcat(full_path,relative_path);
	}
}
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
bool_t check_folder_exist(char *path)
{
	bool_t is_folder_exist = true;
	/* Check for existence */
	if( (_access( path, 0 )) != -1 )
	{
		is_folder_exist = true;
	}
	else
	{
		is_folder_exist = false;
	}
	return is_folder_exist;
}