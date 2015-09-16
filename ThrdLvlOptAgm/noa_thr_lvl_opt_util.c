/*-------------------------- FILE PROLOGUE --------------------------*/


/*------------------------- FILE INCLUSION --------------------------*/
#include "noa_thr_lvl_opt_types.h"
#include "noa_thr_lvl_opt_def.h"
#include "noa_thr_lvl_opt_util.h"

/*------------------------- MACRO DEFINITIONS -----------------------*/
/*------------------------- TYPE DECLARATIONS -----------------------*/
/*------------------------- VARIABLE DEFINITION ---------------------*/

/*vl path array of network A and network B*/
extern VL_Path_Tag phy_path_arr[TOTAL_VL_NUM];

/*vl parameter array of network A and B*/
extern VL_Para_Tag vl_para_arr[TOTAL_VL_NUM];
/* ---------------------- FUNCTION DECLARATIONS ---------------------*/


int get_vl_multi_index(Sw_Port_SP_Tag sw_port_sp,int vl)/*加上A/B网的信息是有意义的，一是：提高计算速度。
																		   二是：由于我们把A/B网做在一起，虽然我们这个项目里，这个函数的返回值只有一个
																		   ，但是从代码的通用性上来说，
																		   可能有多个值，这里加上网络信息，就保证既有一个值，又有通用性*/
{
	int ret = INVALID;
	int multi_index =0;
	int nd_index =0;
	VL_Path_Tag path = phy_path_arr[vl];/*找个这个VL在AorB网中的路径信息*/
	for (multi_index = 0 ; multi_index < path.multi_num ; multi_index++)
	{
		for (nd_index = 1; nd_index < (PATH_ND_COUNT- 1); nd_index++)/*我对参数做了修改*/
		{
			/*get node*/
			Phy_Node_Tag nd_asst_pt;
			/*get parameter info of vl*/
			VL_Para_Tag para = vl_para_arr[vl];
			nd_asst_pt = path.nd_arr[multi_index][nd_index];      /*把数据取出来*/
			if ((nd_asst_pt.node_index == sw_port_sp.sw_index) && 
				(nd_asst_pt.output_port_id == sw_port_sp.port )&&
				(para.sp == (sw_port_sp.sp_index+1)))          /*依次比较*/
			{
				ret = multi_index;/*这里找到的其实是一发多收VL的第一条经过这个buffer_Tag的路径，但是对我们来说，这就足够了，
									因为在他们没有分开前本身就是一个流，在分开前复制的。而且不会有分开后来又路线重合的境况。
									基于以上情况，所以我们对一个VL，ret只有一个返回值*/
				break;
			}
		}
		if (ret != INVALID)      
		{
			break;
		}
	}
	return ret;//最好再加个提醒：返回INVALID_INDEX
}