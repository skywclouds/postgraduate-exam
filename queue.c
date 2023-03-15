/**
 * @file queue.c
 * @author He Wang
 * @brief 复习数据结构 队列代码
 * @date 2023-03-04
 */

#include <stdio.h>
#include <malloc.h>

typedef struct QNode
{
    int elem;
    struct QNode *next;
}QNode;
typedef struct
{
    QNode *front;
    QNode *rear;
}LinkQuene;

/*初始化队列
*/
int InitQuene(LinkQuene *Q);
/*入队
*/
int EnQueue(LinkQuene *Q,int e);
/*出队
*/
int DeQueue(LinkQuene *Q,int *e);

int main()
{
    LinkQuene *Q = (LinkQuene*)malloc(sizeof(LinkQuene));
    InitQuene(Q);
    for(int i = 0;i < 10;i++)
    {
        EnQueue(Q,i+1);
    }
    for(int i = 0;i < 10;i++)
    {
        int e = 0;
        DeQueue(Q,&e);
        printf("%d,",e);
    }
    return 0;
}

int InitQuene(LinkQuene *Q)
{
    Q->front = (QNode*)malloc(sizeof(QNode));
    Q->rear = Q->front;
    return 0;
}
int EnQueue(LinkQuene *Q,int e)
{
    QNode *p = (QNode*)malloc(sizeof(QNode));
    p->elem = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return 0;
}
int DeQueue(LinkQuene *Q,int *e)
{
    if(Q->front == Q->rear)
        return -1;
    QNode *p = Q->front->next;
    *e = p->elem;
    Q->front->next =  p->next;
    free(p);
    return 0;
}