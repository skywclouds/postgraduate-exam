/**
 * @file array.c
 * @author He Wang
 * @brief 复习数据结构 线索二叉树代码
 * @date 2023-03-14
 */

#include <stdio.h>
#include <malloc.h>

typedef struct BiThrNode//定义线索二叉树结点
{
    int data;
    int ltag;
    int rtag;
    struct BiThrNode *lchild;
    struct BiThrNode *rchild;

}BiThrNode;

BiThrNode *pre;//记录当前遍历结点的上一个结点

/*将二叉树T线索化，Thrt是头结点
*/
int inOrderThreading(BiThrNode *Thrt,BiThrNode *T);
/*线索化二叉树的关键算法
*/
void inThreading(BiThrNode *T);
/*遍历线索化后的二叉树
*/
int inOrderTraverse(BiThrNode *T);

int main()
{
    BiThrNode b1 = {'C',0,0,NULL,NULL};
    BiThrNode b2 = {'A',0,0,NULL,NULL};
    BiThrNode b3 = {'I',0,0,NULL,NULL};
    BiThrNode b4 = {'G',0,0,NULL,NULL};
    BiThrNode b5 = {'E',0,0,NULL,NULL};
    BiThrNode b6 = {'B',0,0,&b2,&b1};
    BiThrNode b7 = {'H',0,0,&b4,&b3};
    BiThrNode b8 = {'D',0,0,&b6,&b5};
    BiThrNode T = {'F',0,0,&b8,&b7};
    pre = (BiThrNode*)malloc(sizeof(BiThrNode));
    BiThrNode Thrt = {'#',0,0,NULL,NULL};
    inOrderThreading(&Thrt,&T);
    printf("\n");
    printf("%d\n",b2.rtag);
    inOrderTraverse(&Thrt);
    return 0;
}

int inOrderThreading(BiThrNode *Thrt,BiThrNode *T)
{
    Thrt->ltag = 0;
    Thrt->rtag = 1;
    Thrt->rchild = Thrt;//设置Thrt的后继为其本身
    if(T == NULL)//如果T为空，让Thrt的左孩子指向自己
    {
        Thrt->lchild = Thrt;
    }else
    {
        Thrt->lchild = T;
        pre = Thrt;//T的上一个结点是pre
        inThreading(T);
        pre->rchild = Thrt;//T的最后一个结点的后继指向Thrt
        pre->rtag = 1;
        Thrt->rchild = pre;//Thrt的后继指向T的最后一个结点
    }
    return 0;
}
void inThreading(BiThrNode *T)
{
    if(T != NULL)
    {
        inThreading(T->lchild);
        printf("%c",T->data);
        if(T->lchild == NULL)
        {
            T->ltag = 1;
            T->lchild = pre;//前驱指向pre
        }
        if(pre->rchild == NULL)
        {
            pre->rtag = 1;
            pre->rchild = T;//T是pre的下一个结点，所以让pre的后继指向T
        }
        pre = T;
        inThreading(T->rchild);
    }
}
int inOrderTraverse(BiThrNode *T)
{
    BiThrNode *p = T->lchild;
    while(p != T)
    {
        while(p->ltag == 0)
            p = p->lchild;//先找到最左侧的结点，即中序遍历的第一个结点
        printf("%c",p->data);
        while(p->rtag == 1 && p->rchild != T)
        {//遍历该结点的后续结点
            p = p->rchild;
            printf("%c",p->data);
        }
        p = p->rchild;//若后续结点有右孩子，
        //这代表其左孩子都已完成遍历，所以从其右孩子开始下一轮遍历
    }
    return 0;
}