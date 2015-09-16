/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml_win32_native.h
*
* DESCRIPTION:
*   using windows file
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
#ifndef __XML_WIN32_NATIVE_H__
#define __XML_WIN32_NATIVE_H__

#if defined(_MSC_VER) && _MSC_VER >= 1400
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#pragma warning(disable: 4996)
#endif

#define WIN32_LEAN_AND_MEAN
/*------------------------- FILE INCLUSION --------------------------*/
#include <windows.h>

/* ----------------------- MACRO DEFINITIONS ------------------------*/
#define pthread_self()			GetCurrentThread()
#define pthread_mutex_init(a, b)	InitializeCriticalSection(a)
#define pthread_mutex_lock(a)		EnterCriticalSection(a)
#define pthread_mutex_unlock(a)		LeaveCriticalSection(a)
#define pthread_mutex_destroy(a)	DeleteCriticalSection(a)
/* ----------------------- TYPE DECLARATIONS ------------------------*/
typedef HANDLE pthread_t;
typedef CRITICAL_SECTION pthread_mutex_t;
/*------------------------- VARIABLE DEFINITION ---------------------*/

/*------------------------- FUNCTION DECLARATIONS --------------------*/


#endif /* __XML_WIN32_NATIVE_H__ */

