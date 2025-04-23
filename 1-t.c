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
        printf("顺序表的空间不够,无法建立顺序表\n");
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
        printf("位置错误,获取失败\n");
        return 0;
    }
    *ptr = L->data[i - 1];
    return 1;
}

int Insert(SeqList *L, int i, DataType x)
{
    if (L->length >= MaxSize)
    {
        printf("上溢错误,插入失败\n");
        return 0;
    }
    if (i < 1 || i > L->length + 1)
    {
        printf("位置错误,插入失败\n");
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
        printf("下溢错误,删除失败\n");
        return 0;
    }
    if (i < 1 || i > L->length)
    {
        printf("位置错误,删除失败\n");
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
        printf("顺序表创建成功。\n");
        printf("当前线性表的数据为: ");
        PrintList(&L);

        int choice;
        while (1)
        {
            printf("\n++++++++ 顺序表实验菜单 ++++++++\n");
            printf("1. 插入元素\n");
            printf("2. 删除元素\n");
            printf("3. 按值查找元素\n");
            printf("4. 按位序查找元素\n");
            printf("5. 打印顺序表\n");
            printf("6. 获取顺序表长度\n");
            printf("0. 退出\n");
            printf("请选择操作(0-6): ");
            if (scanf("%d", &choice) != 1)
            {
                while (getchar() != '\n')
                    ;
                printf("输入无效，请重新选择。\n");
                continue;
            }
            switch (choice)
            {
            case 1:
                printf("请输入要插入的位置(1~%d): ", L.length + 1);
                scanf("%d", &pos);
                printf("请输入要插入的元素: ");
                scanf("%d", &x);
                if (Insert(&L, pos, x))
                {
                    printf("在第 %d 个位置插入 %d 后数据为: ", pos, x);
                    PrintList(&L);
                }
                break;
            case 2:
                printf("请输入要删除的元素序号(1~%d): ", L.length);
                scanf("%d", &pos);
                if (Delete(&L, pos, &x) == 1)
                {
                    printf("删除第 %d 个元素 %d 成功, 删除后数据为: ", pos, x);
                    PrintList(&L);
                }
                break;
            case 3:
                printf("请输入要按值查找的元素: ");
                scanf("%d", &x);
                i = Locate(&L, x);
                if (i == 0)
                {
                    printf("查找失败, 线性表中没有元素 %d\n", x);
                }
                else
                {
                    printf("元素 %d 的位置(序号)为: %d\n", x, i);
                }
                break;
            case 4:
                printf("请输入要按位序查找的元素序号(1~%d): ", L.length);
                scanf("%d", &i);
                if (Get(&L, i, &x) == 1)
                {
                    printf("第 %d 个元素值是 %d\n", i, x);
                }
                break;
            case 5:
                printf("当前线性表的数据为: ");
                PrintList(&L);
                break;
            case 6:
                printf("当前线性表的长度为: %d\n", Length(&L));
                break;
            case 0:
                printf("程序推出。\n");
                return 0;
            default:
                printf("无效的选择，请重新输入。\n");
                break;
            }
        }
    }
    else
    {
        printf("顺序表创建失败。\n");
    }
    return 0;
}
