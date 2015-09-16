/*-------------------------- FILE PROLOGUE --------------------------*/




#ifndef __NOA_THR_LVL_OPT_BSC_ALG_H__
#define __NOA_THR_LVL_OPT_BSC_ALG_H__
#include "noa_thr_lvl_opt_types.h"

extern void bgn_thr_lvl_opt(int network,int priority,int vl_count);

extern void fst_hop_vl_arv_crv(int priority,int vl_count);

extern void cal_arv_crv(int vl_index,int multi_index);

extern void cal_port_out_vl_arv_crv(Sw_Port_SP_Tag buff_sw_port_sp,Buff_Sg_Path_Para_Tag all_buff_vl_para[TOTAL_VL_NUM],int network);

extern Srv_Crv_Para_Tag  cal_service_crv(Sw_Port_SP_Tag sw_port_sp,double sw_port_speed_C);

extern int cal_max_frame_size(Sw_Port_SP_Tag sw_port_sp);
/**********************************************************************

*********************************************************************/
extern double cal_sum_burst(Sw_Port_SP_Tag sw_port_sp);
/**********************************************************************

*
*********************************************************************/
extern double cal_sum_p(Sw_Port_SP_Tag sw_port_sp);

extern int get_hop(long vl, int multi_index,int sw_index);

#endif/*__NOA_THR_LVL_OPT_BSC_ALG_H__*/