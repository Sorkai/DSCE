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
    printf("��ջ��ʼ����ɡ�\n");

    while (running)
    {
        printf("\n====== ��ջ��ʵ�� ======\n");
        printf("1. ��ջ\n");
        printf("2. ��ջ\n");
        printf("3. ��ȡջ��Ԫ��\n");
        printf("4. �ж�ջ�Ƿ�Ϊ��\n");
        printf("5. ������ջ\n");
        printf("0. �˳�����\n");
        printf("========================\n");
        printf("������������: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("������Ч�����������֡�\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("������Ҫ��ջ���ַ�: ");
            while (scanf(" %c", &x) != 1)
            {
                printf("������Ч��������һ���ַ�: ");
                while (getchar() != '\n')
                    ;
            }
            Push(&top, x);
            printf("Ԫ�� '%c' ����ջ��\n", x);
            break;
        case 2:
            if (Pop(&top, &x))
            {
                printf("��ջԪ��: '%c'\n", x);
            }
            break;
        case 3:
            if (GetTop(top, &x))
            {
                printf("��ǰջ��Ԫ��Ϊ: '%c'\n", x);
            }
            break;
        case 4:
            if (Empty(top))
            {
                printf("ջΪ��\n");
            }
            else
            {
                printf("ջ�ǿ�\n");
            }
            break;
        case 5:
            DestroyStack(&top);
            break;
        case 0:
            running = 0;
            DestroyStack(&top);
            printf("�������˳���\n");
            break;
        default:
            printf("��Ч�Ĳ�����ţ����������롣\n");
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
        printf("�ڴ����ʧ�ܣ��޷���ջ\n");
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
        printf("�������,ɾ��ʧ��\n");
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
        printf("�������,ȡջ��ʧ��\n");
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
        printf("��ջ�����١�\n");
    }
    else
    {
        printf("ջ��Ϊ�ջ�֮ǰ�ѱ����١�\n");
    }
}
