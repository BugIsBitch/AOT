/*-------------------------- FILE PROLOGUE --------------------------*/


/*------------------------- FILE INCLUSION --------------------------*/
#include "noa_thr_lvl_opt_types.h"

/*------------------------- MACRO DEFINITIONS -----------------------*/
/*------------------------- TYPE DECLARATIONS -----------------------*/
/*------------------------- VARIABLE DEFINITION ---------------------*/

VL_Path_Tag phy_path_arr[TOTAL_VL_NUM];//400M++ ���������¼���ǡ�ĳ�������µ�VL��·����Ϣ
VL_Para_Tag vl_para_arr[TOTAL_VL_NUM];// 2M
int sw_port_speed[SW_COUNT][SW_PORT_COUNT];
//*all vl of switch output port buffer_Tag*/
long output_vl_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT][MAX_PORT_VL_COUNT];
//12.5M ����ǵ����Ľ���������������˿�ͨ����VL������һ�����գ��ڽ���������ǰ�Ḵ�ƶ����ͬһ��VL������һ���������Ĳ�ͬoutput�г���

Srv_Crv_Para_Tag srv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];//1M

/*arrive curve in group technology */
Grp_Arv_Crv_Para_Tag grp_arv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];//1M

/*arrive curve of single vl*/
Arv_Crv_Para_Tag sg_arv_crv_arr[TOTAL_VL_NUM][MAX_MULTI_PATH][HOP];//684M ...[0]Ϊ�����һ���������ĵ�������

/*all switch output buffer_Tag worst delay and queue depth*/
Rec_Info_Tag sw_rec_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];//1M �ӳ����ֽ�Ϊ��λ

/*all vl delay*/
VL_Delay_Tag vl_delay_arr[TOTAL_VL_NUM][TOTAL_NET_WORK];//304M �����A/B��������Ҫ���飡��
/*all switch output buffer_Tag queue depth*/       
int all_sw_buf_queue_dep_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];//1M ����֡Ϊ��λ�����ݻ�ѹ,�浥��8����������

int sw_network_two[SW_COUNT][2];  // ��һ�д�ý����������ĸ������ڶ�����ý������������е�˳��id.

int sw_number_net[TOTAL_NET_WORK];//A/B�����м���������
Buf_Nd_Tag* graph[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//0.32M����ͼ(����������ȼ����Ƶ�ͼ�����ͼ��8��)���ڽ�����
Edge_Tag edge_arr[TOTAL_NET_WORK][SP_COUNT][EDGE_NUM];//0.131M��ߵġ�������ʱ��Ϊ1400(ͬ���磬ͬ���ȼ����������������һ��)
int topsort_buf_id_arr[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//1M����buffer_Tag�ļ���˳��
Sw_Port_SP_Tag ring_sw_port_sp[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//1M�����ÿ��buffer_Tag��������Ϣ,�����ĸ����������ĸ�output@@�ӿ�ӳ��


//int *edge_index[TOTAL_NET_WORK][SP_COUNT][EDGE_NUM][MAX_PORT_VL_COUNT];
/* ---------------------- FUNCTION DECLARATIONS ---------------------*/
//����A/B(0��1)��25���ӿڱ�ţ�0��24����4�����ȼ���0��3����HOP��0,1,2,(3).�����ڼ�������������hop=0�������ߵ�����ǵ�1������������3���������ߵ����������նˣ��Ľӿ�ӳ������Ȼ��


//��������ţ�VL��ź�TPA��Ҫ�����ӿ�ӳ��