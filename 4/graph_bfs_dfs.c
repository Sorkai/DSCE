#include <stdio.h>
#include <stdlib.h> // 用于 exit()

#define MaxSize 10 // 假设图中最多顶点个数

typedef char DataType; // 图中顶点的数据类型,假设为char型

// 定义邻接矩阵存储结构
typedef struct
{
    DataType vertex[MaxSize];   // 存放顶点的一维数组
    int edge[MaxSize][MaxSize]; // 存放边的二维数组
    int vertexNum, edgeNum;     // 图的顶点数和边数
} MGraph;

// 辅助队列结构，用于广度优先遍历
typedef struct
{
    int data[MaxSize]; // 用于存储队列中的元素，这里存储的是图中顶点的索引
    int front;         // 队头指针，指向队列的第一个元素的前一个位置
    int rear;          // 队尾指针，指向队列的最后一个元素
} Queue;

// 初始化队列
void InitQueue(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

// 判断队列是否为空
int IsQueueEmpty(Queue *q)
{
    return q->front == q->rear;
}

// 入队
void EnQueue(Queue *q, int v)
{
    if (q->rear == MaxSize - 1)
    {
        printf("队列已满!\n");
        return;
    }
    q->data[++(q->rear)] = v;
}

// 出队
int DeQueue(Queue *q)
{
    if (IsQueueEmpty(q))
    {
        printf("队列为空!\n");
        return -1; // 返回错误码
    }
    return q->data[++(q->front)];
}

// 创建图的函数
// G: 图的指针
// vertexData: 包含用户输入的顶点数据的数组
// n: 顶点个数
// e: 边的个数
void CreatGraph(MGraph *G, DataType vertexData[], int n, int e)
{
    int i, j, k;
    printf("\n建图...\n");

    // 检查顶点数和边数是否在允许范围内
    if (n > MaxSize || n <= 0)
    {
        printf("顶点数量 %d 无效 (必须大于0且小于等于%d)。\n", n, MaxSize);
        exit(1); // 退出程序
    }
    if (e < 0 || e > n * (n - 1) / 2)
    { // 对于无向简单图，边的最大数量是 n*(n-1)/2
        printf("边的数量 %d 无效。\n", e);
        exit(1); // 退出程序
    }

    G->vertexNum = n;
    G->edgeNum = e;

    // 存储顶点信息
/*     printf("存储顶点信息: ");
    for (i = 0; i < G->vertexNum; i++)
    {
        G->vertex[i] = vertexData[i];
        printf("%c ", G->vertex[i]);
    }
    printf("\n"); */

    // 初始化邻接矩阵，所有边的权重设为0 (表示没有边)
    for (i = 0; i < G->vertexNum; i++)
    {
        for (j = 0; j < G->vertexNum; j++)
        {
            G->edge[i][j] = 0;
        }
    }

    // 依次输入每一条边
    if (e > 0)
    {
        printf("请输入 %d 条边 (顶点编号从0到%d，格式为: 顶点1 顶点2):\n", G->edgeNum, G->vertexNum - 1);
        for (k = 0; k < G->edgeNum; k++)
        {
            printf("第 %d 条边: ", k + 1);
            if (scanf("%d %d", &i, &j) != 2)
            {
                printf("输入格式错误，请输入两个整数。请重新输入。\n");
                // 清理输入缓冲区
                while (getchar() != '\n')
                    ;
                k--; // 重新输入这条边
                continue;
            }
            // 检查输入的顶点编号是否有效
            if (i < 0 || i >= G->vertexNum || j < 0 || j >= G->vertexNum)
            {
                printf("输入的顶点编号 %d 或 %d 无效 (有效范围 0 到 %d)。请重新输入。\n", i, j, G->vertexNum - 1);
                k--; // 重新输入这条边
                continue;
            }
            if (i == j)
            {
                printf("只能简单图。\n", i);
                k--;
                continue;
            }
            if (G->edge[i][j] == 1)
            {
                printf("边 (%d, %d) 已存在。请重新输入。\n", i, j);
                k--;
                continue;
            }
            G->edge[i][j] = 1; // 置有边标志
            G->edge[j][i] = 1; // 无向图，对称位置也置1
        }
    }
    printf("图创建完毕。\n\n");
}

// 全局数组变量 visited，用于标记顶点是否已被访问，0表示未访问，1表示已访问
int visited[MaxSize];

// 深度优先遍历 (Depth First Traverse)
// G: 图的指针
// v: 开始遍历的顶点编号
void DFTraverse(MGraph *G, int v)
{
    int j;
    printf("%c ", G->vertex[v]); // 访问顶点v
    visited[v] = 1;              // 标记顶点v已访问

    // 遍历与顶点v邻接的所有顶点
    for (j = 0; j < G->vertexNum; j++)
    {
        // 如果顶点j与顶点v之间有边，并且顶点j未被访问过
        if (G->edge[v][j] == 1 && visited[j] == 0)
        {
            DFTraverse(G, j); // 从顶点j开始递归进行深度优先遍历
        }
    }
}

// 广度优先遍历 (Breadth First Traverse)
// G: 图的指针
// v: 开始遍历的顶点编号
void BFTraverse(MGraph *G, int v)
{
    int i, j;
    Queue q;
    InitQueue(&q); // 初始化辅助队列

    printf("%c ", G->vertex[v]); // 访问起始顶点v
    visited[v] = 1;              // 标记顶点v已访问
    EnQueue(&q, v);              // 顶点v入队

    while (!IsQueueEmpty(&q))
    {                    // 当队列非空时
        i = DeQueue(&q); // 将队头元素出队并赋值给i

        // 遍历与顶点i邻接的所有顶点
        for (j = 0; j < G->vertexNum; j++)
        {
            // 如果顶点j与顶点i之间有边，并且顶点j未被访问过
            if (G->edge[i][j] == 1 && visited[j] == 0)
            {
                printf("%c ", G->vertex[j]); // 访问顶点j
                visited[j] = 1;              // 标记顶点j已访问
                EnQueue(&q, j);              // 顶点j入队
            }
        }
    }
}

// 主函数
int main()
{
    int i;
    MGraph MG; // 创建图对象
    DataType userVertexData[MaxSize];
    int numVertices, numEdges;
    int startVertexIndex;

    // --- 用户输入顶点数量 ---
    printf("请输入图的顶点数量 (最多 %d): ", MaxSize);
    if (scanf("%d", &numVertices) != 1 || numVertices <= 0 || numVertices > MaxSize)
    {
        printf("输入的顶点数量无效。程序将使用默认值或退出。\n");
        // 可以选择设置一个默认值或直接退出
        // numVertices = 5; // 例如设置默认值
        // printf("将使用默认顶点数: %d\n", numVertices);
        exit(1); // 或者直接退出
    }
    // 清理输入缓冲区，防止影响后续的getchar()或scanf("%c")
    while (getchar() != '\n')
        ;

    // --- 用户输入每个顶点的数据 ---
    printf("请输入 %d 个顶点的数据 (单个字符，例如 A B C ...):\n", numVertices);
    for (i = 0; i < numVertices; i++)
    {
        printf("顶点 %d: ", i);
        scanf(" %c", &userVertexData[i]); // 注意 %c 前的空格，用于消耗可能存在的换行符
        // 清理输入缓冲区，确保只读取一个字符
        while (getchar() != '\n')
            ;
    }

    // --- 用户输入边的数量 ---
    printf("请输入图的边的数量: ");
    if (scanf("%d", &numEdges) != 1 || numEdges < 0 || numEdges > numVertices * (numVertices - 1) / 2)
    {
        printf("输入的边的数量无效。程序将使用默认值或退出。\n");
        exit(1);
    }
    while (getchar() != '\n')
        ; // 清理输入缓冲区

    // 创建图
    CreatGraph(&MG, userVertexData, numVertices, numEdges);

    // 打印邻接矩阵 (可选)
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

    // --- 选择遍历的起始顶点 ---
    if (numVertices > 0)
    {
        printf("请输入开始遍历的顶点编号 (0 到 %d): ", numVertices - 1);
        if (scanf("%d", &startVertexIndex) != 1 || startVertexIndex < 0 || startVertexIndex >= numVertices)
        {
            printf("输入的起始顶点编号无效。将默认从顶点 0 开始。\n");
            startVertexIndex = 0;
        }
        while (getchar() != '\n')
            ; // 清理输入缓冲区
    }
    else
    {
        printf("图中没有顶点，无法进行遍历。\n");
        return 0;
    }

    // --- 深度优先遍历 ---
    printf("\n从顶点 %c (编号 %d) 开始的深度优先遍历序列是: ", MG.vertex[startVertexIndex], startVertexIndex);
    for (i = 0; i < MG.vertexNum; i++)
    { // 初始化 visited 数组
        visited[i] = 0;
    }
    DFTraverse(&MG, startVertexIndex);
    printf("\n\n");

    // --- 广度优先遍历 ---
    printf("从顶点 %c (编号 %d) 开始的广度优先遍历序列是: ", MG.vertex[startVertexIndex], startVertexIndex);
    for (i = 0; i < MG.vertexNum; i++)
    { // 初始化 visited 数组
        visited[i] = 0;
    }
    BFTraverse(&MG, startVertexIndex);
    printf("\n");

    return 0;
}
