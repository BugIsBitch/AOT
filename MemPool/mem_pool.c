/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************
* COPYRIGHT: 
*   2013-2014  
*   All Rights Reserved
*
* FILE NAME:
*   mem_pool.c
*
* FILE DESCRIPTION:
*   allocate memory and manage memory
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
#include "mem_pool.h"
#include "mem_pool_def.h"
#include "mem_pool_type.h"
#include <stdio.h>
#include <stdlib.h>

/*------------------------- MACRO DEFINITIONS -----------------------*/

/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DECLARATIONS ---------------------*/
char pool_arr[__POOL_SIZE];
obj *free_list[__NFREELISTS];
mem_state_t free_list_state[__NFREELISTS];/*��¼�������״̬*/
char *start_free = &(pool_arr[0]);    //mempool��ʼλ��
char *end_free = &(pool_arr[__POOL_SIZE]);    //mempool����λ�õ���һ��λ��
/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/


/*��ʼ���ڴ��*/
void init_mem_pool()
{
	mem_state_t* p_state = NULL;
	obj *p = NULL;
	obj** my_free_list = NULL;
	size_t i = 0;
	for(i = __ALIGN; i <= __MAX_BYTES; i += __ALIGN)
	{
		/*��ʼ��freelist����*/
		my_free_list = free_list + freelist_index(i);
		p_state = free_list_state + freelist_index(i);
		p = *my_free_list;
		p = NULL;
		/*��ʼ���ڴ��״̬��Ϣ*/
		p_state->cntn_chunk_head = NULL;
		p_state->cntn_chunk_num = 0;
		p_state->cntn_unit_num = 0;
		p_state->pre_cntn_head = NULL;
	}
}
/**********************************************************************
* FUNCTION NAME:
*   round_up
*   
* DESCRIPTION:
*    adjust bytes to be multiple of __ALIGN
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     bytes--given bytes
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
*  multiple of __ALIGN
*
* NOTES:
*
*********************************************************************/
size_t round_up(size_t bytes)
{
	return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1));
}
//����bytes����Ӧ��freelist������
size_t freelist_index(size_t bytes)
{
	return ((bytes + __ALIGN - 1) / __ALIGN - 1);
}
void *mem_malloc(size_t nbytes)
{
	
	obj **my_free_list = NULL;
	obj *result = NULL;
	mem_state_t *p_state = NULL;
	if (nbytes > __MAX_BYTES)
	{
		return NULL;
	}
	my_free_list = free_list + freelist_index(nbytes);/*�ҵ��ʵ��Ŀ�����*/
	result = *my_free_list;
	if(result == NULL)
	{
		void *r = refill(round_up(nbytes));
		return r;
	}
	/*���¼���������*/
	p_state = free_list_state + freelist_index(nbytes);
	if (p_state->cntn_chunk_head == result)
	{
		reset_freelist_state(p_state);
	}
	//ȡ�����п�
	*my_free_list = result->free_list_link;
	return result;
}
void mem_free(void *p, size_t nbytes)
{
	obj *q = (obj *)p;
	obj **my_free_list = NULL;
	if(nbytes > (size_t)__MAX_BYTES)
	{
		free(p);
		return;
	}
	my_free_list = free_list + freelist_index(nbytes);
	q->free_list_link = *my_free_list;
	*my_free_list = q;
}
void *refill(size_t n)
{
	obj **my_free_list = NULL;
	obj *result = NULL, *cur_obj = NULL, *next_obj = NULL;
	int i = 0;
	/*Ĭ�ϴ��ڴ��ȡ��16����*/
	size_t nobjs = 16;
	char *chunk = chunk_alloc(n, &nobjs); 
	if(!chunk)
	{
		return NULL;
	}
	
	/*�ڴ�ؿռ�漱������һ���飬��ֱ�ӷ��ظ��û�*/
	if(nobjs == 1)
	{
		return chunk;
	}
	/*����׼����free_list�������µĽڵ�*/
	my_free_list = free_list + freelist_index(n);
	/*������chunk�������ռ��Ͻ���free_list*/
	result = (obj *)chunk;    //�˿鷵�ظ��û�
	*my_free_list = next_obj = (obj *)(chunk + n);
	/*���е������ռ䳬��2��*/
	if (nobjs > 2)
	{
		mem_state_t* p_state = free_list_state+ freelist_index(n);
		p_state->cntn_unit_num = nobjs-1;
		p_state->cntn_chunk_num++;
		p_state->cntn_chunk_head = *my_free_list;
		p_state->pre_cntn_head = *my_free_list;
	}
	for(i = 1; ; i++)
	{
		cur_obj = next_obj;
		next_obj = (obj *)((char *)next_obj + n);
		/*���һ����*/
		if(nobjs - 1 == i)
		{
			cur_obj->free_list_link = NULL;
			break;
		}
		else
		{
			cur_obj->free_list_link = next_obj;    
		}
	}
	return result;
}
//���ڴ��ȡ�����Ŀ�ռ�
char *chunk_alloc(size_t bytes, size_t *nobjs)
{
	char *result = NULL;
	size_t total_bytes = bytes * (*nobjs);    //Ҫ����ֽ���
	size_t bytes_left = end_free - start_free;    //�ڴ��ʣ��ռ�
	bool_t has_big_chunk = false;
	//�ڴ�ؿռ��㹻
	if(bytes_left >= total_bytes)
	{
		result = start_free;
		start_free += total_bytes;
		return result;
	}
	else if(bytes_left >= bytes)
	{
		/*��������ȫ���ģ����ǻ����Է���һ��������*/
		*nobjs = bytes_left/bytes;
		total_bytes = *nobjs * bytes;
		result = start_free;
		start_free += total_bytes;
		return result;
	}
	/*�ڴ��û�п��Է���Ŀ���*/
	else
	{
		int i = 0;
		obj **my_free_list = NULL, *p = NULL;
		/*�ڴ���л���һЩ��ͷ��������ʵ���free-list*/
		if(bytes_left > 0)
		{
			/*�ҵ��ʵ���list*/
			obj **my_free_list = free_list + freelist_index(bytes_left);
			((obj *)start_free)->free_list_link = *my_free_list;/*�����ʼ��ָ��*/
			*my_free_list = (obj *)start_free;
		}
		//start_free = (char *)malloc(bytes_to_get);
		/*����free_list���޿��ÿ�*/
		for(i = bytes; i <= __MAX_BYTES; i += __ALIGN)
		{
			my_free_list = free_list + freelist_index(i);
			p = *my_free_list;
			if(p)
			{
				*my_free_list = p->free_list_link;
				start_free = (char *)p;
				end_free = start_free + i;
				bytes_left = end_free - start_free;
				has_big_chunk = true;
				/*�ҵ��㹻�ռ�*/
				if (bytes_left > total_bytes)
				{
					result = start_free;
					start_free += total_bytes;
					return result;
				}
				/*�ҵ��ռ�ֻ��һ�����߶����*/
				else if (bytes_left > bytes)
				{
					*nobjs = bytes_left/bytes;/*���䵽�ռ�Ŀ�����*/
					total_bytes = (*nobjs) * bytes;/*����ռ��С*/
					result = start_free;
					start_free += total_bytes;
					return result;
				}
			}
		}
		/*û���ҵ�����Ŀ飬��С����������кϲ�*/
		if (false == has_big_chunk)
		{
			result = merge_chunk_alloc(bytes,nobjs);
		}
		else
		{
			/*ȷʵû���㹻�ռ�*/
			end_free = 0;
		}
		return result;
	}
	return NULL;
}

char* merge_chunk_alloc(size_t need_bytes, size_t *nobjs)
{
	bool_t find_chunk = false;
	char* result = NULL;
	mem_state_t* ptr_state = NULL;
	int i = 0;
	/*�ڴ洢�������ڴ�ṹ���ҵ���bytesС�������ڴ沢���кϲ�*/
	for(i = need_bytes -__ALIGN; i > 0; i -= __ALIGN)
	{
		/*�ҵ������Ŀ��ÿռ���кϲ�*/
		ptr_state = free_list_state + freelist_index(i);
		/*���ڿ��õ������ռ��*/
		if ((ptr_state->cntn_chunk_num > 0) &&(i*ptr_state->cntn_unit_num >= need_bytes))
		{
			find_chunk = true;
			break;
		}
	}
	/*�ڿ������������²������������ռ�*/
	if (find_chunk ==false)
	{
		
		for(i = need_bytes -__ALIGN; (i > 0) && (find_chunk == false); i -= __ALIGN)
		{
			ptr_state = free_list_state + freelist_index(i);
			/*����һ�������ڴ浥Ԫ*/
			find_chunk = search_cntn_unit(ptr_state,i,need_bytes/i);
		}
	}
	if (true == find_chunk)
	{
		result = freelist_unit_merge(need_bytes,nobjs,i,ptr_state);
		return result;
	}
	
	return NULL;
}
char* freelist_unit_merge(size_t need_bytes, size_t *nobjs,size_t cur_list_bytes,mem_state_t* p_state)
{
	obj *p = NULL;
	size_t bytes_left = 0;
	size_t total_bytes = 0;
	char* result = NULL;
	start_free = (char *)p_state->cntn_chunk_head;
	end_free = start_free + cur_list_bytes*(p_state->cntn_unit_num);
	bytes_left = end_free - start_free;
	/*����������ȥ���Ѿ������ȥ�Ŀռ�*/
	p_state->pre_cntn_head->free_list_link = ((obj*)(p_state->cntn_chunk_head + bytes_left))->free_list_link;
	/*��������������*/
	reset_freelist_state(p_state);

	*nobjs = bytes_left/need_bytes;/*���䵽�ռ�Ŀ�����*/
	total_bytes = (*nobjs) * need_bytes;/*����ռ��С*/
	result = start_free;
	/*��ʼ��������ڴ�*/
	memset(result,0,total_bytes);
	start_free += total_bytes;
	/*����һ�������ڴ浥Ԫ*/
	search_cntn_unit(p_state,cur_list_bytes,2);
	return result;
}
void reset_freelist_state(mem_state_t *ptr_state)
{
	ptr_state->cntn_chunk_num--;
	ptr_state->cntn_chunk_head = NULL;
	ptr_state->cntn_unit_num = 0;
	ptr_state->pre_cntn_head = NULL;
}
bool_t search_cntn_unit(mem_state_t *ptr_state,size_t nbytes,size_t ncount)
{
	size_t temp_ncount = 1;/*������Ԫ����*/
	size_t unit_size = 0;
	bool_t find_unit = false;/*�Ƿ��ҵ������ڴ浥Ԫ��־*/
	obj **my_free_list = NULL;
	obj *p = NULL;/*��ǰ�ڵ�*/
	obj *pre_p = NULL; /*p�ڵ�ǰ���һ���ڵ�*/
	my_free_list = free_list + freelist_index(nbytes);
	pre_p = p = *my_free_list;
	unit_size = round_up(nbytes);
	while (p && p->free_list_link != NULL)
	{
		size_t i = 1;/*ɨ�������qΪ��׼���Ѿ�ɨ���Ԫ�ؼ���*/
		int temp_byte = 0;
		/*�ҵ���һ���������ڴ�ռ�*/
		obj* q = p->free_list_link;
		i++;
		temp_byte = (q - p)*SIZE_OF_POINTER;/*����������ַ�����ֽ���*/
		/*�ҵ������ռ�����һ���ڴ浥Ԫ*/
		while ((temp_byte == unit_size*(i-1)) && q != NULL)
		{

			if (q->free_list_link != NULL)
			{
				q = q->free_list_link;
				i++;
				/*����������ַ�����ֽ���*/
				temp_byte = (q - p)*SIZE_OF_POINTER;
			}
			
			temp_ncount++;
		}
		/*���������ڴ浥Ԫ*/
		if (1 == temp_ncount)
		{
			pre_p = p;
			p = p->free_list_link;
		}
		/*�ҵ�������Ԫ���ȴ��ڵ���ncount*/
		if (temp_ncount >= ncount)
		{
			update_state(ptr_state,p,pre_p,temp_ncount);
			find_unit = true;
			break;
		}
	}
	return find_unit;
}
void update_state(mem_state_t* ptr_state,obj* cntn_head,obj* pre_head,size_t ncount)
{
	ptr_state->cntn_chunk_head = cntn_head;
	ptr_state->cntn_chunk_num++;
	ptr_state->cntn_unit_num = ncount;
	ptr_state->pre_cntn_head = pre_head;

}