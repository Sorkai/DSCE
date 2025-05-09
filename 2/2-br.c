#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct Node
{
    DataType data;
    struct Node *next;
} Node;

void InitStack(Node **top)
{
    *top = NULL;
}

void Push(Node **top, DataType x)
{
    Node *s = (Node *)malloc(sizeof(Node));
    if (s == NULL)
    {
        printf("内存分配失败，无法入栈\n");
        return;
    }
    s->data = x;
    s->next = *top;
    *top = s;
}

int Pop(Node **top, DataType *ptr_x)
{
    Node *p;
    if (*top == NULL)
    {
        printf("栈空警告：出栈失败 (Stack Underflow)\n");
        return 0;
    }
    p = *top;
    *ptr_x = p->data;
    *top = (*top)->next;
    free(p);
    return 1;
}

int GetTop(Node *top, DataType *ptr_x)
{
    if (top == NULL)
    {
        printf("栈空警告：获取栈顶元素失败 (Stack Underflow)\n");
        return 0;
    }
    *ptr_x = top->data;
    return 1;
}

int IsEmpty(Node *top)
{
    if (top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void DestroyStack(Node **top)
{
    Node *p = *top;
    Node *q;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    *top = NULL;
    printf("栈已销毁\n");
}

int main()
{
    Node *top;
    DataType x;

    InitStack(&top);

    printf("栈初始化完成。\n");

    if (IsEmpty(top))
    {
        printf("当前栈为空。\n");
    }
    else
    {
        printf("当前栈不为空。\n");
    }

    printf("\n尝试从空栈中获取栈顶元素：\n");
    if (GetTop(top, &x))
    {
        printf("栈顶元素为: %c\n", x);
    }

    printf("\n尝试从空栈中弹出元素：\n");
    if (Pop(&top, &x))
    {
        printf("弹出元素: %c\n", x);
    }

    printf("\n对 'A', 'B', 'C' 执行入栈操作。\n");
    Push(&top, 'A');
    Push(&top, 'B');
    Push(&top, 'C');

    if (IsEmpty(top))
    {
        printf("当前栈为空。\n");
    }
    else
    {
        printf("当前栈不为空。\n");
    }

    if (GetTop(top, &x))
    {
        printf("当前栈顶元素为: %c\n", x);
    }

    printf("\n执行一次出栈操作。\n");
    if (Pop(&top, &x))
    {
        printf("弹出元素: %c\n", x);
    }

    if (GetTop(top, &x))
    {
        printf("当前栈顶元素为: %c\n", x);
    }

    printf("\n执行一次出栈操作。\n");
    if (Pop(&top, &x))
    {
        printf("弹出元素: %c\n", x);
    }

    if (GetTop(top, &x))
    {
        printf("当前栈顶元素为: %c\n", x);
    }

    printf("\n请输入一个待插入栈的字符元素: ");
    scanf(" %c", &x);
    Push(&top, x);

    if (GetTop(top, &x))
    {
        printf("当前栈顶元素为: %c\n", x);
    }

    printf("\n销毁栈...\n");
    DestroyStack(&top);

    if (IsEmpty(top))
    {
        printf("当前栈为空。\n");
    }
    else
    {
        printf("当前栈不为空。\n");
    }

    printf("\n尝试从已销毁的栈中获取栈顶元素：\n");
    if (GetTop(top, &x))
    {
        printf("栈顶元素为: %c\n", x);
    }

    printf("\n尝试从已销毁的栈中弹出元素：\n");
    if (Pop(&top, &x))
    {
        printf("弹出元素: %c\n", x);
    }

    return 0;
}
