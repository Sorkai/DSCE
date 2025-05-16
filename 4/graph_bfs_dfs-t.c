#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10

typedef char DataType;

typedef struct
{
    DataType vertex[MaxSize];
    int edge[MaxSize][MaxSize];
    int vertexNum, edgeNum;
} MGraph;

typedef struct
{
    int data[MaxSize];
    int front;
    int rear;
} Queue;

void InitQueue(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

int IsQueueEmpty(Queue *q)
{
    return q->front == q->rear;
}

void EnQueue(Queue *q, int v)
{
    if (q->rear == MaxSize - 1)
    {
        printf("��������!\n");
        return;
    }
    q->data[++(q->rear)] = v;
}

int DeQueue(Queue *q)
{
    if (IsQueueEmpty(q))
    {
        printf("����Ϊ��!\n");
        return -1;
    }
    return q->data[++(q->front)];
}

void CreatGraph(MGraph *G, DataType vertexData[], int n, int e)
{
    int i, j, k;
    printf("\n��ͼ...\n");

    G->vertexNum = n;
    G->edgeNum = e;

    for (i = 0; i < G->vertexNum; i++)
    {
        for (j = 0; j < G->vertexNum; j++)
        {
            G->edge[i][j] = 0;
        }
    }

    if (e > 0)
    {
        printf("������ %d ���� (�����Ŵ�0��%d����ʽΪ: ����1 ����2):\n", G->edgeNum, G->vertexNum - 1);
        for (k = 0; k < G->edgeNum; k++)
        {
            printf("�� %d ����: ", k + 1);
            if (scanf("%d %d", &i, &j) != 2)
            {
                printf("�����ʽ����\n");
                exit(1);
            }
            G->edge[i][j] = 1;
            G->edge[j][i] = 1;
        }
    }
    printf("ͼ������ϡ�\n\n");
}

int visited[MaxSize];

void DFTraverse(MGraph *G, int v)
{
    int j;
    printf("%c ", G->vertex[v]);
    visited[v] = 1;

    for (j = 0; j < G->vertexNum; j++)
    {
        if (G->edge[v][j] == 1 && visited[j] == 0)
        {
            DFTraverse(G, j);
        }
    }
}

void BFTraverse(MGraph *G, int v)
{
    int i, j;
    Queue q;
    InitQueue(&q);

    printf("%c ", G->vertex[v]);
    visited[v] = 1;
    EnQueue(&q, v);

    while (!IsQueueEmpty(&q))
    {
        i = DeQueue(&q);

        for (j = 0; j < G->vertexNum; j++)
        {
            if (G->edge[i][j] == 1 && visited[j] == 0)
            {
                printf("%c ", G->vertex[j]);
                visited[j] = 1;
                EnQueue(&q, j);
            }
        }
    }
}

int main(void)
{
    int i;
    MGraph MG;
    DataType userVertexData[MaxSize];
    int numVertices, numEdges;
    int startVertexIndex;

    printf("������ͼ�Ķ������� (��� %d): ", MaxSize);
    if (scanf("%d", &numVertices) != 1 || numVertices <= 0 || numVertices > MaxSize)
    {
        printf("����Ķ���������Ч��\n");
        exit(1);
    }
    while (getchar() != '\n')
        ;

    printf("������ %d ����������� (�����ַ�):\n", numVertices);
    for (i = 0; i < numVertices; i++)
    {
        printf("���� %d: ", i);
        scanf(" %c", &userVertexData[i]);
        while (getchar() != '\n')
            ;
    }

    printf("������ͼ�ıߵ�����: ");
    if (scanf("%d", &numEdges) != 1 || numEdges < 0 || numEdges > numVertices * (numVertices - 1) / 2)
    {
        printf("����ıߵ�������Ч��\n");
        exit(1);
    }
    while (getchar() != '\n')
        ;

    CreatGraph(&MG, userVertexData, numVertices, numEdges);

    printf("ͼ���ڽӾ���Ϊ:\n");
    printf("  ");
    for (i = 0; i < MG.vertexNum; i++)
    {
        printf("%c ", MG.vertex[i]);
    }
    printf("\n");
    for (i = 0; i < MG.vertexNum; i++)
    {
        printf("%c ", MG.vertex[i]);
        for (int j = 0; j < MG.vertexNum; j++)
        {
            printf("%d ", MG.edge[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    if (numVertices > 0)
    {
        printf("�����뿪ʼ�����Ķ����� (0 �� %d): ", numVertices - 1);
        if (scanf("%d", &startVertexIndex) != 1 || startVertexIndex < 0 || startVertexIndex >= numVertices)
        {
            printf("�������ʼ��������Ч��\n");
            exit(1);
        }
        while (getchar() != '\n')
            ;
    }
    else
    {
        printf("ͼ��û�ж���\n");
        return 0;
    }

    printf("\n�Ӷ��� %c (��� %d) ��ʼ��������ȱ���������: ", MG.vertex[startVertexIndex], startVertexIndex);
    for (i = 0; i < MG.vertexNum; i++)
    {
        visited[i] = 0;
    }
    DFTraverse(&MG, startVertexIndex);
    printf("\n\n");

    printf("�Ӷ��� %c (��� %d) ��ʼ�Ĺ�����ȱ���������: ", MG.vertex[startVertexIndex], startVertexIndex);
    for (i = 0; i < MG.vertexNum; i++)
    {
        visited[i] = 0;
    }
    BFTraverse(&MG, startVertexIndex);
    printf("\n");

    return 0;
}
