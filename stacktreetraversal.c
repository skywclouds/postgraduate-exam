/**
 * @file stacktreetraversal.c
 * @author He Wang
 * @brief 复习数据结构 不用递归遍历二叉树代码
 * @date 2023-04-05
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
    BiTree *base = (BiTree*)malloc(20 * sizeof(BiTree));
    BiTree *top = base;
    *top = *T;//根结点入栈
    top++;
    printf("%d,",(top - 1)->data);//输出根结点
    while(top != base)
    {
        if((top - 1)->lchild)
        {
            *top = *((top - 1)->lchild);//左孩子入栈
            (top - 1)->lchild = NULL;//令当前结点左孩子为空，防止重复遍历
            top++;
            printf("%d,",(top - 1)->data);//输出左孩子
        }else
        {
            if((top - 1)->rchild)
            {
                *(top - 1) = *((top - 1)->rchild);//当前结点出栈，右孩子入栈
                printf("%d,",(top - 1)->data);//输出右孩子
            }       
            else
            {
                top--;//遇到叶子结点，直接使其出栈
            }                
        }
    }
}
void inOrder(BiTree *T)
{
    BiTree *base = (BiTree*)malloc(20 * sizeof(BiTree));
    BiTree *top = base;
    *top = *T;//根结点入栈
    top++;
    while(top != base)
    {
        if((top - 1)->lchild)
        {
            *top = *((top - 1)->lchild);//左孩子入栈
            (top - 1)->lchild = NULL;//令当前结点左孩子为空，防止重复遍历
            top++;
        }else
        {
            printf("%d,",(top - 1)->data);//若左孩子为空，输出当前结点
            if((top - 1)->rchild)//当前结点出栈，右孩子入栈      
                *(top - 1) = *((top - 1)->rchild);
            else
                top--;         
        }
    }
}
void posOrder(BiTree *T)
{
    BiTree *base = (BiTree*)malloc(20 * sizeof(BiTree));
    BiTree *top = base;
    *top = *T;//根结点入栈
    top++;
    while(top != base)
    {
        if((top - 1)->lchild)
        {
            *top = *((top - 1)->lchild);//左孩子入栈
            (top - 1)->lchild = NULL;//令当前结点左孩子为空，防止重复遍历
            top++;
        }else
        {
            if((top - 1)->rchild)
            {
                *top = *((top - 1)->rchild);
                (top - 1)->rchild = NULL;//令当前结点右孩子为空，防止重复遍历
                top++;
            }       
            else
            {
                printf("%d,",(top - 1)->data);//遇到叶子结点，输出
                top--;
            }         
        }
    }
}