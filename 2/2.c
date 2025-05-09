#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct Node
{
    DataType data;
    struct Node *next;
} Node;

void InitStack(Node **top);
int Empty(Node *top);
void Push(Node **top, DataType x);
int Pop(Node **top, DataType *ptr);
int GetTop(Node *top, DataType *ptr);
void DestroyStack(Node **top);

int main(void)
{
    Node *top = NULL;
    DataType x;
    int choice;
    int running = 1;

    InitStack(&top);
    printf("链栈初始化完成。\n");

    while (running)
    {
        printf("\n====== 链栈的实现 ======\n");
        printf("1. 入栈\n");
        printf("2. 出栈\n");
        printf("3. 获取栈顶元素\n");
        printf("4. 判断栈是否为空\n");
        printf("5. 销毁链栈\n");
        printf("0. 退出程序\n");
        printf("========================\n");
        printf("请输入操作编号: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("输入无效，请输入数字。\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("请输入要入栈的字符: ");
            while (scanf(" %c", &x) != 1)
            {
                printf("输入无效，请输入一个字符: ");
                while (getchar() != '\n')
                    ;
            }
            Push(&top, x);
            printf("元素 '%c' 已入栈。\n", x);
            break;
        case 2:
            if (Pop(&top, &x))
            {
                printf("出栈元素: '%c'\n", x);
            }
            break;
        case 3:
            if (GetTop(top, &x))
            {
                printf("当前栈顶元素为: '%c'\n", x);
            }
            break;
        case 4:
            if (Empty(top))
            {
                printf("栈为空\n");
            }
            else
            {
                printf("栈非空\n");
            }
            break;
        case 5:
            DestroyStack(&top);
            break;
        case 0:
            running = 0;
            DestroyStack(&top);
            printf("程序已退出。\n");
            break;
        default:
            printf("无效的操作编号，请重新输入。\n");
        }
    }

    return 0;
}

void InitStack(Node **top)
{
    *top = NULL;
}

int Empty(Node *top)
{
    return (top == NULL);
}

void Push(Node **top, DataType x)
{
    Node *s = (Node *)malloc(sizeof(Node));
    if (s == NULL)
    {
        printf("内存分配失败，无法入栈\n");
        exit(EXIT_FAILURE);
    }
    s->data = x;
    s->next = *top;
    *top = s;
}

int Pop(Node **top, DataType *ptr)
{
    if (Empty(*top))
    {
        printf("下溢错误,删除失败\n");
        return 0;
    }
    Node *p = *top;
    *ptr = p->data;
    *top = (*top)->next;
    free(p);
    p = NULL;
    return 1;
}

int GetTop(Node *top, DataType *ptr)
{
    if (Empty(top))
    {
        printf("下溢错误,取栈顶失败\n");
        return 0;
    }
    *ptr = top->data;
    return 1;
}

void DestroyStack(Node **top)
{
    Node *p = *top;
    Node *q;
    int initiallyEmpty = (*top == NULL);

    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    *top = NULL;

    if (!initiallyEmpty)
    {
        printf("链栈已销毁。\n");
    }
    else
    {
        printf("栈已为空或之前已被销毁。\n");
    }
}
