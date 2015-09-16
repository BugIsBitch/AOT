/*-------------------------- FILE PROLOGUE --------------------------*/
/*********************************************************************/


/*------------------------- FILE INCLUSION --------------------------*/
#include "noa_thr_lvl_opt_types.h"
#include "noa_thr_lvl_opt_def.h"
#include "noa_thr_lvl_opt_init.h"
#include "noa_thr_lvl_opt_util.h"
#include <string.h>
#include <stdio.h>
/*------------------------- MACRO DEFINITIONS -----------------------*/
/*------------------------- TYPE DECLARATIONS -----------------------*/
/*------------------------- VARIABLE DEFINITION ---------------------*/
/*vl path array of network A and B*/
extern VL_Path_Tag phy_path_arr[TOTAL_VL_NUM];


/*vl parameter array of network A*/
extern VL_Para_Tag vl_para_arr[TOTAL_VL_NUM];

extern long output_vl_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT][MAX_PORT_VL_COUNT];

extern Srv_Crv_Para_Tag srv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];

extern Grp_Arv_Crv_Para_Tag grp_arv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];

extern Arv_Crv_Para_Tag sg_arv_crv_arr[TOTAL_VL_NUM][MAX_MULTI_PATH][HOP];

extern Rec_Info_Tag sw_rec_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];

/*all vl delay*/
extern VL_Delay_Tag vl_delay_arr[TOTAL_VL_NUM][TOTAL_NET_WORK];
extern int sw_port_speed[SW_COUNT][SW_PORT_COUNT];
//下面两个为后来加上来的

extern Buf_Nd_Tag *Graph[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];///这个数组的初始化不放在这个地方。有向图(被网络和优先级限制的图，这个图有8张)的邻接链表
extern Edge_Tag edge_arr[TOTAL_NET_WORK][SP_COUNT][EDGE_NUM];//存边的。这里暂时设为1400(同网络，同优先级，两个结点间最多有一条)
extern int topsort_buf_id_arr[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//各个buffer_Tag的计算顺序
extern Sw_Port_SP_Tag ring_sw_port_sp[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//存的是每个buffer_Tag的所属信息,属于哪个交换机的哪个output@@接口映射
extern int all_sw_buf_queue_dep_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];
extern int sw_network_two[SW_COUNT][2]; 
extern int sw_number_net[TOTAL_NET_WORK];
void init_noa_thr_lvl_opt()//初始化一次的
{  
	initial_vl_info();
	init_vl_delay_arr();
	init_edge_arr();
	init_MakeEmpty_buffer();
	init_ring_sw_port_sp();
	initial_sw_net_two();
	init_sw_port_speed();
	initial_sw_number_net();	
}
void initial_snat()  //初始化两次的
{
	initial_vl_path();
	initial_output_port_vl();
	init_srv_crv_arr();
	initial_group_arv_crv();
	init_sg_arv_crv(); 
	init_sw_rec_arr();
	initial_frame_queue();
}



/* ---------------------- FUNCTION DECLARATIONS ---------------------*/

void initial_sw_number_net()
{    
	//int i=0;
	//for (i=0;i<TOTAL_NET_WORK;i++)
	//{
	//	sw_number_net[i]=0;
	//}
}
void initial_vl_path()
{
	long  i = 0;
	int j = 0;
	int k = 0;

	/*initial vl path array*/
	for (i = 0 ; i < TOTAL_VL_NUM; i++)
	{	
		VL_Path_Tag *path = &(phy_path_arr[i]);
		path->multi_num = 0;
		for (j = 0 ; j < MAX_MULTI_PATH; j++)
		{  
			path->path_nd_count[j]=0;
			for (k = 0 ; k < PATH_ND_COUNT; k++)
			{
				path->nd_arr[j][k].input_port_id = INVALID_PORT;
				path->nd_arr[j][k].node_index = INVALID_NODE;
				path->nd_arr[j][k].output_port_id = INVALID_PORT;
			}
		}
	}
}

/**********************************************************************
* FUNCTION NAME:
*   initial_vl_info
*
* DESCRIPTION:
*    initial vl info data structure
*
* INTERFACE:
*   GLOBAL DATA:
*     vl_para_arr_a-vl parameter array of network A
*     vl_para_arr_b-vl parameter array of network B
*   INPUT:
*     None
*
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
*   None
*
* NOTES:
*
*********************************************************************/
void initial_vl_info()
{
	long index = 0;
	/*initial the vl parameter info of network A*/
	for (index = 0; index < TOTAL_VL_NUM; index++)
	{
		VL_Para_Tag *p_para = &(vl_para_arr[index]);
		p_para->bag = 0;
		p_para->sp = INVALID_SP;
		p_para->max_pkt = 0;
		p_para->min_pkt = 0;
		p_para->vlid = -1;
		//strcpy(p_para->vlid,"-1");
		p_para->vl_tpa=0.0;
		p_para->max_burst=0.0;
	}
}
/**********************************************************************
* FUNCTION NAME:
*   initial_output_port_vl
*
* DESCRIPTION:
*    initial switch output buffer_Tag vl info
*
* INTERFACE:
*   GLOBAL DATA:
*     output_vl_arr-all vls of switch output port
*
*   INPUT:
*     None
*
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
*   None
*
* NOTES:
*
*********************************************************************/
void initial_output_port_vl()
{
	int sw_index = 0;
	int sw_port_index = 0;
	int sp_index = 0;
	int vl_index = 0;
	/*initial all switch output buffer_Tag vl info*/
	for (sw_index = 0; sw_index < SW_COUNT_NET ; sw_index++)
	{
		for (sw_port_index = 0 ; sw_port_index < SW_PORT_COUNT; sw_port_index++)
		{
			for (sp_index = 0 ; sp_index < SP_COUNT; sp_index++)
			{
				for (vl_index = 0; vl_index < MAX_PORT_VL_COUNT; vl_index++)
				{
					output_vl_arr[sw_index][sw_port_index][sp_index][vl_index] = INVALID_VL;
				}

			}
		}
	}

}
/**********************************************************************
* FUNCTION NAME:
*   init_srv_crv_arr
*
* DESCRIPTION:
*    initial the switch output port buffer_Tag service curve data structure
*
* INTERFACE:
*   GLOBAL DATA:
*     srv_crv_arr-service curve array
*
*   INPUT:
*     None
*
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
*   None
*
* NOTES:
*
*********************************************************************/
void init_srv_crv_arr()
{
	int i = 0 ;
	int j = 0 ;
	int k = 0;
	/*initial all switch output buffer_Tag*/
	for (i = 0 ; i < SW_COUNT_NET ; i++)
	{
		for (j = 0 ; j < SW_PORT_COUNT; j++)
		{
			for (k = 0 ; k < SP_COUNT ; k++)
			{
				Srv_Crv_Para_Tag *service_curve = &(srv_crv_arr[i][j][k]);
				service_curve->R = 0.0;
				service_curve->T = 0.0;
			}
		}
	}
}

/**********************************************************************
* FUNCTION NAME:
*   initial_group_arv_crv
*
* DESCRIPTION:
*    initial the switch output port buffer_Tag arrive curve in grouping technology
*
* INTERFACE:
*   GLOBAL DATA:
*     grp_arv_crv_arr-aggregation arrive curve array
*
*   INPUT:
*     None
*
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
*   None
*
* NOTES:
*
*********************************************************************/
void initial_group_arv_crv()
{
	int i = 0;
	int j = 0;
	int k = 0;
	/*initial arrive curve data in group technology*/
	for (i = 0; i < SW_COUNT_NET; i++)
	{
		for (j = 0 ; j < SW_PORT_COUNT; j++)
		{
			for (k = 0 ; k < SP_COUNT ; k++)
			{
				grp_arv_crv_arr[i][j][k].en = 0.0;
				grp_arv_crv_arr[i][j][k].y = 0.0;
			}
		}
	}
}
/**********************************************************************
* FUNCTION NAME:
*   init_sg_arv_crv
*
* DESCRIPTION:
*    initial the single vl arrive curve data
*
* INTERFACE:
*   GLOBAL DATA:
*     sg_arv_crv_arr-vl arrive curve array
*
*   INPUT:
*     None
*
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
*   None
*
* NOTES:
*
*********************************************************************/
void init_sg_arv_crv()
{
	long vl_index = 0 ;
	int multi_index = 0;
	int hop_index = 0;
	/*initial vl arrive curve data*/
	for (vl_index = 0 ; vl_index < TOTAL_VL_NUM ; vl_index++)
	{
		for (multi_index = 0 ; multi_index < MAX_MULTI_PATH;multi_index++)
		{
			for (hop_index = 0 ; hop_index < HOP ; hop_index++)
			{
				sg_arv_crv_arr[vl_index][multi_index][hop_index].burst = 0.0;
				sg_arv_crv_arr[vl_index][multi_index][hop_index].edge_index = INVALID;//悬空
				sg_arv_crv_arr[vl_index][multi_index][hop_index].arv_p=0.0;
			}
		}
	}
}
/**********************************************************************
* FUNCTION NAME:
*   init_sw_rec_arr
*
* DESCRIPTION:
*    initial switch record array data
*
* INTERFACE:
*   GLOBAL DATA:
*     sw_rec_arr-switch record array
*
*   INPUT:
*     None
*
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
*   None
*
* NOTES:
*
*********************************************************************/
void init_sw_rec_arr()
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0 ; i < SW_COUNT_NET ; i++)
	{
		for (j = 0 ; j < SW_PORT_COUNT; j++)
		{
			for (k = 0 ; k < SP_COUNT; k++)
			{
				Rec_Info_Tag *rec = &(sw_rec_arr[i][j][k]);
				rec->queue_depth = 0;
				rec->worst_delay = 0.0;
			}
		}
	}
}

void init_vl_delay_arr()
{
	long i=0;
	int j=0;
	int k=0;
	for (i = 0 ; i < TOTAL_VL_NUM ; i++)
	{      
		for (j=0;j<TOTAL_NET_WORK;j++)
		{

			VL_Delay_Tag *vl_delay= &(vl_delay_arr[i][j]);
			for (k=0;k<MAX_MULTI_PATH;k++)
			{
				vl_delay->path_delay_arr[k].sg_pth_bst_dl = 0.0;
				vl_delay->path_delay_arr[k].sg_pth_wrt_dl= 0.0;
			}	
		}
	}
}





void init_edge_arr()
{
	long i=0;
	int j=0;
	int k=0;
	for (i=0;i<TOTAL_NET_WORK;i++)
	{
		for (j=0;j<SP_COUNT;j++)
		{
			for (k=0;k<EDGE_NUM;k++)
			{
				Edge_Tag* edg=&edge_arr[i][j][k];
				edg->head=INVALID;
				edg->tail=INVALID;
			}
		}
	}
}
void init_MakeEmpty_buffer()
{
	long i=0;
	int j=0;
	int k=0;
	for (i=0;i<TOTAL_NET_WORK;i++)
	{
		for (j=0;j<SP_COUNT;j++)
		{
			for (k=0;k<BUFFER_NUM;k++)
			{
				topsort_buf_id_arr[i][j][k] =INVALID;
			}
		}
	}           
}
//void init_ring_sw_port_sp()
//{
//	long i=0;
//	int j=0;
//	int k=0;
//	for (i=0;i<TOTAL_NET_WORK;i++)
//	{
//		for (j=0;j<SP_COUNT;j++)
//		{
//			for (k=0;k<BUFFER_NUM;k++)
//			{
//				Sw_Port_SP_Tag* sw_po_sp_tag=&ring_sw_port_sp[i][j][k];
//				sw_po_sp_tag->port=INVALID_PORT;
//				sw_po_sp_tag->sp_index=INVALID_SP;
//				sw_po_sp_tag->sw_index=INVALID_NODE;
//			}
//		}
//	}           
//}
void init_ring_sw_port_sp()//自然的一一映射
{   
	int network=0;
	int i=0;
    int j=0;
	for (network=0;network<TOTAL_NET_WORK;network++)
	{
		for (i=0;i<SP_COUNT;i++)
		{
			for (j=0;j<BUFFER_NUM;j++)
			{   
			int n=INVALID;
			Sw_Port_SP_Tag *sw_port_para=&(ring_sw_port_sp[network][i][j]);
			n=j/SW_PORT_COUNT;
			sw_port_para->port=j-n*SW_PORT_COUNT;
			sw_port_para->sp_index=i;
			sw_port_para->sw_index=n;
			}
		}
	}	
}

void initial_frame_queue()
{
	int i,j,k=0;
	for (i=0;i<SW_COUNT_NET;i++)
	{
		for (j=0;j<SW_PORT_COUNT;j++)
		{
			for (k=0;k<SP_COUNT;k++)
			{
				all_sw_buf_queue_dep_arr[i][j][k]=0;
			}
		}
	}
}
void initial_sw_net_two()
{
	int i=0;
	int j=0;
	for (i=0;i<SW_COUNT;i++)
	{
     sw_network_two[i][0]=-1;
	 sw_network_two[i][1]=-1;
	}
}

void init_sw_port_speed()
{
	int i=0;
	int j=0;
	for (i=0;i<SW_COUNT;i++)
	{
		for (j=0;j<SW_PORT_COUNT;j++)
		{
			sw_port_speed[i][j]=0;
		}
	}
}