#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10 /* 假设图中最多顶点个数 */

typedef char DataType; /* 图中顶点的数据类型,假设为char型 */

// 定义邻接矩阵存储结构
typedef struct
{
    DataType vertex[MaxSize];   /* 存放顶点的一维数组 */
    int edge[MaxSize][MaxSize]; /* 存放边的二维数组 */
    int vertexNum, edgeNum;     /* 图的顶点数和边数 */
} MGraph;

int visited[MaxSize] = {0}; /* 全局数组变量 visited 初始化, 用于标记顶点是否被访问过 */

/**
 * @brief 创建无向图的邻接矩阵
 * @param G 指向图结构体的指针
 * @param a 包含顶点数据的数组
 * @param n 图的顶点数
 * @param e 图的边数
 */
void CreatGraph(MGraph *G, DataType a[], int n, int e)
{
    int i, j, k;
    // 初始化顶点数和边数
    G->vertexNum = n;
    G->edgeNum = e;

    // 存储顶点信息
    for (i = 0; i < G->vertexNum; i++)
    {
        G->vertex[i] = a[i];
    }

    // 初始化邻接矩阵，所有边的权重设为0 (表示没有边)
    for (i = 0; i < G->vertexNum; i++)
    {
        for (j = 0; j < G->vertexNum; j++)
        {
            G->edge[i][j] = 0;
        }
    }

    printf("请输入 %d 条边 (格式: 顶点1索引 顶点2索引):\n", e);
    // 依次输入每一条边
    for (k = 0; k < G->edgeNum; k++)
    {
        // 输入边依附的顶点编号 (从0开始的索引)
        scanf("%d%d", &i, &j);
        // 验证输入的顶点索引是否有效
        if (i >= 0 && i < G->vertexNum && j >= 0 && j < G->vertexNum)
        {
            G->edge[i][j] = 1; // 置有边标志
            G->edge[j][i] = 1; // 因为是无向图，对称位置也置1
        }
        else
        {
            printf("无效的顶点索引: %d, %d. 请重新输入这条边。\n", i, j);
            k--; // 当前边输入无效，需要重新输入
        }
    }
}

/**
 * @brief 从顶点v开始深度优先遍历图G
 * @param G 指向图结构体的指针
 * @param v 开始遍历的顶点索引
 */
void DFSTraverse(MGraph *G, int v)
{
    // 打印当前访问的顶点
    printf("%c ", G->vertex[v]);
    // 标记当前顶点已被访问
    visited[v] = 1;

    // 遍历所有顶点，查找与当前顶点v邻接且未被访问过的顶点
    for (int j = 0; j < G->vertexNum; j++)
    {
        // 如果顶点j与顶点v之间有边，并且顶点j未被访问过
        if (G->edge[v][j] == 1 && visited[j] == 0)
        {
            DFSTraverse(G, j); // 递归访问顶点j
        }
    }
}

/**
 * @brief 打印邻接矩阵 (用于调试和验证)
 * @param G 指向图结构体的指针
 */
void PrintGraph(MGraph *G)
{
    int i, j;
    printf("\n邻接矩阵:\n  ");
    for (i = 0; i < G->vertexNum; i++)
    {
        printf("%c ", G->vertex[i]);
    }
    printf("\n");
    for (i = 0; i < G->vertexNum; i++)
    {
        printf("%c ", G->vertex[i]);
        for (j = 0; j < G->vertexNum; j++)
        {
            printf("%d ", G->edge[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int i;
    // 顶点数据，例如 'A', 'B', 'C', 'D', 'E'
    DataType vertexData[] = {'A', 'B', 'C', 'D', 'E'};
    int numVertices = 5; // 顶点数量
    int numEdges = 6;    // 边的数量

    MGraph MG; // 创建图对象

    // 创建具有5个顶点6条边的无向图
    // 顶点数据为 vertexData, 顶点数为 numVertices, 边数为 numEdges
    CreatGraph(&MG, vertexData, numVertices, numEdges);

    // 打印邻接矩阵 (可选, 用于验证图是否正确创建)
    PrintGraph(&MG);

    // 确保 visited 数组在使用前已正确初始化 (虽然全局变量默认初始化为0，但显式重置是个好习惯)
    for (i = 0; i < MaxSize; i++)
    {
        visited[i] = 0;
    }

    printf("\n深度优先遍历序列是: ");
    // 从顶点0 (即'A') 出发进行深度优先遍历
    // 您可以修改起始顶点，例如 DFSTraverse(&MG, 1) 从顶点'B'开始
    DFSTraverse(&MG, 0);
    printf("\n");

    // 如果图不是连通的，需要对每个未访问的顶点调用DFSTraverse
    for (i = 0; i < MG.vertexNum; i++)
    {
        if (visited[i] == 0)
        {
            DFSTraverse(&MG, i);
        }
    }
    printf("\n");

    return 0;
}
