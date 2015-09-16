/*-------------------------- FILE PROLOGUE --------------------------*/



#ifndef __NOA_THR_LVL_OPT_GRAPH_H__
#define __NOA_THR_LVL_OPT_GRAPH_H__


extern void graph_initial(int i,int sp_r) ;  //

extern void create_graph(int network,int priority,int vl_count);//

extern  int create_edge(int a,int b,int i,int sp_r,int *m_pointer);//

extern int find_edge_id(int i,int sp_r,int a,int b,int m);

extern  void find_ring(int i,int sp_r);//

extern  void check_edge(int a,int b,int w,int sp_r);//

extern  void top_sort(int network,int priority);

extern  int look_number(int w,int sp_r,int k,int j);

extern  void indegree(int buffer_indegree[],int num,int w,int sp_r);

#endif /* __NOA_THR_LVL_OPT_GRAPH_H__*/
