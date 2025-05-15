#include <stdio.h>
#include <stdlib.h>

typedef char DataType;
typedef struct BiNode
{
    DataType data;
    struct BiNode *lchild, *rchild;
} BiNode;

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

    BiNode *node = (BiNode *)malloc(sizeof(BiNode));
    if (node == NULL)
    {
        fprintf(stderr, "内存分配失败！\n");
        exit(EXIT_FAILURE);
    }
    node->data = ch;
    node->lchild = CreatBiTree();
    node->rchild = CreatBiTree();
    return node;
}

void PreOrder(BiNode *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%c ", root->data);
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}

void InOrder(BiNode *root)
{
    if (root == NULL)
    {
        return;
    }
    InOrder(root->lchild);
    printf("%c ", root->data);
    InOrder(root->rchild);
}

void PostOrder(BiNode *root)
{
    if (root == NULL)
    {
        return;
    }
    PostOrder(root->lchild);
    PostOrder(root->rchild);
    printf("%c ", root->data);
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

int main(void)
{
    BiNode *root = NULL;

    printf("前序遍历顺序输入二叉树节点 (#表示空节点):\n");
    root = CreatBiTree();

    if (root != NULL)
    {
        printf("\n该二叉树的根结点是: %c\n", root->data);

        printf("\n前序遍历序列: ");
        PreOrder(root);
        printf("\n");

        printf("中序遍历序列: ");
        InOrder(root);
        printf("\n");

        printf("后序遍历序列: ");
        PostOrder(root);
        printf("\n\n");
    }
    else
    {
        printf("二叉树为空。\n");
    }

    FreeBiTree(root);
    root = NULL;

    getchar();
    getchar();
    return 0;
}