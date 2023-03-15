/**
 * @file stack.c
 * @author He Wang
 * @brief 复习数据结构 栈代码
 * @date 2023-03-04
 */
#include <stdio.h>
#include <malloc.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct//定义栈
{
    int *base;
    int *top;
    int stacksize;
}SqStack;

/*初始化栈
*/
int InitStack(SqStack *S);
/*判断栈是否为空
*/
int IsEmpty(SqStack *S);
/*获取栈顶元素
*/
int GetTop(SqStack *S,int *e);
/*向栈中插入元素
*/
int Push(SqStack *S,int e);
/*删除栈顶元素
*/
int Pop(SqStack *S,int *e);
/*进制转换
*/
void conversion(int e);
/*清除栈
*/
void ClearStack(SqStack *S);
/*行编辑
*/
void LineEdit();

int main()
{
    SqStack *S = (SqStack*)malloc(sizeof(SqStack));
    InitStack(S);
    for(int i = 0;i < 10;i++)
    {
        Push(S,i+1);
        int e = 0;
        GetTop(S,&e);
        printf("%d,",e);
    }
    printf("\n");
    conversion(1348);
    printf("\n");
    LineEdit();
    return 0;
}

int InitStack(SqStack *S)
{
    S->base = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return 0;
}
int IsEmpty(SqStack *S)
{
    if(S->base == S->top)
        return 1;
    else
        return 0;
}
int GetTop(SqStack *S,int *e)
{
    if(S->base == S->top)
        return -1;
    *e = *(S->top - 1);
    return 0;
}
int Push(SqStack *S,int e)
{
    if(S->top - S->base >= S->stacksize)
    {
        S->base = (int*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(int));
        S->top = S->base + S->stacksize;
    }
    *(S->top) = e;
    S->top++;
    S->stacksize += STACKINCREMENT;
    return 0;
}
int Pop(SqStack *S,int *e)
{
    if(S->base == S->top)
        return -1;
    *e = *(S->top - 1);
    S->top--;
    return 0;
}
void conversion(int e)
{
    SqStack *S = (SqStack*)malloc(sizeof(SqStack));
    InitStack(S);
    while(e)
    {
        Push(S,e % 8);
        e = e / 8;
    }
    int n = 0;
    while(!IsEmpty(S))
    {
        Pop(S,&n);
        printf("%d",n);
    }
}
void ClearStack(SqStack *S)
{
    int e = 0;
    while (!IsEmpty(S))
    {
        Pop(S,&e);
    }
    
}
void LineEdit()
{
    SqStack *line = (SqStack*)malloc(sizeof(SqStack));
    InitStack(line);
    char ch = 'a';
    scanf("%c",&ch);
    while (ch != '!')
    {
        if(ch == '#')
        {
            int e = 0;
            Pop(line,&e);
        }else if (ch == '@')
        {
            ClearStack(line);
        }else{
            Push(line,ch);
        }
        scanf("%c",&ch);
    }
    SqStack *tl = (SqStack*)malloc(sizeof(SqStack));
    InitStack(tl);
    while (!IsEmpty(line))
    {
        int e = 0;
        Pop(line,&e);
        Push(tl,e);
    }
    while (!IsEmpty(tl))
    {
        int e = 0;
        Pop(tl,&e);
        printf("%c,",e);
    }
    
}