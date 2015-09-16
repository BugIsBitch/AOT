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


int get_vl_multi_index(Sw_Port_SP_Tag sw_port_sp,int vl)/*����A/B������Ϣ��������ģ�һ�ǣ���߼����ٶȡ�
																		   ���ǣ��������ǰ�A/B������һ����Ȼ���������Ŀ���������ķ���ֵֻ��һ��
																		   �����ǴӴ����ͨ��������˵��
																		   �����ж��ֵ���������������Ϣ���ͱ�֤����һ��ֵ������ͨ����*/
{
	int ret = INVALID;
	int multi_index =0;
	int nd_index =0;
	VL_Path_Tag path = phy_path_arr[vl];/*�Ҹ����VL��AorB���е�·����Ϣ*/
	for (multi_index = 0 ; multi_index < path.multi_num ; multi_index++)
	{
		for (nd_index = 1; nd_index < (PATH_ND_COUNT- 1); nd_index++)/*�ҶԲ��������޸�*/
		{
			/*get node*/
			Phy_Node_Tag nd_asst_pt;
			/*get parameter info of vl*/
			VL_Para_Tag para = vl_para_arr[vl];
			nd_asst_pt = path.nd_arr[multi_index][nd_index];      /*������ȡ����*/
			if ((nd_asst_pt.node_index == sw_port_sp.sw_index) && 
				(nd_asst_pt.output_port_id == sw_port_sp.port )&&
				(para.sp == (sw_port_sp.sp_index+1)))          /*���αȽ�*/
			{
				ret = multi_index;/*�����ҵ�����ʵ��һ������VL�ĵ�һ���������buffer_Tag��·�������Ƕ�������˵������㹻�ˣ�
									��Ϊ������û�зֿ�ǰ�������һ�������ڷֿ�ǰ���Ƶġ����Ҳ����зֿ�������·���غϵľ�����
									��������������������Ƕ�һ��VL��retֻ��һ������ֵ*/
				break;
			}
		}
		if (ret != INVALID)      
		{
			break;
		}
	}
	return ret;//����ټӸ����ѣ�����INVALID_INDEX
}