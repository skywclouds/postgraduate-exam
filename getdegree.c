/**
 * @file getdegree.c
 * @author He Wang
 * @brief 复习数据结构 求孩子-兄弟树的度
 * @date 2023-11-02
 */

#include <stdio.h>
#include <malloc.h>

typedef struct csNode
{
    char data;
    struct csNode* child;
    struct csNode* sibling;
}csNode,csTree;

/**
 * @brief 求孩子-兄弟树的度
 * 
 * @param T 树的根节点
 */
int getDegree(csTree *T);

int main()
{
    csNode n1 = {'f',NULL,NULL};//  a
    csNode n2 = {'e',NULL,&n1};//  /
    csNode n3 = {'d',NULL,&n2};// b->c
    csNode n4 = {'c',&n3,NULL};//   /
    csNode n5 = {'b',NULL,&n4};//  d->e->f
    csTree *T = (csTree*)malloc(sizeof(csTree));
    T->data = 'a';T->child = &n5;T->sibling = NULL;
    printf("Degree of T is %d\n",getDegree(T));
    return 0;
}

int getDegree(csTree *T)
{
    if(!T->child)//如果没有孩子，则度为0
        return 0;
    csNode *p = T->child;
    int child_num = 0;
    int degree = 0;
    while(p)
    {
        //遍历每一个孩子，寻找度的最大值
        int temp_degree = getDegree(p);
        if(temp_degree > degree)
            degree = temp_degree;
        p = p->sibling;
        child_num++;
    }
    //孩子中度的最大值与自身的度比较，返回最大值
    if(child_num > degree)
        degree = child_num;    
    return degree;
}