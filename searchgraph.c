/**
 * @file graph.c
 * @author He Wang
 * @brief 复习数据结构 遍历图代码
 * @date 2023-03-23
 */

#include <stdio.h>
#include <malloc.h>

int visited[8];//用于记录当前顶点是否被访问的数组
int G[8][8];//图的邻接矩阵


typedef struct node//定义队列结点
{
    int data;
    struct node *next;
}node;
typedef struct//定义队列
{
    struct node *head;
    struct node *rear;
}queue;

/*深度优先搜索树
*/
int DFSTraverse(int(*G)[8],int v,int *visited);
/*广度优先搜索树
*/
int BFSTraverse(int(*G)[8],int v,int *visited,queue *q);

int main()
{
    for(int i = 0;i < 8;i++)
        visited[i] = 0;
    G[0][1] = 1;G[0][2] = 1;
    G[1][3] = 1;G[1][4] = 1;
    G[2][5] = 1;G[2][6] = 1;
    G[3][7] = 1;
    G[4][7] = 1;
    DFSTraverse(G,0,visited);
    printf("\n");
    for(int i = 0;i < 8;i++)
        visited[i] = 0;
    queue *q = (queue*)malloc(sizeof(queue));//创建队列
    node *h = (node*)malloc(sizeof(node));//队列头结点
    q->head = h;
    q->rear = h;
    BFSTraverse(G,0,visited,q);
    return 0;
}

int DFSTraverse(int(*G)[8],int v,int *visited)
{
    *(visited + v) = 1;
    printf("%d,",v+1);
    for(int i = 0;i < 8;i++) 
        if(G[v][i] > 0 && *(visited + i) == 0)          
            DFSTraverse(G,i,visited);      
    return 0;
}
int BFSTraverse(int(*G)[8],int v,int *visited,queue *q)
{
    *(visited + v) = 1;
    node *f = (node*)malloc(sizeof(node));//第一个结点入队列
    f->data = v;
    f->next = NULL;
    q->rear->next = f;
    q->rear = f;
    while(q->head != q->rear)//循环终止条件为队列为空
    {
        int u = q->head->next->data;//队头元素出队
        printf("%d,",u+1);
        q->head = q->head->next;
        for(int i = 0;i < 8;i++)//将队头所有未访问的相邻顶点入队
        {
            if(G[u][i] > 0 && *(visited + i) == 0)
            {
                *(visited + i) = 1;
                node *p = (node*)malloc(sizeof(node));
                p->data = i;
                p->next = NULL;
                q->rear->next = p;
                q->rear = p;
            }
        }
    }
    return 0;
}