/**
 * @file getTreeWidth.c
 * @author He Wang
 * @brief 复习数据结构 求二叉树的宽度代码
 * @date 2023-07-23
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
 * @brief 求二叉树的宽度
 * 
 * @param 二叉树的根结点 
 */
int getWidth(BiNode *T);

int main()
{
    BiNode b1 = {'G',NULL,NULL};//    A
    BiNode b2 = {'F',NULL,NULL};//   / \     /  
    BiNode b3 = {'H',&b1,NULL};//   B   C
    BiNode b4 = {'D',NULL,NULL};// /   / \  /   
    BiNode b5 = {'E',&b1,&b3};//  D   E   F
    BiNode b6 = {'B',&b4,NULL};//    /      /
    BiNode b7 = {'C',&b5,&b2};//    H   
    BiNode T = {'A',&b6,&b7};//    /
    int width = getWidth(&T);//   G
    printf("The width of this tree is: %d.",width);
    return 0;
}

int getWidth(BiNode *T)
{
    BiNode* q[20];//定义队列
    int head = 0;//队头
    int rear = 0;//队尾
    int length = 0;//当前最大长度
    int t_length = 0;//当前层的长度
    BiNode *p1 = NULL;//队列队头的节点
    BiNode *p2 = T;//当前层的最后一个节点
    BiNode *p3 = NULL;//队列队尾的节点
    q[rear++] = T;//根节点入队
    while(head != rear)//进行层次遍历
    {
        p1 = q[head++];//队头节点出队
        t_length++;//当前层宽度加一
        if(p1->lchild)//队头节点的孩子入队   
            q[rear++] = p1->lchild;
        if(p1->rchild)
            q[rear++] = p1->rchild;
        p3 = q[rear - 1];
        //队头节点是当前层的最后一个节点时，p3页恰好到达下一层最后一个节点
        if(p1 == p2)
        {
            p2 = p3;
            if(t_length > length)//更新宽度
                length = t_length;
            t_length = 0;        
        }  
    }
    
    return length;
}