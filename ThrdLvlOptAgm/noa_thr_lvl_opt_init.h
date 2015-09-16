/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************

*********************************************************************/


#ifndef __NOA_THR_LVL_OPT_INIT_H__
#define __NOA_THR_LVL_OPT_INIT_H__

/*------------------------- FILE INCLUSION --------------------------*/

extern void init_noa_thr_lvl_opt();//
extern void initial_snat();
extern void initial_sw_number_net();
extern void initial_vl_path();//

extern void initial_vl_info();//

extern void initial_output_port_vl();//


extern void init_srv_crv_arr();//


extern void initial_group_arv_crv();


extern void init_sg_arv_crv();


extern void init_sw_rec_arr();

extern void init_vl_delay_arr();

extern void init_vl_max_num_1();
extern void init_edge_arr();
extern void init_MakeEmpty_buffer();

extern void init_ring_sw_port_sp();
extern void initial_frame_queue();
extern void initial_sw_net_two();
extern void initial_all_ring();
extern void init_sw_port_speed();
#endif /* __NOA_THR_LVL_OPT_INIT_H__*/