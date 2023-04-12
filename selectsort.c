/**
 * @file selectsort.c
 * @author He Wang
 * @brief 复习数据结构 选择排序代码
 * @date 2023-04-12
 */

#include <stdio.h>

/*选择排序
*/
void selectSort(int *arr,int n);
/*遍历数组
*/
void visit(int *arr, int n);

int main()
{
    int arr[] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);
    selectSort(arr,n);
    visit(arr, n);
    return 0;
}

void selectSort(int *arr,int n)
{
    for(int i = 0;i < n;i++)
    {
        int index = i;
        for(int j = i;j < n;j++)
            if(arr[j] < arr[index])
                index = j;
        int temp = arr[i];
        arr[i] = arr[index];
        arr[index] = temp;
    }
}
void visit(int *arr, int n)
{
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
}