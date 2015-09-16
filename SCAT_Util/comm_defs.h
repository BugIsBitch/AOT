/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   scat_comm_defs.h
*
* FILE DESCRIPTION:
*   macro defination for SNAT and SCT tool
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

#ifndef __SCAT_COMM_DEFS_H__
#define __SCAT_COMM_DEFS_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include <stdio.h>
/*------------------------- MACRO DEFINITIONS -----------------------*/
#define true 1
#define TRUE 1
#define false 0
#define FALSE 0
/*------------------------- TYPE DECLARATIONS -----------------------*/
typedef signed char int8;
typedef signed short int16_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef size_t            bool_t;         /* declaration for bool type */

#define BSWAP_16(x) \
	(uint16_t)((((uint16_t)(x) & 0x00ff) << 8) | \
	(((uint16_t)(x) & 0xff00) >> 8) \
	)
#define BSWAP_32(x) \
	(uint32_t)((((uint32_t)(x) & 0xff000000) >> 24) | \
	(((uint32_t)(x) & 0x00ff0000) >> 8) | \
	(((uint32_t)(x) & 0x0000ff00) << 8) | \
	(((uint32_t)(x) & 0x000000ff) << 24) \
	)
#define MED_VAL_LEN 64
#define SPEED_VAL_LEN 30
#define MAX_PATH_LEN 260
#endif/*__SCAT_COMM_DEFS_H__*/