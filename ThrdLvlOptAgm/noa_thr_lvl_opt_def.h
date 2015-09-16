

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
#define INVALID_NODE 200//大于（168-1）就行
#define INVALID_PORT 100//大于（25-1）就行
#define INVALID_VL  -4
#define INVALID_SP -5
//#define INVALID_PARA -6
//#define INVALID_HOP -7
//#define INVALID_EDGE -8
#define C 104857.6     //100M/S===104857.6 字节/ms
#define MAX_FRAME_SIZE 1538
#define VL_GROUP_COUNT 4096/*maximum of vl_group data structure count*/

#define L_TECH 0.05/*技术延迟5微妙，技术抖动1微妙//暂时设为50微妙*/


#define OUTPUT_FRAME_SUM 1024
#define ND_NM_LEN 65     /*交换机名称,终端名称,各个port名称字符串长度64+1,*/
#define MAX_VL_PATHNAME 33  //同上
#define PATH_ND_COUNT 5
#define MAX_MULTI_PATH 152
#define MAX_ES_CNT 152  //这里指的是普通终端和自带终端的数量之和
//#define MAX_ALL_ES_CNT 168
#define TOTAL_VL_NUM 10000
#define TOTAL_NET_WORK 2
#define CRET_SHR_VL_NUM 4096
#define GROUP_LINK_COUNT 25
#define MAX_PORT_VL_COUNT 4096
#define SW_COUNT 16//A/B网总共有16个交换机
#define SW_COUNT_NET 8//A/或B网有8个交换机（在A/B网交换机数量不等时，表示大的那个）
#define HOP 3/**/
#define MAX_TPA 10000/*TPA的最大个数*/


#define BUFFER_NUM 200 //网络中的buffer_Tag总数25*8（或者25*SW_COUNT_NET）
#define EDGE_NUM 1400   //A(/B)网络中潜在的环的边个数最多为：7*25*8

/* ----------------------- TYPE DECLARATIONS ------------------------*/
/*------------------------- VARIABLE DEFINITION ---------------------*/

/*------------------------- VARIABLE DEFINITION --------------------*/

#endif /* __NOA_THR_LVL_OPT_DEF_H__*/