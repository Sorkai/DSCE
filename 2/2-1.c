#include <stdio.h>
#include <stdlib.h>

// 将栈元素的数据类型定义为 char 型
typedef char DataType;

// 定义链栈的节点结构
typedef struct Node
{
    DataType data;
    struct Node *next;
} Node;

// 函数原型声明
void InitStack(Node **top);
int Empty(Node *top);
void Push(Node **top, DataType x);
int Pop(Node **top, DataType *ptr);
int GetTop(Node *top, DataType *ptr);
void DestroyStack(Node **top);

int main(void)
{
    Node *top = NULL; // 定义链栈的栈顶指针，必须初始化为 NULL
    DataType x;       // 用于存储操作数据的变量
    int choice;       // 用于存储用户菜单选择
    int running = 1;  // 控制主循环的标志

    InitStack(&top); // 初始化链栈
    printf("链栈初始化完成。\n");

    while (running)
    {
        // 显示操作菜单
        printf("\n====== 链栈操作菜单 ======\n");
        printf("1. 入栈 (Push)\n");
        printf("2. 出栈 (Pop)\n");
        printf("3. 获取栈顶元素 (GetTop)\n");
        printf("4. 判断栈是否为空 (Empty)\n");
        printf("5. 销毁链栈 (DestroyStack)\n");
        printf("0. 退出程序\n");
        printf("=========================\n");
        printf("请输入操作编号: ");

        // 获取用户选择，并进行输入验证
        if (scanf("%d", &choice) != 1)
        {
            printf("输入无效，请输入数字。\n");
            // 清除输入缓冲区中的无效输入
            while (getchar() != '\n')
                ;     // 读取并丢弃缓冲区中的剩余字符，直到遇到换行符
            continue; // 继续下一次循环，重新显示菜单
        }

        // 根据用户选择执行相应操作
        switch (choice)
        {
        case 1:
            printf("请输入要入栈的字符: ");
            // 读取字符，注意 scanf " %c" 前的空格可以消耗掉上一次输入（如数字编号）后的换行符
            while (scanf(" %c", &x) != 1)
            { // 注意是 " %c"
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
            DestroyStack(&top); // 销毁栈
            // 销毁后，如果不是要退出，可能需要重新初始化才能继续使用
            // printf("栈已销毁。如果需要继续操作，请考虑重新初始化或退出。\n"); // 可选的更详细提示
            break;
        case 0:
            running = 0;        // 设置循环结束标志
            DestroyStack(&top); // 退出前确保销毁栈，释放内存
            printf("程序已退出。\n");
            break;
        default:
            printf("无效的操作编号，请重新输入。\n");
        }
    }

    return 0; // 程序正常结束
}

/**
 * @brief 初始化链栈
 * @param top 指向栈顶指针的指针 (Node **top)
 */
void InitStack(Node **top)
{
    *top = NULL;
}

/**
 * @brief 判断链栈是否为空
 * @param top 栈顶指针 (Node *top)
 * @return int 如果栈为空返回 1，否则返回 0
 */
int Empty(Node *top)
{
    return (top == NULL);
}

/**
 * @brief 入栈操作 (Push)
 * @param top 指向栈顶指针的指针 (Node **top)
 * @param x   要入栈的元素值 (DataType x)
 */
void Push(Node **top, DataType x)
{
    Node *s = (Node *)malloc(sizeof(Node));
    if (s == NULL)
    {
        printf("内存分配失败，无法入栈\n"); // 对应上溢情况
        exit(EXIT_FAILURE);                 // 发生严重错误，退出程序
    }
    s->data = x;
    s->next = *top;
    *top = s;
}

/**
 * @brief 出栈操作 (Pop)
 * @param top 指向栈顶指针的指针 (Node **top)
 * @param ptr 用于接收出栈元素值的指针 (DataType *ptr)
 * @return int 如果出栈成功返回 1，如果栈为空（下溢）返回 0
 */
int Pop(Node **top, DataType *ptr)
{
    if (Empty(*top))
    {
        // 修改点：严格按照指导书的错误提示文本
        printf("下溢错误,删除失败\n"); // 指导书P2示例："下溢错误,删除失败\n"
        return 0;
    }
    Node *p = *top;
    *ptr = p->data;
    *top = (*top)->next;
    free(p);
    p = NULL; // 良好的编程习惯，避免悬挂指针
    return 1;
}

/**
 * @brief 获取栈顶元素 (GetTop)
 * @param top 栈顶指针 (Node *top)
 * @param ptr 用于接收栈顶元素值的指针 (DataType *ptr)
 * @return int 如果获取成功返回 1，如果栈为空（下溢）返回 0
 */
int GetTop(Node *top, DataType *ptr)
{
    if (Empty(top))
    {
        // 修改点：严格按照指导书的错误提示文本
        printf("下溢错误,取栈顶失败\n"); // 指导书P2示例："下溢错误,取栈顶失败\n"
        return 0;
    }
    *ptr = top->data;
    return 1;
}

/**
 * @brief 销毁链栈
 * @param top 指向栈顶指针的指针 (Node **top)
 * @description 释放链栈中所有节点的内存
 */
void DestroyStack(Node **top)
{
    Node *p = *top;
    Node *q;
    int initiallyEmpty = (*top == NULL); // 检查销毁前是否为空

    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    *top = NULL;

    // 根据栈在销毁前是否为空给出不同提示，更友好
    if (!initiallyEmpty)
    {
        printf("链栈已销毁。\n");
    }
    else
    {
        // 如果栈在调用DestroyStack时就已经是空的
        printf("栈已为空或之前已被销毁。\n");
    }
}
