/**
 * @file binarysorttree.c
 * @author He Wang
 * @brief 复习数据结构 二叉排序树代码
 * @date 2023-03-31
 */

#include <stdio.h>
#include <malloc.h>

typedef struct BiTree
{
    int data;
    struct BiTree* lchild;
    struct BiTree* rchild;
}BiTree;

/*中序遍历二叉树
*/
void inOrder(BiTree *T);
/*查找二叉排序树中的元素
*/
BiTree* searchBST(BiTree *T,int key);
/*寻找结点的双亲
*/
void findParent(BiTree *T,int key,BiTree *parent);
/*向二叉排序树中插入元素
*/
int insertBST(BiTree *T,int e);
/*创建二叉排序树
*/
void createBST(BiTree *T,int n,int *arr);
/*删除二叉排序树中的元素
*/
int deleteBST(BiTree *T,int key);

int main()
{
    BiTree *T = (BiTree*)malloc(sizeof(BiTree));
    int arr[] = {45,12,53,3,37,100,5,101,4};
    createBST(T,9,arr);
    inOrder(T);
    printf("\n");
    int del[] = {101,53,12};
    for(int i = 0;i < 3;i++)
    {
        printf("delete %d\n",del[i]);
        deleteBST(T,del[i]);
        inOrder(T);
        printf("\n");
    }
    return 0;
}
void inOrder(BiTree *T)
{
    if(T != NULL)
    {
        inOrder(T->lchild);
        printf("%d,",T->data);
        inOrder(T->rchild);
    }
}
BiTree* searchBST(BiTree *T,int key)
{
    if(T == NULL || T->data == key)
        return T;
    else if(T->data > key)
        return searchBST(T->lchild,key);
    else
        return searchBST(T->rchild,key); 
}
int insertBST(BiTree *T,int e)
{
    if(T->data == e)
    {
        return 0;
    }
    else if(T->data > e)
    {
        if(T->lchild == NULL)
        {
            BiTree *bt = (BiTree*)malloc(sizeof(BiTree));
            bt->data = e;
            bt->lchild = NULL;
            bt->rchild = NULL;
            T->lchild = bt;
            return 1;
        }else
        {
            insertBST(T->lchild,e);
        }
    }else
    {
        if(T->rchild == NULL)
        {
            BiTree *bt = (BiTree*)malloc(sizeof(BiTree));
            bt->data = e;
            bt->lchild = NULL;
            bt->rchild = NULL;
            T->rchild = bt;
            return 1;
        }else
        {
            insertBST(T->rchild,e);
        }
    }
    return 0;
}
void createBST(BiTree *T,int n,int *arr)
{
    T->data = *arr;
    T->lchild = NULL;
    T->rchild = NULL;
    for(int i = 1;i < n;i++)
    {
        insertBST(T,*(arr + i));
    }
}
void findParent(BiTree *T,int key,BiTree *parent)
{
    //若key是其双亲结点的左孩子，则parent的左孩子指向双亲结点
    //若key是其双亲结点的右孩子，则parent的右孩子指向双亲结点
    if(T)
    {
        findParent(T->lchild,key,parent);
        if(T->lchild != NULL && T->lchild->data == key)
        {
            parent->data = T->data;
            parent->lchild = T;
        }else if(T->rchild != NULL && T->rchild->data == key)
        {
            parent->data = T->data;
            parent->rchild = T;
        }
        findParent(T->rchild,key,parent);
    }
}
int deleteBST(BiTree *T,int key)
{
    BiTree *s = searchBST(T,key);//首先判断要删除的结点是否在树中
    if(s)//在树中
    {
        if(s->lchild == NULL && s->rchild == NULL)//结点为叶子结点
        {
            BiTree *parent = (BiTree*)malloc(sizeof(BiTree));
            parent->data = key;
            parent->lchild = NULL;
            parent->rchild = NULL; 
            findParent(T,key,parent);//寻找结点的双亲结点
            if(parent->data != key)//找到双亲结点
            {
                if(parent->lchild != NULL)
                {
                    parent->lchild->lchild = NULL;
                    free(s);
                }else
                {
                    parent->rchild->rchild = NULL;
                    free(s);
                }
                
            }else//找不到双亲结点，说明要删除的结点是根结点
            {   
                free(T);
            }
        }else if(s->lchild == NULL)//节点右子树不为空
        {
            BiTree *t = s->rchild;
            s->data = t->data;
            s->lchild = t->lchild;
            s->rchild = t->rchild;
            free(t);
        }else if(s->rchild == NULL)//节点左子树不为空
        {
            BiTree *t = s->lchild;
            s->data = t->data;
            s->lchild = t->lchild;
            s->rchild = t->rchild;
            free(t);
        }
        else//左右子树均不为空
        {
            BiTree *q = s;
            BiTree *l = s->lchild;
            while(l->rchild != NULL)//找到结点左子树的最右侧尽头的孩子
            {
                q = l;
                l = l->rchild;
            }
            s->data = l->data;//用左子树的最右侧尽头的孩子替代要删除的结点
            if(q == s)//若结点左子树没有右孩子，修改当前结点的左子树
            {
                q->lchild = l->lchild;
            }else//修改右子树
            {
                q->rchild = l->lchild;
            }
            free(l);
        } 
    }else//不在树中，返回0
    {
        return 0;
    }
    return 1;
}