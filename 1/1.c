#include <stdio.h>
#include <stdlib.h> // �����Ҫ exit() ���������, ���ڴ˴������ϸ����
#include <time.h>   // ����ͷ�ļ�, ���������

// ����˳�����������
#define MaxSize 100

// ����˳���Ԫ�ص��������� (�������Ϊ int)
typedef int DataType;

// ����˳���Ľṹ��
typedef struct
{
    DataType data[MaxSize]; // �������Ԫ�ص�����
    int length;             // ˳���ĵ�ǰ����
} SeqList;

/**
 * @brief �����鴴��˳���
 * @param L ָ�� SeqList �ṹ���ָ�롣
 * @param a ������ʼ���ݵ����顣
 * @param n ���� 'a' �е�Ԫ�ظ�����
 * @return ����ɹ����� 1, ��������С���� MaxSize ���� 0��
 */
int CreateList(SeqList *L, DataType a[], int n)
{
    // ����ʼ��С�Ƿ񳬹������������
    if (n > MaxSize)
    {
        printf("˳���Ŀռ䲻��,�޷�����˳���\n"); // �ռ䲻��
        return 0;                                    // ��ʾʧ��
    }
    // ������ 'a' �е�Ԫ�ظ��Ƶ��б� 'L'
    for (int i = 0; i < n; i++)
    {
        L->data[i] = a[i];
    }
    // �����б�ĵ�ǰ����
    L->length = n;
    return 1; // ��ʾ�ɹ�
}

/**
 * @brief ��ӡ˳����Ԫ�ء�
 * @param L ָ�� SeqList �ṹ���ָ�롣
 */
void PrintList(SeqList *L)
{
    // �����б���ӡÿ��Ԫ��
    for (int i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n"); // ��ĩβ��ӡһ�����з�
}

/**
 * @brief ��ȡ˳���ĵ�ǰ���ȡ�
 * @param L ָ�� SeqList �ṹ���ָ�롣
 * @return �б�ĵ�ǰ���ȡ�
 */
int Length(SeqList *L)
{
    return L->length;
}

/**
 * @brief ���Ҹ���Ԫ�� 'x' ���б��е�λ�� (���, ��1��ʼ)��
 * @param L ָ�� SeqList �ṹ���ָ�롣
 * @param x Ҫ������Ԫ�ء�
 * @return ����ҵ�Ԫ��, ��������� 1 ��λ��, ���򷵻� 0��
 */
int Locate(SeqList *L, DataType x)
{
    // �����б��Բ���Ԫ��
    for (int i = 0; i < L->length; i++)
    {
        // ����ҵ�Ԫ��, ��������� 1 ��λ��
        if (L->data[i] == x)
        {
            return i + 1;
        }
    }
    return 0; // δ�ҵ�Ԫ��
}

/**
 * @brief ��ȡָ��λ�� 'i' (���� 1 ������) ��Ԫ�ء�
 * @param L ָ�� SeqList �ṹ���ָ�롣
 * @param i Ҫ������Ԫ�صĻ��� 1 ��λ�á�
 * @param ptr ���ڴ洢��������Ԫ�ص�ָ�롣
 * @return ����ɹ����� 1, ���λ����Ч���� 0��
 */
int Get(SeqList *L, int i, DataType *ptr)
{
    // ���λ�� 'i' �Ƿ���Ч (���� 1 �� length ֮��)
    if (i < 1 || i > L->length)
    {
        printf("λ�ô���,��ȡʧ��\n"); // λ�ô���
        return 0;                      // ��ʾʧ��
    }
    // ����Ԫ�ز�����洢�� 'ptr' ָ���λ��
    *ptr = L->data[i - 1]; // ����Ϊ���� 0 ����������
    return 1;              // ��ʾ�ɹ�
}

/**
 * @brief ��ָ��λ�� 'i' (���� 1 ������) ����Ԫ�� 'x'��
 * @param L ָ�� SeqList �ṹ���ָ�롣
 * @param i Ҫ����Ԫ�صĻ��� 1 ��λ�á�
 * @param x Ҫ�����Ԫ�ء�
 * @return ����ɹ����� 1, ����б�������λ����Ч���� 0��
 */
int Insert(SeqList *L, int i, DataType x)
{
    // ����Ƿ���� (�б�����)
    if (L->length >= MaxSize)
    {
        printf("�������,����ʧ��\n"); // �������
        return 0;                      // ��ʾʧ��
    }
    // ������λ�� 'i' �Ƿ���Ч (���� 1 �� length + 1 ֮��)
    if (i < 1 || i > L->length + 1)
    {
        printf("λ�ô���,����ʧ��\n"); // λ�ô���
        return 0;                      // ��ʾʧ��
    }
    // �ƶ�Ԫ��Ϊ��Ԫ���ڳ��ռ�
    // ��ĩβ��ʼ�������ƶ�
    for (int j = L->length; j >= i; j--)
    {
        L->data[j] = L->data[j - 1];
    }
    // ��ָ��λ�ò�����Ԫ�� (����Ϊ���� 0 ������)
    L->data[i - 1] = x;
    // �����б�ĳ���
    L->length++;
    return 1; // ��ʾ�ɹ�
}

/**
 * @brief ɾ��ָ��λ�� 'i' (���� 1 ������) ��Ԫ�ء�
 * @param L ָ�� SeqList �ṹ���ָ�롣
 * @param i Ҫɾ����Ԫ�صĻ��� 1 ��λ�á�
 * @param ptr ���ڴ洢��ɾ��Ԫ��ֵ��ָ�롣
 * @return ����ɹ����� 1, ����б�Ϊ�ջ�λ����Ч���� 0��
 */
int Delete(SeqList *L, int i, DataType *ptr)
{
    // ����Ƿ����� (�б�Ϊ��)
    if (L->length == 0)
    {
        printf("�������,ɾ��ʧ��\n"); // �������
        return 0;                      // ��ʾʧ��
    }
    // ���ɾ��λ�� 'i' �Ƿ���Ч (���� 1 �� length ֮��)
    if (i < 1 || i > L->length)
    {
        printf("λ�ô���,ɾ��ʧ��\n"); // λ�ô���
        return 0;                      // ��ʾʧ��
    }
    // �洢��ɾ��Ԫ�ص�ֵ
    *ptr = L->data[i - 1]; // ����Ϊ���� 0 ������
    // �ƶ�Ԫ�����ɾ��Ԫ�����µĿ�ȱ
    // ��ɾ���㿪ʼ��ĩβ�ƶ�
    for (int j = i; j < L->length; j++)
    {
        L->data[j - 1] = L->data[j];
    }
    // �����б�ĳ���
    L->length--;
    return 1; // ��ʾ�ɹ�
}

// ������, ������ʾ˳������
int main()
{
    SeqList L;
    int n, i, x, pos;
    DataType r[MaxSize]; // ���ڴ���������

    srand((unsigned int)time(NULL)); // ��ʼ�����������

    // �������Ԫ�ظ���, ��ΧΪ 5-20
    n = rand() % 16 + 5;

    // ������� n ��Ԫ��, ��Χ���Զ���, �������Ϊ 0-99
    for (i = 0; i < n; i++)
    {
        r[i] = rand() % 100;
    }

    // ʹ��������ݴ����б�
    if (CreateList(&L, r, n))
    {
        printf("˳������ɹ���\n");
        printf("��ǰ���Ա������Ϊ: ");
        PrintList(&L);

        int choice;
        while (1)
        {
            printf("\n====== ˳�������˵� ======\n");
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
                // ��������֣�������뻺����
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
                // ������Ϣ�� Delete �����ڲ�����
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
                // ������Ϣ�� Get �����ڲ�����
                break;
            case 5:
                printf("��ǰ���Ա������Ϊ: ");
                PrintList(&L);
                break;
            case 6:
                printf("��ǰ���Ա�ĳ���Ϊ: %d\n", Length(&L));
                break;
            case 0:
                printf("���˳�����\n");
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

    return 0; // ��ʾ�ɹ�ִ��
}
