#include <stdio.h>
#include <stdlib.h> // 如果需要 exit() 函数则包含, 但在此处并非严格必需
#include <time.h>   // 新增头文件, 用于随机数

// 定义顺序表的最大容量
#define MaxSize 100

// 定义顺序表元素的数据类型 (这里假设为 int)
typedef int DataType;

// 定义顺序表的结构体
typedef struct
{
    DataType data[MaxSize]; // 存放数据元素的数组
    int length;             // 顺序表的当前长度
} SeqList;

/**
 * @brief 从数组创建顺序表。
 * @param L 指向 SeqList 结构体的指针。
 * @param a 包含初始数据的数组。
 * @param n 数组 'a' 中的元素个数。
 * @return 如果成功返回 1, 如果数组大小超过 MaxSize 返回 0。
 */
int CreateList(SeqList *L, DataType a[], int n)
{
    // 检查初始大小是否超过最大允许容量
    if (n > MaxSize)
    {
        printf("顺序表的空间不够,无法建立顺序表\n"); // 空间不足
        return 0;                                    // 表示失败
    }
    // 将数组 'a' 中的元素复制到列表 'L'
    for (int i = 0; i < n; i++)
    {
        L->data[i] = a[i];
    }
    // 设置列表的当前长度
    L->length = n;
    return 1; // 表示成功
}

/**
 * @brief 打印顺序表的元素。
 * @param L 指向 SeqList 结构体的指针。
 */
void PrintList(SeqList *L)
{
    // 遍历列表并打印每个元素
    for (int i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n"); // 在末尾打印一个换行符
}

/**
 * @brief 获取顺序表的当前长度。
 * @param L 指向 SeqList 结构体的指针。
 * @return 列表的当前长度。
 */
int Length(SeqList *L)
{
    return L->length;
}

/**
 * @brief 查找给定元素 'x' 在列表中的位置 (序号, 从1开始)。
 * @param L 指向 SeqList 结构体的指针。
 * @param x 要搜索的元素。
 * @return 如果找到元素, 返回其基于 1 的位置, 否则返回 0。
 */
int Locate(SeqList *L, DataType x)
{
    // 遍历列表以查找元素
    for (int i = 0; i < L->length; i++)
    {
        // 如果找到元素, 返回其基于 1 的位置
        if (L->data[i] == x)
        {
            return i + 1;
        }
    }
    return 0; // 未找到元素
}

/**
 * @brief 获取指定位置 'i' (基于 1 的索引) 的元素。
 * @param L 指向 SeqList 结构体的指针。
 * @param i 要检索的元素的基于 1 的位置。
 * @param ptr 用于存储检索到的元素的指针。
 * @return 如果成功返回 1, 如果位置无效返回 0。
 */
int Get(SeqList *L, int i, DataType *ptr)
{
    // 检查位置 'i' 是否有效 (介于 1 和 length 之间)
    if (i < 1 || i > L->length)
    {
        printf("位置错误,获取失败\n"); // 位置错误
        return 0;                      // 表示失败
    }
    // 检索元素并将其存储在 'ptr' 指向的位置
    *ptr = L->data[i - 1]; // 调整为基于 0 的数组索引
    return 1;              // 表示成功
}

/**
 * @brief 在指定位置 'i' (基于 1 的索引) 插入元素 'x'。
 * @param L 指向 SeqList 结构体的指针。
 * @param i 要插入元素的基于 1 的位置。
 * @param x 要插入的元素。
 * @return 如果成功返回 1, 如果列表已满或位置无效返回 0。
 */
int Insert(SeqList *L, int i, DataType x)
{
    // 检查是否溢出 (列表已满)
    if (L->length >= MaxSize)
    {
        printf("上溢错误,插入失败\n"); // 上溢错误
        return 0;                      // 表示失败
    }
    // 检查插入位置 'i' 是否有效 (介于 1 和 length + 1 之间)
    if (i < 1 || i > L->length + 1)
    {
        printf("位置错误,插入失败\n"); // 位置错误
        return 0;                      // 表示失败
    }
    // 移动元素为新元素腾出空间
    // 从末尾开始向插入点移动
    for (int j = L->length; j >= i; j--)
    {
        L->data[j] = L->data[j - 1];
    }
    // 在指定位置插入新元素 (调整为基于 0 的索引)
    L->data[i - 1] = x;
    // 增加列表的长度
    L->length++;
    return 1; // 表示成功
}

/**
 * @brief 删除指定位置 'i' (基于 1 的索引) 的元素。
 * @param L 指向 SeqList 结构体的指针。
 * @param i 要删除的元素的基于 1 的位置。
 * @param ptr 用于存储被删除元素值的指针。
 * @return 如果成功返回 1, 如果列表为空或位置无效返回 0。
 */
int Delete(SeqList *L, int i, DataType *ptr)
{
    // 检查是否下溢 (列表为空)
    if (L->length == 0)
    {
        printf("下溢错误,删除失败\n"); // 下溢错误
        return 0;                      // 表示失败
    }
    // 检查删除位置 'i' 是否有效 (介于 1 和 length 之间)
    if (i < 1 || i > L->length)
    {
        printf("位置错误,删除失败\n"); // 位置错误
        return 0;                      // 表示失败
    }
    // 存储被删除元素的值
    *ptr = L->data[i - 1]; // 调整为基于 0 的索引
    // 移动元素以填补删除元素留下的空缺
    // 从删除点开始向末尾移动
    for (int j = i; j < L->length; j++)
    {
        L->data[j - 1] = L->data[j];
    }
    // 减少列表的长度
    L->length--;
    return 1; // 表示成功
}

// 主函数, 用于演示顺序表操作
int main()
{
    SeqList L;
    int n, i, x, pos;
    DataType r[MaxSize]; // 用于存放随机数据

    srand((unsigned int)time(NULL)); // 初始化随机数种子

    // 随机生成元素个数, 范围为 5-20
    n = rand() % 16 + 5;

    // 随机生成 n 个元素, 范围可自定义, 这里假设为 0-99
    for (i = 0; i < n; i++)
    {
        r[i] = rand() % 100;
    }

    // 使用随机数据创建列表
    if (CreateList(&L, r, n))
    {
        printf("顺序表创建成功。\n");
        printf("当前线性表的数据为: ");
        PrintList(&L);

        int choice;
        while (1)
        {
            printf("\n====== 顺序表操作菜单 ======\n");
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
                // 输入非数字，清空输入缓冲区
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
                // 错误消息在 Delete 函数内部处理
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
                // 错误消息在 Get 函数内部处理
                break;
            case 5:
                printf("当前线性表的数据为: ");
                PrintList(&L);
                break;
            case 6:
                printf("当前线性表的长度为: %d\n", Length(&L));
                break;
            case 0:
                printf("已退出程序。\n");
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

    return 0; // 表示成功执行
}
