/**
 * @file quicksort.c
 * @author He Wang
 * @brief 复习数据结构 快速排序代码
 * @date 2023-04-12
 */

#include <stdio.h>

/*快速排序
*/
void quickSort(int *arr,int low,int high);
/*快速排序辅助算法
*/
int partition(int *arr,int low,int high);
/*交换数组中的元素
*/
void exchange(int *arr,int i,int j);
/*遍历数组
*/
void visit(int *arr, int n);

int main()
{
    int arr[] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr,0,n-1);
    visit(arr, n);
    return 0;
}

void quickSort(int *arr,int low,int high)
{
    if (high > low)
    {
        int p = partition(arr,low,high);//分割重排数组
        quickSort(arr,low,p-1);//对左右给两个部分进行快速排序
        quickSort(arr,p+1,high);
    }
}
int partition(int *arr,int low,int high)
{
    int i = low + 1;
    int j = high;
    while(i < j)
        if(arr[i] > arr[low])//比哨兵大，移到右边
            exchange(arr,i,j);
        else
            i++;
        if(arr[j] < arr[low])//比哨兵小，移到左边
            exchange(arr,i,j);
        else
            j--;
    if(i == j && arr[j] > arr[low])//把哨兵放在正确的位置
        exchange(arr,low,--j);      
    else
        exchange(arr,low,j);
    return j;
    
}
void exchange(int *arr,int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void visit(int *arr, int n)
{
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
}