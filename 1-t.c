#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MaxSize 100
typedef int DataType;
typedef struct
{
    DataType data[MaxSize];
    int length;
} SeqList;

int CreateList(SeqList *L, DataType a[], int n)
{
    if (n > MaxSize)
    {
        printf("˳���Ŀռ䲻��,�޷�����˳���\n");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        L->data[i] = a[i];
    }
    L->length = n;
    return 1;
}

void PrintList(SeqList *L)
{
    for (int i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

int Length(SeqList *L)
{
    return L->length;
}

int Locate(SeqList *L, DataType x)
{
    for (int i = 0; i < L->length; i++)
    {
        if (L->data[i] == x)
        {
            return i + 1;
        }
    }
    return 0;
}

int Get(SeqList *L, int i, DataType *ptr)
{
    if (i < 1 || i > L->length)
    {
        printf("λ�ô���,��ȡʧ��\n");
        return 0;
    }
    *ptr = L->data[i - 1];
    return 1;
}

int Insert(SeqList *L, int i, DataType x)
{
    if (L->length >= MaxSize)
    {
        printf("�������,����ʧ��\n");
        return 0;
    }
    if (i < 1 || i > L->length + 1)
    {
        printf("λ�ô���,����ʧ��\n");
        return 0;
    }
    for (int j = L->length; j >= i; j--)
    {
        L->data[j] = L->data[j - 1];
    }
    L->data[i - 1] = x;
    L->length++;
    return 1;
}

int Delete(SeqList *L, int i, DataType *ptr)
{
    if (L->length == 0)
    {
        printf("�������,ɾ��ʧ��\n");
        return 0;
    }
    if (i < 1 || i > L->length)
    {
        printf("λ�ô���,ɾ��ʧ��\n");
        return 0;
    }
    *ptr = L->data[i - 1];
    for (int j = i; j < L->length; j++)
    {
        L->data[j - 1] = L->data[j];
    }
    L->length--;
    return 1;
}

int main()
{
    SeqList L;
    int n, i, x, pos;
    DataType r[MaxSize];

    srand((unsigned int)time(NULL));
    n = rand() % 16 + 5;
    for (i = 0; i < n; i++)
    {
        r[i] = rand() % 100;
    }
    if (CreateList(&L, r, n))
    {
        printf("˳������ɹ���\n");
        printf("��ǰ���Ա������Ϊ: ");
        PrintList(&L);

        int choice;
        while (1)
        {
            printf("\n++++++++ ˳���ʵ��˵� ++++++++\n");
            printf("1. ����Ԫ��\n");
            printf("2. ɾ��Ԫ��\n");
            printf("3. ��ֵ����Ԫ��\n");
            printf("4. ��λ�����Ԫ��\n");
            printf("5. ��ӡ˳���\n");
            printf("6. ��ȡ˳�����\n");
            printf("0. �˳�\n");
            printf("��ѡ�����(0-6): ");
            if (scanf("%d", &choice) != 1)
            {
                while (getchar() != '\n')
                    ;
                printf("������Ч��������ѡ��\n");
                continue;
            }
            switch (choice)
            {
            case 1:
                printf("������Ҫ�����λ��(1~%d): ", L.length + 1);
                scanf("%d", &pos);
                printf("������Ҫ�����Ԫ��: ");
                scanf("%d", &x);
                if (Insert(&L, pos, x))
                {
                    printf("�ڵ� %d ��λ�ò��� %d ������Ϊ: ", pos, x);
                    PrintList(&L);
                }
                break;
            case 2:
                printf("������Ҫɾ����Ԫ�����(1~%d): ", L.length);
                scanf("%d", &pos);
                if (Delete(&L, pos, &x) == 1)
                {
                    printf("ɾ���� %d ��Ԫ�� %d �ɹ�, ɾ��������Ϊ: ", pos, x);
                    PrintList(&L);
                }
                break;
            case 3:
                printf("������Ҫ��ֵ���ҵ�Ԫ��: ");
                scanf("%d", &x);
                i = Locate(&L, x);
                if (i == 0)
                {
                    printf("����ʧ��, ���Ա���û��Ԫ�� %d\n", x);
                }
                else
                {
                    printf("Ԫ�� %d ��λ��(���)Ϊ: %d\n", x, i);
                }
                break;
            case 4:
                printf("������Ҫ��λ����ҵ�Ԫ�����(1~%d): ", L.length);
                scanf("%d", &i);
                if (Get(&L, i, &x) == 1)
                {
                    printf("�� %d ��Ԫ��ֵ�� %d\n", i, x);
                }
                break;
            case 5:
                printf("��ǰ���Ա������Ϊ: ");
                PrintList(&L);
                break;
            case 6:
                printf("��ǰ���Ա�ĳ���Ϊ: %d\n", Length(&L));
                break;
            case 0:
                printf("�����Ƴ���\n");
                return 0;
            default:
                printf("��Ч��ѡ�����������롣\n");
                break;
            }
        }
    }
    else
    {
        printf("˳�����ʧ�ܡ�\n");
    }
    return 0;
}
