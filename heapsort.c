/**
 * @file heapsort.c
 * @author He Wang
 * @brief 复习数据结构 堆排序代码
 * @date 2023-04-13
 */

#include <stdio.h>

/*调整堆算法
*/
void heapAdjust(int *arr,int s,int m);
/*堆排序
*/
void heapSort(int *arr,int n);
/*遍历数组
*/
void visit(int *arr, int n);

int main()
{
    int arr[] = { 0, 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
    int n = sizeof(arr) / sizeof(arr[0]) - 1;
    heapSort(arr,n);
    visit(arr, n);
    return 0;
}

void heapAdjust(int *arr,int s,int m)
{
    int i = s;
    int rc = arr[i];
    //int j;
    for(int j = 2*i;j <= m;j *= 2)
    {
        if(j < m && arr[j] < arr[j+1])//选择孩子中较大的
            j++;
        if(rc >= arr[j])//已经建成堆了，推出循环
            break;
        arr[i] = arr[j];//移动元素
        i = j;
    }
    arr[i] = rc;//把堆顶元素放到相应的位置
}
void heapSort(int *arr,int n)
{
    for(int i = n/2;i > 0;i--)//将数组建成堆
        heapAdjust(arr,i,n);
    for(int i = n;i > 1;i--)
    {
        int temp = arr[1];//把堆顶元素移除
        arr[1] = arr[i];
        arr[i] = temp;
        heapAdjust(arr,1,i-1);//重新调整堆
    }
}
void visit(int *arr, int n)
{
    for (int i = 1; i <= n; i++) 
        printf("%d ", arr[i]);
}