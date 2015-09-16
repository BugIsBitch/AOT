/*-------------------------- FILE PROLOGUE --------------------------*/

#ifndef __NOA_THR_LVL_OPT_CRT_ALG_H__
#define __NOA_THR_LVL_OPT_CRT_ALG_H__

#include "noa_thr_lvl_opt_types.h"
#include "noa_thr_lvl_opt_def.h"

extern void cal_group_arv_crv( Sw_Port_SP_Tag sw_port_sp, Buff_Sg_Path_Para_Tag all_buff_vl_para[TOTAL_VL_NUM]);


extern Flow_Para_Tag cal_link_para(int gp_vl_arr[GROUP_LINK_COUNT][VL_GROUP_COUNT],int link_index,
	                                                 int lnk_vl_cnt,Buff_Sg_Path_Para_Tag all_buff_vl_para[VL_GROUP_COUNT]);

extern void cal_grp_arv_para(Sw_Port_SP_Tag sw_port_sp,Flow_Para_Tag link_para_arr[]);


extern double cal_y(Flow_Para_Tag link_para_arr[],int link_para_count);

extern void bubble_sort(Flow_Para_Tag link_para_arr[],int arr_size);

extern void get_link_vl_count(Sw_Port_SP_Tag sw_port_sp,int gp_vl_arr[GROUP_LINK_COUNT][VL_GROUP_COUNT],
	                                        int vl_gp_count_arr[GROUP_LINK_COUNT],Buff_Sg_Path_Para_Tag all_buff_vl_para[TOTAL_VL_NUM]);


#endif /*__NOA_THR_LVL_OPT_CRT_ALG_H__*/