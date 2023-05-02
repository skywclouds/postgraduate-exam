/**
 * @file findcircle.c
 * @author He Wang
 * @brief 复习数据结构 找到图中的环代码
 * @date 2023-05-02
 */

#include <stdio.h>
#include <malloc.h>

typedef struct ArcBox//定义十字链表弧结点
{
    int data;
    struct ArcBox *nextarc;//下一条弧
}ArcBox;

typedef struct//定义十字链表顶点结点
{
    int data;
    ArcBox *firstarc;//该顶点的第一条出弧
}VexNode;

typedef struct//定义十字链表图
{
    VexNode vlist[20];
    int vexnum;
}LGraph;

/**
 * @brief 初始化三个数组
 * 
 * @param v 记录当前结点是否能形成环
 * @param t 记录当前结点是否已被访问
 * @param s 数组实现的栈
 */
void initArray(int *v,int *t,int *s);
/**
 * @brief 找到图中的环
 * 
 * @param G 图
 * @param f 从f开始找环
 * @param c 当前结点
 * @param v 记录当前结点是否能形成环
 * @param t 记录当前结点是否已被访问
 * @param s 栈
 * @return int 
 */
int findCircle(LGraph *G,int f,int c,int *v,int *t,int *s);

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
    //记录当前结点是否能形成环，结点是否已被访问，栈数组
    int v[20];int t[20];int s[21];
    initArray(v,t,s);
    for(int i = 0;i < LG->vexnum;i++)//遍历每一个结点，寻找环
    {
        if(findCircle(LG,i,i,v,t,s))
        {
            printf("find circle.\n");
            for(int i = *s-1;i > 0;i--)
                printf("%c,",*(s+i)+65);
            printf("%c\n",i+65);
            initArray(v,t,s);
        }
    }
    return 0;
}

void initArray(int *v,int *t,int *s)
{
    for(int i = 0;i < 20;i++)
    {
        v[i] = 1;
        t[i] = 0;
        s[i+1] = 0;
    }
    s[0] = 1;
}

int findCircle(LGraph *G,int f,int c,int *v,int *t,int *s)
{
    //printf("current node is %c\n",G->vlist[c].data+65);
    t[c] = 1;//记录该结点已被访问
    for(ArcBox *a = G->vlist[c].firstarc;a != NULL;a = a->nextarc)
    {
        //如果该结点没被访问过且可能形成环，或者已经找到了环，则进一步判断
        if((t[a->data] == 0 && v[a->data] != 0 && findCircle(G,f,a->data,v,t,s)) 
            || a->data == f)
        {
            *(s + *s) = c;//当前结点入栈
            *s = *s + 1;
            return 1;//返回成功
        }else
        {
            v[a->data] = 0;//指向的结点标记为不能形成环
        }
    }
    t[c] = 0;//退出时消除该结点的访问记录
    return 0;//没有指向的结点或所有指向的结点都不能形成环，则返回失败
}
