/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************

*********************************************************************/


/*------------------------- FILE INCLUSION --------------------------*/
#include "snat_types.h"
#include "snat_def.h"
#include "snat_util.h"
#include "compute_delay.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/
/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DEFINITION --------------------*/
/*vl path array of network A and network B*/
extern VL_Path_Tag vl_path_arr[TOTAL_VL_NUM];
/*all switch output buffer_Tag worst delay and queue depth*/
extern Rec_Info_Tag sw_rec_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];
/*service curve*/
extern Service_Curve_Para_Tag all_srv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];

/*arrive curve in group technology */
extern Group_Arv_Crv_Para_Tag all_group_arv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];//
/*all vl delay*/
extern VL_Delay_Tag vl_delay_arr[TOTAL_VL_NUM][TOTAL_NET_WORK];//

extern VL_Parameter_Tag vl_para_arr[TOTAL_VL_NUM];//
extern long vl_max_num_1;
//补 就算每条VL的最大突发度
Arrive_Curve_Para_Tag all_sg_arrive_curve_arr[TOTAL_VL_NUM][MAX_MULTI_PATH][HOP];
/* ---------------------- FUNCTION DECLARATIONS ---------------------*/

void  cal_vl_max_burst()
{
	long vl_index = 0;
	for (vl_index = 0 ; vl_index <vl_max_num_1;  vl_index++)
	{
		int nd_index = 0;
		int multi_index = 0;
		/*get vl path info*/
		VL_Path_Tag path =  vl_path_arr[vl_index];
		double vl_max_burst=0.0;
		double array_max_burst=vl_para_arr[vl_index].max_burst;
		/*calculate the worst-case delay of vl*/
		for(multi_index = 0 ; multi_index < path.multi_num;multi_index++)//如果分路径数为0，就直接跳过了
		{   
		    int vlpath_hop=path.path_nd_count[multi_index];
			double vlpath_max_burst=all_sg_arrive_curve_arr[vl_index][multi_index][vlpath_hop-1].burst;
			if (vlpath_max_burst>vl_max_burst)
			{
				vl_max_burst=vlpath_max_burst;
			}
		}
		if (vl_max_burst>array_max_burst)
		{
           vl_para_arr[vl_index].max_burst=vl_max_burst;
		}
	}	
}
void  cal_vl_delay(int network)
{
	long vl_index = 0;
	for (vl_index = 0 ; vl_index <vl_max_num_1;  vl_index++)
	{
		int nd_index = 0;
		int multi_index = 0;
		/*get vl path info*/
		VL_Path_Tag path =  vl_path_arr[vl_index];
		/*calculate the worst-case delay of vl*/
		for(multi_index = 0 ; multi_index < path.multi_num;multi_index++)
		{   
			if (path.path_nd_count[multi_index]!=0)//这条是多余的，确定有分路径后，每条分路径不可能是0跳
			{  
				double sg_vl_worst_delay = 0.0;
				double sg_vl_best_delay = 0.0;
				sg_vl_worst_delay = 0.0;
				sg_vl_best_delay = 0.0;
				for(nd_index = 1; nd_index < path.path_nd_count[multi_index]+1; nd_index++)
				{
					Sw_Port_SP_Tag sw_port_sp;
					double sw_delay = 0.0;
					/*get the vl parameter info*/
					VL_Parameter_Tag para = vl_para_arr[vl_index];
					//if (path.nd_arr[multi_index][nd_index].node_id== INVALID_NODE)
					//{
					//	break;
					//}
					sw_port_sp.port = path.nd_arr[multi_index][nd_index].output_port_id;
					/*sp index*/
					sw_port_sp.sp_index  = para.sp;
					/*get switch index according to its identifier*/
					sw_port_sp.sw_index = path.nd_arr[multi_index][nd_index].node_id;
					/*get the worst-case delay of switch output port*/
					sw_delay = sw_rec_arr[sw_port_sp.sw_index][sw_port_sp.port][sw_port_sp.sp_index].worst_delay;
					/*calculate the worst-case delay of vl*/			   
					sg_vl_worst_delay += sw_delay;
					/*technical delay*/
					sg_vl_worst_delay += L_TECH;
					/*calculate the best delay of vl*/
					sg_vl_best_delay += L_TECH;
				}
				vl_delay_arr[vl_index][network].vlpath_delay_arr[multi_index].vl_worst_delay= sg_vl_worst_delay;
				vl_delay_arr[vl_index][network].vlpath_delay_arr[multi_index].vl_best_delay = sg_vl_best_delay;

			}
			
		}
	}	
}

