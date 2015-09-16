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
*   log manager
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
#include "scat_log_def.h"
#include <stdio.h>
#include <string.h>
#include "scat_log.h"
#include <assert.h>
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DECLARATIONS ---------------------*/

static Map_Path_Itm_Num_Tag path_itm_num[MAX_LOG_PATH_CNT];

/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/
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
*     file_path--log file path
*     item_num--each item count
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
void log_init(char *path)
{
	FILE *fp = NULL;
	int path_len = 0;
	Log_Item_Num_Tag *item_num = NULL;
    assert(path != NULL);
    path_len = strlen(path);
	if (path_len < (PATH_LEN-1))
	{
		add_data(path);
	}
	/*open log file*/
	fp = fopen(path,"w+");
	/*write log head*/
	log_head(fp);
	item_num  = get_log_itm(path);
	assert(item_num != NULL);
	/*initial number of every item type*/
	item_num->log_crt_num = 0;
	item_num->log_err_num = 0;
	item_num->log_info_num = 0;
	item_num->log_war_num = 0;
}
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
void log_head(FILE *fp)
{
	if (fp != NULL)
	{
		/*critical*/
		fprintf(fp,"%s",LOG_HEAD_CRT);
		fprintf(fp,"%d",0);
		/*Placeholder*/
		fprintf(fp,"%s\n","       ");

		/*errors*/
		fprintf(fp,"%s",LOG_HEAD_ERR);
		fprintf(fp,"%d",0);
		/*Placeholder*/
		fprintf(fp,"%s\n","       ");

		/*warning*/
		fprintf(fp,"%s",LOG_HEAD_WAR);
		fprintf(fp,"%d",0);
		/*Placeholder*/
		fprintf(fp,"%s\n","       ");

		/*information*/
		fprintf(fp,"%s",LOG_HEAD_INFO);
		fprintf(fp,"%d",0);
		/*Placeholder*/
		fprintf(fp,"%s\n","       ");

		fclose(fp);
	}
}
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
void log_end(char*file_path)
{
	
	clear_map_data(file_path);
}

void set_itm_num(char* file_path,FILE *fp)
{
	int offset = 0;
	Log_Item_Num_Tag *item_num = get_log_itm(file_path);
	/* write the number of critical item*/
	offset = strlen(LOG_HEAD_CRT);
	fseek(fp,offset,SEEK_SET);
	fprintf(fp,"%d",item_num->log_crt_num);

	/*error head offset*/
	offset += strlen(LOG_HEAD_ERR) + 10;
	/* write the number of error item*/
	fseek(fp,offset,SEEK_SET);
	fprintf(fp,"%d",item_num->log_err_num);

	/*warning head offset*/
	offset += strlen(LOG_HEAD_WAR) +10;
	/* write the number of warning item*/
	fseek(fp,offset,SEEK_SET);
	fprintf(fp,"%d",item_num->log_war_num);

	/*information head offset*/
	offset += strlen(LOG_HEAD_INFO) + 10;
	/* write the number of information item*/
	fseek(fp,offset,SEEK_SET);
	fprintf(fp,"%d",item_num->log_info_num);
}
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
void log_entry(char*file_path, Log_Item_Tag *log_item)
{
	char log_msg[MSG_LEN];
	int msg_len = 0;
	FILE *fp = NULL;
	assert(log_item != NULL);
	msg_len = strlen(log_item->msg);
	if (msg_len > (MSG_LEN-1))
	{
		strncpy(log_msg,log_item->msg,MSG_LEN-1);
		log_msg[MSG_LEN-1] = '\0';
	}
	else
	{
		strncpy(log_msg,log_item->msg,msg_len);
		log_msg[msg_len] = '\0';
	}
	fp = fopen(file_path,"r+");
	/*print log item*/
	if (fp)
	{
		fseek(fp,0,SEEK_END);
		/*Statistics the number log item of every type*/
		stc_item_num(file_path,log_item);
		/*File name*/
		fprintf(fp,"%s",log_item->file_name);
		fprintf(fp,"%s",",");
		/*element xpath*/
		fprintf(fp,"%s",log_item->node_xpath);
		fprintf(fp,"%s",",");
		/*error type*/
		if (log_item->error_id == 0)
		{
			fprintf(fp,"%s","NA");
		}
		else
		{
			fprintf(fp,"%d",log_item->error_id);
		}
		fprintf(fp,"%s",",");
		/*log type*/
		fprintf(fp,"%s",log_item->log_type);
		fprintf(fp,"%s",",");
		/*Description*/
		fprintf(fp,"%s\n",log_msg);
		/*set number of each item type*/
		set_itm_num(file_path,fp);
		fclose(fp);
	}

}
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
void log_comment(char*file_path,const char *comment)
{
	char temp_com[COM_LEN];
	int com_len = 0;
	FILE *fp = NULL;
	assert(comment != NULL);
	 /*open file*/
	fp = fopen(file_path,"r+");
	com_len = strlen(comment);
	if (fp)
	{
		if (com_len > (COM_LEN-1))
		{
			strncpy(temp_com,comment,COM_LEN-1);
			temp_com[COM_LEN-1] = '\0';
		}
		else
		{
			strncpy(temp_com,comment,com_len);
			temp_com[com_len] = '\0';
		}
		fseek(fp,0,SEEK_END);
		/*write comment to given file*/
		fprintf(fp,"%s" ,"#");
		fprintf(fp,"%s\n",temp_com);
	}
    fclose(fp);
}
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
void stc_item_num(char*file_path,Log_Item_Tag *log_item)
{
	Log_Item_Num_Tag *item_num = get_log_itm(file_path);
	assert(log_item != NULL);
	/*error type*/
	if (strcmp(log_item->log_type,LOG_ERR) == 0)
	{
        item_num->log_err_num++;
	}
	/*warning type*/
	else if (strcmp(log_item->log_type,LOG_WAR) == 0)
	{
		item_num->log_war_num++;
	}
	/*information type*/
	else if (strcmp(log_item->log_type,LOG_INFO) == 0)
	{
		item_num->log_info_num++;
	}
	/*critical type*/
	else if (strcmp(log_item->log_type,LOG_CRT) == 0)
	{
		item_num->log_crt_num++;
	}
}
/**********************************************************************
* FUNCTION NAME:
*   clear_map_data
*
* DESCRIPTION:
*  The function clear number of each log item
*
*
* INTERFACE:
*   GLOBAL DATA:
*     item_num--each item count
*
*   INPUT:
*     path-- log file path
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
static void clear_map_data(char *path)
{
	int index = 0;
	for ( ; index < MAX_LOG_PATH_CNT; index++)
	{
		Map_Path_Itm_Num_Tag *temp =&(path_itm_num[index]);
		if (!strcmp(temp->log_path,path))
		{
			strncpy(temp->log_path,"\0",1);
			temp->num_itm.log_crt_num = -1;
			temp->num_itm.log_err_num = -1;
			temp->num_itm.log_info_num = -1;
			temp->num_itm.log_war_num = -1;
			break;
		}
	}
}
/**********************************************************************
* FUNCTION NAME:
*   add_data
*
* DESCRIPTION:
*  The function add data to log map 
*
*
* INTERFACE:
*   GLOBAL DATA:
*     item_num--each item count
*
*   INPUT:
*     path-- log file path
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
static void add_data(char *path)
{
	int index = 0;
	for ( ; index < MAX_LOG_PATH_CNT; index++)
	{
		Map_Path_Itm_Num_Tag *temp =&(path_itm_num[index]);
		int len = strlen(temp->log_path);
		if (len == 0)
		{
			strcpy(temp->log_path,path);
			temp->num_itm.log_crt_num = 0;
			temp->num_itm.log_err_num = 0;
			temp->num_itm.log_info_num = 0;
			temp->num_itm.log_war_num = 0;
			break;
		}
	}
}
/**********************************************************************
* FUNCTION NAME:
*   get_log_itm
*
* DESCRIPTION:
*  The function get log item
*
*
* INTERFACE:
*   GLOBAL DATA:
*     item_num--each item count
*
*   INPUT:
*     path-- log file path
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
* return log item
*
* NOTES:
*
*********************************************************************/
static Log_Item_Num_Tag *get_log_itm(char *path)
{
	int index = 0;
	Log_Item_Num_Tag *num_itm = NULL;
	for ( ; index < MAX_LOG_PATH_CNT; index++)
	{
		Map_Path_Itm_Num_Tag *temp = &(path_itm_num[index]);
		if (!strcmp(temp->log_path,path))
		{
             num_itm = &(temp->num_itm);
			 break;
		}
	}
	return num_itm;
}