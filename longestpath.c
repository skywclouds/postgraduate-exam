/**
 * @file longestpath.c
 * @author He Wang
 * @brief 复习数据结构 无权有向图中的最长路径
 * @date 2023-11-20
 */

#include <stdio.h>
#include <malloc.h>
#include "LGraph.h"

/**
 * @brief v出发的最长路径
 * 
 * @param G 图
 * @param v 出发点
 * @param path 路径
 * @param length 路径长度
 * @param visited
 */
void findPath(LGraph *G,int u,int* path, int* length,int* visited);

int main()
{
    LGraph *LG = (LGraph*)malloc(sizeof(LGraph));
    LG->vexnum = 5;
    int visited[LG->vexnum];
    for(int i = 0;i < LG->vexnum;i++)
    {
        VexNode temp_v = {i,NULL};
        LG->vlist[i] = temp_v;
        visited[i] = 0;
    }
    ArcBox a1 = {4,NULL};
    ArcBox a2 = {2,&a1};
    ArcBox a3 = {1,&a2};LG->vlist[0].firstarc = &a3;
    ArcBox a4 = {3,NULL};LG->vlist[1].firstarc = &a4;
    ArcBox a5 = {1,NULL};LG->vlist[2].firstarc = &a5;
    int path[LG->vexnum];//创建路径数组
    int length = 0;//记录路径长度的变量
    findPath(LG,0,path,&length,visited);
    printf("longest length is %d\n",length);
    printf("longest_path is:");
    for(int i = 0;i < length;i++)
        printf("%d,",path[i]);
    return 0;
}

void findPath(LGraph *G,int u,int* path, int* length,int* visited)
{
    if(!visited[u])
    {
        visited[u] = 1;
        int longest_path[G->vexnum];//记录最长路径和最长长度
        int longest_length = 0;
        for(ArcBox* a = G->vlist[u].firstarc;a;a = a->nextarc)
        {
            int t_path[G->vexnum];//把当前路径复制一份
            int t_length = *length + 1;
            for(int i = 0;i < *length;i++)
                t_path[i] = path[i];
            t_path[*length] = u;//当前节点进入路径
            findPath(G,a->data,t_path,&t_length,visited);
            if(t_length > longest_length)//找到了比当前最长路径长的路径
            {
                longest_length = t_length;
                for(int i = 0;i < longest_length;i++)
                    longest_path[i] = t_path[i];
            }
        }
        //修改长度和路径
        if(longest_length)//如果u没有邻接点，则longest_length为0
        {
            *length = longest_length;
            for(int i = 0;i < *length;i++)
                path[i] = longest_path[i];
        }
        else
        {
            path[*length] = u;
            *length = *length+1;
        }
        visited[u] = 0;
    }
}