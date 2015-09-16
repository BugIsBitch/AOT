/*这个模块要找到所有的环边，并为所有的buffer_Tag给排个序*/
/*它的输入是：/*vl path array of network A and network B*/

#include "noa_thr_lvl_opt_graph.h"
#include "noa_thr_lvl_opt_types.h"
#include "noa_thr_lvl_opt_def.h"
#include <stdio.h>
#include <stdlib.h>
#include "MemPool/mem_pool.h"

/*vl path array of network A and network B*/
extern VL_Path_Tag phy_path_arr[TOTAL_VL_NUM];
extern VL_Para_Tag vl_para_arr[TOTAL_VL_NUM];
extern Arv_Crv_Para_Tag sg_arv_crv_arr[TOTAL_VL_NUM][MAX_MULTI_PATH][HOP];
/*all vl of switch output port buffer_Tag*/
extern long output_vl_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT][MAX_PORT_VL_COUNT];
extern Buf_Nd_Tag *graph[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//201行的邻接链表
extern Edge_Tag edge_arr[TOTAL_NET_WORK][SP_COUNT][EDGE_NUM];//所有的边放在这里，标明了它是不是属于TPA边
extern int topsort_buf_id_arr[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];
extern int sw_network_two[SW_COUNT][2];  




//void ring_begin(int i,int sp_r)
//{
//	create_graph(i,sp_r);
//    find_ring(i,sp_r);
//	buffer_Topsort(i,sp_r);
//}

///////////////////////////////*建立有向图*///////////////////////////
void graph_initial(int network,int priority)//有向图的邻接链表的初始化，并返回该邻接链表的地址。//当没有那么多buffer的时候，实际上建立了一些虚拟buffer
{ 
  int buf_id=0;
  /*对Buffer进行编号*/
  for (buf_id =0; buf_id < BUFFER_NUM;buf_id++)
  {   
	  Buf_Nd_Tag *head=NULL;
      head=(Buf_Nd_Tag *)malloc(sizeof(Buf_Nd_Tag));//开辟出足够的连续空间来装一个结点（buffer_Tag）
	  head->buf_id = buf_id;
      head->next=NULL;
      graph[network][priority][buf_id]=head;//head为头指针，即：指向头结点的指针
  }
}

void create_graph(int network,int priority,int vl_count)//理论上边最多有8*7*25=1400个边，这里的边是那些：可能导致有向环的边（有buffer_Tag计算依赖关系的边）
{  
	int vl_index,mult_path_index,hop_index;
	int edge_index = 0;
	vl_index = 0;
	mult_path_index = 0;
	hop_index = 0;
	/*network=0表示A网，=1表示B网*/
    graph_initial(network,priority);//初始化有向图
   
	for ( vl_index = 0;vl_index <vl_count;vl_index++)
	{
      if (vl_para_arr[vl_index].sp==priority)//是这个优先级的VL才考虑
      {
		  int son_vl_num=0;
		  son_vl_num=phy_path_arr[vl_index].multi_num;
		  for (mult_path_index=0;mult_path_index<son_vl_num;mult_path_index++)
		  {   
			  int hop_num=phy_path_arr[vl_index].path_nd_count[mult_path_index];/*获取有几条*/
			  if (hop_num >= 2)//只有两跳及其以上才可以找到：有向边
			  {
				  for (hop_index = 1;hop_index < hop_num;hop_index++)//遍历它的所有的跳
				  {  
					  int start_node_index = 0 ,end_node_index = 0;
					  int cur_edge_index = 0;
					  int cur_nd_index=phy_path_arr[vl_index].nd_arr[mult_path_index][hop_index].node_index;
				      int next_nd_index = phy_path_arr[vl_index].nd_arr[mult_path_index][hop_index+1].node_index;
					  start_node_index = (phy_path_arr[vl_index].nd_arr[mult_path_index][hop_index].output_port_id)+cur_nd_index*SW_PORT_COUNT;
					  end_node_index = (phy_path_arr[vl_index].nd_arr[mult_path_index][hop_index+1].output_port_id)+next_nd_index*SW_PORT_COUNT;
					  cur_edge_index = create_edge(start_node_index,end_node_index,network,priority,&edge_index);//连接有向边
					  sg_arv_crv_arr[vl_index][mult_path_index][hop_index].edge_index=cur_edge_index;
					  
				  }
			  }  
		  }
      }  
	}

}

int create_edge(int start_node_index,int end_node_index,int network,int priority,int *p_edge_index) //   1《a和b《200
{   
	int ret=0;
	int j=0;
	Buf_Nd_Tag *p=graph[network][priority][start_node_index]->next;
	while(p!=NULL)
	{  
		if (p->buf_id == end_node_index)
	   {   
               ret=find_edge_id(network,priority,start_node_index,end_node_index,*p_edge_index);
  			   j=1;//这个边有了，就不用添加了，直接跳出来,还要返回这个有向图的边的id//////
			   break;
	   }
		else
	    {
            p=p->next;
	    }
	}
    if (j==0)//这个边还没添加
    {   
		p=(Buf_Nd_Tag *)malloc(sizeof(Buf_Nd_Tag));//开辟出足够的连续空间来装一个结点（buffer_Tag）
		p->buf_id=end_node_index;
		p->next=graph[network][priority][start_node_index]->next;//在a行的头结点后插入一个新的结点
		graph[network][priority][start_node_index]->next=p;
        (*p_edge_index)++;
		edge_arr[network][priority][*p_edge_index].head=start_node_index;
		edge_arr[network][priority][*p_edge_index].tail=end_node_index;
		ret=*p_edge_index;
    }
	return ret;
}
int find_edge_id(int network,int priority,int start_node_index,int end_node_index,int edge_index)//找有这种首尾结点的边的id
{  
	int ret=-1;     //这个时候要报错，我要多加些报错的东西进去。
	int cur_edge_index=0;
	for ( cur_edge_index = 0;cur_edge_index <= edge_index;cur_edge_index++)
	{   
	     if (edge_arr[network][priority][cur_edge_index].head==start_node_index && edge_arr[network][priority][cur_edge_index].tail==end_node_index)
	     {
	          ret= cur_edge_index;
	     }
	}
	return ret;
}


///////////////////////*对无环有向图Buf_Nd_Tag *Graph_1[BUFFER_NUM+1]进行拓扑排序*///////////////////////////
//int topsort_buf_id_arr[BUFFER_NUM];//存入度为0的结点,到最后，所有的点都被存入这个数组中
void top_sort(int network,int priority)
{
 int buffer_indegree[BUFFER_NUM];//存各个结点的入度
 int buf_index=0;
 while(buf_index < BUFFER_NUM)//说明还有结点没有找到
  {
	   int cur_buf_indx=0;
	   int number_exist=-1;
	   indegree(buffer_indegree,BUFFER_NUM,network,priority);//计算各个结点的入度
	   for (cur_buf_indx=0;cur_buf_indx<BUFFER_NUM;cur_buf_indx++)
	   {
		  if (buffer_indegree[cur_buf_indx]==0)
			{ 
			  number_exist=look_number(network,priority,buf_index,cur_buf_indx);//判断j是否已经被存过,在topsort_buf_id_arr的前k个元素中寻找
			  if (number_exist==0)
			  {
				  topsort_buf_id_arr[network][priority][buf_index]=cur_buf_indx;  //依次存在这个数组里面
				  buf_index++;
			  }
			}
		 }
  }
}

int look_number(int network,int priority,int end_buf_indx,int src_buf)
{   int i=0;
    int number_exist=0;
	for (i=0;i<end_buf_indx;i++)
	{ 
		if (topsort_buf_id_arr[network][priority][i]==src_buf)
		{   
			number_exist=1;
			break;
		}	
	}
	return number_exist;
}
void indegree(int buffer_indegree[],int num,int network,int priority)
{
	int buf_indx=0;
	int cur_buf_indx=0;
	for (buf_indx = 0;buf_indx<BUFFER_NUM; buf_indx++)
	{
		buffer_indegree[buf_indx]=0;//这里0表示“空”

	}
	for (buf_indx=0;buf_indx<num;buf_indx++)
	{  
		Buf_Nd_Tag *p=graph[network][priority][buf_indx]->next;
		while(p!=NULL)
		{  
			cur_buf_indx=p->buf_id;
			buffer_indegree[cur_buf_indx]++;
			p=p->next;
		}
	}
}
