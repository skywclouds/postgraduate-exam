/**
 * @file longestpath_tree.c
 * @author He Wang
 * @brief 复习数据结构 二叉树中从根节点出发的最长路径
 * @date 2023-11-22
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
 * @brief 最长路径
 * 
 * @param T 树
 * @param path 路径
 * @param length 路径长度
 */
void findPath(BiNode *T,int* path, int* length);

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
    int path[20];        //           H
    int length = 0;
    findPath(&T,path,&length);
    printf("longest_length is %d\n",length);
    printf("longest_path is:");
    for(int i = 0;i < length;i++)
        printf("%c,",path[i]);
    return 0;
}

void findPath(BiNode *T,int* path, int* length)
{
    BiNode *t_path[20];//后序遍历栈，同时储存当前路径
    int t_length = 0;//栈顶下标，同时也表示当前路径长度
    BiNode *p = T;//当前节点
    BiNode *r = NULL;//上一次出栈节点
    while(p || t_length)
    {
        if(p)//一直向左走
        {
            t_path[t_length++] = p;
            p = p->lchild;
        }
        else
        {
            p = t_path[t_length-1];
            if(!(p->rchild))//如果走到了叶子节点
            {
                if(t_length > *length)//更新路径
                {
                    *length = t_length;
                    for(int i = 0;i < t_length;i++)
                        path[i] = t_path[i]->data;
                }
                r = p;//出栈
                p = NULL;
                t_length--;
            }
            else if(p->rchild == r)//右子树已被遍历，出栈
            {
                r = p;
                p = NULL;
                t_length--;
            }
            else//右子树没被遍历，遍历右子树
                p = p->rchild;
        }
    }
}
