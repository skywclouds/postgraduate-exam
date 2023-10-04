/**
 * @file stacktreetraversal.c
 * @author He Wang
 * @brief 复习数据结构 非递归遍历二叉树代码
 * @date 2023-10-04
 */

#include <stdio.h>
#include <malloc.h>

typedef struct BiTree
{
    int data;
    struct BiTree *lchild;
    struct BiTree *rchild;
}BiTree;

/*前序遍历
*/
void preOrder(BiTree *T);
/*中序遍历
*/
void inOrder(BiTree *T);
/*后序遍历
*/
void posOrder(BiTree *T);

int main()
{
    BiTree b1 = {6,NULL,NULL};
    BiTree b2 = {7,NULL,NULL};
    BiTree b3 = {4,NULL,NULL};
    BiTree b4 = {5,NULL,NULL};
    BiTree b5 = {2,&b3,&b4};
    BiTree b6 = {3,&b1,&b2};
    BiTree T = {1,&b5,&b6};
    printf("preOrder:");
    preOrder(&T);
    printf("\n");
    printf("inOrder:");
    inOrder(&T);
    printf("\n");
    printf("posOrder:");
    posOrder(&T);
    printf("\n");
}

void preOrder(BiTree *T)
{
    BiTree *s[20];//建立栈
    int top = 0;
    s[top++] = T;//根节点入栈
    BiTree *p;
    while(top)
    {
        p = s[top - 1];//取出栈顶元素
        top--;
        printf("%d,",p->data);
        if(p->rchild)//右，左孩子依次入栈
            s[top++] = p->rchild;
        if(p->lchild)
            s[top++] = p->lchild;
    }
}
void inOrder(BiTree *T)
{
    BiTree *s[20];//建立栈
    int top = 0;
    BiTree *p = T;
    while(p || top)
    {
        if(p)//向左走到尽头
        {
            s[top++] = p;
            p = p->lchild;
        }else//走到尽头之后输出栈顶元素，之后遍历右子树
        {
            p = s[top - 1];
            top--;
            printf("%d,",p->data);
            p = p->rchild;//若没有又子树，则p为null，下一次仍然出栈
        }
    }
}
void posOrder(BiTree *T)
{
    BiTree *s[20];//建立栈
    int top = 0;
    BiTree *p = T;
    BiTree *r;//上一次出栈的元素
    while(p || top)
    {
        if(p)//向左走到尽头
        {
            s[top++] = p;
            p = p->lchild;
        }else
        {
            p = s[top - 1];
            if(!p->rchild || p->rchild == r)//如果右子树已被遍历
            {
                printf("%d,",p->data);
                r = p;
                top--;
                p = NULL;//将p置为NULL，防止左子树重复入栈
            }
            else
                p = p->rchild;//遍历右子树 
        }
    }
}