#ifndef __NOA_THR_LVL_IO_H__
#define __NOA_THR_LVL_IO_H__


#include "noa_thr_lvl_opt_types.h"


extern VL_Path_Tag* get_vl_path_arr(long i);
extern void set_vl_path_arr(long i,VL_Path_Tag path);
extern VL_Para_Tag get_vl_para_arr(long i);
extern void set_vl_para_arr(long i,VL_Para_Tag parame);
extern void set_vl_para_tpa(long i,double tpa_ac);
extern long get_vl_para_id (long i);
extern long get_output_vl_arr(int i,int j,int k,int l);
extern void set_output_vl_arr(int i,int j,int k,int l,long vl);
extern Sg_VL_Delay_Tag get_vl_delay(long i,int j,int k);
extern void set_vl_delay(long i,int j,VL_Delay_Tag delay_1);
extern int get_all_sw_buf_queue_dep_arr(int i,int j,int k);
extern void set_all_sw_buf_queue_dep_arr(int i,int j,int k,int queue_1);
extern Rec_Info_Tag *get_sw_rec_arr(int i,int j,int k);
extern void set_sw_rec_arr(int i,int j,int k,Rec_Info_Tag rec_1);
extern void set_vl_max_num_1(long vl_max_num);
extern void set_sw_network_two(int i,int network);
extern void ag_set_sw_net_two();
extern void set_sw_port_speed(int sw_i,int port_i,int speed);
extern int get_sw_number_net(int network);
extern int get_set_sw_net_two(int i,int j);

extern int get_sw_ord_id(int sw_net, int sw_network_id);
extern int get_all_ring_num(int i) ;
extern int get_all_ring_edge_num(int i,int j);
extern int get_all_ring_loop(int i,int j,int k);
extern double get_vl_max_burst(long i);
extern double get_vl_tpa(long i);
#endif /* __NOA_THR_LVL_IO_H__*/