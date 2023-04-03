/**
 * @file balancedbinarytree.c
 * @author He Wang
 * @brief 复习数据结构 二叉排序树代码
 * @date 2023-04-03
 */

#define LH 1
#define EH 0
#define RH -1

#include <stdio.h>
#include <malloc.h>

typedef struct BSTNode
{
    int data;
    int bf;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
}BSTNode, *BSTree;

/*前序遍历二叉树
*/
void preOrder(BSTree T);
/*中序遍历二叉树
*/
void inOrder(BSTree T);
/*单次右旋
*/
void R_Rotate(BSTree *p);
/*单次左旋
*/
void L_Rotate(BSTree *p);
/*左平衡
*/
void LeftBalance(BSTree *p);
/*右平衡
*/
void RightBalance(BSTree *p);
/*向平衡二叉树中插入结点
*/
int insertAVL(BSTree *T,int e,int *taller);

int main()
{
    int arr[] = {3,4,5,7,6,1,2};
    BSTree T = NULL;  
    for(int i = 0;i < 7;i++)
    {
        int taller = 0;
        printf("insert %d\n",arr[i]);
        insertAVL(&T,arr[i],&taller);
        printf("preOrder: ");
        preOrder(T);
        printf("\n");
        printf("inOrder: ");
        inOrder(T);
        printf("\n");
    }
    return 0;
}

void preOrder(BSTree T)
{
    if(T)
    {
        printf("%d,",T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}
void inOrder(BSTree T)
{
    if(T)
    {
        inOrder(T->lchild);
        printf("%d,",T->data);
        inOrder(T->rchild);
    }
}
void R_Rotate(BSTree *p)
{
    BSTree lc = (*p)->lchild;
    (*p)->lchild = lc->rchild;
    lc->rchild = *p;
    *p = lc;
}
void L_Rotate(BSTree *p)
{
    BSTree rc = (*p)->rchild;
    (*p)->rchild = rc->lchild;
    rc->lchild = *p;
    *p = rc;
}
void LeftBalance(BSTree *p)
{
    BSTree lc = (*p)->lchild;
    switch (lc->bf)//因为新结点要么接在lc的左子树上，要么接在lc的右子树上
    {//所以只有LH和RH两种情况，没有EH
        case LH:
            (*p)->bf = EH;
            lc->bf = EH;
            R_Rotate(p);
            break;
        case RH:
            BSTree rd = lc->rchild;
            switch (rd->bf)
            {//此处代码注释略
                case LH:
                    (*p)->bf = RH;
                    lc->bf = EH;
                    break;
                case EH:
                    (*p)->bf = EH;
                    lc->bf = EH;
                    break;
                case RH:
                    (*p)->bf = EH;
                    lc->bf = LH;
                    break;
            }
            rd->bf = EH;
            //此处的&((*p)->lchild)不能替换为&lc
            //因为lc是指针，不是二重指针，直接指向结点本体
            //如果替换成&lc，则只修改了lc，没有修改&((*p)->lchild)
            L_Rotate(&((*p)->lchild));//对p的左孩子左旋
            R_Rotate(p);//再对p右旋
            break;
    }
}
void RightBalance(BSTree *p)
{
    BSTree rc = (*p)->rchild;
    switch (rc->bf)//因为新结点要么接在rc的左子树上，要么接在rc的右子树上
    {//所以只有LH和RH两种情况，没有EH
        case RH:
            (*p)->bf = EH;
            rc->bf = EH;
            L_Rotate(p);
            break;
        case LH:
            BSTree ld = rc->lchild;
            switch (ld->bf)
            {//此处代码注释略
                case RH:
                    (*p)->bf = LH;
                    rc->bf = EH;
                    break;
                case EH:
                    (*p)->bf = EH;
                    rc->bf = EH;
                    break;
                case LH:
                    (*p)->bf = EH;
                    rc->bf = RH;
                    break;
            }
            ld->bf = EH;
            //此处的&((*p)->rchild)不能替换为&rc
            //因为rc是指针，不是二重指针，直接指向结点本体
            //如果替换成&rc，则只修改了rc，没有修改&((*p)->rchild)
            R_Rotate(&((*p)->rchild));//对p的右孩子右旋
            L_Rotate(p);//再对p左旋
            break;
    }
}
int insertAVL(BSTree *T,int e,int *taller)
{
    if(*T == NULL)//如果T是空树，创建新结点
    {
        *T = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = e;
        (*T)->bf = EH;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        *taller = 1;
        return 1;
    }else if((*T)->data != e)
    {
        if((*T)->data > e)
        {
            if(!insertAVL(&((*T)->lchild),e,taller))
                return 0;//如果插入未成功，直接结束，返回0
            if(taller)//如果树长高了
            {
                switch ((*T)->bf)
                {
                case LH://本来就是左子树高，插入之后左子树更高了
                    LeftBalance(T);//需要进行左平衡
                    *taller = 0;//平衡之后高度下降了，相当于没变高
                    break;
                case EH://本来是平衡的 ，左子树变高后变成LH
                    (*T)->bf = LH;
                    *taller = 1;
                    break;
                case RH://本来右子树高，插入之后平衡了
                    (*T)->bf = EH;
                    taller = 0;
                    break;
                }
            }
        }else
        {
            if(!insertAVL(&((*T)->rchild),e,taller))
                return 0;//如果插入未成功，直接结束，返回0
            if(taller)//如果树长高了
            {
                switch ((*T)->bf)
                {
                case RH://本来就是右子树高，插入之后右子树更高了
                    RightBalance(T);//需要进行右平衡
                    *taller = 0;//平衡之后高度下降了，相当于没变高
                    break;
                case EH://本来是平衡的 ，右子树变高后变成RH
                    (*T)->bf = RH;
                    *taller = 1;
                    break;
                case LH://本来左子树高，插入之后平衡了
                    (*T)->bf = EH;
                    taller = 0;
                    break;
                }
            }
        }
        return 1;
    }else//如果新插入的结点已在树中，什么也不做
    {
        *taller = 0;
        return 0;
    }
}