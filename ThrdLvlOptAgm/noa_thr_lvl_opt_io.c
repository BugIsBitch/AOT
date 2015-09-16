
#include "noa_thr_lvl_opt_def.h"
#include "noa_thr_lvl_opt_types.h"
#include <string.h>
#include <stdio.h>

extern VL_Path_Tag phy_path_arr[TOTAL_VL_NUM];
extern VL_Para_Tag vl_para_arr[TOTAL_VL_NUM];
extern long output_vl_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT][MAX_PORT_VL_COUNT];
extern Rec_Info_Tag sw_rec_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];
extern VL_Delay_Tag vl_delay_arr[TOTAL_VL_NUM][TOTAL_NET_WORK];
extern int all_sw_buf_queue_dep_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];
extern char es_sw_name_arr[SW_COUNT+MAX_ES_CNT][100];
extern int sw_network_two[SW_COUNT][2]; 
extern int sw_number_net[TOTAL_NET_WORK];
extern int sw_port_speed[SW_COUNT][SW_PORT_COUNT];

VL_Path_Tag* get_vl_path_arr(long i)
{ 
	VL_Path_Tag *ret =NULL;
	ret=&(phy_path_arr[i]);
	return ret;                         //这个返的是地址
}
void set_vl_path_arr(long i,VL_Path_Tag path)
{  
	int j,k=0;
	phy_path_arr[i].multi_num=path.multi_num;
	for (j=0;j<MAX_MULTI_PATH;j++)
	{   
		phy_path_arr[i].path_nd_count[j]=path.path_nd_count[j];
		
		for (k=0;k<PATH_ND_COUNT;k++)
		{  
			phy_path_arr[i].nd_arr[j][k].input_port_id=path.nd_arr[j][k].input_port_id;
			phy_path_arr[i].nd_arr[j][k].output_port_id=path.nd_arr[j][k].output_port_id;
			phy_path_arr[i].nd_arr[j][k].node_index=path.nd_arr[j][k].node_index;
		}
	}
}


VL_Para_Tag get_vl_para_arr(long i)
{ 
	VL_Para_Tag ret;
	ret=vl_para_arr[i];
	return ret;                           //这个ret返回的不是地址
}
void set_vl_para_arr(long i,VL_Para_Tag parame)
{  
	vl_para_arr[i].bag=parame.bag;
	vl_para_arr[i].max_pkt=parame.max_pkt;
	vl_para_arr[i].min_pkt=parame.min_pkt;
	vl_para_arr[i].sp=parame.sp;
	vl_para_arr[i].vlid=parame.vlid;
    //vl_para_arr[i].max_burst=parame.max_burst;
	//strcpy(vl_para_arr[i].vlid,parame.vlid);
} 
long get_vl_para_id (long i)
{
	long ret=vl_para_arr[i].vlid;
	return ret;
}
void set_vl_para_tpa(long i,double tpa_ac)
{
	vl_para_arr[i].vl_tpa=tpa_ac;
}
long get_output_vl_arr(int i,int j,int k,int l)
{
	long ret;
	ret=output_vl_arr[i][j][k][l];
	return ret;
}
void set_output_vl_arr(int i,int j,int k,int l,long vl)
{  
	output_vl_arr[i][j][k][l] =vl;
}



Sg_VL_Delay_Tag get_vl_delay(long i,int j,int k)
{
	Sg_VL_Delay_Tag  ret;
	ret=vl_delay_arr[i][j].path_delay_arr[k];
	return ret;
}
void set_vl_delay(long i,int j,VL_Delay_Tag delay_1)
{ 
	int k=0;
	for (k=0;k<MAX_MULTI_PATH;k++)
	{
		vl_delay_arr[i][j].path_delay_arr[k]=delay_1.path_delay_arr[k];
	}
}

int get_all_sw_buf_queue_dep_arr(int i,int j,int k)
{
	int ret=0;
	ret=all_sw_buf_queue_dep_arr[i][j][k];
	return ret;
}
void set_all_sw_buf_queue_dep_arr(int i,int j,int k,int queue_1)
{
	all_sw_buf_queue_dep_arr[i][j][k]=queue_1;
}
Rec_Info_Tag* get_sw_rec_arr(int i,int j,int k)
{
	Rec_Info_Tag *ret;
	ret=&(sw_rec_arr[i][j][k]);
	return ret;
}
void set_sw_rec_arr(int i,int j,int k,Rec_Info_Tag rec_1)
{ 
	sw_rec_arr[i][j][k].worst_delay=rec_1.worst_delay;
	sw_rec_arr[i][j][k].queue_depth=rec_1.queue_depth;
}

void set_sw_network_two(int i,int network)
{
	sw_network_two[i][0]=network;

}

void ag_set_sw_net_two() //为了防止XML里交换机的排序并没有依照A/B网分开，这里进行了重新排序，便于我们在一个网内对交换机的buffer排序
{
	int i=0;
	int a=0;
	int b=0;
	for (i=0;i<SW_COUNT;i++)
	{
		if (sw_network_two[i][0]==0)
		{   
			sw_network_two[i][1]=a;
			a++;
		}
		else if (sw_network_two[i][0]==1)
		{   
			sw_network_two[i][1]=b;
			b++;
		}
	}
	sw_number_net[0]=a;
	sw_number_net[1]=b;
}
void set_sw_port_speed(int sw_i,int port_i,int speed)
{
	sw_port_speed[sw_i][port_i]=speed;
}
int get_sw_number_net(int network)
{
	int sw_number=0;
	sw_number=sw_number_net[network];
	return sw_number;
}
int get_set_sw_net_two(int i,int j)
{
	int ret=0;
	ret=sw_network_two[i][j];
	return ret;
}
int get_sw_ord_id(int sw_net, int sw_network_id)//第一个参数表示网络，第二个参数表示在单网中的id,得到在其在双网中的排序id
{   
	int i=0;
    int ret=0;
	for (i=0;i<SW_COUNT;i++)
	{
	   if (sw_network_two[i][0]==sw_net && sw_network_two[i][1]==sw_network_id)
	   {  
		   ret=i;
		   break;
	   }
	}
	return ret;
}


double get_vl_max_burst(long i)
{
	double ret=vl_para_arr[i].max_burst;
	return ret;
}
double get_vl_tpa(long i)
{
	double ret=vl_para_arr[i].vl_tpa;
	return ret;
}