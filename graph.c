/**
 * @file graph.c
 * @author He Wang
 * @brief 复习数据结构 图代码
 * @date 2023-03-23
 */

#define MAX_VERTEX_NUM 20

#include <stdio.h>
#include <malloc.h>

typedef struct//定义邻接矩阵图
{
    int vexnum;
    int arcnum;
    char vexs[MAX_VERTEX_NUM]; 
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
}MGraph;
typedef struct ArcBox//定义十字链表弧结点
{
    int tailvex;//弧尾
    int headvex;//弧头
    struct ArcBox *hlink;//与该弧具有相同弧头的弧
    struct ArcBox *tlink;//与该弧具有相同弧尾的弧
}ArcBox;
typedef struct//定义十字链表顶点结点
{
    char data;
    ArcBox *firstin;//该顶点的第一个入弧
    ArcBox *firstout;//该顶点的第一个出弧
}VexNode;
typedef struct//定义十字链表图
{
    VexNode xlist[MAX_VERTEX_NUM];
    int vexnum;
    int arcnum;
}OLGraph;

/*定义无向网
*/
int CreateUDN(MGraph *G);
/*定义十字链表表示的有向图
*/
int CreateOL(OLGraph *G);
/*返回顶点的位置（邻接矩阵）
*/
int locate_1(MGraph *G, char v);
/*返回顶点的位置（十字链表）
*/
int locate_2(OLGraph *G, char v);
/*输出邻接矩阵
*/
void printAM(MGraph *G);
/*输出十字链表
*/
void printOL(OLGraph *G);

int main()
{
    // MGraph *MG = (MGraph*)malloc(sizeof(MGraph));
    // CreateUDN(MG);
    // printAM(MG);    
    OLGraph *OG = (OLGraph*)malloc(sizeof(OLGraph));
    CreateOL(OG);      
    printOL(OG);        
    return 0;
}

int CreateUDN(MGraph *G)
{
    int vexnum = 0;
    scanf("%d",&vexnum);//输入顶点个数
    printf("vexnum is %d\n",vexnum);
    G->vexnum = vexnum;
    int arcnum = 0;
    scanf("%d",&arcnum);//输入边的个数
    printf("arcnum is %d\n",arcnum);
    G->arcnum = arcnum;
    for(int i = 0;i < G->vexnum;i++)//输入各个顶点
    {
        getchar();//getchar用于清空缓冲区
        char v = ' ';
        scanf("%c",&v);
        printf("the current vex is %c\n",v);
        G->vexs[i] = v;
    }   

    for(int i = 0;i < G->vexnum;i++)    
        for(int j = 0;j < G->vexnum;j++)        
            G->arcs[i][j] = -1;      
    
    for(int k = 0;k < G->arcnum;k++)//输入各个弧
    {
        char v1 = ' ';
        char v2 = ' ';
        int w = 0;
        getchar();
        scanf("%c",&v1);
        getchar();
        scanf("%c",&v2);
        getchar();
        scanf("%d",&w);
        int i = locate_1(G,v1);
        int j = locate_1(G,v2);
        printf("i is %d i is %d w is %d\n",i,j,w);
        G->arcs[i][j] = w;
        G->arcs[j][i] = G->arcs[i][j];
    }
    return 0;
}
int CreateOL(OLGraph *G)
{
    int vexnum = 0;
    scanf("%d",&vexnum);//输入顶点个数
    printf("vexnum is %d\n",vexnum);
    G->vexnum = vexnum;
    int arcnum = 0;
    scanf("%d",&arcnum);//输入边的个数
    printf("arcnum is %d\n",arcnum);
    G->arcnum = arcnum;
    for(int i = 0;i < G->vexnum;i++)//输入各个顶点
    {
        getchar();//getchar用于清空缓冲区
        char v = ' ';
        scanf("%c",&v);
        printf("the current vex is %c\n",v);
        G->xlist[i].data = v;
        G->xlist[i].firstin = NULL;
        G->xlist[i].firstout = NULL;
    }
    for(int k = 0;k < G->arcnum;k++)//输入各个弧
    {
        char v1 = ' ';
        char v2 = ' ';
        getchar();
        scanf("%c",&v1);
        getchar();
        scanf("%c",&v2);
        int i = locate_2(G,v1);
        int j = locate_2(G,v2);
        printf("i is %d j is %d\n",i,j);
        ArcBox *p = (ArcBox*)malloc(sizeof(ArcBox));//创建弧结点
        p->tailvex = i;
        p->headvex = j;
        p->hlink = G->xlist[j].firstin;//使用头插法把弧结点插入十字链表
        p->tlink = G->xlist[i].firstout;
        G->xlist[j].firstin = p;
        G->xlist[i].firstout = p;
    }
    
    return 0;
}
int locate_1(MGraph *G, char v)
{
    for(int i = 0;i < G->vexnum;i++) 
        if(G->vexs[i] == v)
            return i;
    return -1;
}
int locate_2(OLGraph *G, char v)
{
    for(int i = 0;i < G->vexnum;i++) 
        if(G->xlist[i].data == v)
            return i;
    return -1;
}
void printAM(MGraph *G)
{
    for(int i = 0;i < G->vexnum;i++)
    {
        for(int j = 0;j < G->vexnum;j++)
        {
            printf("%d ",G->arcs[i][j]);
        }      
        printf("\n");
    }
}
void printOL(OLGraph *G)
{
    for(int i = 0;i < G->vexnum;i++)
    {
        ArcBox *p = G->xlist[i].firstout;
        while(p != NULL)
        {
            printf("<%d,%d>",p->tailvex,p->headvex);
            p = p->tlink;
        }
        printf("\n");
    }
}
