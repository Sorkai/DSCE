#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

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
    int choice, running = 1;

    InitStack(&top);
    printf("链栈初始化完成。\n");

    while (running)
    {
        printf("\n====== 链栈操作菜单 ======\n");
        printf("1. 入栈\n");
        printf("2. 出栈\n");
        printf("3. 获取栈顶元素\n");
        printf("4. 判断栈是否为空\n");
        printf("5. 销毁链栈\n");
        printf("0. 退出程序\n");
        printf("=========================\n");
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
            printf("请输入要入栈的整数: ");
            while (scanf("%d", &x) != 1)
            {
                printf("输入无效，请输入一个整数: ");
                while (getchar() != '\n')
                    ;
            }
            Push(&top, x);
            printf("元素 %d 已入栈。\n", x);
            break;
        case 2:
            if (Pop(&top, &x))
                printf("出栈元素: %d\n", x);
            break;
        case 3:
            if (GetTop(top, &x))
                printf("当前栈顶元素为: %d\n", x);
            break;
        case 4:
            if (Empty(top))
                printf("栈为空\n");
            else
                printf("栈非空\n");
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
        exit(1);
    }
    s->data = x;
    s->next = *top;
    *top = s;
}

int Pop(Node **top, DataType *ptr)
{
    if (Empty(*top))
    {
        printf("栈为空（下溢），删除失败\n");
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
        printf("栈为空（下溢），获取栈顶元素失败\n");
        return 0;
    }
    *ptr = top->data;
    return 1;
}

void DestroyStack(Node **top)
{
    Node *p = *top;
    Node *q;
    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    *top = NULL;
    printf("链栈已销毁\n");
}
