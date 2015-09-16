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

#ifndef __XML_GLOBAL_H__
#define __XML_GLOBAL_H__

/*------------------------- FILE INCLUSION --------------------------*/

/* ----------------------- MACRO DEFINITIONS ------------------------*/

/* ----------------------- TYPE DECLARATIONS ------------------------*/

/*------------------------- VARIABLE DEFINITION ---------------------*/

/*------------------------- FUNCTION DECLARATIONS --------------------*/

/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/

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
extern unsigned int get_output_crc();

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
extern void set_output_crc(unsigned int crc32);

#endif/*__XML_GLOBAL_H__*/