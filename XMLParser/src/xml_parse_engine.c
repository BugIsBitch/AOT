/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2011-2012  
*   SAVIC
*   All Rights Reserved
*
* FILE NAME:
*   xml_parse_engine.c
*
* FILE DESCRIPTION:
*   parsing xml file
*
* DEFINED FUNCTION:
*  append_parser_item
    parse_line
	parse_xpath_line
	_func_load_quoted
	_func_load_dquoted
	_func_load_open_spec_node
	_func_load_close_cdata
	_func_load_close_comment
	_func_load_close_pi
	_func_load_open_node
	_func_load_close_node
	_func_load_end_node
	_func_load_white
	_func_load_default
	_func_xpath_ignore
	_func_xpath_new_node
	_func_xpath_quote
	_func_xpath_dquote
	_func_xpath_open_brackets
	_func_xpath_condition_or
	_func_xpath_close_brackets
	_func_xpath_condition_and
	_func_xpath_path_or
	_func_xpath_operator_equal
	_func_xpath_default
	_func_xpath_all
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
#include "../include/xml_parse_engine.h"
#include "../include/xml_internal.h"
#include "../include/xml.h"
#include <string.h>
/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DECLARATIONS ---------------------*/
/*total xpath node array*/
xpath_node_t xpath_nd_array[TOTAL_XPATH][MAX_NODE_PER_XPATH];

/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/

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
void append_parser_item(xml_parser_item_t *item,char* key,xml_parse_func func)
{
	if (item != NULL)
	{
		item->chunk = key?key[0]:0;
        item->count =  PARSE_ITEM_COUNT;
	    item->def_count= PARSE_ITM_DEF_COUNT;
		item->func = func;
	}
}
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
void append_xpath_parser_item(xpath_parser_item_t *item,char* key,xpath_parser_func func)
{
	if (item != NULL)
	{
		item->chunk = key?key[0]:0;
		item->count =  PARSE_ITEM_COUNT;
		item->def_count= PARSE_ITM_DEF_COUNT;
		item->func = func;
	}
}
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
int parse_line(xml_parser_item_t * parse_array, char *line, int len, xml_load_ctx_t * ctx)
{
	int ret = 0;
	int count = parse_array[0].count;
	int def_count = parse_array[0].def_count;
	char * line_end = line;
	char * chunk = line;

	if(len > 0) 
	{
		line_end = line + len;
	} 
	else 
	{
		line_end = line + strlen(line);
	}

	while(chunk < line_end) 
	{
		int i = 0;
		/*there is no error in parsing*/
		if (ret >= 0)
		{
			/*keyword*/
			for(; i < count; i++) 
			{
				if(chunk[0] == parse_array[i].chunk)
				{ 
					ret = parse_array[i].func(chunk, ctx);
					if(ret > 0) 
					{ 
						chunk += ret;
						break; 
					}
				}
			}
		}
		else
		{
			break;
		}
		/*there is no error in parsing*/
		if (ret >= 0)
		{
			/*load default*/
			for(; i >= count && i < def_count; i++) 
			{
				ret = parse_array[i].func(chunk, ctx);
				if(ret > 0) 
				{ 
					chunk += ret;
					break;
				} 
			}
		}
		else
		{
			break;
		}
		
	}
	if (ret >= 0)
	{
		ret = (int)(chunk - line);
	}
	return ret;
}
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
int parse_xpath_line(xpath_parser_item_t * parse_array, char *line, int len, xpath_ctx_t * ctx)
{
	int ret = 0;
	int count = parse_array[0].count;
	int def_count = parse_array[0].def_count;
	char * line_end = line;
	char * chunk = line;

	if(len > 0) 
	{
		line_end = line + len;
	} 
	else 
	{
		line_end = line + strlen(line);
	}

	while(chunk < line_end) 
	{
		int i = 0;
		/*there is no error in parsing*/
		if (ret >= 0)
		{
			/*keyword*/
			for(; i < count; i++) 
			{
				if(chunk[0] == parse_array[i].chunk)
				{ 
					ret = parse_array[i].func(chunk, ctx);
					if(ret > 0) 
					{ 
						chunk += ret;
						break; 
					}
				}
			}
		}
		else
		{
			break;
		}
		/*there is no error in parsing*/
		if (ret >= 0)
		{
			/*load default*/
			for(; i >= count && i < def_count; i++) 
			{
				ret = parse_array[i].func(chunk, ctx);
				if(ret > 0) 
				{ 
					chunk += ret;
					break;
				} 
			}
		}
		else
		{
			break;
		}

	}
	if (ret >= 0)
	{
		ret = (int)(chunk - line);
	}
	return ret;
}
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
int _func_load_quoted(char * chunk, xml_load_ctx_t * context)
{
    int ret = 0;
	/*quote start*/
	if(context->mode == MODE_COMMENT_NONE)
	{
		context->mode = MODE_COMMENT_QUOTE;
	}
	else if (context->mode == MODE_COMMENT_DQUOTE)
	{
		ret = ATTRIBUTE_ERROR;
	}
	/*quote end*/
	else
	{
		context->mode = MODE_COMMENT_NONE;
	}
	
	return ret;
}
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
int _func_load_dquoted(char * chunk, xml_load_ctx_t * context)
{
    int ret = 0;
	/*quote start*/
	if(context->mode == MODE_COMMENT_NONE) 
	{
		context->mode = MODE_COMMENT_DQUOTE;
	} 
	else if (context->mode == MODE_COMMENT_QUOTE)
	{
		ret = ATTRIBUTE_ERROR;
	}
	/*quote end*/
	else
	{
		context->mode = MODE_COMMENT_NONE;
		if (context->inside_node_state == STATE_INSIDE_VAL &&
			context->candidat_arg->value == NULL)
		{
			/*create attribute*/
			int is_alloc_suc = PROCESS_SUCCESS;
			/*为属性分配空间，多分配一个字符保存结束字符*/
			is_alloc_suc = malloc_attr_value(context->candidat_arg,1,context->fisrt_or_second);
			if (is_alloc_suc = PROCESS_SUCCESS)
			{
				/*copy value*/
				copy_string(context->candidat_arg->value,chunk,0);
			}
			else
			{
				ret = is_alloc_suc;
			}
		}
	}

	return ret;
}

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
int _func_load_open_node(char * chunk, xml_load_ctx_t * context)
{

	int cur = 1;

	switch(context->state)
	{
		case STATE_NODE_CDATA:
		case STATE_NODE_COMMENT:
			break;
		default:
			context->state = STATE_NODE_BEG;
			context->previous_state = STATE_NODE_BEG;
			break;
	}

	context->pos += cur;
	return cur;
}
/**********************************************************************
* FUNCTION NAME:
*   _func_load_close_node
*
* DESCRIPTION:
*  This function handle the keyword'>'.
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
int _func_load_close_node(char * chunk, xml_load_ctx_t* context)
{

	int cur = 1;
	int error_code = 0;
	switch(context->state)
	{
		int is_valid = 0;
		case STATE_NODE_NAME:
			
			 context->current_node = parent_node(context->current_node, &(context->candidat_node),context->fisrt_or_second,&error_code);
			
			assert(context->current_node != NULL);
			if (error_code == OUT_OF_MEMORY)
			{
				cur = error_code;
			}
			break;
			/*end of the attribute */
		case STATE_NODE_ATTR:
			if((context->mode != MODE_COMMENT_DQUOTE)||(context->mode != MODE_COMMENT_QUOTE)) 
			{
				if(context->inside_node_state == STATE_INSIDE_VAL)
				{
					if(context->content_quoted)
					{
						context->content_quoted = 0;
					} 
				}
				/*first insert attribute node and value node to the current node at the end of the node
				insert the current node to the tree*/
				context->current_node = parent_node(context->current_node, &(context->candidat_node),context->fisrt_or_second,&error_code);
				if (error_code == OUT_OF_MEMORY)
				{
					cur = error_code;
				}
				context->inside_node_state = STATE_INSIDE_ARG_BEG;
			}
			else 
			{
				/*node error*/
				cur = NODE_ERROR;
			}
			break;
		case STATE_NODE_SINGLE:
			/*alloc memory for node and set its parent*/
			if ((context->previous_state != STATE_NODE_COMMENT) && 
				(context->previous_state != STATE_NODE_CDATA))
			{
				context->current_node = parent_node(context->current_node, &(context->candidat_node),context->fisrt_or_second,&error_code);
				is_valid = is_cur_nd_valid(context->current_node);
			}
			/*alloc memory failed*/
			if (error_code == OUT_OF_MEMORY )
			{
				cur = error_code;
			}
			/*the current node didn't correctly closed*/
			else if (context->current_node->is_nd_closed == 0 ||
				       is_valid == NODE_ERROR)
			{
				cur = NODE_ERROR;
			}
			else
			{
				if(context->current_node->prnt != NULL) 
				{ 
					context->current_node = context->current_node->prnt; 
				} 
			}
			break;
		case STATE_NODE_END:
			/*set current node end pos*/
			close_node(context->current_node, &(context->candidat_node));
			/*the current node didn't correctly closed*/
			if (context->current_node->is_nd_closed == 0)
			{
				cur = NODE_ERROR;
			}
			/*at the end of the node set the node parent as the current node value*/
			else if(context->current_node->prnt != NULL) 
			{
				context->current_node = context->current_node->prnt; 
			}
			break;
		case STATE_NODE_CDATA:
		case STATE_NODE_CONTENT:
			
			cur = NODE_ERROR;
			break;
		default:
			/*node error*/
			cur = UNKNOWN;
			break;
	}
	/*is parse error*/
	if (cur == 1)
	{
		//context->state = STATE_NODE_CONTENT;
		//context->previous_state = STATE_NODE_CONTENT;
		/*ignore text node*/
		while((chunk[cur] != '<')&&(chunk[cur] != '\0')) 
		{
			cur++; 
		}
		context->pos += cur;
	}
	return cur;
}

/**********************************************************************
* FUNCTION NAME:
*   _func_load_open_spec_node
*
* DESCRIPTION:
*  This function handle the keyword'!'  .
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
int _func_load_open_spec_node(char * chunk, xml_load_ctx_t * context)
{
	int cur = 1;
	if(context->state == STATE_NODE_BEG) 
	{
		/*ignore comment node*/
		if(strncmp(chunk, "!--", 3)==0) 
		{
			cur = 3;
			context->state = STATE_NODE_COMMENT;
			context->previous_state = STATE_NODE_BEG;
			while((chunk[cur] != '-')&&(chunk[cur] != '\0'))
			{ 
				cur++;
			}
		} 
		/*ignore cdata node*/
		else if(strncmp(chunk, "![CDATA[", 8)==0) 
		{
			context->state = STATE_NODE_CDATA;
			context->previous_state = STATE_NODE_BEG;
			while((chunk[cur] != '[')&&(chunk[cur] != '\0')) { cur++; }
		} 
		else 
		{
			context->state = STATE_NODE_SINGLE;
			context->previous_state = STATE_NODE_SINGLE;
		}
	}
	else
	{
		cur = UNKNOWN;
	}
	if (cur != UNKNOWN)
	{
		context->pos += cur;
	}
	return cur;
}
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
int _func_load_close_comment(char * chunk, xml_load_ctx_t * context)
{
	int cur = 1;
	/*ignore comment node*/
	if(context->state == STATE_NODE_COMMENT)    
	{
		if(chunk[1] == '-') 
		{
			cur = 2;
			context->state = STATE_NODE_SINGLE;
			context->previous_state = STATE_NODE_COMMENT;
		}
	}
	else if (context->state == STATE_NODE_ATTR)
	{
		cur =0;
	}
	else
	{
		cur = UNKNOWN;
	}
	if (cur != UNKNOWN)
	{
		context->pos += cur;
	}
	return cur;
}
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
*      context -- xml parsing context
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
int _func_load_close_cdata(char * chunk, xml_load_ctx_t *context)
{
	int cur = 1;
   /* ignore cdata node*/
	if(context->state == STATE_NODE_CDATA)  
	{
		if(chunk[1] == ']')
		{
			cur = 2;
			context->state = STATE_NODE_SINGLE;
			context->previous_state = STATE_NODE_CDATA;
		}
		else
		{
			cur = NODE_ERROR;
		}
	}
	else
	{
		cur = UNKNOWN;
	}
	if (cur >= 0)
	{
		context->pos += cur;
	}
	return cur;
}
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
int _func_load_close_pi(char * chunk, xml_load_ctx_t *context)
{
	int len;/*length of name*/
	int cur = 1;

	if(context->state == STATE_NODE_BEG)     
	{
		cur = 1;
		context->state = STATE_NODE_PI;
		context->previous_state = STATE_NODE_PI;
		/*create node*/
		create_node(&(context->candidat_node),context->pos -1, context->src, ELM_NODE | context->type);
		/*get node name*/
		while(!WHITE(chunk[cur])&&(chunk[cur] != ' >' &&(chunk[cur] != '?'))
			    &&(chunk[cur] != '/')&&(chunk[cur] != ':')&&(chunk[cur] != '\0')) 
		{ 
			cur++;
		}
		/*remove element '?'*/
        len = cur - 1;
		(context->candidat_node).depth = 0;
		if (len >= NAME_LEN)
		{
			cur = NAME_TOO_LON;
		}
		else
		{
			/*copy name*/
			copy_string((context->candidat_node).node_name,chunk+1,len);
			/*set type*/
			set_type(&(context->candidat_node), PI_NODE);
		}
	}
	else if(context->previous_state == STATE_NODE_PI) 
	{
		if(context->mode == MODE_COMMENT_NONE) 
		{
			cur = 1;
			context->candidat_node.end = context->pos;
			context->state = STATE_NODE_SINGLE;
			cur = is_head_correct(&(context->candidat_node));
		}
	}
	else
	{
		cur = HEAD_ERROR;
	}
    if (cur != HEAD_ERROR && cur != NAME_TOO_LON)
    {
        context->pos += cur;
    }
	return cur;
}
/**********************************************************************
* FUNCTION NAME:
*   _func_load_end_node
*
* DESCRIPTION:
*  This function handle the keyword '>' :according to the context state.
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
int _func_load_end_node(char * chunk, xml_load_ctx_t *context)
{
	int cur = 1;

	switch(context->state) 
	{
		case STATE_NODE_BEG:
			/*create node*/
			create_node(&(context->candidat_node),context->pos -1, context->src, ELM_NODE | context->type);
			context->candidat_node.is_nd_closed = 1;
			context->state = STATE_NODE_END;
			break;
		case STATE_NODE_NAME:
			context->state = STATE_NODE_SINGLE;
			context->candidat_node.is_nd_closed = 1;
			break;
		case STATE_NODE_ATTR:
			/*normal*/
			if((context->mode != MODE_COMMENT_DQUOTE)&&(context->mode != MODE_COMMENT_QUOTE)) 
			{ 
				if(context->inside_node_state == STATE_INSIDE_VAL)    
				{
					if(context->content_quoted) 
					{
						context->content_quoted = 0;
					}
				}
				context->inside_node_state = STATE_INSIDE_ARG_BEG;
				context->state = STATE_NODE_SINGLE;
				context->candidat_node.is_nd_closed = 1;
			}
			break;
		default:
			cur = UNKNOWN;
			break;
	}
    if ((cur != NODE_ERROR) && (cur != UNKNOWN))
    {
		context->pos += cur;
    }
	return cur;
}
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
int _func_load_white(char * chunk,xml_load_ctx_t *context)
{
	int cur = 1;

	switch(context->state)
	{
		case STATE_NODE_SINGLE:
			context->state = context->previous_state;
			break;
		case STATE_NODE_NAME:
			context->state = STATE_NODE_ATTR;
			context->inside_node_state = STATE_INSIDE_ARG_BEG;
			break;
		case STATE_NODE_ATTR:
			/*normal*/
			if(context->mode == MODE_COMMENT_NONE) 
			{
				if(context->inside_node_state == STATE_INSIDE_VAL) 
				{
					/* attribute value process is completed*/
					if(context->content_quoted) 
					{
						context->content_quoted = 0;
					}
					context->inside_node_state = STATE_INSIDE_ARG_BEG;
				}
			}
			break;
		case STATE_NODE_PI:
			/*set previous state*/
			context->previous_state = context->state;
			context->state = STATE_NODE_ATTR;
			context->inside_node_state = STATE_INSIDE_ARG_BEG;
			break;
		default:
			break;
	}
	if (cur != UNKNOWN)
	{
		context->pos += cur;
	}
	return cur;
}
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
int _func_load_default(char * chunk,xml_load_ctx_t *context)
{
	int cur = 1;
	
	switch(context->state) 
	{
		case STATE_NODE_SINGLE:
			context->state = context->previous_state;
			break;
		case STATE_NODE_BEG:
			context->state = STATE_NODE_NAME;
			/*create new node*/
			create_node(&(context->candidat_node ),context->pos-1, context->src, ELM_NODE | context->type);
			/*get length node name*/
			while(!WHITE(chunk[cur])&&(chunk[cur] != '>')
				     &&(chunk[cur] != '/')&&(chunk[cur] != ':')&&(chunk[cur] != '\0')) 
			{ 
				cur++;
			}
			/*is name too long*/
			if (cur >= NAME_LEN)
			{
				cur = NAME_TOO_LON;
			}
			else
			{
				/*copy node name*/
				copy_string((context->candidat_node).node_name,chunk,cur);
			}
			break;
		case STATE_NODE_ATTR:
			
			if(context->inside_node_state == STATE_INSIDE_ARG_BEG)  
			{
				/*create attribute*/
				context->candidat_arg = malloc_attribute(&(context->candidat_node),context->fisrt_or_second);
				context->inside_node_state = STATE_INSIDE_ARG;
				
				/*get attribute name*/
				while((chunk[cur] != '=')&&
					    (chunk[cur] != '>')&&
						(!WHITE(chunk[cur])) &&
						(chunk[cur] != '\0')) 
				{
					cur++; 
				}
				/*is name too long*/
				if (cur >= NAME_LEN)
				{
					cur = NAME_TOO_LON;
				}
				else
				{
					/*create attribute succeed*/
					if (context->candidat_arg != NULL)
					{
						/*copy attribute name*/
						copy_string(context->candidat_arg->name,chunk,cur);
						/*attribute name*/
						copy_string(context->curr_name,chunk,cur);
					}
					else
					{
						cur = OUT_OF_MEMORY;
					}
				}
			} 
			/*attribute value */
			else if(context->inside_node_state == STATE_INSIDE_VAL_BEG)  
			{
				if(context->mode != MODE_COMMENT_NONE) 
				{
					context->content_quoted = 1;
				} 	
				context->inside_node_state = STATE_INSIDE_VAL;

			} 
			else if((context->inside_node_state == STATE_INSIDE_ARG)&&(chunk[0] == '=')) 
			{
				context->inside_node_state = STATE_INSIDE_VAL_BEG;
			}
			else if (context->inside_node_state == STATE_INSIDE_VAL)
			{
				if(context->mode != MODE_COMMENT_NONE) 
				{
					/*get value and insert value to attribute*/
					while ((chunk[cur] != '\0') && 
						(chunk[cur] != '\"'))
					{
						cur++;
					}
					if (cur >= VALUE_LEN)
					{
						cur = VALUE_TOO_LON;
					}
					else
					{
						if (context->candidat_arg != NULL)
						{
							int value_len = cur +1;
							int is_alloc_suc = PROCESS_SUCCESS;
							/*为属性分配空间，多分配一个字符保存结束字符*/
							is_alloc_suc = malloc_attr_value(context->candidat_arg,value_len,context->fisrt_or_second);
							 if (is_alloc_suc = PROCESS_SUCCESS)
							 {
								 /*copy value*/
								 copy_string(context->candidat_arg->value,chunk,value_len-1);
							 }
							 else
							 {
								 cur = is_alloc_suc;
							 }
						}
					}
				} 
				/*there is no attribute value*/
				if(context->content_quoted == 0)
				{
					cur = ATTRIBUTE_ERROR;
				}
			}
			else
			{
                 cur = ATTRIBUTE_ERROR;
			}
			break;
		case STATE_NODE_END:
			/*node end correctly*/
			while ((!WHITE(chunk[cur])) &&
				     (chunk[cur] != '\0') &&
					 (chunk[cur] != '>'))
            {
				cur++;
            }
			copy_string(context->curr_name,chunk,cur);
			if (strcmp(context->current_node->node_name,context->curr_name) != 0 &&
				strcmp(context->current_node->node_name,"xml") != 0)
			{
                 cur = NODE_ERROR;
			}
			break;
		default:
			break;
	}
    if (cur > 0)
    {
		context->pos += cur;
    }
	return cur;
}
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
int _func_xpath_ignore(char *chunk, xpath_ctx_t *ctx)
{

	return 1;
}
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
int _func_xpath_new_node(char *chunk, xpath_ctx_t *ctx)
{
	int cur = 0;
    
	if ((0 ==ctx->quoted) && (0 ==ctx->dquoted) && (0 ==ctx->bracket)) 
	{
		int offset = 0;
		if ((chunk[cur] == '/') && (ctx->is_first_node)) 
		{
			ctx->new_node = ctx->first_node;
			ctx->first_node->abs = 1;
		} 
		else if ((chunk[cur] == '/') && (ctx->is_next_or_path_node)) 
		{
			ctx->first_node->abs = 1;
		} 
		else
		{
			/*allocate a new node from the array*/
			ctx->col++;
			if (ctx->col < MAX_NODE_PER_XPATH)
			{
				ctx->new_node = &(xpath_nd_array[ctx->row][ctx->col]);
			}
		}
		ctx->is_first_node = 0;
		ctx->is_next_or_path_node = 0;
		ctx->new_node = set_axes(ctx->new_node, chunk + cur, &offset);
		cur = offset;
	}
	else
	{
		cur = XPATH_ERROR;
	}
	
	return cur;
}
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
int _func_xpath_quote(char *chunk, xpath_ctx_t *ctx)
{
    int cur = 0;
	if (0 ==ctx->dquoted)
	{
		if ((1 == ctx->quoted) &&( ctx->content_quoted == MODE_COMMENT_QUOTE)) 
		{
			ctx->content_quoted = MODE_COMMENT_NONE;
			chunk[0] = '\0';
		}
		ctx->quoted = (ctx->quoted + 1) % 2;

		cur++;
	}
	else
	{
        cur = XPATH_ERROR;
	}
	
	return cur;
}
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
int _func_xpath_dquote(char *chunk, xpath_ctx_t *ctx)
{
	int cur = 0;
	if (0 == ctx->quoted)
	{
		if ((1==ctx->dquoted) && ctx->content_quoted == MODE_COMMENT_DQUOTE)
		{
			ctx->content_quoted = MODE_COMMENT_NONE;
			chunk[0] = '\0';
		}
		ctx->dquoted = (ctx->dquoted + 1) % 2;

		cur++;
	}
	else
	{
		cur = XPATH_ERROR;
	}
	
	return cur;
}
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
int _func_xpath_open_brackets(char *chunk,xpath_ctx_t *ctx)
{
	int cur = 0;
	if ((0 ==ctx->quoted) && (0 == ctx->dquoted)) 
	{
		ctx->bracket = (ctx->bracket + 1) % 2;
		chunk[0] = '\0';
		/*condition array index*/
		ctx->new_node->cur_cond_index++;
		if (ctx->new_node->cur_cond_index < MAX_COND_COUNT)
		{
			ctx->new_cond = &((ctx->new_node->cond_array)[ctx->new_node->cur_cond_index]);
		}	
		ctx->new_cond->arg1 = chunk + cur + 1;
		cur++;
	} 
	else 
	{
		cur = XPATH_ERROR;
	}
	return cur;
}
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
int _func_xpath_close_brackets(char *chunk,xpath_ctx_t *ctx)
{
	int cur = 0;
	if ((0 == ctx->quoted) && (0 ==ctx->dquoted))
	{
		ctx->bracket = (ctx->bracket + 1) % 2;
		chunk[0] = '\0';

		if (NULL == ctx->new_cond) 
		{
			cur = XPATH_ERROR;
		}
	}
	if (cur != XPATH_ERROR)
	{
		cur++;
	}
	return cur;
}
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
int _func_xpath_condition_or(char *chunk, xpath_ctx_t *ctx)
{
	int cur = 1;
	size_t len = 0;

	len = strlen(COND_OR);

	if (strncmp(chunk, COND_OR, len) == 0) 
	{
		if (is_separator(*(chunk - 1)) && is_separator(*(chunk + len))) 
		{
			 if (ctx->bracket && (0 ==ctx->quoted) && (0 == ctx->dquoted)) 
			 {
				if (ctx->new_cond->func != FUNC_XPATH) 
				{
					chunk[-1] = '\0';
					cur += (int)strlen(COND_OR);
					ctx->new_node->cur_cond_index++;
					assert(ctx->new_node->cur_cond_index < MAX_COND_COUNT);
					ctx->new_cond = &((ctx->new_node->cond_array)[ctx->new_node->cur_cond_index]);
					ctx->new_cond->rel = OPERATOR_OR;
					ctx->new_cond->arg1 = chunk + cur + 1;
				}
			}
			 else
			 {
				 cur = XPATH_ERROR;
			 }
		}
	}
	return cur;
}
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
int _func_xpath_condition_and(char *chunk,xpath_ctx_t *ctx)
{
	int cur = 1;
	size_t len = 0;
	len = strlen(COND_AND);

	if (strncmp(chunk, COND_AND, len) == 0) 
	{
		if (is_separator(*(chunk - 1)) && is_separator(*(chunk + len)))
		{
			if (ctx->bracket && (0 ==ctx->quoted) && (0 ==ctx->dquoted))
			{
				if (ctx->new_cond->func != FUNC_XPATH) 
				{
					chunk[-1] = '\0';
					cur += (int)strlen(COND_AND);
					ctx->new_node->cur_cond_index++;
					assert(ctx->new_node->cur_cond_index < MAX_COND_COUNT);
					ctx->new_cond = &((ctx->new_node->cond_array)[ctx->new_node->cur_cond_index]);
					ctx->new_cond->rel = OPERATOR_AND;
					ctx->new_cond->arg1 = chunk + cur + 1;
				}
			}
			else
			{
				cur = XPATH_ERROR;
			}
		}
	}
	return cur;
}
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
int _func_xpath_path_or(char *chunk,xpath_ctx_t *ctx)
{
	int cur = 0;
	if ((0 == ctx->bracket) && (0 ==ctx->quoted) && (0 ==ctx->dquoted))
	{
		chunk[-1] = '\0';
		cur += (int)strlen(PATH_OR);
		ctx->is_next_or_path_node = 1;
		ctx->row++;
		assert(ctx->row < TOTAL_XPATH);
		/*reset col*/
		ctx->col = 0;
		ctx->new_node = &(xpath_nd_array[ctx->row][ctx->col]);
		
	}
	else
	{
		cur = XPATH_ERROR;
	}
	return cur;
}
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
static int _func_xpath_operators(char *chunk, xpath_ctx_t *ctx, int op)
{
	int cur = 0;
	if ((1 == ctx->bracket) && (0 ==ctx->quoted) && (0 ==ctx->dquoted))
	{
		if (ctx->new_cond->func == FUNC_STRCOMP) 
		{
			chunk[cur] = '\0';
			ctx->new_cond->op = op;
			if (WHITE(chunk[cur - 1])) 
			{
				chunk[cur - 1] = '\0';
			}
			if (chunk[cur + 1] == '=')
			{
				cur++;
				chunk[cur] = '\0';
			}
			if (WHITE(chunk[cur + 1])) 
			{
				cur++;
				chunk[cur] = '\0';
			}
			ctx->new_cond->arg2 = chunk + cur + 1;
			if (ctx->new_cond->arg2[0] == '"') 
			{
				ctx->content_quoted = MODE_COMMENT_DQUOTE;
				ctx->new_cond->arg2++;
			} 
			else if (ctx->new_cond->arg2[0] == '\'') 
			{
				ctx->content_quoted = MODE_COMMENT_QUOTE;
				ctx->new_cond->arg2++;
			}
			cur++;
		}
	}
	else
	{
		cur = XPATH_ERROR;
	}
	return cur;
}
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
int _func_xpath_operator_equal(char *chunk,  xpath_ctx_t *ctx)
{
	ctx->new_cond->func = FUNC_STRCOMP;
	return _func_xpath_operators(chunk, ctx, OPERATOR_EQU);
}
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
int _func_xpath_default(char *chunk,xpath_ctx_t *ctx)
{
	int cur = 0;
	/*remove separator*/
	if (is_separator(chunk[0]))
	{
		chunk[0] = '\0';
        cur += 1;
	}
	
   /* the absolute path*/
	if ((ctx->is_first_node) || (ctx->is_next_or_path_node)) 
	{
		if ((0 == ctx->quoted) && (0 ==ctx->dquoted) && (0 ==ctx->bracket))
		{
			int offset = 0;
			if ((chunk[cur] == '/') && (ctx->is_first_node))
			{
				ctx->new_node = ctx->first_node;
				ctx->first_node->abs = 1;
			} 
			else if ((chunk[cur] == '/') && (ctx->is_next_or_path_node)) 
			{
				ctx->first_node->abs = 1;
			} 
			ctx->is_first_node = 0;
			ctx->is_next_or_path_node = 0;
			ctx->new_node = set_axes(ctx->new_node, chunk + cur, &offset);
			cur += offset;
		}
	} 
	else
	{
		/*condition*/
		if ((1== ctx->bracket) &&(0 ==ctx->quoted) && (0 ==ctx->dquoted)) 
		{
			if (ctx->new_cond->func != FUNC_XPATH) 
			{
				ctx->new_cond->func = FUNC_XPATH;
				if (chunk[0] == '@')
				{
					cur++;
				}
				ctx->new_cond->arg1 = chunk + cur;
			}
			else
			{
				cur = 1;
			}
		}
		else
		{
			cur = 1;
		}
	}
    
	return cur;
}
