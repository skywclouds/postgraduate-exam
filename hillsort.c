/**
 * @file hillsort.c
 * @author He Wang
 * @brief 复习数据结构 希尔排序代码
 * @date 2023-04-11
 */

#include <stdio.h>

/*希尔排序
*/
void hillSort(int *arr, int n);
/*遍历数组
*/
void visit(int *arr, int n);

int main() {
    int arr[] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);
    hillSort(arr, n);
    printf("Hill Sort:\n");
    visit(arr, n);
    return 0;
}

void hillSort(int *arr, int n) {
    //gap从大到小
    for (int gap = n / 2; gap > 0; gap /= 2) {
        //对每一个gap进行插入排序
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}
void visit(int *arr, int n)
{
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
}