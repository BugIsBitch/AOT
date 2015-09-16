
#define MAX_VEX 1000
typedef struct 
{
    char portNm[64];/*物理端口名称*/
	char guid[255];/*物理端口唯一标示*/
}PhysPort;

typedef struct
{
	int adjvex;/*邻接点*/

	EdgeNode *next;/*下一个邻接点*/

}EdgeNode;
typedef struct 
{
	char devNm[64];/*终端设备名称*/

	PhysPort *portInfo;/*端口信息*/

	char physProtoclType[32];/*网络类型*/

	EdgeNode *firstEdge;

}VertexNode,AdjList[MAX_VEX];

typedef struct 
{
	AdjList adjlist;/*网络拓扑结构*/
	int numVertexes;/*顶点数*/
	int numEdges;/*边数*/
}PhysGraph;