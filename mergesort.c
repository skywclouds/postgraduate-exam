/**
 * @file mergesort.c
 * @author He Wang
 * @brief 复习数据结构 归并排序代码
 * @date 2023-04-13
 */

#include <stdio.h>

/*合并有序数组
*/
void merge(int *arr,int i,int m,int n);
/*归并排序
*/
void mergeSort(int *arr,int s,int t);
/*遍历数组
*/
void visit(int *arr, int n);

int main()
{
    int arr[] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr,0,n-1);
    visit(arr, n);
    return 0;
}
void merge(int *arr,int l,int m,int n)
{
    int a1[m-l+1];
    int a2[n-m];
    for(int i = 0;i < m-l+1;i++) 
        a1[i] = arr[l+i];
    for(int i = 0;i < n-m;i++)
        a2[i] = arr[m+1+i];
    int i = 0;
    int j = 0;
    int k = l;
    while (i < m-l+1 && j < n-m)
    {
        if(a1[i] < a2[j])
        {
            arr[k] = a1[i];
            i++;
        }else
        {
            arr[k] = a2[j];
            j++;
        }
        k++;
    }
    if(i == m-l+1)
    {
        for(;j < n-m;j++)
        {
            arr[k] = a2[j];
            k++;
        }
    }else
    {
        for(;i < m-l+1;i++)
        {
            arr[k] = a1[i];
            k++;
        }
    }
}
void mergeSort(int *arr,int s,int t)
{
    if(s < t)
    {
        int m = (s+t)/2;
        mergeSort(arr,s,m);//对左侧归并排序
        mergeSort(arr,m+1,t);//对右侧归并排序
        merge(arr,s,m,t);//合并左右两侧
    }
}
void visit(int *arr, int n)
{
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
}
