/*-------------------------- FILE PROLOGUE --------------------------*/


#ifndef __NOA_THR_LVL_OPT_TYPES_H__
#define __NOA_THR_LVL_OPT_TYPES_H__

/*------------------------- FILE INCLUSION --------------------------*/
#include "noa_thr_lvl_opt_def.h"
/* ----------------------- MACRO DEFINITIONS ------------------------*/

/* ----------------------- TYPE DECLARATIONS ------------------------*/


/*********************************************************************/
/*  Definitions for VL node and associate port structure.            */
/*********************************************************************/
typedef struct Phy_Node   
{
	unsigned char node_index;//��ʱ����Ϊ���������ն˵�id���ն˵Ľ��idΪ����es_sw_name_arr[SW_COUNT+MAX_ES_CNT][100]�е�index
	unsigned char input_port_id;  //˵��:���ﶼ����id,������index
	unsigned char output_port_id;

}Phy_Node_Tag;

/*********************************************************************/
/*  Definitions for VL path structure.                           */
/*********************************************************************/
typedef struct VL_Path//ֻ��¼Ҫ����ġ�������
{
	short int multi_num;/*VL��·���Ķ��٣�=�ж��ٽ���ES,������A/B������*/
	short int path_nd_count[MAX_MULTI_PATH];/*��¼������·���м�����0��X��3������0��ʾ�÷�·��û��VLPATH���ȼ�û��SW��ͨ����������*/
	Phy_Node_Tag nd_arr[MAX_MULTI_PATH][PATH_ND_COUNT];/*switch and end system total numbers of path*/
}VL_Path_Tag;


/*********************************************************************/
/*  Definitions for the parameters of a VL structure.                           */
/*********************************************************************/
typedef struct VL_Para
{   
	double vl_tpa;/*TPA value of current VL*/
    short min_pkt;/*maximum number of packet*/
    short max_pkt;/*minimum number of packet*/
    double bag; /* BAG value*/
    short sp;  /* priority*/
    short vlid;  
    double max_burst;
}VL_Para_Tag;

/*********************************************************************/
/*  Definitions for link parameter in grouping technique structure.                           */
/*********************************************************************/
typedef struct Flow_Para
{
	double max_burst;/*the maximum burst of a VL on the link*/
	double sum_p_link;     /*the sum p of all VLs on the link*/
	double inflection_point_e;/*the inflection point of the arrival curve with grouping technique*/
}Flow_Para_Tag;

/*********************************************************************/
/*  Definitions for service curve parameter data structure.                           */
/*********************************************************************/
typedef struct Srv_Crv_Para
{
	double R;/*rate*/

	double T;/*wait delay*/

}Srv_Crv_Para_Tag;

/*********************************************************************/
/*  Definitions for switch output port data structure.                           */
/*********************************************************************/

typedef struct Arv_Crv_Para
{   
	short edge_index;/*�ߵ�����*/

    double arv_p;/*the p of the arrive curve*/

    double burst;/*the burst of the arrive curve*/

}Arv_Crv_Para_Tag;
/*********************************************************************/
/*  Definitions for group arrive curve data structure.                           */
/*********************************************************************/
typedef struct Grp_Arv_Crv_Para
{
	double en;/*maximum x value of inflection point*/

	double y;/*maximum y value of inflection point*/
}Grp_Arv_Crv_Para_Tag;

/*********************************************************************/
/*  Definitions for node results record data structure.                           */
/*********************************************************************/
typedef struct Rec_Info
{
	double worst_delay;/*worst delay of switch output buffer_Tag*/

	int queue_depth;/*queue depth of switch output buffer_Tag*/    //�����Ǵ����ֽ�Ϊ��λ�����ݻ�ѹ��������ʵû���ϡ�

}Rec_Info_Tag;

/*********************************************************************/
/*  Definitions for vl best delay and worst delay                          */
/*********************************************************************/
typedef struct Sg_VL_Delay
{

	double sg_pth_wrt_dl;/*worst delay of single path*/

	double sg_pth_bst_dl;/*best delay of single path*/

}Sg_VL_Delay_Tag;

/*********************************************************************/
/*  Definitions for VL delay                          */
/*********************************************************************/
typedef struct VL_Delay
{
	Sg_VL_Delay_Tag path_delay_arr[MAX_MULTI_PATH];/*vl delay array*/

	int mult_path_num;/*the number of single path in a VL*/

}VL_Delay_Tag;

typedef struct Buff_Sg_Path_Para
{
	int hop_index;/*VL��������һ��*/

	int vl_multi_index;/*VL����������·��*/
}Buff_Sg_Path_Para_Tag;

typedef struct Buf_Nd
{
	short buf_id;/*�洢Buffer�ı�ţ����ڽ�������ÿ��buffer���б��*/

	struct Buf_Nd *next;

}Buf_Nd_Tag;

typedef struct Edge
{   
	int head;              //�ߵ�ͷ���
	int tail;                    //�ߵ�β���.
}Edge_Tag;

/*********************************************************************/
/*  Definitions for switch output buffer_Tag data structure.                           */
/*********************************************************************/
typedef struct Sw_Port_SP
{
	int sw_index;/*switch index*/
	int sp_index;/*priority index*/ //��Ϊ0��1
	int port;/*switch output port*/
}Sw_Port_SP_Tag;

#endif /* __NOA_THR_LVL_OPT_TYPES_H__*/