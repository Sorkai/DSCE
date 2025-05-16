#include <stdio.h>
#include <stdlib.h> // ���� exit()

#define MaxSize 10 // ����ͼ����ඥ�����

typedef char DataType; // ͼ�ж������������,����Ϊchar��

// �����ڽӾ���洢�ṹ
typedef struct
{
    DataType vertex[MaxSize];   // ��Ŷ����һά����
    int edge[MaxSize][MaxSize]; // ��űߵĶ�ά����
    int vertexNum, edgeNum;     // ͼ�Ķ������ͱ���
} MGraph;

// �������нṹ�����ڹ�����ȱ���
typedef struct
{
    int data[MaxSize]; // ���ڴ洢�����е�Ԫ�أ�����洢����ͼ�ж��������
    int front;         // ��ͷָ�룬ָ����еĵ�һ��Ԫ�ص�ǰһ��λ��
    int rear;          // ��βָ�룬ָ����е����һ��Ԫ��
} Queue;

// ��ʼ������
void InitQueue(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

// �ж϶����Ƿ�Ϊ��
int IsQueueEmpty(Queue *q)
{
    return q->front == q->rear;
}

// ���
void EnQueue(Queue *q, int v)
{
    if (q->rear == MaxSize - 1)
    {
        printf("��������!\n");
        return;
    }
    q->data[++(q->rear)] = v;
}

// ����
int DeQueue(Queue *q)
{
    if (IsQueueEmpty(q))
    {
        printf("����Ϊ��!\n");
        return -1; // ���ش�����
    }
    return q->data[++(q->front)];
}

// ����ͼ�ĺ���
// G: ͼ��ָ��
// vertexData: �����û�����Ķ������ݵ�����
// n: �������
// e: �ߵĸ���
void CreatGraph(MGraph *G, DataType vertexData[], int n, int e)
{
    int i, j, k;
    printf("\n��ͼ...\n");

    // ��鶥�����ͱ����Ƿ�������Χ��
    if (n > MaxSize || n <= 0)
    {
        printf("�������� %d ��Ч (�������0��С�ڵ���%d)��\n", n, MaxSize);
        exit(1); // �˳�����
    }
    if (e < 0 || e > n * (n - 1) / 2)
    { // ���������ͼ���ߵ���������� n*(n-1)/2
        printf("�ߵ����� %d ��Ч��\n", e);
        exit(1); // �˳�����
    }

    G->vertexNum = n;
    G->edgeNum = e;

    // �洢������Ϣ
/*     printf("�洢������Ϣ: ");
    for (i = 0; i < G->vertexNum; i++)
    {
        G->vertex[i] = vertexData[i];
        printf("%c ", G->vertex[i]);
    }
    printf("\n"); */

    // ��ʼ���ڽӾ������бߵ�Ȩ����Ϊ0 (��ʾû�б�)
    for (i = 0; i < G->vertexNum; i++)
    {
        for (j = 0; j < G->vertexNum; j++)
        {
            G->edge[i][j] = 0;
        }
    }

    // ��������ÿһ����
    if (e > 0)
    {
        printf("������ %d ���� (�����Ŵ�0��%d����ʽΪ: ����1 ����2):\n", G->edgeNum, G->vertexNum - 1);
        for (k = 0; k < G->edgeNum; k++)
        {
            printf("�� %d ����: ", k + 1);
            if (scanf("%d %d", &i, &j) != 2)
            {
                printf("�����ʽ�����������������������������롣\n");
                // �������뻺����
                while (getchar() != '\n')
                    ;
                k--; // ��������������
                continue;
            }
            // �������Ķ������Ƿ���Ч
            if (i < 0 || i >= G->vertexNum || j < 0 || j >= G->vertexNum)
            {
                printf("����Ķ����� %d �� %d ��Ч (��Ч��Χ 0 �� %d)�����������롣\n", i, j, G->vertexNum - 1);
                k--; // ��������������
                continue;
            }
            if (i == j)
            {
                printf("ֻ�ܼ�ͼ��\n", i);
                k--;
                continue;
            }
            if (G->edge[i][j] == 1)
            {
                printf("�� (%d, %d) �Ѵ��ڡ����������롣\n", i, j);
                k--;
                continue;
            }
            G->edge[i][j] = 1; // ���б߱�־
            G->edge[j][i] = 1; // ����ͼ���Գ�λ��Ҳ��1
        }
    }
    printf("ͼ������ϡ�\n\n");
}

// ȫ��������� visited�����ڱ�Ƕ����Ƿ��ѱ����ʣ�0��ʾδ���ʣ�1��ʾ�ѷ���
int visited[MaxSize];

// ������ȱ��� (Depth First Traverse)
// G: ͼ��ָ��
// v: ��ʼ�����Ķ�����
void DFTraverse(MGraph *G, int v)
{
    int j;
    printf("%c ", G->vertex[v]); // ���ʶ���v
    visited[v] = 1;              // ��Ƕ���v�ѷ���

    // �����붥��v�ڽӵ����ж���
    for (j = 0; j < G->vertexNum; j++)
    {
        // �������j�붥��v֮���бߣ����Ҷ���jδ�����ʹ�
        if (G->edge[v][j] == 1 && visited[j] == 0)
        {
            DFTraverse(G, j); // �Ӷ���j��ʼ�ݹ����������ȱ���
        }
    }
}

// ������ȱ��� (Breadth First Traverse)
// G: ͼ��ָ��
// v: ��ʼ�����Ķ�����
void BFTraverse(MGraph *G, int v)
{
    int i, j;
    Queue q;
    InitQueue(&q); // ��ʼ����������

    printf("%c ", G->vertex[v]); // ������ʼ����v
    visited[v] = 1;              // ��Ƕ���v�ѷ���
    EnQueue(&q, v);              // ����v���

    while (!IsQueueEmpty(&q))
    {                    // �����зǿ�ʱ
        i = DeQueue(&q); // ����ͷԪ�س��Ӳ���ֵ��i

        // �����붥��i�ڽӵ����ж���
        for (j = 0; j < G->vertexNum; j++)
        {
            // �������j�붥��i֮���бߣ����Ҷ���jδ�����ʹ�
            if (G->edge[i][j] == 1 && visited[j] == 0)
            {
                printf("%c ", G->vertex[j]); // ���ʶ���j
                visited[j] = 1;              // ��Ƕ���j�ѷ���
                EnQueue(&q, j);              // ����j���
            }
        }
    }
}

// ������
int main()
{
    int i;
    MGraph MG; // ����ͼ����
    DataType userVertexData[MaxSize];
    int numVertices, numEdges;
    int startVertexIndex;

    // --- �û����붥������ ---
    printf("������ͼ�Ķ������� (��� %d): ", MaxSize);
    if (scanf("%d", &numVertices) != 1 || numVertices <= 0 || numVertices > MaxSize)
    {
        printf("����Ķ���������Ч������ʹ��Ĭ��ֵ���˳���\n");
        // ����ѡ������һ��Ĭ��ֵ��ֱ���˳�
        // numVertices = 5; // ��������Ĭ��ֵ
        // printf("��ʹ��Ĭ�϶�����: %d\n", numVertices);
        exit(1); // ����ֱ���˳�
    }
    // �������뻺��������ֹӰ�������getchar()��scanf("%c")
    while (getchar() != '\n')
        ;

    // --- �û�����ÿ����������� ---
    printf("������ %d ����������� (�����ַ������� A B C ...):\n", numVertices);
    for (i = 0; i < numVertices; i++)
    {
        printf("���� %d: ", i);
        scanf(" %c", &userVertexData[i]); // ע�� %c ǰ�Ŀո��������Ŀ��ܴ��ڵĻ��з�
        // �������뻺������ȷ��ֻ��ȡһ���ַ�
        while (getchar() != '\n')
            ;
    }

    // --- �û�����ߵ����� ---
    printf("������ͼ�ıߵ�����: ");
    if (scanf("%d", &numEdges) != 1 || numEdges < 0 || numEdges > numVertices * (numVertices - 1) / 2)
    {
        printf("����ıߵ�������Ч������ʹ��Ĭ��ֵ���˳���\n");
        exit(1);
    }
    while (getchar() != '\n')
        ; // �������뻺����

    // ����ͼ
    CreatGraph(&MG, userVertexData, numVertices, numEdges);

    // ��ӡ�ڽӾ��� (��ѡ)
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

    // --- ѡ���������ʼ���� ---
    if (numVertices > 0)
    {
        printf("�����뿪ʼ�����Ķ����� (0 �� %d): ", numVertices - 1);
        if (scanf("%d", &startVertexIndex) != 1 || startVertexIndex < 0 || startVertexIndex >= numVertices)
        {
            printf("�������ʼ��������Ч����Ĭ�ϴӶ��� 0 ��ʼ��\n");
            startVertexIndex = 0;
        }
        while (getchar() != '\n')
            ; // �������뻺����
    }
    else
    {
        printf("ͼ��û�ж��㣬�޷����б�����\n");
        return 0;
    }

    // --- ������ȱ��� ---
    printf("\n�Ӷ��� %c (��� %d) ��ʼ��������ȱ���������: ", MG.vertex[startVertexIndex], startVertexIndex);
    for (i = 0; i < MG.vertexNum; i++)
    { // ��ʼ�� visited ����
        visited[i] = 0;
    }
    DFTraverse(&MG, startVertexIndex);
    printf("\n\n");

    // --- ������ȱ��� ---
    printf("�Ӷ��� %c (��� %d) ��ʼ�Ĺ�����ȱ���������: ", MG.vertex[startVertexIndex], startVertexIndex);
    for (i = 0; i < MG.vertexNum; i++)
    { // ��ʼ�� visited ����
        visited[i] = 0;
    }
    BFTraverse(&MG, startVertexIndex);
    printf("\n");

    return 0;
}
