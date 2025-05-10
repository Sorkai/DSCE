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

    printf("����ǰ�����˳������������ڵ����� ('#'��ʾ�սڵ�):\n");
    // ABCD####E#FGH####
    // ABD##E##CF#G###
    // ABD###CEG###F##
    printf("����: ");
    root = CreatBiTree();

    if (root != NULL)
    {
        printf("\n�ö������ĸ������: %c\n", root->data);

        printf("\n�ö�������ǰ�����������: ");
        PreOrder(root);
        printf("\n");

        printf("\n�ö��������������������: ");
        InOrder(root);
        printf("\n");

        printf("\n�ö������ĺ������������: ");
        PostOrder(root);
        printf("\n");
    }
    else
    {
        printf("�����Ķ�����Ϊ�ա�\n");
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
        fprintf(stderr, "�������\n");
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
            fprintf(stderr, "�ڴ����ʧ�ܣ�\n");
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
