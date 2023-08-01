/**
 * @file findcircle2.c
 * @author He Wang
 * @brief 复习数据结构 找到图中的环代码_非递归算法
 * @date 2023-08-01
 */

#include <stdio.h>
#include <malloc.h>

typedef struct ArcBox//定义弧结点
{
    int data;
    struct ArcBox *nextarc;//下一条弧
}ArcBox;

typedef struct//定义顶点结点
{
    int data;
    ArcBox *firstarc;//该顶点的第一条出弧
}VexNode;

typedef struct//定义链表图
{
    VexNode vlist[20];
    int vexnum;
}LGraph;

/**
 * @brief 初始化三个数组
 * 
 * @param t 记录当前结点是否已被访问
 * @param s 数组实现的栈
 */
void initArray(int *t,int *s);

/**
 * @brief 找到图中的环
 * 
 * @param G 图
 * @param f 从f开始找环
 * @param t 记录当前结点是否已被访问
 * @param s 栈
 * @return int 
 */
int findCircle(LGraph *G,int f,int *t,int *s);

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
    //记录结点是否已被访问，栈数组
    int t[20];int s[21];
    initArray(t,s);
    for(int i = 0;i < LG->vexnum;i++)//遍历每一个结点，寻找环
    {
        if(findCircle(LG,i,t,s))
        {
            printf("find circle.\n");
            for(int i = 1;i <= *s-1;i++)
                printf("%c,",*(s+i)+65);
            printf("%c\n",i+65);
        }
        initArray(t,s);
    }
    return 0;
}

void initArray(int *t,int *s)
{
    for(int i = 0;i < 20;i++)
        t[i] = s[i+1] = 0;
    s[0] = 1;
}

int findCircle(LGraph *G,int f,int *t,int *s)
{
    int step = 0;//记录是否前进了
    int c = f;//当前结点
    *(t + c) = 1;//记录该结点已被访问
    *(s + *s) = c;//当前结点入栈
    *s = *s + 1;
    while (*s > 1)
    {
        //遍历当前结点的每一个邻接结点
        for(ArcBox *a = G->vlist[c].firstarc;a != NULL;a = a->nextarc)
        {
            if (a->data == f)//如果找到了环    
                return 1;//返回成功
            
            if(!*(t + a->data))//如果该结点没有被访问
            {
                c = a->data;//更新当前结点
                *(s + *s) = c;//该结点入栈
                *s = *s + 1;
                *(t + c) = 1;//标记该结点为被访问
                step = 1;
                break;
            }
        }
        if(!step)//如果所有邻接结点都被访问
        {
            *s = *s - 1;//退栈
            c = *(s + *s - 1);//更新当前结点
        }else
            step = 0;
    }
    return 0;
}