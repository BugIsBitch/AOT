/*-------------------------- FILE PROLOGUE --------------------------*/




/*------------------------- FILE INCLUSION --------------------------*/
#include "noa_thr_lvl_opt_types.h"
#include "noa_thr_lvl_opt_def.h"
#include "noa_thr_lvl_opt_util.h"
#include "noa_thr_lvl_opt_crt_alg.h"
/*------------------------- MACRO DEFINITIONS -----------------------*/
/*------------------------- TYPE DECLARATIONS -----------------------*/

/*------------------------- VARIABLE DEFINITION --------------------*/
/*vl path array of network A and network B*/
extern VL_Path_Tag phy_path_arr[TOTAL_VL_NUM];

/*arrive curve of single vl*/
extern Arv_Crv_Para_Tag sg_arv_crv_arr[TOTAL_VL_NUM][MAX_MULTI_PATH][HOP];//hop=3
/*all vl of switch output port buffer_Tag*/
extern long output_vl_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT][MAX_PORT_VL_COUNT];

/*arrive curve in group technology */
extern Grp_Arv_Crv_Para_Tag grp_arv_crv_arr[SW_COUNT_NET][SW_PORT_COUNT][SP_COUNT];

/*vl parameter array of network A and B*/
extern VL_Para_Tag vl_para_arr[TOTAL_VL_NUM];

extern Sw_Port_SP_Tag ring_sw_port_sp[TOTAL_NET_WORK][SP_COUNT][BUFFER_NUM];//存的是每个buffer_Tag的所属信息
//extern long vl_max_num_1;
/* ---------------------- FUNCTION DECLARATIONS ---------------------*/


void cal_group_arv_crv( Sw_Port_SP_Tag sw_port_sp, Buff_Sg_Path_Para_Tag all_buff_vl_para[TOTAL_VL_NUM])
{   
	int i,j,k,m=0;
	int link_index = 0;

    static int gp_vl_arr[GROUP_LINK_COUNT][VL_GROUP_COUNT];/*B:定义一个分link 的数组来分别存储这些VL*/
	int vl_gp_count_arr[GROUP_LINK_COUNT];                  /*C:主要是下面调用的函数用，用来存储每个link中VL的总数*/
	static Flow_Para_Tag link_para_arr[GROUP_LINK_COUNT];/*A用来存储计算好的单个link的信息*/
	for (i=0;i<GROUP_LINK_COUNT;i++)                         //初始化定义的三个数组
	{
		for (j=0;j<VL_GROUP_COUNT;j++)
		{
			gp_vl_arr[i][j]=INVALID_VL;
		}
	}
	for (k=0;k<GROUP_LINK_COUNT;k++)
	{
        vl_gp_count_arr[k]=0;
	}
	for (m=0;m<GROUP_LINK_COUNT;m++)
	{
		link_para_arr[m].inflection_point_e=0.0;
		link_para_arr[m].max_burst=0.0;
		link_para_arr[m].sum_p_link=0.0;
	}

	get_link_vl_count(sw_port_sp,gp_vl_arr,vl_gp_count_arr,all_buff_vl_para);/*这个函数对这个buffer_Tag要返回三个存好的数组*/
	for (link_index = 0; link_index <GROUP_LINK_COUNT ; link_index++)
	{   
		int lnk_vl_count=vl_gp_count_arr[link_index];
		link_para_arr[link_index] = cal_link_para(gp_vl_arr,link_index,lnk_vl_count,all_buff_vl_para);
	}
	/*compute arrival curve parameter with grouping technique*/
	cal_grp_arv_para(sw_port_sp,link_para_arr);

 }



Flow_Para_Tag cal_link_para(int gp_vl_arr[GROUP_LINK_COUNT][VL_GROUP_COUNT],int link_index,
									                        int lnk_vl_cnt,Buff_Sg_Path_Para_Tag all_buff_vl_para[VL_GROUP_COUNT])
{
	Flow_Para_Tag link_para;
	double sum_burst = 0.0;
	int i=0;
	//int network_index = 0;
	link_para.inflection_point_e = 0.0;
	link_para.max_burst = 0.0;
	link_para.sum_p_link = 0.0;

	for (i = 0 ; i < lnk_vl_cnt; i++)
	{   //int vl_network;
        int vl_multi_index;
        int hop;
		Arv_Crv_Para_Tag arv_crv_para;
		long vl ;
		double burst_min=0.0;
		vl= gp_vl_arr[link_index][i];

		//vl_network=all_buff_vl_para[vl].vl_network_index;
		vl_multi_index =all_buff_vl_para[vl].vl_multi_index;
		hop = all_buff_vl_para[vl].hop_index;//这里的hop其实为这个vl进过了其路径上第hop个交换机的出口
		/*get the vl arrival curve parameter*/
		arv_crv_para = sg_arv_crv_arr[vl][vl_multi_index][hop-1];
		burst_min=MIN(vl_para_arr[vl].vl_tpa,arv_crv_para.burst);  //我们在算输入曲线的时候，要把进来的到达曲线跟TPA的突发度进行比较，取小的那个。
		//arv_crv_para要是没有效值的话，应该报个错
		if (link_para.max_burst < burst_min)
		{
			link_para.max_burst = burst_min;
		}
		/*compute sum burst and sum p*/
		sum_burst += arv_crv_para.burst;
		link_para.sum_p_link += arv_crv_para.arv_p;
	}
	/*compute en*/
	link_para.inflection_point_e =(sum_burst - link_para.max_burst )/(C - link_para.sum_p_link);

	return link_para;
}

void cal_grp_arv_para(Sw_Port_SP_Tag sw_port_sp,Flow_Para_Tag link_para_arr[])
{

	int j = 0;
	int i = 0;
	int k = 0;
	double sum_max_burst=0.0;
	Flow_Para_Tag link_para_arr_1[MAX_PORT_VL_COUNT];
	Grp_Arv_Crv_Para_Tag *p_gp_arv_crv_para;
	p_gp_arv_crv_para = &(grp_arv_crv_arr[sw_port_sp.sw_index][sw_port_sp.port][sw_port_sp.sp_index]);
	for (k=0;k<MAX_PORT_VL_COUNT;k++)        // 初始化数组link_para_arr_1
	{
		link_para_arr_1[k].inflection_point_e=0.0;
		link_para_arr_1[k].max_burst=0.0;
		link_para_arr_1[k].sum_p_link=0.0;
	}
	/*remove invalid data from link_para_arr*/
	for (i = 0 ; i < SW_PORT_COUNT ; i++)/**/
	{
		/*judge whether the data valid*/
		if(link_para_arr[i].inflection_point_e > 0.0)//这样可以吗？这个涉及到精确度的问题
		{
			link_para_arr_1[j] = link_para_arr[i];
			j++;
		}
		else
		{
			sum_max_burst=sum_max_burst+link_para_arr[i].max_burst;
		}
	}
	/*sort the temp_lk_para_arr according to value of en*/
	if (j==0)
	{
		p_gp_arv_crv_para->en =0.0;
		p_gp_arv_crv_para->y=sum_max_burst;
	}
	else
	{
		bubble_sort(link_para_arr_1,j);
		p_gp_arv_crv_para->en = link_para_arr_1[j-1].inflection_point_e;
		p_gp_arv_crv_para->y = cal_y(link_para_arr_1,j)+sum_max_burst;
	}   
}

double cal_y(Flow_Para_Tag link_para_arr[],int link_para_count)
{
	double p = 0.0;
	double y = 0.0;
	int i  = 0;
	/*the sum maximum burst of all links*/
	/*first element of the array*/
	p = link_para_arr[0].sum_p_link;
	y +=link_para_arr[0].max_burst+(link_para_count*C)*link_para_arr[0].inflection_point_e;/*加上第一个突发度和第一个提升，*/

	/*other element of the array*/
	for (i = 1 ; i <link_para_count ; i++)
	{   	
		/*加上其它的突发度和其它的提升*/
		y += link_para_arr[i].max_burst+((link_para_count- i)*C +p)*(link_para_arr[i].inflection_point_e - link_para_arr[i-1].inflection_point_e);
        p += link_para_arr[i].sum_p_link;	
	}
	return y;
}
/**********************************************************************
* FUNCTION NAME:
*   bubble_sort
*
* DESCRIPTION:
*     bubble sort
*
* INTERFACE:
*   GLOBAL DATA:
*     
*
*   INPUT:
*     Flow_Para_Tag* arr --group link info
*     int arr_size --- record the number of effective elements
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
*********************************************************************//*冒泡排序*/
void bubble_sort(Flow_Para_Tag link_para_arr[],int arr_size)
{

	int index_i =0;
	int index_j = 0;
	int  flag = 1;

	for(index_i = 0;(index_i != arr_size) && (flag == 1); index_i++)
	{
		/*if the element is in order*/
		flag = 0;
		for (index_j = 1; index_j != arr_size-index_i;index_j++)
		{

			if(link_para_arr[index_j-1].inflection_point_e >link_para_arr[index_j].inflection_point_e)
			{
				Flow_Para_Tag temp = link_para_arr[index_j-1];
				link_para_arr[index_j-1] = link_para_arr[index_j];
				link_para_arr[index_j] = temp;
				flag = 1;
			}
		}
	}
}
/**********************************************************************
*我们的交换模型是：由于一发多收在分开的地方去复制，我们的VL的路径是以一个交换机为一个分叉结点的树状传输
**********************************************************************/
void get_link_vl_count(Sw_Port_SP_Tag sw_port_sp,int gp_vl_arr[GROUP_LINK_COUNT][VL_GROUP_COUNT],
				                   int vl_gp_count_arr[GROUP_LINK_COUNT],Buff_Sg_Path_Para_Tag all_buff_vl_para[TOTAL_VL_NUM])
{			
	int i=0;
	int vl_index = 0;
	int index=0;
	for (vl_index = 0; vl_index < MAX_PORT_VL_COUNT ; vl_index++)
	{   
		int multi_index = 0;
	    int nd_index = 0;
        VL_Path_Tag path;
		int vl_find=0;                 //表明这个VL找到存好没有。
		int vl = output_vl_arr[sw_port_sp.sw_index][sw_port_sp.port][sw_port_sp.sp_index][vl_index];/*在指定的网指定buffer_Tag里取VL*/
		if (vl==INVALID_VL)
		{
			break;
		}
	     path = phy_path_arr[vl];
		while (multi_index < path.multi_num&&vl_find==0)   //&&表示同时成立
		{
			for (nd_index = 1 ; nd_index < PATH_ND_COUNT; nd_index++)/*这个从1遍历好些，1才是交换机。*/
			{
				if(sw_port_sp.sw_index == path.nd_arr[multi_index][nd_index].node_index)
				{
					int input_port = path.nd_arr[multi_index][nd_index].input_port_id;
					index=vl_gp_count_arr[input_port];/*这个存的是每一行LINK 里面的VL的位置，存一个位置后移一位*/
					gp_vl_arr[input_port][index] = vl;//把VL分类存在这里
					/*下面存下这个buffer_Tag中该VL的在这个buffer_Tag的信息*/
					all_buff_vl_para[vl].hop_index=nd_index;//这里的hop其实为这个vl进过了其路径上第hop个交换机的出口
					all_buff_vl_para[vl].vl_multi_index=multi_index;
					vl_gp_count_arr[input_port]++;/*位置后移*/
					vl_find=1;
					break;
				}
			}
			multi_index++;
		} 
	}
}