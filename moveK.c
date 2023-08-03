/**
 * @file moveK.c
 * @author He Wang
 * @brief 复习数据结构 把顺序表中元素向后移动k位
 * @date 2023-08-03
 */

#include <stdio.h>

int main()
{
    //原理是先把前n-k位逆置，再把后k位逆置，最后把整个数组逆置
    int arr[10] = {0,1,2,3,4,5,6,7,8,9};
    int arr_size = sizeof(arr)/sizeof(int);
    int k = 3;
    k = arr_size - k;//方便操作
    for(int i = 0;i < k/2;i++)//把前n-k位逆置
    {
        int temp = arr[i];
        arr[i] = arr[k-1-i];
        arr[k-1-i] = temp;
    }
    for(int i = k;i < (arr_size + k)/2;i++)//再把后k位逆置
    {
        int temp = arr[i];
        arr[i] = arr[arr_size-1-i+k];
        arr[arr_size-1-i+k] = temp;
    }
    for(int i = 0;i < arr_size/2;i++)//把整个数组逆置
    {
        int temp = arr[i];
        arr[i] = arr[arr_size-1-i];
        arr[arr_size-1-i] = temp;
    }
    for(int i = 0;i < arr_size;i++)
        printf("%d,",arr[i]);
    return 0;
}