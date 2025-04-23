#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

// 定义链栈的节点结构
typedef struct Node
{
    DataType data;     // 存放栈元素的数据域
    struct Node *next; // 指向下一个节点的指针
} Node;

void InitStack(Node **top);
int Empty(Node *top);
void Push(Node **top, DataType x);
int Pop(Node **top, DataType *ptr);
int GetTop(Node *top, DataType *ptr);
void DestroyStack(Node **top);

int main(void)
{
    Node *top = NULL; // 定义链栈的栈顶指针，必须初始化为 NULL
    DataType x;       // 用于存储出栈或获取的元素值

    // 1. 初始化链栈 (注意传递 top 的地址)
    InitStack(&top);
    printf("链栈初始化完成。\n");

    // 2. 入栈操作
    printf("对 15 和 10 执行入栈操作...\n");
    Push(&top, 15); // 注意传递 top 的地址
    Push(&top, 10); // 注意传递 top 的地址
    printf("入栈操作完成。\n");

    // 3. 获取当前栈顶元素
    if (GetTop(top, &x))
    {                                      // 不需要修改 top，直接传递值
        printf("当前栈顶元素为: %d\n", x); // 应输出 10
    }

    // 4. 出栈操作
    if (Pop(&top, &x))
    {                                                  // 需要修改 top，传递地址
        printf("执行一次出栈操作，删除元素: %d\n", x); // 应输出 10
    }

    // 5. 再次获取栈顶元素
    if (GetTop(top, &x))
    {
        printf("当前栈顶元素为: %d\n", x); // 应输出 15
    }

    // 6. 用户输入元素并入栈
    printf("请输入一个待插入栈的整数元素: ");
    // 添加输入验证，确保用户输入的是整数
    while (scanf("%d", &x) != 1)
    {
        printf("输入无效，请输入一个整数: ");
        // 清除输入缓冲区中的无效输入
        while (getchar() != '\n')
            ;
    }
    Push(&top, x);
    printf("元素 %d 已入栈。\n", x);

    // 7. 再次获取栈顶元素
    if (GetTop(top, &x))
    {
        printf("当前栈顶元素为: %d\n", x); // 输出用户输入的元素
    }

    // 8. 判断栈是否为空
    if (Empty(top))
    { // 不需要修改 top，直接传递值
        printf("栈为空\n");
    }
    else
    {
        printf("栈非空\n"); // 应输出栈非空
    }

    // 9. 尝试对空栈进行 Pop 操作 (测试下溢)
    printf("尝试连续出栈直到栈空...\n");
    while (Pop(&top, &x))
    {
        printf("出栈元素: %d\n", x);
    }
    // 此时栈已空，再次 Pop 会触发下溢
    Pop(&top, &x);
    GetTop(top, &x); // 尝试获取空栈顶元素

    // 10. 销毁链栈 (释放所有节点内存)
    // 注意：虽然上面的循环已经将栈变空，但 DestroyStack 仍然是必要的，
    // 因为它能处理栈在任意状态下的销毁，并且将 top 设为 NULL。
    // 如果栈非空，此函数会释放所有剩余节点。
    DestroyStack(&top); // 需要修改 top，传递地址

    return 0; // 程序正常结束
}

/**
 * @brief 初始化链栈
 *
 * @param top 指向栈顶指针的指针 (Node **top)
 * @description 将栈顶指针设置为 NULL，表示一个空栈
 */
void InitStack(Node **top)
{
    *top = NULL; // 将指针本身（即 main 函数中的 top）设置为 NULL
}

/**
 * @brief 判断链栈是否为空
 *
 * @param top 栈顶指针 (Node *top)
 * @return int 如果栈为空返回 1，否则返回 0
 */
int Empty(Node *top)
{
    return (top == NULL); // 直接判断栈顶指针是否为 NULL
}

/**
 * @brief 入栈操作 (Push)
 *
 * @param top 指向栈顶指针的指针 (Node **top)
 * @param x   要入栈的元素值 (DataType x)
 * @description 创建新节点，将元素 x 存入，并将新节点插入到链栈顶部
 */
void Push(Node **top, DataType x)
{
    // 1. 创建新节点
    Node *s = (Node *)malloc(sizeof(Node));
    // 检查内存分配是否成功
    if (s == NULL)
    {
        printf("内存分配失败，无法入栈\n");
        // 在实际应用中可能需要更健壮的错误处理，例如退出程序
        exit(EXIT_FAILURE); // 或者 return; 根据需求决定
    }

    // 2. 将数据存入新节点
    s->data = x;

    // 3. 将新节点插入到栈顶
    s->next = *top; // 新节点的 next 指向原来的栈顶
    *top = s;       // 更新栈顶指针，使其指向新节点
}

/**
 * @brief 出栈操作 (Pop)
 *
 * @param top 指向栈顶指针的指针 (Node **top)
 * @param ptr 用于接收出栈元素值的指针 (DataType *ptr)
 * @return int 如果出栈成功返回 1，如果栈为空（下溢）返回 0
 * @description 删除栈顶节点，并通过 ptr 返回其元素值
 */
int Pop(Node **top, DataType *ptr)
{
    // 1. 检查栈是否为空 (下溢判断)
    if (Empty(*top))
    { // 等价于 if (*top == NULL)
        printf("栈为空（下溢），删除失败\n");
        return 0; // 返回 0 表示失败
    }

    // 2. 保存栈顶节点指针和数据
    Node *p = *top; // p 指向要删除的栈顶节点
    *ptr = p->data; // 通过指针 ptr 返回栈顶元素的值

    // 3. 更新栈顶指针 (删除节点)
    *top = (*top)->next; // 栈顶指针指向下一个节点

    // 4. 释放原栈顶节点的内存
    free(p);
    p = NULL; // 好习惯：将释放后的指针设为 NULL

    return 1; // 返回 1 表示成功
}

/**
 * @brief 获取栈顶元素 (GetTop)
 *
 * @param top 栈顶指针 (Node *top)
 * @param ptr 用于接收栈顶元素值的指针 (DataType *ptr)
 * @return int 如果获取成功返回 1，如果栈为空（下溢）返回 0
 * @description 读取栈顶元素的值，但不删除节点
 */
int GetTop(Node *top, DataType *ptr)
{
    // 1. 检查栈是否为空 (下溢判断)
    if (Empty(top))
    {
        printf("栈为空（下溢），获取栈顶元素失败\n");
        return 0; // 返回 0 表示失败
    }

    // 2. 通过指针 ptr 返回栈顶元素的值
    *ptr = top->data;

    return 1; // 返回 1 表示成功
}

/**
 * @brief 销毁链栈
 *
 * @param top 指向栈顶指针的指针 (Node **top)
 * @description 释放链栈中所有节点的内存
 */
void DestroyStack(Node **top)
{
    Node *p = *top; // p 用于遍历链栈
    Node *q;        // q 用于临时保存下一个节点，防止断链

    while (p != NULL)
    {
        q = p->next; // 保存下一个节点的指针
        free(p);     // 释放当前节点
        p = q;       // 移动到下一个节点
    }

    *top = NULL; // 最后将栈顶指针设置为 NULL
    printf("链栈已销毁\n");
}
