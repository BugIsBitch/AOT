
#define MAX_VEX 1000
typedef struct 
{
    char portNm[64];/*����˿�����*/
	char guid[255];/*����˿�Ψһ��ʾ*/
}PhysPort;

typedef struct
{
	int adjvex;/*�ڽӵ�*/

	EdgeNode *next;/*��һ���ڽӵ�*/

}EdgeNode;
typedef struct 
{
	char devNm[64];/*�ն��豸����*/

	PhysPort *portInfo;/*�˿���Ϣ*/

	char physProtoclType[32];/*��������*/

	EdgeNode *firstEdge;

}VertexNode,AdjList[MAX_VEX];

typedef struct 
{
	AdjList adjlist;/*�������˽ṹ*/
	int numVertexes;/*������*/
	int numEdges;/*����*/
}PhysGraph;