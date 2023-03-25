/**
 * @file prim.c
 * @author He Wang
 * @brief 复习数据结构 普利姆算法代码
 * @date 2023-03-25
 */

#include <stdio.h>
#include <malloc.h>

typedef struct closedge//定义closedge数组
{
    int vex;
    int lowcost;
}closedge;

typedef struct Graph//定义图
{
    int matrix[6][6];
    struct closedge ce[6];
}Graph;

/*初始化图
*/
int initGraph(Graph *G);
/*求出closedge数组中最小的一项
*/
int mininum(Graph *G);
/*普利姆算法
*/
void miniSpanTree_Prim(Graph *G,int u);

int main()
{
    Graph *G = (Graph*)malloc(sizeof(Graph));
    initGraph(G);
    miniSpanTree_Prim(G,0);
    return 0;
}

int initGraph(Graph *G)
{
    for(int i = 0;i < 6;i++)
        for(int j = 0;j < 6;j++)
            G->matrix[i][j] = __INT_MAX__;
    G->matrix[0][1] = 6;G->matrix[0][2] = 1;
    G->matrix[0][3] = 5;
    G->matrix[1][0] = 6;G->matrix[1][2] = 5;
    G->matrix[1][4] = 3;
    G->matrix[2][0] = 1;G->matrix[2][1] = 5;
    G->matrix[2][3] = 5;G->matrix[2][4] = 6;
    G->matrix[2][5] = 4;
    G->matrix[3][0] = 5;G->matrix[3][2] = 5;
    G->matrix[3][5] = 2;
    G->matrix[4][1] = 3;G->matrix[4][2] = 6;
    G->matrix[4][5] = 6;
    G->matrix[5][2] = 4;G->matrix[5][3] = 2;
    G->matrix[5][4] = 6;
    return 0;
}
int mininum(Graph *G)
{
    int r = 0;
    for(int i = 0;i < 6;i++)
    {
        if(G->ce[i].lowcost != 0)
        {
            r = i;
            break;
        }
    }
    for(int i = r;i < 6;i++)
    {
        if(G->ce[i].lowcost < G->ce[r].lowcost && G->ce[i].lowcost != 0)
        {
            r = i;
        }
    }
    return r;
}
void miniSpanTree_Prim(Graph *G,int u)
{
    G->ce[u].lowcost = 0;//初始化closedge数组
    for(int i = 0;i < 6;i++)
    {
        if(i != u)
        {
            G->ce[i].vex = u;
            G->ce[i].lowcost = G->matrix[i][u];
        }
    }
    for(int i = 1;i < 6;i++)//操作剩下的n-1个顶点
    {
        int k = mininum(G);
        printf("<%d,%d>\n",G->ce[k].vex+1,k+1);//输出最小生成树的边
        G->ce[k].lowcost = 0;//将顶点k加入最小生成树
        for(int i = 0;i < 6;i++)
        {
            if(G->matrix[i][k] < G->ce[i].lowcost)//更新closedge数组
            {
                G->ce[i].vex = k;
                G->ce[i].lowcost = G->matrix[i][k];
            }
        }
    }
}