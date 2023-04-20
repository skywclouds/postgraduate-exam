/**
 * @file allancestors.c
 * @author He Wang
 * @brief 复习数据结构 找到树中结点的所有祖先代码
 * @date 2023-04-20
 */

#include <stdio.h>
#include <malloc.h>

typedef struct BiNode
{
    char data;
    struct BiNode* lchild;
    struct BiNode* rchild;
}BiNode;

/**
 * @brief 找到树中结点的所有祖先
 * 
 * @param T 树的根结点
 * @param c 结点的值
 * @param s 储存祖先的栈
 */
void findAncestor(BiNode *T, char c,int *s);

int main()
{
    int *s = (int*)malloc(20*sizeof(int));//定义栈
    *s = 0;//第一个元素存储栈的长度
    BiNode b1 = {'H',NULL,NULL};//    A
    BiNode b2 = {'F',NULL,NULL};//   / \    /
    BiNode b3 = {'G',&b1,NULL};//   B   C
    BiNode b4 = {'D',NULL,NULL};// / \      /
    BiNode b5 = {'E',&b2,&b3};//  D   E 
    BiNode b6 = {'B',&b4,&b5};//     / \    /
    BiNode b7 = {'C',NULL,NULL};//  F   G   /
    BiNode T = {'A',&b6,&b7};//        /
    findAncestor(&T,'H',s);//         H
    for(int i = 1;i <= *s;i++) 
        printf("%c,",*(s+i)); 
    return 0;
}

void findAncestor(BiNode *T, char c,int *s)
{
    if(T)
    {
        if(T->data != c)//不是c结点，入栈，并继续深度优先遍历
        {
            *(s+*s+1) = T->data;
            *s = *s + 1;
            findAncestor(T->lchild,c,s);
            findAncestor(T->rchild,c,s);
            *s = *s - 1;//左右子树都遍历结束后将当前元素出栈
        }else//找到了c结点，输出栈中所有元素，即c结点的所有祖先
        {
            for(int i = 1;i <= *s;i++) 
                printf("%c,",*(s+i));
            printf("\n");
        }
    }
}