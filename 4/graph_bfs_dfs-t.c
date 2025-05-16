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
        printf("队列已满!\n");
        return;
    }
    q->data[++(q->rear)] = v;
}

int DeQueue(Queue *q)
{
    if (IsQueueEmpty(q))
    {
        printf("队列为空!\n");
        return -1;
    }
    return q->data[++(q->front)];
}

void CreatGraph(MGraph *G, DataType vertexData[], int n, int e)
{
    int i, j, k;
    printf("\n建图...\n");

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
        printf("请输入 %d 条边 (顶点编号从0到%d，格式为: 顶点1 顶点2):\n", G->edgeNum, G->vertexNum - 1);
        for (k = 0; k < G->edgeNum; k++)
        {
            printf("第 %d 条边: ", k + 1);
            if (scanf("%d %d", &i, &j) != 2)
            {
                printf("输入格式错误！\n");
                exit(1);
            }
            G->edge[i][j] = 1;
            G->edge[j][i] = 1;
        }
    }
    printf("图创建完毕。\n\n");
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

    printf("请输入图的顶点数量 (最多 %d): ", MaxSize);
    if (scanf("%d", &numVertices) != 1 || numVertices <= 0 || numVertices > MaxSize)
    {
        printf("输入的顶点数量无效。\n");
        exit(1);
    }
    while (getchar() != '\n')
        ;

    printf("请输入 %d 个顶点的数据 (单个字符):\n", numVertices);
    for (i = 0; i < numVertices; i++)
    {
        printf("顶点 %d: ", i);
        scanf(" %c", &userVertexData[i]);
        while (getchar() != '\n')
            ;
    }

    printf("请输入图的边的数量: ");
    if (scanf("%d", &numEdges) != 1 || numEdges < 0 || numEdges > numVertices * (numVertices - 1) / 2)
    {
        printf("输入的边的数量无效。\n");
        exit(1);
    }
    while (getchar() != '\n')
        ;

    CreatGraph(&MG, userVertexData, numVertices, numEdges);

    printf("图的邻接矩阵为:\n");
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
        printf("请输入开始遍历的顶点编号 (0 到 %d): ", numVertices - 1);
        if (scanf("%d", &startVertexIndex) != 1 || startVertexIndex < 0 || startVertexIndex >= numVertices)
        {
            printf("输入的起始顶点编号无效。\n");
            exit(1);
        }
        while (getchar() != '\n')
            ;
    }
    else
    {
        printf("图中没有顶点\n");
        return 0;
    }

    printf("\n从顶点 %c (编号 %d) 开始的深度优先遍历序列是: ", MG.vertex[startVertexIndex], startVertexIndex);
    for (i = 0; i < MG.vertexNum; i++)
    {
        visited[i] = 0;
    }
    DFTraverse(&MG, startVertexIndex);
    printf("\n\n");

    printf("从顶点 %c (编号 %d) 开始的广度优先遍历序列是: ", MG.vertex[startVertexIndex], startVertexIndex);
    for (i = 0; i < MG.vertexNum; i++)
    {
        visited[i] = 0;
    }
    BFTraverse(&MG, startVertexIndex);
    printf("\n");

    return 0;
}
