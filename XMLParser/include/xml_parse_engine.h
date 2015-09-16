/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml_parse_engine.h
*
* DESCRIPTION:
*   parsing xml file
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

#ifndef __XML_PARSE_ENGINE_H__
#define __XML_PARSE_ENGINE_H__


/*------------------------- FILE INCLUSION --------------------------*/
#include "xml_types.h"
/* ----------------------- MACRO DEFINITIONS ------------------------*/

/* ----------------------- TYPE DECLARATIONS ------------------------*/

/*------------------------- VARIABLE DEFINITION ---------------------*/

/*------------------------- FUNCTION DECLARATIONS --------------------*/

/**********************************************************************
* FUNCTION NAME:
*   append_parser_item
*
* DESCRIPTION:
*  This function add data to a parser item.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     item --new parser item
*     key --the char to trigger callback for
*     func -- the function to call on match
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
extern void append_parser_item(xml_parser_item_t *item,char* key,xml_parse_func func);
/**********************************************************************
* FUNCTION NAME:
*   append_xpath_parser_item
*
* DESCRIPTION:
*  This function add data to an xpath parser item.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     item --new xpath parser item
*     key --the char to trigger callback for
*     func -- the function to call on match
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
extern void append_xpath_parser_item(xpath_parser_item_t *item,char* key,xpath_parser_func func);
/**********************************************************************
* FUNCTION NAME:
*   parse_line
*
* DESCRIPTION:
*  This function parse a line : it calls parsing functions when key matches
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     parse_array --the parser item array
*     line -- the string to parse
*     len -- the len of string or 0 if auto calculate len (using \0)
*     ctx --user data passed to the callbacks
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
* if the function successfully executed  return the number of int8s processed else return error type
*
* NOTES:
*
*********************************************************************/
extern int parse_line(xml_parser_item_t * parse_array, char *line, int len, xml_load_ctx_t * ctx);
/**********************************************************************
* FUNCTION NAME:
*   parse_xpath_line
*
* DESCRIPTION:
*  This function parse xpath : it calls parsing functions when key matches
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     parse_array --the parser item array
*     line -- the string to parse
*     len -- the len of string or 0 if auto calculate len (using \0)
*     ctx --user data passed to the callbacks
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
* if the function successfully executed  return the number of int8s processed else
* return error type
*
* NOTES:
*
*********************************************************************/
extern int parse_xpath_line(xpath_parser_item_t * parse_array, char *line, int len, xpath_ctx_t * ctx);

/**********************************************************************
* FUNCTION NAME:
*   _func_load_quoted
*
* DESCRIPTION:
*  This function handle the single quote.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if the function successfully executed  return the 0  otherwise
* return error type
*
* NOTES:
*
*********************************************************************/
extern int _func_load_quoted(char * chunk, xml_load_ctx_t* data);
/**********************************************************************
* FUNCTION NAME:
*   _func_load_dquoted
*
* DESCRIPTION:
*  This function handle the double quote.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if the function successfully executed  return the 0  otherwise
* return error type
*
* NOTES:
*
*********************************************************************/
extern int _func_load_dquoted(char * chunk, xml_load_ctx_t* data);
/**********************************************************************
* FUNCTION NAME:
*   _func_load_open_spec_node
*
* DESCRIPTION:
*  This function handle the keyword '!'  .
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_load_open_spec_node(char * chunk, xml_load_ctx_t* data);
/**********************************************************************
* FUNCTION NAME:
*   _func_load_close_cdata
*
* DESCRIPTION:
*  This function handle the keyword ']'  .
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_load_close_cdata(char * chunk, xml_load_ctx_t* data);
/**********************************************************************
* FUNCTION NAME:
*   _func_load_close_comment
*
* DESCRIPTION:
*  This function handle the keyword '-'  .
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_load_close_comment(char * chunk, xml_load_ctx_t* data);
/**********************************************************************
* FUNCTION NAME:
*   _func_load_close_pi
*
* DESCRIPTION:
*  This function handle the keyword '?'  .
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_load_close_pi(char * chunk, xml_load_ctx_t* data);
/**********************************************************************
* FUNCTION NAME:
*   _func_load_open_node
*
* DESCRIPTION:
*  This function handle the keyword '<'.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* return 1
*
* NOTES:
*
*********************************************************************/
extern int _func_load_open_node(char * chunk, xml_load_ctx_t* data);
/**********************************************************************
* FUNCTION NAME:
*   _func_load_close_node
*
* DESCRIPTION:
*  This function handle the keyword '>'.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_load_close_node(char * chunk, xml_load_ctx_t* data);
/**********************************************************************
* FUNCTION NAME:
*   _func_load_end_node
*
* DESCRIPTION:
*   This function handle the keyword '>' :according to the context state..
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_load_end_node(char * chunk, xml_load_ctx_t* data);
/**********************************************************************
* FUNCTION NAME:
*   _func_load_white
*
* DESCRIPTION:
*  This function handle the keyword ' ' :according to the context state.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_load_white(char * chunk, xml_load_ctx_t* data);
/**********************************************************************
* FUNCTION NAME:
*   _func_load_default
*
* DESCRIPTION:
*  This function handle the all the other words :according to the context state.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     context -- xml parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_load_default(char * chunk, xml_load_ctx_t* data);


/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_ignore
*
* DESCRIPTION:
*  This function ignore useless char.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --xpath string to parse
*
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* return 1
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_ignore(char *chunk,xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_new_node
*
* DESCRIPTION:
*  This function handle the keyword '/' and create a new xpath node.
*
* INTERFACE:
*   GLOBAL DATA:
*     xpath_nd_array--the xpath node array
*
*   INPUT:
*     chunk --xpath string to parse
*    
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*      ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_new_node(char *chunk, xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_quote
*
* DESCRIPTION:
*  This function handle the single quote.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --xpath string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_quote(char *chunk, xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_dquote
*
* DESCRIPTION:
*  This function handle the double quote.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --xpath string to parse
*    
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*      ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_dquote(char *chunk, xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_open_brackets
*
* DESCRIPTION:
*  This function handle the keyword '['.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --xpath string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_open_brackets(char *chunk, xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_close_brackets
*
* DESCRIPTION:
*  This function handle the keyword ']'.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --xpath string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_close_brackets(char *chunk, xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_condition_or
*
* DESCRIPTION:
*  This function handle the keywords "or".
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --xpath string to parse
*    
*    
*   OUTPUT:
*      ctx -- xpath parsing context
*
*   INPUT/OUTPUT:
*     None
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_condition_or(char *chunk,xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_condition_and
*
* DESCRIPTION:
*  This function handle the keywords "and".
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --xpath string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_condition_and(char *chunk,xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_path_or
*
* DESCRIPTION:
*  This function handle the keyword "|".
*
* INTERFACE:
*   GLOBAL DATA:
*     xpath_nd_array--xpath node array
*
*   INPUT:
*     chunk --xpath string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_path_or(char *chunk,xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_operator_equal
*
* DESCRIPTION:
*  This function handle the equal operator.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --xpath string to parse
*    
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*      ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_operator_equal(char *chunk,xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_default
*
* DESCRIPTION:
*  This function handle the xpath words other than the given keywords.
*
* INTERFACE:
*   GLOBAL DATA:
*     xpath_nd_array--xpath node array
*
*   INPUT:
*     chunk --xpath string to parse
*     
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern int _func_xpath_default(char *chunk, xpath_ctx_t *ctx);
/**********************************************************************
* FUNCTION NAME:
*   _func_xpath_operators
*
* DESCRIPTION:
*  This function handle the given operators.
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     chunk --xpath string to parse
*     operator --given operator
*    
*   OUTPUT:
*     None
*
*   INPUT/OUTPUT:
*     ctx -- xpath parsing context
*
* AUTHOR:
*   Fu Pei
*
* RETURN VALUE:
* 
* if successfully executed return the number of char have been handled else return 
* error type
*
* NOTES:
*
*********************************************************************/
extern  int _func_xpath_operators(char *chunk, xpath_ctx_t *ctx, int operator);

#endif /* __XML_PARSE_ENGINE_H__ */
