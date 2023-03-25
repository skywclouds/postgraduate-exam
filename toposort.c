/**
 * @file toposort.c
 * @author He Wang
 * @brief 复习数据结构 拓扑排序代码
 * @date 2023-03-25
 */

#include <stdio.h>
#include <malloc.h>

typedef struct Graph//定义图
{
    int matrix[6][6];
    int indegree[6];//储存各顶点的入度
}Graph;
typedef struct stack//定义栈
{
    int *base;
    int *top;
}stack;

/*初始化图
*/
int initGraph(Graph *G);
/*拓扑排序
*/
int topologicalSort(Graph *G);
/*求各个点的入度
*/
int findInDegree(Graph *G);
/*初始化栈
*/
int initStack(stack *s);
/*向栈中添加元素
*/
int push(stack *S,int e);
/*取出栈顶元素
*/
int pop(stack *S);

int main()
{
    Graph *G = (Graph*)malloc(sizeof(Graph));
    initGraph(G);
    topologicalSort(G);
    return 0;
}

int initGraph(Graph *G)
{
    for(int i = 0;i < 6;i++)
        for(int j = 0;j < 6;j++)
            G->matrix[i][j] = 0;
    G->matrix[0][1] = 1;
    G->matrix[0][2] = 1;
    G->matrix[0][3] = 1;
    G->matrix[2][1] = 1;
    G->matrix[2][4] = 1;
    G->matrix[3][4] = 1;
    G->matrix[5][3] = 1;
    G->matrix[5][4] = 1;
    findInDegree(G);
    return 0;
}
int topologicalSort(Graph *G)
{
    stack *S = (stack*)malloc(sizeof(stack));
    initStack(S);
    for(int i = 0;i < 6;i++)//将入度为0的元素入栈    
        if(G->indegree[i] == 0)
            push(S,i);      
    while(S->base + 1 != S->top)
    {
        int v = pop(S);//取出栈顶元素
        printf("%d,",v+1);
        for(int i = 0;i < 6;i++)//将其邻接顶点的入度减一    
            if(G->matrix[v][i] == 1)           
                if(--G->indegree[i] == 0)//若入度等于0则入栈              
                    push(S,i);                          
    }   
    return 0;
}
int findInDegree(Graph *G)
{
    for(int i = 0;i < 6;i++)
        G->indegree[i] = 0;
    for(int i = 0;i < 6;i++)   
        for(int j = 0;j < 6;j++)    
            if(G->matrix[i][j] > 0)
                G->indegree[j]++;
    return 0;
}
int initStack(stack *S)
{
    S->base = (int*)malloc(6*sizeof(int));
    S->top = S->base + 1;
    return 0;
}
int push(stack *S,int e)
{
    *(S->top++) = e;
    return 0;
}
int pop(stack *S)
{
    return *(--S->top);
}