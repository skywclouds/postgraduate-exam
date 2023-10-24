/**
 * @file findCircle3.c
 * @author He Wang
 * @brief 复习数据结构 判断图中有无环代码_多种算法
 * @date 2023-10-24
 */

#include <stdio.h>
#include <malloc.h>
#include "LGraph.h"

/**
 * @brief 拓扑排序判断图中是否有环
 * @param G 图
 */
int topo(LGraph *G);

/**
 * @brief 后向边判断图中是否有环
 * @param G 图
 */
int behindEdge(LGraph *G);
/**
 * @brief 后向边判断图中是否有环的DFS部分
 * @param G 图
 * @param c 当前节点
 * @param v visited数组
 * @param s 存储已遍历节点的栈
 * @param b 标记是否有环
 */
void DFS_behindEdge(LGraph *G,int c,int *v,int *s,int *b);
/**
 * @brief 非递归后向边判断图中是否有环
 * @param G 图
 */
int no_recursion_behindEdge(LGraph *G);

int main()
{
    LGraph *LG = (LGraph*)malloc(sizeof(LGraph));
    LG->vexnum = 9;
    for(int i = 0;i < LG->vexnum;i++)
    {
        VexNode temp_v = {i,NULL};
        LG->vlist[i] = temp_v;
    }
    ArcBox a1 = {2,NULL};
    ArcBox a2 = {1,&a1};LG->vlist[0].firstarc = &a2;
    ArcBox a3 = {3,NULL};LG->vlist[1].firstarc = &a3;
    ArcBox a4 = {3,NULL};
    ArcBox a5 = {4,&a4};LG->vlist[2].firstarc = &a5;
    ArcBox a6 = {5,NULL};
    ArcBox a7 = {1,&a6};LG->vlist[3].firstarc = &a7;
    ArcBox a8 = {8,NULL};
    ArcBox a9 = {6,&a8};
    ArcBox a10 = {5,&a9};LG->vlist[4].firstarc = &a10;
    ArcBox a11 = {7,NULL};LG->vlist[6].firstarc = &a11;
    ArcBox a12 = {0,NULL};LG->vlist[8].firstarc = &a12;
    if(topo(LG))
        printf("topo: have circle.\n");
    else
        printf("topo: no circle.\n");
    if(behindEdge(LG))
        printf("behindEdge: have circle.\n");
    else
        printf("behindEdge: no circle.\n");
    if(no_recursion_behindEdge(LG))
        printf("no_recursion_behindEdge: have circle.\n");
    else
        printf("no_recursion_behindEdge: no circle.\n");
    return 0;
}

int topo(LGraph *G)
{
    //求所有节点的入度
    int degree[G->vexnum];
    for(int i = 0;i < G->vexnum;i++)
        degree[i] = 0;
    for(int i = 0;i < G->vexnum;i++)
        for(ArcBox *a = G->vlist[i].firstarc;a;a=a->nextarc)
            degree[a->data]++;
    //进行拓扑排序
    int s[G->vexnum];
    int top = 0;
    for(int i = 0;i < G->vexnum;i++)
        if(degree[i] == 0)
            s[top++] = i;
    while(top)
    {
        int c = s[--top];
        for(ArcBox *a = G->vlist[c].firstarc;a;a=a->nextarc)
        {
            degree[a->data]--;
            if(degree[a->data] == 0)
                s[top++] = a->data;
        }
    }
    //如果有节点未被拓扑排序，则有环
    for(int i = 0;i < G->vexnum;i++)
        if(degree[i])
            return 1;
    return 0;
}

int behindEdge(LGraph *G)
{
    int visited[G->vexnum];//visited数组
    for(int i = 0;i < G->vexnum;i++)
        visited[i] = 0;
    int s[G->vexnum];//定义栈以存储遍历过的节点
    s[0] = 1;
    int b = 0;//标记是否有环
    //从每个节点开始找环
    for(int i = 0;i < G->vexnum;i++)
        DFS_behindEdge(G,i,visited,s,&b);  
    return b;
}

void DFS_behindEdge(LGraph *G,int c,int *v,int *s,int *b)
{
    v[c] = 1;//标记该节点被访问
    s[s[0]++] = c;//当前节点入栈
    for(ArcBox *a = G->vlist[c].firstarc;a;a = a->nextarc)
    {
        //如果visited是1，代表节点在dfs树中，即找到了后向边
        if(v[a->data] == 1)
        {
            //输出环
            int p = s[0]-1;
            while(s[p] != a->data)
                p--;
            while(p != s[0])
                printf("%c,",s[p++]+65);  
            printf("\n");
            *b = 1;//标记为有环
        }
        //没找到环，继续DFS    
        if(v[a->data] == 0)
            DFS_behindEdge(G,a->data,v,s,b);
    }
    v[c] = 2;//标记该节点被访问，且被退回
    s[0]--;//当前节点出栈
}

int no_recursion_behindEdge(LGraph *G)
{
    int visited[G->vexnum];//visited数组
    for(int i = 0;i < G->vexnum;i++)
        visited[i] = 0;
    //定义栈以存储遍历过的节点
    //为什么是2*G->vexnum，因为一个存放节点，一个存放已经遍历了几条边
    int s[2*G->vexnum];
    int top = 0;
    int b = 0;//标记是否有环
    for(int i = 0;i < G->vexnum;i++)
    {
        if(visited[i] == 0)
        {
            s[top++] = G->vlist[i].data;//当前节点入栈
            s[top++] = 0;
            visited[i] = 1;
            while(top)
            {
                int c = s[top-2];//取栈顶节点
                int num = s[top-1];//取栈顶节点已遍历的边数
                int step = 0;
                for(ArcBox *a = G->vlist[c].firstarc;a;a = a->nextarc)
                {
                    for(int i = 0;i < num;i++)//跳过已遍历的边
                        a = a->nextarc;
                    if(!a)
                        break;
                    num++;//已遍历的边数+1
                    //如果visited是1，代表节点在dfs树中，即找到了后向边
                    if(visited[a->data] == 1)
                    {
                        //输出环
                        int p = top-2;
                        while(s[p] != a->data)
                            p -= 2;
                        while(p != top)
                        {
                            printf("%c,",s[p]+65);
                            p += 2;
                        }     
                        printf("\n");
                        b = 1;//标记为有环
                    }
                    //没找到环，继续DFS
                    if(visited[a->data] == 0)
                    {
                        //更新遍历的边数
                        //为什么在这里更新，因为在step被改为1，如果不是在
                        //这里改，那么step还是0，那么将会退栈，等于没更新
                        s[top-1] = num;
                        s[top++] = a->data;//新节点入栈
                        s[top++] = 0;
                        visited[a->data] = 1;
                        step = 1;
                        break;
                    }
                }
                if(step == 0)//没找到环，且邻接节点均被访问，后退
                {
                    visited[c] = 2;
                    top -= 2;
                }
            }
        }
    }
    return b;
}