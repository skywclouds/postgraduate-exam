/**
 * @file dfstopo.c
 * @author He Wang
 * @brief 复习数据结构 用深度优先搜索实现拓扑排序
 * @date 2023-08-25
 */

#define VEX_NUM 4

#include <stdio.h>
/**
 * @brief 初始化图
 */
void initGraph(int (*G)[4]);
/**
 * @brief 求出图中每个节点的入度
 */
void getDegree(int (*G)[4],int *degree);

int main()
{
    int G[VEX_NUM][VEX_NUM];//定义图
    initGraph(G);
    int vex[VEX_NUM] = {0,0,0,0};//标记节点是否被访问
    int degree[VEX_NUM] = {0,0,0,0};//求出每个节点的入度
    getDegree(G,degree);
    int s[10] = {1,0,0,0,0,0,0,0,0,0};//定义并初始化栈
    for(int i = 0;i < VEX_NUM;i++)//非递归深度优先搜索
    {
        if(!degree[i])//从入度为0的节点开始搜索
        {
            //定义一个辅助栈用于搜索
            int s1[10] = {1,0,0,0,0,0,0,0,0,0};
            int c = i;//当前节点
            s1[s1[0]++] = c;//当前节点入辅助栈
            while(s1[0] > 1)//栈不空就继续搜索
            {
                int step = 0;//记录是否前进
                for(int j = 0;j < VEX_NUM;j++)//寻找下一个节点
                {
                    if(G[c][j] && !vex[j])
                    {
                        c = j;//更新当前节点
                        step = 1;
                        vex[j] = 1;
                        s1[s1[0]++] = c;//当前节点入辅助栈
                        break;
                    }
                }
                if(!step)//如果没有往下搜索
                {
                    s[s[0]++] = c;//当前节点入结果栈
                    c = s1[--s1[0]-1];//退栈并更新当前节点
                }
            }
        }
    }
    for(int i = s[0]-1;i > 0;i--)//输出结果
        printf("%c,",'A'+s[i]);
    return 0;
}

void getDegree(int (*G)[4],int *degree)
{
    for(int i = 0;i < VEX_NUM;i++)
        for(int j = 0;j < VEX_NUM;j++)  
            if(G[i][j])
                degree[j]++;
}

void initGraph(int (*G)[4])
{
    for(int i = 0;i < VEX_NUM;i++)
        for(int j = 0;j < VEX_NUM;j++) 
            G[i][j] = 0;
    G[0][1] = 1;//A→→→B
    G[0][2] = 1;// \  ↑     /
    G[2][1] = 1;//   →C
    G[3][2] = 1;//    ↑
                //    D→
}