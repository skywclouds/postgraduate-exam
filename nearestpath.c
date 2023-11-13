/**
 * @file nearestpath.c
 * @author He Wang
 * @brief 复习数据结构 无权有向图中的最短路径
 * @date 2023-11-13
 */

#include <stdio.h>
#include <malloc.h>
#include "LGraph.h"

/**
 * @brief s到e的最短路径
 * 
 * @param G 图
 * @param s 起始点
 * @param e 终止点
 */
void findPath(LGraph *G,int s,int e);

int main()
{
    LGraph *LG = (LGraph*)malloc(sizeof(LGraph));
    LG->vexnum = 5;
    for(int i = 0;i < LG->vexnum;i++)
    {
        VexNode temp_v = {i,NULL};
        LG->vlist[i] = temp_v;
    }
    ArcBox a1 = {2,NULL};
    ArcBox a2 = {1,&a1};LG->vlist[0].firstarc = &a2;
    ArcBox a3 = {3,&a1};LG->vlist[1].firstarc = &a3;
    ArcBox a4 = {4,NULL};LG->vlist[2].firstarc = &a4;
    LG->vlist[3].firstarc = &a4;
    findPath(LG,0,4);

    return 0;
}

void findPath(LGraph *G,int s,int e)
{
    int visited[G->vexnum];
    int pre[G->vexnum];//记录每个节点在BFS中被谁带入队列
    for(int i = 0;i < G->vexnum;i++)
    {
        visited[i] = 0;
        pre[i] = 0;
    }
    int queue[10] = {0};//创建队列
    int front = 0;int rear = 0;
    queue[rear++] = s;//初始节点入队
    visited[s] = 1;
    while(front != rear)
    {
        int c = queue[front++];//队头节点的各个邻接点入队
        for(ArcBox *a = G->vlist[c].firstarc;a != NULL;a = a->nextarc)
        {
            if(!visited[a->data])
            {
                visited[a->data] = 1;
                pre[a->data] = c;
                if(a->data == e)
                {//遇到终止节点，跳出循环
                    front = rear = 0;//跳出while
                    break;//跳出for
                }
                queue[rear++] = a->data;//不是终止节点则入队
            }     
        }
    }
    int index = e;
    while(index)//这里把队列当栈用，把终止节点的前驱依次入栈
    {
        queue[rear++] = index;
        index = pre[index];
    }
    queue[rear++] = s;
    while(rear--)//输出栈中所有元素，即为最短路径
        printf("%d,",queue[rear]);
}