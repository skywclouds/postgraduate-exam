/**
 * @file linklist.c
 * @author He Wang
 * @brief 复习数据结构 线性表代码
 * @date 2023-03-04
 */
#include <stdio.h>
#include <malloc.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct//定义线性表
{
    int *elem;
    int length;
    int listsize;
}SqList;
typedef struct LNode//定义线性链表
{
    int elem;
    struct LNode *next;
    
}LNode;

/*初始化线性表
*/
int INitList_Sq(SqList *L);
/*向线性表中插入元素
*/
int ListInsert_Sq(SqList *L,int i,int e);
/*创建线性链表
*/
int CreateList_L(LNode **L,int n);
/*合并链表
*/
void MergeList();

int main()
{
    SqList *L = (SqList*)malloc(sizeof(SqList));
    INitList_Sq(L);
    printf("L's length is %d\n",L->length);
    for(int i = 0;i <= 10;i++){
        ListInsert_Sq(L,i,i);
    }
    for(int i = 0;i < L->length;i++)
    {
        int e = *(L->elem + i);
        printf("%d,",e);
    }
    LNode *LN;
    CreateList_L(&LN,10);
    LNode *p = LN->next;
    printf("\n");
    while (p != NULL)
    {
        printf("%d,",p->elem);
        p = p->next;
    }
    printf("\n");
    MergeList();
    return 0;
}

int INitList_Sq(SqList *L)
{
    L->elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return 0;
}
int ListInsert_Sq(SqList *L,int i,int e)
{
    if(i<1 || i>L->length+1)
        return -1;
    if(L->length>=L->listsize)
    {
        int *newbase = (int*)realloc(L->elem,(L->length+LISTINCREMENT)*sizeof(int));
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    int *q = L->elem+i-1;
    for(int *p = L->elem+L->length-1;p >= q;p--)
        *(p+1) = *(p);
    *q = e;
    L->length++;
    return 0;
}
int CreateList_L(LNode **L,int n)
{
    *L = (LNode*)malloc(sizeof(LNode));
    (*L)->next = NULL;
    for(int i = n;i > 0;i--)
    {
        LNode *p = (LNode*)malloc(sizeof(LNode));
        p->elem = i;
        p->next = (*L)->next;
        (*L)->next = p;
    }
    return 0;
}
void MergeList()
{
    LNode *LA = (LNode*)malloc(sizeof(LNode));
    LNode *LB = (LNode*)malloc(sizeof(LNode));
    LA->next = NULL;
    LB->next = NULL;
    LNode *pa = LA;
    LNode *pb = LB;
    int arr1[] = {1,3,5,7,9};
    int arr2[] = {2,4,6,8,10,11,12,13,14,15};
    for(int i = 0;i < sizeof(arr1)/sizeof(int);i++)
    {
        LNode *p = (LNode*)malloc(sizeof(LNode));
        p->elem = arr1[i];
        p->next = NULL;
        pa->next = p;
        pa = p;
    }
    for(int i = 0;i < sizeof(arr2)/sizeof(int);i++)
    {
        LNode *p = (LNode*)malloc(sizeof(LNode));
        p->elem = arr2[i];
        p->next = NULL;
        pb->next = p;
        pb = p;
    }
    pa = LA->next;
    pb = LB->next;
    LNode *LC = (LNode*)malloc(sizeof(LNode));
    LC->next = NULL;
    LNode *pc = LC;
    while (pa != NULL && pb != NULL)
    {
        LNode *p = (LNode*)malloc(sizeof(LNode));
        p->next = NULL;
        if(pa->elem < pb->elem)
        {
            p->elem = pa->elem;
            pa = pa->next;
        }                    
        else{
            p->elem = pb->elem;
            pb = pb->next;
        }
        pc->next = p;
        pc = p;
    }
    if(pa == NULL)
    {
        while (pb != NULL)
        {
            LNode *p = (LNode*)malloc(sizeof(LNode));
            p->next = NULL;
            p->elem = pb->elem;
            pb = pb->next;
            pc->next = p;
            pc = p;
        }
        
    }else{
        while (pa != NULL)
        {
            LNode *p = (LNode*)malloc(sizeof(LNode));
            p->next = NULL;
            p->elem = pa->elem;
            pa = pa->next;
            pc->next = p;
            pc = p;
        }
    }
    pc = LC->next;
    while(pc != NULL)
    {
        printf("%d,",pc->elem);
        pc = pc->next;
    }
}