/**
 * @file binarytree.c
 * @author He Wang
 * @brief 复习数据结构 二叉树基础代码
 * @date 2023-03-14
 */
#include <stdio.h>
#include <malloc.h>

typedef struct BiNode//定义二叉树结点
{
    int data;
    struct BiNode *lchild;
    struct BiNode *rchild;
}BiNode;

/*创建二叉树
*/
int createBiTree(BiNode **T);
/*先序遍历二叉树
*/
int preOrderTraverse(BiNode *T);
/*中序遍历二叉树
*/
int inOrderTraverse(BiNode *T);
/*后序遍历二叉树
*/
int posOrderTraverse(BiNode *T);

int main()
{
    BiNode *T;
    createBiTree(&T);
    printf("\n");
    preOrderTraverse(T);
    printf("\n");
    inOrderTraverse(T);
    printf("\n");
    posOrderTraverse(T);
    return 0;

}

int createBiTree(BiNode **T)
{
    char ch = ' ';
    scanf("%c",&ch);
    printf("%c",ch);
    if(ch == '#')
    {
        *T = NULL;
    }else
    {
        *T = (BiNode*)malloc(sizeof(BiNode));
        (*T)->data = ch;
        createBiTree(&((*T)->lchild));
        createBiTree(&((*T)->rchild));
    }

    return 0;
}
int preOrderTraverse(BiNode *T)
{
    if(T != NULL)
    {
        printf("%c",T->data);
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
    return 0;
}
int inOrderTraverse(BiNode *T)
{
    if(T != NULL)
    {
        inOrderTraverse(T->lchild);
        printf("%c",T->data);
        inOrderTraverse(T->rchild);
    }
    return 0;
}
int posOrderTraverse(BiNode *T)
{
    if(T != NULL)
    {
        posOrderTraverse(T->lchild);
        posOrderTraverse(T->rchild);
        printf("%c",T->data);
    }
    return 0;
}
