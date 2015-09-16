/*���ģ��Ҫ�ҵ����еĻ��ߣ���Ϊ���е�buffer_Tag���Ÿ���*/
/*���������ǣ�/*vl path array of network A and network B*/

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
extern Buf_Nd_Tag *graph[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//201�е��ڽ�����
extern Edge_Tag edge_arr[TOTAL_NET_WORK][SP_COUNT][EDGE_NUM];//���еı߷���������������ǲ�������TPA��
extern int topsort_buf_id_arr[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];
extern int sw_network_two[SW_COUNT][2];  




//void ring_begin(int i,int sp_r)
//{
//	create_graph(i,sp_r);
//    find_ring(i,sp_r);
//	buffer_Topsort(i,sp_r);
//}

///////////////////////////////*��������ͼ*///////////////////////////
void graph_initial(int network,int priority)//����ͼ���ڽ�����ĳ�ʼ���������ظ��ڽ�����ĵ�ַ��//��û����ô��buffer��ʱ��ʵ���Ͻ�����һЩ����buffer
{ 
  int buf_id=0;
  /*��Buffer���б��*/
  for (buf_id =0; buf_id < BUFFER_NUM;buf_id++)
  {   
	  Buf_Nd_Tag *head=NULL;
      head=(Buf_Nd_Tag *)malloc(sizeof(Buf_Nd_Tag));//���ٳ��㹻�������ռ���װһ����㣨buffer_Tag��
	  head->buf_id = buf_id;
      head->next=NULL;
      graph[network][priority][buf_id]=head;//headΪͷָ�룬����ָ��ͷ����ָ��
  }
}

void create_graph(int network,int priority,int vl_count)//�����ϱ������8*7*25=1400���ߣ�����ı�����Щ�����ܵ������򻷵ıߣ���buffer_Tag����������ϵ�ıߣ�
{  
	int vl_index,mult_path_index,hop_index;
	int edge_index = 0;
	vl_index = 0;
	mult_path_index = 0;
	hop_index = 0;
	/*network=0��ʾA����=1��ʾB��*/
    graph_initial(network,priority);//��ʼ������ͼ
   
	for ( vl_index = 0;vl_index <vl_count;vl_index++)
	{
      if (vl_para_arr[vl_index].sp==priority)//��������ȼ���VL�ſ���
      {
		  int son_vl_num=0;
		  son_vl_num=phy_path_arr[vl_index].multi_num;
		  for (mult_path_index=0;mult_path_index<son_vl_num;mult_path_index++)
		  {   
			  int hop_num=phy_path_arr[vl_index].path_nd_count[mult_path_index];/*��ȡ�м���*/
			  if (hop_num >= 2)//ֻ�������������ϲſ����ҵ��������
			  {
				  for (hop_index = 1;hop_index < hop_num;hop_index++)//�����������е���
				  {  
					  int start_node_index = 0 ,end_node_index = 0;
					  int cur_edge_index = 0;
					  int cur_nd_index=phy_path_arr[vl_index].nd_arr[mult_path_index][hop_index].node_index;
				      int next_nd_index = phy_path_arr[vl_index].nd_arr[mult_path_index][hop_index+1].node_index;
					  start_node_index = (phy_path_arr[vl_index].nd_arr[mult_path_index][hop_index].output_port_id)+cur_nd_index*SW_PORT_COUNT;
					  end_node_index = (phy_path_arr[vl_index].nd_arr[mult_path_index][hop_index+1].output_port_id)+next_nd_index*SW_PORT_COUNT;
					  cur_edge_index = create_edge(start_node_index,end_node_index,network,priority,&edge_index);//���������
					  sg_arv_crv_arr[vl_index][mult_path_index][hop_index].edge_index=cur_edge_index;
					  
				  }
			  }  
		  }
      }  
	}

}

int create_edge(int start_node_index,int end_node_index,int network,int priority,int *p_edge_index) //   1��a��b��200
{   
	int ret=0;
	int j=0;
	Buf_Nd_Tag *p=graph[network][priority][start_node_index]->next;
	while(p!=NULL)
	{  
		if (p->buf_id == end_node_index)
	   {   
               ret=find_edge_id(network,priority,start_node_index,end_node_index,*p_edge_index);
  			   j=1;//��������ˣ��Ͳ�������ˣ�ֱ��������,��Ҫ�����������ͼ�ıߵ�id//////
			   break;
	   }
		else
	    {
            p=p->next;
	    }
	}
    if (j==0)//����߻�û���
    {   
		p=(Buf_Nd_Tag *)malloc(sizeof(Buf_Nd_Tag));//���ٳ��㹻�������ռ���װһ����㣨buffer_Tag��
		p->buf_id=end_node_index;
		p->next=graph[network][priority][start_node_index]->next;//��a�е�ͷ�������һ���µĽ��
		graph[network][priority][start_node_index]->next=p;
        (*p_edge_index)++;
		edge_arr[network][priority][*p_edge_index].head=start_node_index;
		edge_arr[network][priority][*p_edge_index].tail=end_node_index;
		ret=*p_edge_index;
    }
	return ret;
}
int find_edge_id(int network,int priority,int start_node_index,int end_node_index,int edge_index)//����������β���ıߵ�id
{  
	int ret=-1;     //���ʱ��Ҫ������Ҫ���Щ����Ķ�����ȥ��
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


///////////////////////*���޻�����ͼBuf_Nd_Tag *Graph_1[BUFFER_NUM+1]������������*///////////////////////////
//int topsort_buf_id_arr[BUFFER_NUM];//�����Ϊ0�Ľ��,��������еĵ㶼���������������
void top_sort(int network,int priority)
{
 int buffer_indegree[BUFFER_NUM];//������������
 int buf_index=0;
 while(buf_index < BUFFER_NUM)//˵�����н��û���ҵ�
  {
	   int cur_buf_indx=0;
	   int number_exist=-1;
	   indegree(buffer_indegree,BUFFER_NUM,network,priority);//��������������
	   for (cur_buf_indx=0;cur_buf_indx<BUFFER_NUM;cur_buf_indx++)
	   {
		  if (buffer_indegree[cur_buf_indx]==0)
			{ 
			  number_exist=look_number(network,priority,buf_index,cur_buf_indx);//�ж�j�Ƿ��Ѿ������,��topsort_buf_id_arr��ǰk��Ԫ����Ѱ��
			  if (number_exist==0)
			  {
				  topsort_buf_id_arr[network][priority][buf_index]=cur_buf_indx;  //���δ��������������
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
		buffer_indegree[buf_indx]=0;//����0��ʾ���ա�

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
