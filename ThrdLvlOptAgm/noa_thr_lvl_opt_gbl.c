/*-------------------------- FILE PROLOGUE --------------------------*/


/*------------------------- FILE INCLUSION --------------------------*/
#include "noa_thr_lvl_opt_types.h"

/*------------------------- MACRO DEFINITIONS -----------------------*/
/*------------------------- TYPE DECLARATIONS -----------------------*/
/*------------------------- VARIABLE DEFINITION ---------------------*/

VL_Path_Tag phy_path_arr[TOTAL_VL_NUM];//400M++ 这是数组记录的是“某个网”下的VL的路径信息
VL_Para_Tag vl_para_arr[TOTAL_VL_NUM];// 2M
int sw_port_speed[SW_COUNT][SW_PORT_COUNT];
//*all vl of switch output port buffer_Tag*/
long output_vl_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT][MAX_PORT_VL_COUNT];
//12.5M 存的是单网的交换机的所有输出端口通过的VL；由于一发多收，在交换机发送前会复制多个，同一个VL可能在一个交换机的不同output中出现

Srv_Crv_Para_Tag srv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];//1M

/*arrive curve in group technology */
Grp_Arv_Crv_Para_Tag grp_arv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];//1M

/*arrive curve of single vl*/
Arv_Crv_Para_Tag sg_arv_crv_arr[TOTAL_VL_NUM][MAX_MULTI_PATH][HOP];//684M ...[0]为到达第一个交换机的到达曲线

/*all switch output buffer_Tag worst delay and queue depth*/
Rec_Info_Tag sw_rec_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];//1M 队长以字节为单位

/*all vl delay*/
VL_Delay_Tag vl_delay_arr[TOTAL_VL_NUM][TOTAL_NET_WORK];//304M 这个有A/B网，还需要检验！！
/*all switch output buffer_Tag queue depth*/       
int all_sw_buf_queue_dep_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];//1M 存以帧为单位的数据积压,存单网8个交换机的

int sw_network_two[SW_COUNT][2];  // 第一列存该交换机属于哪个网，第二个存该交换机在其网中的顺序id.

int sw_number_net[TOTAL_NET_WORK];//A/B网各有几个交换机
Buf_Nd_Tag* graph[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//0.32M有向图(被网络和优先级限制的图，这个图有8张)的邻接链表
Edge_Tag edge_arr[TOTAL_NET_WORK][SP_COUNT][EDGE_NUM];//0.131M存边的。这里暂时设为1400(同网络，同优先级，两个结点间最多有一条)
int topsort_buf_id_arr[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//1M各个buffer_Tag的计算顺序
Sw_Port_SP_Tag ring_sw_port_sp[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//1M存的是每个buffer_Tag的所属信息,属于哪个交换机的哪个output@@接口映射


//int *edge_index[TOTAL_NET_WORK][SP_COUNT][EDGE_NUM][MAX_PORT_VL_COUNT];
/* ---------------------- FUNCTION DECLARATIONS ---------------------*/
//网络A/B(0和1)，25个接口编号（0到24），4个优先级（0到3），HOP（0,1,2,(3).经过第几个交换机，第hop=0到达曲线到达的是第1个交换机，第3个到达曲线到达的是最后终端）的接口映射是天然的


//交换机编号，VL编号和TPA需要建立接口映射