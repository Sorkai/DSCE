#include <stdio.h>
#include <stdlib.h>

typedef char DataType;

typedef struct BiNode
{
    DataType data;
    struct BiNode *lchild, *rchild;
} BiNode;

#define MAX_QUEUE_SIZE 100

BiNode *CreatBiTree();
void PreOrder(BiNode *root);
void LevelOrder(BiNode *root);
void FreeBiTree(BiNode *root);

BiNode *CreatBiTree()
{
    char ch;
    if (scanf(" %c", &ch) != 1)
    {
        fprintf(stderr, "输入错误！\n");
        return NULL;
    }

    if (ch == '#')
    {
        return NULL;
    }
    else
    {
        BiNode *root = (BiNode *)malloc(sizeof(BiNode));
        if (root == NULL)
        {
            fprintf(stderr, "内存分配失败！\n");
            exit(EXIT_FAILURE);
        }
        root->data = ch;
        root->lchild = CreatBiTree();
        root->rchild = CreatBiTree();
        return root;
    }
}

void PreOrder(BiNode *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        printf("%c ", root->data);
        PreOrder(root->lchild);
        PreOrder(root->rchild);
    }
}

void LevelOrder(BiNode *root)
{
    if (root == NULL)
    {
        printf("树为空，无法进行层序遍历。\n");
        return;
    }

    BiNode *queue[MAX_QUEUE_SIZE];
    int front = 0;
    int rear = 0;

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
    {
        BiNode *currentNode = queue[front++];
        printf("%c ", currentNode->data);

        if (currentNode->lchild != NULL)
        {
            if (rear < MAX_QUEUE_SIZE)
            {
                queue[rear++] = currentNode->lchild;
            }
            else
            {
                fprintf(stderr, "队列已满，无法将左孩子入队 (节点数据: %c)。\n", currentNode->lchild->data);
            }
        }

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

void FreeBiTree(BiNode *root)
{
    if (root == NULL)
    {
        return;
    }
    FreeBiTree(root->lchild);
    FreeBiTree(root->rchild);
    free(root);
}

int main()
{
    BiNode *root = NULL;

    printf("请按照前序遍历顺序输入二叉树节点数据 ('#'表示空节点):\n");
    printf("例如: ABD##E##CF#G### (对于树 A(B(D,E),C(null,F(G))))\n");
    printf("输入: ");
    root = CreatBiTree();

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

    FreeBiTree(root);
    root = NULL;

    return 0;
}
