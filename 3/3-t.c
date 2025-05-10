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
void InOrder(BiNode *root);
void PostOrder(BiNode *root);
void FreeBiTree(BiNode *root);

int main()
{
    BiNode *root = NULL;

    printf("按照前序遍历顺序输入二叉树节点数据 ('#'表示空节点):\n");
    // ABCD####E#FGH####
    // ABD##E##CF#G###
    // ABD###CEG###F##
    printf("输入: ");
    root = CreatBiTree();

    if (root != NULL)
    {
        printf("\n该二叉树的根结点是: %c\n", root->data);

        printf("\n该二叉树的前序遍历序列是: ");
        PreOrder(root);
        printf("\n");

        printf("\n该二叉树的中序遍历序列是: ");
        InOrder(root);
        printf("\n");

        printf("\n该二叉树的后序遍历序列是: ");
        PostOrder(root);
        printf("\n");
    }
    else
    {
        printf("创建的二叉树为空。\n");
    }

    FreeBiTree(root);
    root = NULL;
    getchar();
    getchar();

    return 0;
}

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

void InOrder(BiNode *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        InOrder(root->lchild);
        printf("%c ", root->data);
        InOrder(root->rchild);
    }
}

void PostOrder(BiNode *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        printf("%c ", root->data);
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
