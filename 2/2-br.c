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
        printf("�ڴ����ʧ�ܣ��޷���ջ\n");
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
        printf("ջ�վ��棺��ջʧ�� (Stack Underflow)\n");
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
        printf("ջ�վ��棺��ȡջ��Ԫ��ʧ�� (Stack Underflow)\n");
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
    printf("ջ������\n");
}

int main()
{
    Node *top;
    DataType x;

    InitStack(&top);

    printf("ջ��ʼ����ɡ�\n");

    if (IsEmpty(top))
    {
        printf("��ǰջΪ�ա�\n");
    }
    else
    {
        printf("��ǰջ��Ϊ�ա�\n");
    }

    printf("\n���Դӿ�ջ�л�ȡջ��Ԫ�أ�\n");
    if (GetTop(top, &x))
    {
        printf("ջ��Ԫ��Ϊ: %c\n", x);
    }

    printf("\n���Դӿ�ջ�е���Ԫ�أ�\n");
    if (Pop(&top, &x))
    {
        printf("����Ԫ��: %c\n", x);
    }

    printf("\n�� 'A', 'B', 'C' ִ����ջ������\n");
    Push(&top, 'A');
    Push(&top, 'B');
    Push(&top, 'C');

    if (IsEmpty(top))
    {
        printf("��ǰջΪ�ա�\n");
    }
    else
    {
        printf("��ǰջ��Ϊ�ա�\n");
    }

    if (GetTop(top, &x))
    {
        printf("��ǰջ��Ԫ��Ϊ: %c\n", x);
    }

    printf("\nִ��һ�γ�ջ������\n");
    if (Pop(&top, &x))
    {
        printf("����Ԫ��: %c\n", x);
    }

    if (GetTop(top, &x))
    {
        printf("��ǰջ��Ԫ��Ϊ: %c\n", x);
    }

    printf("\nִ��һ�γ�ջ������\n");
    if (Pop(&top, &x))
    {
        printf("����Ԫ��: %c\n", x);
    }

    if (GetTop(top, &x))
    {
        printf("��ǰջ��Ԫ��Ϊ: %c\n", x);
    }

    printf("\n������һ��������ջ���ַ�Ԫ��: ");
    scanf(" %c", &x);
    Push(&top, x);

    if (GetTop(top, &x))
    {
        printf("��ǰջ��Ԫ��Ϊ: %c\n", x);
    }

    printf("\n����ջ...\n");
    DestroyStack(&top);

    if (IsEmpty(top))
    {
        printf("��ǰջΪ�ա�\n");
    }
    else
    {
        printf("��ǰջ��Ϊ�ա�\n");
    }

    printf("\n���Դ������ٵ�ջ�л�ȡջ��Ԫ�أ�\n");
    if (GetTop(top, &x))
    {
        printf("ջ��Ԫ��Ϊ: %c\n", x);
    }

    printf("\n���Դ������ٵ�ջ�е���Ԫ�أ�\n");
    if (Pop(&top, &x))
    {
        printf("����Ԫ��: %c\n", x);
    }

    return 0;
}
