/**
 * @file allancestors2.c
 * @author He Wang
 * @brief 复习数据结构 找到树中结点的所有祖先代码
 * @date 2023-10-25
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
 */
void findAncestor(BiNode *T, char c);

int main()
{
    BiNode b1 = {'H',NULL,NULL};//    A
    BiNode b2 = {'F',NULL,NULL};//   / \    /
    BiNode b3 = {'G',&b1,NULL};//   B   C
    BiNode b4 = {'D',NULL,NULL};// / \      /
    BiNode b5 = {'E',&b2,&b3};//  D   E 
    BiNode b6 = {'B',&b4,&b5};//     / \    /
    BiNode b7 = {'C',NULL,NULL};//  F   G   /
    BiNode T = {'A',&b6,&b7};//        /
    findAncestor(&T,'H');//           H
    return 0;
}

void findAncestor(BiNode *T, char c)
{
    BiNode* s[20];//栈
    int top = 0;
    BiNode *p = T;//当前节点
    BiNode *r = NULL;//上一次出栈的节点
    while(p || top)
    {
        if(p)//节点非空，进栈
        {
            if(p->data == c)//找到目标节点，则跳出循环            
                break;            
            s[top++] = p;
            p = p->lchild;
        }else
        {
            p = s[top-1];//节点为空，则取栈顶元素
            if(!p->rchild || p->rchild == r)//若没有右孩子或右孩子已被遍历，出栈
            {
                top--;
                r = p;
                p = NULL;    
            }else//否则，右孩子进栈     
                p = p->rchild;
        }
    }
    for(int i = 0;i < top;i++)//输出
        printf("%c,",s[i]->data);
}