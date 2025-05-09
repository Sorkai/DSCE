#include <stdio.h>
#include <stdlib.h> // For malloc, NULL, exit, EXIT_FAILURE

// 定义二叉树节点的数据类型
typedef char DataType;

// 定义二叉树节点结构体
typedef struct BiNode
{
    DataType data;                  // 节点数据
    struct BiNode *lchild, *rchild; // 指向左右子节点的指针
} BiNode;

// 假设队列的最大容量，根据实际需要调整
// 对于层序遍历，队列最多可能需要存储树中最宽一层的节点数
#define MAX_QUEUE_SIZE 100

// 函数声明
BiNode *CreatBiTree();
void PreOrder(BiNode *root);
void LevelOrder(BiNode *root); // 新增层序遍历函数声明
void FreeBiTree(BiNode *root);

/**
 * @brief 根据前序遍历序列创建二叉树
 * @details 用户输入字符序列，'#'表示空节点
 * @return BiNode* 返回创建的树的根节点指针
 */
BiNode *CreatBiTree()
{
    char ch;
    // 注意：scanf前面的空格可以帮助忽略前一次输入残余的换行符等空白字符
    if (scanf(" %c", &ch) != 1)
    { // 从标准输入读取一个字符
        fprintf(stderr, "输入错误！\n");
        return NULL;
    }

    if (ch == '#')
    {
        return NULL; // 如果是'#', 表示空树或子树结束，返回NULL
    }
    else
    {
        BiNode *root = (BiNode *)malloc(sizeof(BiNode)); // 为新节点分配内存
        if (root == NULL)
        {
            fprintf(stderr, "内存分配失败！\n");
            exit(EXIT_FAILURE); // 退出程序
        }
        root->data = ch;              // 设置新节点的数据域
        root->lchild = CreatBiTree(); // 递归创建左子树
        root->rchild = CreatBiTree(); // 递归创建右子树
        return root;                  // 返回当前子树的根节点
    }
}

/**
 * @brief 前序遍历二叉树并打印节点数据
 * @param root BiNode* 要遍历的二叉树的根节点
 */
void PreOrder(BiNode *root)
{
    if (root == NULL)
    {
        return; // 递归调用的结束条件：如果节点为空，则返回
    }
    else
    {
        printf("%c ", root->data); // 访问并打印根节点的数据域
        PreOrder(root->lchild);    // 前序递归遍历左子树
        PreOrder(root->rchild);    // 前序递归遍历右子树
    }
}

/**
 * @brief 层序遍历二叉树并打印节点数据
 * @param root BiNode* 要遍历的二叉树的根节点
 */
void LevelOrder(BiNode *root)
{
    if (root == NULL)
    {
        printf("树为空，无法进行层序遍历。\n");
        return;
    }

    BiNode *queue[MAX_QUEUE_SIZE]; // 定义一个指针数组作为队列
    int front = 0;                 // 队头索引
    int rear = 0;                  // 队尾索引（指向下一个可插入位置）

    // 根节点入队
    if (rear < MAX_QUEUE_SIZE)
    {
        queue[rear++] = root;
    }
    else
    {
        fprintf(stderr, "队列已满，无法将根节点入队。\n");
        return;
    }

    while (front != rear)
    {                                         // 当队列不为空时
        BiNode *currentNode = queue[front++]; // 队首元素出队
        printf("%c ", currentNode->data);     // 访问当前节点

        // 如果当前节点有左孩子，则左孩子入队
        if (currentNode->lchild != NULL)
        {
            if (rear < MAX_QUEUE_SIZE)
            {
                queue[rear++] = currentNode->lchild;
            }
            else
            {
                fprintf(stderr, "队列已满，无法将左孩子入队 (节点数据: %c)。\n", currentNode->lchild->data);
                // 可以选择在这里返回，或者继续处理队列中剩余的元素直到队列满
                // 为简单起见，这里继续，但后续入队会失败
            }
        }

        // 如果当前节点有右孩子，则右孩子入队
        if (currentNode->rchild != NULL)
        {
            if (rear < MAX_QUEUE_SIZE)
            {
                queue[rear++] = currentNode->rchild;
            }
            else
            {
                fprintf(stderr, "队列已满，无法将右孩子入队 (节点数据: %c)。\n", currentNode->rchild->data);
            }
        }
    }
}

/**
 * @brief 释放二叉树占用的内存（后序遍历方式释放）
 * @param root BiNode* 要释放的二叉树的根节点
 */
void FreeBiTree(BiNode *root)
{
    if (root == NULL)
    {
        return;
    }
    FreeBiTree(root->lchild); // 递归释放左子树
    FreeBiTree(root->rchild); // 递归释放右子树
    free(root);               // 释放当前节点
}

// 主函数
int main()
{
    BiNode *root = NULL; // 定义二叉树的根指针变量，并初始化为NULL

    printf("请按照前序遍历顺序输入二叉树节点数据 ('#'表示空节点):\n");
    printf("例如: ABD##E##CF#G### (对于树 A(B(D,E),C(null,F(G))))\n");
    printf("输入: ");
    root = CreatBiTree(); // 调用函数建立一棵二叉树

    if (root != NULL)
    {
        printf("\n该二叉树的根结点是: %c\n", root->data);

        printf("\n该二叉树的前序遍历序列是: ");
        PreOrder(root);
        printf("\n");

        printf("\n该二叉树的层序遍历序列是: ");
        LevelOrder(root);
        printf("\n");
    }
    else
    {
        printf("创建的二叉树为空。\n");
    }

    FreeBiTree(root); // 释放二叉树占用的内存
    root = NULL;      // 将root置为NULL，避免悬挂指针

    return 0;
}
