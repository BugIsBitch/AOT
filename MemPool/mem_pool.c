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
mem_state_t free_list_state[__NFREELISTS];/*记录连续块的状态*/
char *start_free = &(pool_arr[0]);    //mempool开始位置
char *end_free = &(pool_arr[__POOL_SIZE]);    //mempool结束位置的下一个位置
/* ---------------------- FUNCTION IMPLEMENTATION ---------------------*/


/*初始化内存池*/
void init_mem_pool()
{
	mem_state_t* p_state = NULL;
	obj *p = NULL;
	obj** my_free_list = NULL;
	size_t i = 0;
	for(i = __ALIGN; i <= __MAX_BYTES; i += __ALIGN)
	{
		/*初始化freelist链表*/
		my_free_list = free_list + freelist_index(i);
		p_state = free_list_state + freelist_index(i);
		p = *my_free_list;
		p = NULL;
		/*初始化内存池状态信息*/
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
//返回bytes所对应的freelist索引号
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
	my_free_list = free_list + freelist_index(nbytes);/*找到适当的空链表*/
	result = *my_free_list;
	if(result == NULL)
	{
		void *r = refill(round_up(nbytes));
		return r;
	}
	/*重新计算连续块*/
	p_state = free_list_state + freelist_index(nbytes);
	if (p_state->cntn_chunk_head == result)
	{
		reset_freelist_state(p_state);
	}
	//取出空闲块
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
	/*默认从内存池取得16个块*/
	size_t nobjs = 16;
	char *chunk = chunk_alloc(n, &nobjs); 
	if(!chunk)
	{
		return NULL;
	}
	
	/*内存池空间告急仅返回一个块，则直接返回给用户*/
	if(nobjs == 1)
	{
		return chunk;
	}
	/*否则准备向free_list中纳入新的节点*/
	my_free_list = free_list + freelist_index(n);
	/*以下在chunk的连续空间上建立free_list*/
	result = (obj *)chunk;    //此块返回给用户
	*my_free_list = next_obj = (obj *)(chunk + n);
	/*空闲的连续空间超过2个*/
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
		/*最后一个块*/
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
//从内存池取连续的块空间
char *chunk_alloc(size_t bytes, size_t *nobjs)
{
	char *result = NULL;
	size_t total_bytes = bytes * (*nobjs);    //要求的字节数
	size_t bytes_left = end_free - start_free;    //内存池剩余空间
	bool_t has_big_chunk = false;
	//内存池空间足够
	if(bytes_left >= total_bytes)
	{
		result = start_free;
		start_free += total_bytes;
		return result;
	}
	else if(bytes_left >= bytes)
	{
		/*不够分配全部的，但是还可以分配一个或多个块*/
		*nobjs = bytes_left/bytes;
		total_bytes = *nobjs * bytes;
		result = start_free;
		start_free += total_bytes;
		return result;
	}
	/*内存池没有可以分配的块了*/
	else
	{
		int i = 0;
		obj **my_free_list = NULL, *p = NULL;
		/*内存池中还有一些零头，先配给适当的free-list*/
		if(bytes_left > 0)
		{
			/*找到适当的list*/
			obj **my_free_list = free_list + freelist_index(bytes_left);
			((obj *)start_free)->free_list_link = *my_free_list;/*保存初始的指针*/
			*my_free_list = (obj *)start_free;
		}
		//start_free = (char *)malloc(bytes_to_get);
		/*看看free_list有无可用块*/
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
				/*找到足够空间*/
				if (bytes_left > total_bytes)
				{
					result = start_free;
					start_free += total_bytes;
					return result;
				}
				/*找到空间只够一个或者多个块*/
				else if (bytes_left > bytes)
				{
					*nobjs = bytes_left/bytes;/*分配到空间的块数量*/
					total_bytes = (*nobjs) * bytes;/*分配空间大小*/
					result = start_free;
					start_free += total_bytes;
					return result;
				}
			}
		}
		/*没有找到更大的块，找小的连续块进行合并*/
		if (false == has_big_chunk)
		{
			result = merge_chunk_alloc(bytes,nobjs);
		}
		else
		{
			/*确实没有足够空间*/
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
	/*在存储的连续内存结构中找到比bytes小的连续内存并进行合并*/
	for(i = need_bytes -__ALIGN; i > 0; i -= __ALIGN)
	{
		/*找到连续的可用空间进行合并*/
		ptr_state = free_list_state + freelist_index(i);
		/*存在可用的连续空间块*/
		if ((ptr_state->cntn_chunk_num > 0) &&(i*ptr_state->cntn_unit_num >= need_bytes))
		{
			find_chunk = true;
			break;
		}
	}
	/*在空闲链表中重新查找满足条件空间*/
	if (find_chunk ==false)
	{
		
		for(i = need_bytes -__ALIGN; (i > 0) && (find_chunk == false); i -= __ALIGN)
		{
			ptr_state = free_list_state + freelist_index(i);
			/*找下一个连续内存单元*/
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
	/*空闲链表中去掉已经分配出去的空间*/
	p_state->pre_cntn_head->free_list_link = ((obj*)(p_state->cntn_chunk_head + bytes_left))->free_list_link;
	/*更新连续块数量*/
	reset_freelist_state(p_state);

	*nobjs = bytes_left/need_bytes;/*分配到空间的块数量*/
	total_bytes = (*nobjs) * need_bytes;/*分配空间大小*/
	result = start_free;
	/*初始化分配的内存*/
	memset(result,0,total_bytes);
	start_free += total_bytes;
	/*找下一个连续内存单元*/
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
	size_t temp_ncount = 1;/*连续单元数量*/
	size_t unit_size = 0;
	bool_t find_unit = false;/*是否找到连续内存单元标志*/
	obj **my_free_list = NULL;
	obj *p = NULL;/*当前节点*/
	obj *pre_p = NULL; /*p节点前面的一个节点*/
	my_free_list = free_list + freelist_index(nbytes);
	pre_p = p = *my_free_list;
	unit_size = round_up(nbytes);
	while (p && p->free_list_link != NULL)
	{
		size_t i = 1;/*扫描计数，q为基准，已经扫描的元素计数*/
		int temp_byte = 0;
		/*找到第一个连续的内存空间*/
		obj* q = p->free_list_link;
		i++;
		temp_byte = (q - p)*SIZE_OF_POINTER;/*计算两个地址相差的字节数*/
		/*找到连续空间的最后一个内存单元*/
		while ((temp_byte == unit_size*(i-1)) && q != NULL)
		{

			if (q->free_list_link != NULL)
			{
				q = q->free_list_link;
				i++;
				/*计算两个地址相差的字节数*/
				temp_byte = (q - p)*SIZE_OF_POINTER;
			}
			
			temp_ncount++;
		}
		/*不是连续内存单元*/
		if (1 == temp_ncount)
		{
			pre_p = p;
			p = p->free_list_link;
		}
		/*找到连续单元长度大于等于ncount*/
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