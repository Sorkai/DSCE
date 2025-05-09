#include <stdio.h>
#include <stdlib.h>

// ��ջ��㶨��
typedef struct StackNode
{
    int data;
    struct StackNode *next;
} StackNode, *LinkStack;

// ��ʼ����ջ
void InitStack(LinkStack *top)
{
    *top = NULL;
}

// ��ջ
void Push(LinkStack *top, int x)
{
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->data = x;
    p->next = *top;
    *top = p;
}

// ��ջ
int Pop(LinkStack *top, int *x)
{
    if (*top == NULL)
        return 0; // ��ջ
    StackNode *p = *top;
    *x = p->data;
    *top = p->next;
    free(p);
    return 1;
}

// ȡջ��Ԫ��
int GetTop(LinkStack top, int *x)
{
    if (top == NULL)
        return 0;
    *x = top->data;
    return 1;
}

// �ж�ջ��
int StackEmpty(LinkStack top)
{
    return top == NULL;
}

// ����������
int main()
{
    LinkStack S;
    int x;
    InitStack(&S);

    printf("��ջ��1 2 3\n");
    Push(&S, 1);
    Push(&S, 2);
    Push(&S, 3);

    if (GetTop(S, &x))
        printf("ջ��Ԫ�أ�%d\n", x);

    printf("��ջ��");
    while (Pop(&S, &x))
    {
        printf("%d ", x);
    }
    printf("\n");

    if (StackEmpty(S))
        printf("ջ�ѿ�\n");
    getchar();
    return 0;
}