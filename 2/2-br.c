#include <stdio.h>
#include <stdlib.h>

// 链栈结点定义
typedef struct StackNode
{
    int data;
    struct StackNode *next;
} StackNode, *LinkStack;

// 初始化空栈
void InitStack(LinkStack *top)
{
    *top = NULL;
}

// 入栈
void Push(LinkStack *top, int x)
{
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->data = x;
    p->next = *top;
    *top = p;
}

// 出栈
int Pop(LinkStack *top, int *x)
{
    if (*top == NULL)
        return 0; // 空栈
    StackNode *p = *top;
    *x = p->data;
    *top = p->next;
    free(p);
    return 1;
}

// 取栈顶元素
int GetTop(LinkStack top, int *x)
{
    if (top == NULL)
        return 0;
    *x = top->data;
    return 1;
}

// 判断栈空
int StackEmpty(LinkStack top)
{
    return top == NULL;
}

// 测试主函数
int main()
{
    LinkStack S;
    int x;
    InitStack(&S);

    printf("入栈：1 2 3\n");
    Push(&S, 1);
    Push(&S, 2);
    Push(&S, 3);

    if (GetTop(S, &x))
        printf("栈顶元素：%d\n", x);

    printf("出栈：");
    while (Pop(&S, &x))
    {
        printf("%d ", x);
    }
    printf("\n");

    if (StackEmpty(S))
        printf("栈已空\n");
    getchar();
    return 0;
}