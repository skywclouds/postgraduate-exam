/**
 * @file staticsearch.c
 * @author He Wang
 * @brief 复习数据结构 静态查找代码
 * @date 2023-03-29
 */

#include <stdio.h>
#include <malloc.h>

typedef struct SSTable//静态查找表的顺序存储结构
{
    int *elem;
    int length;
}SSTable;

/*顺序查找
*/
int search_Seq(SSTable *ST,int key);
/*二分查找
*/
int search_Bin(SSTable *ST,int key);

int main()
{
    SSTable *ST = (SSTable*)malloc(sizeof(SSTable));
    ST->length = 10;
    ST->elem = (int*)malloc((ST->length + 1)*sizeof(int));
    for(int i = 0;i <= ST->length;i++)
    {
        ST->elem[i] = i;
    }
    int pos = search_Seq(ST,5);
    printf("%d is in %d\n",5,pos);
    pos = search_Bin(ST,3);
    printf("%d is in %d\n",3,pos);
    return 0;
}

int search_Seq(SSTable *ST,int key)
{
    ST->elem[0] = key;
    int i = ST->length;
    while (ST->elem[i] != key)   
        i--;       
    return i;
}
int search_Bin(SSTable *ST,int key)
{
    int low = 1;
    int high = ST->length;
    int mid = (low + high)/2;
    while(low <= high)
    {
        if(ST->elem[mid] == key)
            return mid;
        else if(ST->elem[mid] < key)
            low = mid + 1;
        else    
            high = mid - 1;          
        mid = (low + high)/2;
    }
    return 0;
}