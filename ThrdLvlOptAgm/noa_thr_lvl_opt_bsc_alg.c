/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************

*********************************************************************/


/*------------------------- FILE INCLUSION --------------------------*/
#include "noa_thr_lvl_opt_types.h"
#include "noa_thr_lvl_opt_def.h"
#include "noa_thr_lvl_opt_util.h"
#include "noa_thr_lvl_opt_bsc_alg.h"
#include "noa_thr_lvl_opt_crt_alg.h"
#include "noa_thr_lvl_opt_graph.h"
#include "noa_thr_lvl_opt_io.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/
/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DEFINITION --------------------*/
/*vl path array of network A and network B*/
extern VL_Path_Tag phy_path_arr[TOTAL_VL_NUM];
/*vl parameter array of network A and B*/
extern VL_Para_Tag vl_para_arr[TOTAL_VL_NUM];
/*service curve*/
extern Srv_Crv_Para_Tag srv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];
/*arrive curve of single vl*/
extern Arv_Crv_Para_Tag sg_arv_crv_arr[TOTAL_VL_NUM][MAX_MULTI_PATH][HOP];
/*switch identifier map with array index*/
//extern int sw_id_arr[SW_COUNT];
extern Grp_Arv_Crv_Para_Tag grp_arv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];
extern Rec_Info_Tag sw_rec_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];
/*all vl of switch output port buffer_Tag*/
extern long output_vl_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT][MAX_PORT_VL_COUNT];
extern Sw_Port_SP_Tag ring_sw_port_sp[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];
extern  int topsort_buf_id_arr[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//buffer_Tag的计算顺序


extern Buf_Nd_Tag edge_arr[TOTAL_NET_WORK][SP_COUNT][EDGE_NUM];
extern int sw_network_two[SW_COUNT][2]; 
extern int sw_number_net[TOTAL_NET_WORK];
int sw_port_speed[SW_COUNT][SW_PORT_COUNT];
/* ---------------------- FUNCTION DECLARATIONS ---------------------*/


/*第一个参数是网络号 第二个参数是优先级*/
void bgn_thr_lvl_opt(int network,int priority,int vl_count)
{
	int buf_index=0;
	long vl_index=0;
	static Buff_Sg_Path_Para_Tag all_buff_vl_para[TOTAL_VL_NUM];
	int network_sw_number=sw_number_net[network];
	for (vl_index=0;vl_index<TOTAL_VL_NUM;vl_index++)//初始化数组all_buff_vl_para[TOTAL_VL_NUM]
	{
		all_buff_vl_para[vl_index].hop_index=INVALID;
		all_buff_vl_para[vl_index].vl_multi_index=INVALID;
	}
	top_sort(network,priority);
	fst_hop_vl_arv_crv(priority,vl_count);                  //先把所有的第一跳的到达曲线给算出来  
	for (buf_index = 0;buf_index < BUFFER_NUM;buf_index++)
	{   
		int cur_buf_index=0;
		Sw_Port_SP_Tag sw_port_sp; 

		cur_buf_index=topsort_buf_id_arr[network][priority][buf_index];//当不满的时候，存在一些虚拟buffer
		sw_port_sp.port =ring_sw_port_sp[network][priority][cur_buf_index].port;
		sw_port_sp.sp_index = priority;
		sw_port_sp.sw_index = ring_sw_port_sp[network][priority][cur_buf_index].sw_index;
		
		if (sw_port_sp.sw_index<network_sw_number)
		{
			cal_group_arv_crv(sw_port_sp,all_buff_vl_para);      //计算有向图(1/4)的某个结点(1/200)的聚合到达曲线
			cal_port_out_vl_arv_crv(sw_port_sp,all_buff_vl_para,network);//算出该结点的延迟后，进而算出所有从该结点出去的到达曲线
		}  
	}
}

void fst_hop_vl_arv_crv(int priority,int vl_count)
{
	long vl_index;
	for(vl_index=0;vl_index<vl_count;vl_index++)/*对每个优先级，对所有VL做计算*/
	{ 
		if(vl_para_arr[vl_index].sp == priority)/*判断VL跟指定的SP是否相等*/
		{ 
			int multi_index=0;
			VL_Path_Tag path;
			path = phy_path_arr[vl_index];/*从路径库中找到指定网指定vl的路径。*/

			for (multi_index = 0 ; multi_index < path.multi_num ; multi_index++)/*对所有的目的ES依次去处理*/
			{  
				if (path.path_nd_count[multi_index]!=0)//没有hop，说明这个分路径在本网（A/B）中不存在
				{
				  cal_arv_crv(vl_index,multi_index);
				}
			}
		}					
	}
}


void cal_arv_crv(int vl_index,int multi_index)//我们要把那些没有跳（或者hop=0)的分链路给标出来
{    
	VL_Para_Tag vl_para=vl_para_arr[vl_index];//VL的信息

	Arv_Crv_Para_Tag arv_crv_para;

	/*计算单个到达曲线的斜率和突发度，并存储*/
	arv_crv_para.arv_p=vl_para.max_pkt/vl_para.bag;
	arv_crv_para.burst=vl_para.max_pkt;
	arv_crv_para.edge_index=INVALID;//这个边不是有向图中的边
	/*store the arrival curve*/
	sg_arv_crv_arr[vl_index][multi_index][0]=arv_crv_para;//第0处为通过第一个交换机的到达曲线

}

void cal_port_out_vl_arv_crv(Sw_Port_SP_Tag buff_sw_port_sp,Buff_Sg_Path_Para_Tag all_buff_vl_para[TOTAL_VL_NUM],int network)
{ 
	 double worst_delay = 0.0;
	 int vl_index=0;
	 int sw = 0,output_port_index = 0,sp=0;
	 int two_sw_network_id=0;
	 double output_port_speed=0;
	  //B:下面为服务曲线的信息
	  Srv_Crv_Para_Tag srv_crv_para;
	  //C:下面为聚合到达曲线的信息
	  Grp_Arv_Crv_Para_Tag gp_arv_crv_para;
  
	  two_sw_network_id=get_sw_ord_id(network,buff_sw_port_sp.sw_index);
	  output_port_speed=C*(sw_port_speed[two_sw_network_id][buff_sw_port_sp.port])/100;
	  srv_crv_para=cal_service_crv(buff_sw_port_sp,output_port_speed);

	  sw=buff_sw_port_sp.sw_index;
	  output_port_index=buff_sw_port_sp.port;
	  sp=buff_sw_port_sp.sp_index;

	  gp_arv_crv_para=grp_arv_crv_arr[sw][output_port_index][sp];//得到聚合到达曲线。/*计算最大延迟并存储*/
	  worst_delay = srv_crv_para.T + gp_arv_crv_para.y/srv_crv_para.R - gp_arv_crv_para.en;
	  sw_rec_arr[sw][output_port_index][sp].worst_delay = worst_delay;

	  for (vl_index = 0; vl_index < MAX_PORT_VL_COUNT ; vl_index++)/*这里可以加个break,*/
	  {   
		  int hop_index = 0,mult_indx = 0;
		  int vl = output_vl_arr[sw][output_port_index][sp][vl_index];/*在指定的网指定buffer_Tag里取VL*/
		  if (vl==INVALID_VL)
		  {
			  break;
		  }
	  
		//  Arv_Crv_Para_Tag arv_crv_para;
		  hop_index=all_buff_vl_para[vl].hop_index;//该buffer_Tag是现VL第几个交换机的
		  mult_indx=all_buff_vl_para[vl].vl_multi_index;

		  if ( hop_index < HOP)
		  {   
			  VL_Para_Tag vl_para= vl_para_arr[vl];
			  sg_arv_crv_arr[vl][mult_indx][hop_index].burst=sg_arv_crv_arr[vl][mult_indx][hop_index-1].burst+
			  sg_arv_crv_arr[vl][mult_indx][hop_index].arv_p*(worst_delay-vl_para.max_pkt/output_port_speed);
			  sg_arv_crv_arr[vl][mult_indx][hop_index].arv_p=sg_arv_crv_arr[vl][mult_indx][hop_index-1].arv_p;
		  }
      }
}


Srv_Crv_Para_Tag  cal_service_crv(Sw_Port_SP_Tag sw_port_sp,double output_port_speed)
{
	Srv_Crv_Para_Tag srv_crv_para;
    int sp = sw_port_sp.sp_index;
	int max_frm_sz = 0;
	double sum_burst = 0.0;
	double sum_p = 0.0;
	srv_crv_para.R =0.0;
	srv_crv_para.T = 0.0;
	if (sp == 0)
	{
		/*max frame size*/
		max_frm_sz = cal_max_frame_size(sw_port_sp);
		srv_crv_para.R=output_port_speed;  
		srv_crv_para.T=max_frm_sz/srv_crv_para.R;           
	}
	else
	{
		/*max frame size*/
		max_frm_sz = cal_max_frame_size(sw_port_sp);
		/*calculate sum of burst*/
		sum_burst = cal_sum_burst(sw_port_sp);
		/*calculate sum of long-term rate p*/
		sum_p = cal_sum_p(sw_port_sp);
		/*whether the sum_burst and sum_p valid*/
		
		//max_frm_sz = cal_max_frame_size(sw_port_sp);
		srv_crv_para.R = output_port_speed-sum_p;                                          
		srv_crv_para.T = (max_frm_sz+sum_burst)/srv_crv_para.R;
		
	}
		
	return srv_crv_para;
}
/**********************************************************************
* FUNCTION NAME:
*   cal_max_frame_size
*
* DESCRIPTION:
*    calculate low priority max frame size
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     sw_port_sp--switch output port buffer_Tag
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
*   service curve parameter
*
* NOTES:
*
*********************************************************************/
int cal_max_frame_size(Sw_Port_SP_Tag sw_port_sp)//找比这个优先级大的
{
	int sp= 0;
	int vl_index = 0;
	int max_frm_sz = 0;
	//int network_index = 0;
	long vl = INVALID_VL;
	/*find max frame in switch low priority buffer_Tag*/
	if(sw_port_sp.sp_index+1<SP_COUNT)
	{
	   for(sp=sw_port_sp.sp_index+1;sp<SP_COUNT;sp++)
	    {
		  for (vl_index = 0; vl_index < MAX_PORT_VL_COUNT; vl_index++)
		   {
			vl= output_vl_arr[sw_port_sp.sw_index][sw_port_sp.port][sp][vl_index];
			/*is vl invalid*/
			if(vl == INVALID_VL)
			 {
				break;
			 }
			if (max_frm_sz < vl_para_arr[vl].max_pkt)
			 {
				max_frm_sz = vl_para_arr[vl].max_pkt;
			 }
		   }
	     }
     }
	return max_frm_sz;
}
/**********************************************************************
* FUNCTION NAME:
*   cal_sum_burst
*
* DESCRIPTION:
*    calculate sum of burst with high priority  
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     sw_port_sp--switch output port buffer_Tag
*     hop--which hop
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
*   if successfully executed return sum of burst else return 0.0
*
* NOTES:
*
*********************************************************************/
double cal_sum_burst(Sw_Port_SP_Tag sw_port_sp)
{
	long vl = INVALID_VL;
	int hop = 0;
	int sp_higher = 0;
	int vl_index = 0;
	double sum_burst = 0.0;
	int multi_index = 0;
	for(sp_higher=sw_port_sp.sp_index-1;sp_higher >= 0;sp_higher--)/*高优先级的A/B网的所有的vl遍历*/
	{
		Sw_Port_SP_Tag sw_pt_hg;/*构造高优先级buffer_Tag结构*/
		sw_pt_hg.port = sw_port_sp.port;
		sw_pt_hg.sw_index = sw_port_sp.sw_index;
		sw_pt_hg.sp_index = sp_higher;

		for (vl_index = 0; vl_index < MAX_PORT_VL_COUNT; vl_index++)
		{
			vl= output_vl_arr[sw_port_sp.sw_index][sw_port_sp.port][sp_higher][vl_index];
             if (vl == INVALID_VL)
             {
				 break;
             }
			/*which vl single path pass the switch*/ 
			multi_index = get_vl_multi_index(sw_pt_hg,vl);
			/*借助这个函数发现这个vl的哪个分路径通过这个buffer_Tag。任何时候，一个buffer_Tag只有一个分路径流*/
			if (multi_index != INVALID)
			{
				hop = get_hop(vl,multi_index,sw_port_sp.sw_index);   /*发现这个路径的哪一跳*/
                sum_burst += sg_arv_crv_arr[vl][multi_index][hop].burst;
			}
		}
	}
	return sum_burst;
}
/**********************************************************************
* FUNCTION NAME:
*   cal_sum_p
*
* DESCRIPTION:
*    calculate sum of long-term rate p of high priority  
*
* INTERFACE:
*   GLOBAL DATA:
*     None
*
*   INPUT:
*     sw_port_sp--switch output port buffer_Tag
*     hop--which hop
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
*   if successfully executed return sum of long-term rate p else return 0.0
*
* NOTES:
*
*********************************************************************/
double cal_sum_p(Sw_Port_SP_Tag sw_port_sp)
{
	long vl = INVALID_VL;
	int hop = 0;
	double sum_p = 0;
	int sp_higher = 0;
	int vl_index = 0;
	//int network_index = 0;
	int multi_index =0;
	/*traverse higher priority */
	for(sp_higher=sw_port_sp.sp_index-1;sp_higher >= 0;sp_higher--)
	{
		Sw_Port_SP_Tag sw_pt_hg;/*构造高优先级buffer_Tag结构*/
		sw_pt_hg.port = sw_port_sp.port;
		sw_pt_hg.sw_index = sw_port_sp.sw_index;
		sw_pt_hg.sp_index = sp_higher;
		//for (network_index = 0; network_index < TOTAL_NET_WORK ; network_index++)
		//{
			for (vl_index = 0; vl_index < MAX_PORT_VL_COUNT; vl_index++)
			{
				vl= output_vl_arr[sw_port_sp.sw_index][sw_port_sp.port][sp_higher][vl_index];
				if (vl == INVALID_VL)
				{
					break;
				}

				/*which vl single path pass the switch*/ 
				multi_index = get_vl_multi_index(sw_pt_hg,vl);
				if (multi_index != INVALID)
				{
				hop = get_hop(vl,multi_index,sw_port_sp.sw_index);
				sum_p += sg_arv_crv_arr[vl][multi_index][hop].arv_p;
				}
			}
		//}
		
	}
	return sum_p;
}
 int get_hop(long vl, int multi_index,int sw_index)
{
	int ret = -1;
	int nd_index = 0;
	VL_Path_Tag path = phy_path_arr[vl];
    for(nd_index=1; nd_index < PATH_ND_COUNT-1; nd_index++)
	{
		if (path.nd_arr[multi_index][nd_index].node_index==sw_index)
		{
			ret = nd_index-1;
			break;
		}
	}
	return ret;
}
