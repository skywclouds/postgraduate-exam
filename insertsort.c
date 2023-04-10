/**
 * @file insertsort.c
 * @author He Wang
 * @brief 复习数据结构 插入排序代码
 * @date 2023-04-10
 */

#include <stdio.h>
#include <malloc.h>

typedef struct SqList
{
    int r[20];
    int length;
}SqList;

/*遍历数组
*/
void visit(SqList *L);
/*直接插入排序
*/
void inserSort(SqList *L);
/*折半插入排序
*/
void BinserSort(SqList *L);

int main()
{
    SqList *L = (SqList*)malloc(sizeof(SqList));
    SqList *L2 = (SqList*)malloc(sizeof(SqList));
    L->length = 8;
    L->r[0] = 0;L->r[1] = 49;
    L->r[2] = 38;L->r[3] = 65;
    L->r[4] = 97;L->r[5] = 76;
    L->r[6] = 13;L->r[7] = 27;
    L->r[8] = 49;
    *L2 = *L;
    printf("insert sort:\n");
    inserSort(L);
    visit(L);
    printf("binary insert sort:\n");
    BinserSort(L2);
    visit(L2);
    return 0;
}

void visit(SqList *L)
{
    for(int i = 1;i <= L->length;i++)    
        printf("%d,",L->r[i]);    
    printf("\n");
}
void inserSort(SqList *L)
{
    for(int i = 2;i <= L->length;i++)
    {
        if(L->r[i] < L->r[i-1])//如果小于就插入，如果大于直接就有序了，不用插入
        {
            L->r[0] = L->r[i];//当前结点设为哨兵
            L->r[i] = L->r[i-1];
            int j;
            for(j = i-2;L->r[0] < L->r[j];j--)
                L->r[j+1] = L->r[j];
             L->r[j+1] = L->r[0];
        }
    }
}
void BinserSort(SqList *L)
{
    for(int i = 2;i <= L->length;i++)
    {
        if(L->r[i] < L->r[i-1])//如果小于就插入，如果大于直接就有序了，不用插入
        {
            L->r[0] = L->r[i];//当前结点设为哨兵
            int low = 1;
            int high = i - 1;
            int m;
            while(low <= high)
            {
                m = (low + high) / 2;
                if(L->r[m] > L->r[0])
                    high = m - 1;
                else
                    low = m + 1;
            }
            for(int j = i-1;j > high;j--)        
                L->r[j+1] = L->r[j];        
            L->r[high+1] = L->r[0];
        }
    }
}