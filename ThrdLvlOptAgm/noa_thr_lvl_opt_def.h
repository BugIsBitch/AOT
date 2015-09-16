

#ifndef __NOA_THR_LVL_OPT_DEF_H__
#define __NOA_THR_LVL_OPT_DEF_H__
/* ----------------------- TYPE DECLARATIONS ------------------------*/
/*------------------------- VARIABLE DEFINITION ---------------------*/



/*------------------------- VARIABLE DEFINITION --------------------*/
#define SP_COUNT 2
#define SW_PORT_COUNT 25
#define SP1 1
//#define SP2 2
//#define SP3 3
//#define SP4 4
#define MAX(a,b) (a)>(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define PROCESS_SUC 1//
#define INVALID -1//
//#define INVALID_INDEX -1
#define INVALID_NODE 200//���ڣ�168-1������
#define INVALID_PORT 100//���ڣ�25-1������
#define INVALID_VL  -4
#define INVALID_SP -5
//#define INVALID_PARA -6
//#define INVALID_HOP -7
//#define INVALID_EDGE -8
#define C 104857.6     //100M/S===104857.6 �ֽ�/ms
#define MAX_FRAME_SIZE 1538
#define VL_GROUP_COUNT 4096/*maximum of vl_group data structure count*/

#define L_TECH 0.05/*�����ӳ�5΢���������1΢��//��ʱ��Ϊ50΢��*/


#define OUTPUT_FRAME_SUM 1024
#define ND_NM_LEN 65     /*����������,�ն�����,����port�����ַ�������64+1,*/
#define MAX_VL_PATHNAME 33  //ͬ��
#define PATH_ND_COUNT 5
#define MAX_MULTI_PATH 152
#define MAX_ES_CNT 152  //����ָ������ͨ�ն˺��Դ��ն˵�����֮��
//#define MAX_ALL_ES_CNT 168
#define TOTAL_VL_NUM 10000
#define TOTAL_NET_WORK 2
#define CRET_SHR_VL_NUM 4096
#define GROUP_LINK_COUNT 25
#define MAX_PORT_VL_COUNT 4096
#define SW_COUNT 16//A/B���ܹ���16��������
#define SW_COUNT_NET 8//A/��B����8������������A/B����������������ʱ����ʾ����Ǹ���
#define HOP 3/**/
#define MAX_TPA 10000/*TPA��������*/


#define BUFFER_NUM 200 //�����е�buffer_Tag����25*8������25*SW_COUNT_NET��
#define EDGE_NUM 1400   //A(/B)������Ǳ�ڵĻ��ı߸������Ϊ��7*25*8

/* ----------------------- TYPE DECLARATIONS ------------------------*/
/*------------------------- VARIABLE DEFINITION ---------------------*/

/*------------------------- VARIABLE DEFINITION --------------------*/

#endif /* __NOA_THR_LVL_OPT_DEF_H__*/