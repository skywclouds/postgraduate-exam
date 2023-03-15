/**
 * @file array.c
 * @author He Wang
 * @brief 复习数据结构 数组代码
 * @date 2023-03-11
 */
#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>

#define MAX_ARRAY_DIM 8

typedef struct//定义数组
{
    int *base;//数组元素基址
    int dim;//数组维度
    int *bounds;//数组维度元素基址
    int *constants;//储存每个维度地址偏移量
}Array;

/*初始化数组
*/
int InitArray(Array *A,int dim,...);
/*根据下标返回元素的值
*/
int Value(Array *A,int *e,...);
/*根据下标给元素赋值
*/
int Assign(Array *A,int e,...);

int main()
{
    Array *A = (Array*)malloc(sizeof(Array));
    int dim = 3;
    InitArray(A,dim,3,4,5);
    Assign(A,100,2,3,4);
    int e = 0;
    Value(A,&e,2,3,4);
    printf("%d",e);
    
}

int InitArray(Array *A,int dim,...)
{
    if(dim < 1 || dim > MAX_ARRAY_DIM)//检验维度是否合法
        return -1;
    A->dim = dim;
    A->bounds = (int*)malloc(dim*sizeof(int));//给数组维数分配空间
    int elemtotal = 1;//数组元素个数
    va_list ap;
    va_start(ap,dim);
    for(int i = 0;i < dim;i++)//计算数组元素个数
    {
        *(A->bounds + i) = va_arg(ap,int);
        elemtotal = elemtotal * (*(A->bounds + i));
    }
    va_end(ap);
    A->base = (int*)malloc(elemtotal*sizeof(int));//给数组元素分配空间
    A->constants = (int*)malloc(dim*sizeof(int));//给偏移量分配空间
    *(A->constants + dim - 1) = 1;
    for(int i = dim - 1;i > 0;i--)//计算偏移量
    {
        *(A->constants + i - 1) = *(A->bounds + i) * (*(A->constants + i));
    }
    return 0;
}
int Value(Array *A,int *e,...)
{
    va_list ap;
    va_start(ap,A->dim);
    int off = 0;
    for(int i = 0;i < A->dim;i++)
    {
        int d = va_arg(ap,int);
        off += A->constants[i] * d;
    }
    va_end(ap);
    *e = *(A->base + off);
    return 0;
}
int Assign(Array *A,int e,...)
{
    va_list ap;
    va_start(ap,A->dim);
    int off = 0;
    for(int i = 0;i < A->dim;i++)
    {
        int d = va_arg(ap,int);
        off += A->constants[i] * d;
    }
    *(A->base + off) = e;
    return 0;
}