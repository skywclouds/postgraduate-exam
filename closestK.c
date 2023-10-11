/**
 * @file closestK.c
 * @author He Wang
 * @brief 复习数据结构 无向图中距离某节点最短距离为k的节点
 * @date 2023-10-11
 */

#define VEXNUM 10
#define QUEUESIZE 5

#include <stdio.h>
#include <malloc.h>

typedef struct Grpah
{
    int adj[VEXNUM][VEXNUM];
    int visited[VEXNUM];
}Grpah;

typedef struct Queue
{
    int front;
    int rear;
    int arr[QUEUESIZE];
}Queue;

/*初始化图
*/
void initGraph(Grpah *G);
/*初始化队列
*/
void initQueue(Queue *Q);
/*入队
*/
void EnQueue(Queue *Q,int e);
/*出队
*/
int DeQueue(Queue *Q);

int main()
{
    Grpah *G = (Grpah*)malloc(sizeof(Grpah));//创建图并初始化
    initGraph(G);
    Queue *Q = (Queue*)malloc(sizeof(Queue));//创建队列并初始化
    initQueue(Q);
    EnQueue(Q,0);//0号节点入队
    G->visited[0] = 1;
    int c_num = 1;//当前层未被遍历的节点数
    int n_num = 0;//下一层的已入队的节点数
    int layer_num = 0;//已经遍历的层数
    int k = 3;
    while(Q->rear != Q->front)//如果队列不空
    {
        int c = DeQueue(Q);//队头节点出队
        c_num--;//当前层未被遍历的节点数减一
        for(int i = 0;i < VEXNUM;i++)//相邻节点入队
            if(G->adj[c][i] == 1 && !G->visited[i])
            {
                EnQueue(Q,i);
                G->visited[i] = 1;
                n_num++;
            }
        if(c_num == 0)//如果当前层已全被遍历
        {
            c_num = n_num;
            n_num = 0;
            layer_num++;
            if(layer_num == k)
                break;
        }
    }
    while(Q->rear != Q->front)//此时队列中剩余的节点就是最短距离为k的全部节点
        printf("%d,",DeQueue(Q));
    return 0;
}

void initGraph(Grpah *G)
{
    for(int i = 0;i < VEXNUM;i++)
        for(int j = 0;j < VEXNUM;j++)
            G->adj[i][j] = 0;
    G->adj[0][1] = 1;G->adj[1][0] = 1;
    G->adj[0][2] = 1;G->adj[2][0] = 1;
    G->adj[1][3] = 1;G->adj[3][1] = 1;
    G->adj[1][4] = 1;G->adj[4][1] = 1;
    G->adj[2][5] = 1;G->adj[5][2] = 1;
    G->adj[2][6] = 1;G->adj[6][2] = 1;
    G->adj[3][7] = 1;G->adj[7][3] = 1;
    G->adj[5][8] = 1;G->adj[8][5] = 1;
    G->adj[6][9] = 1;G->adj[9][6] = 1;
    for(int i = 0;i < VEXNUM;i++)//定义访问数组
        G->visited[i] = 0;
}

void initQueue(Queue *Q)
{
    for(int i = 0;i < QUEUESIZE;i++)//定义队列    
        Q->arr[i] = 0;    
    Q->front = 0;
    Q->rear = 0;
}

void EnQueue(Queue *Q,int e)
{
    Q->arr[Q->rear] = e;
    Q->rear = (Q->rear + 1) % QUEUESIZE;
}

int DeQueue(Queue *Q)
{
    int res = Q->arr[Q->front];
    Q->front = (Q->front + 1) % QUEUESIZE;
    return res;
}