#include <iostream>
#include <cstring>
#include <stack>
#include <queue>

using namespace std;


const int MAX_GRAPH_SIZE = 16;

int VertexCount;                               // 图中顶点
bool IsVisited[MAX_GRAPH_SIZE];                // 顶点的访问标志，Visited[i]表示在一次遍历中顶点i是否被访问过
bool HasEdge[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];  // HasEdge[i][j]表示顶点i与j之间是否存在边


// 初始化图
// 图的顶点从1开始编号
void InitGraph()
{
    cout << "请输入图的顶点数："; cin >> VertexCount;
    int edge_count; cout << "请输入图的边数："; cin >> edge_count;
    cout << "请输入图中边的顶点对：" << endl;
    for (int i = 1; i <= edge_count; ++i)
    {
        int u, v; cin >> u >> v;
        HasEdge[u][v] = true;
        HasEdge[v][u] = true;
    }
}


// 找到编号为v的顶点的第一个邻接顶点
int FirstAdj(int v)
{
    if (v <= 0 || v > VertexCount) return 0;  // 检查参数合法性
    for (int u = 1; u <= VertexCount; ++u) {
        if (HasEdge[v][u]) return u;
    }
    return 0;
}


// 设w是v的邻接顶点, 找到v的排在w后的下一个邻接顶点
int NextAdj(int v, int w)
{
    if (v <= 0 || v > VertexCount) return 0;  // 检查参数合法性
    if (w <= 0 || w > VertexCount) return 0;  // 同上
    for (int u = w + 1; u <= VertexCount; ++u) {
        if (HasEdge[v][u]) return u;
    }
    return 0;
}


// 对连通图从顶点v开始进行深度优先访问
void DepthFirstSearch(int v)
{
    memset(IsVisited, 0, sizeof(IsVisited));  // 清空访问标志
    stack<int> stk;
    stk.push(v);  // 从v顶点开始
    while (!stk.empty())
    {
        int vertex = stk.top(); stk.pop();  // 访问当前顶点
        if (IsVisited[vertex]) continue;
        cout << vertex; IsVisited[vertex] = true;
        for (int w = FirstAdj(vertex); w != 0; w = NextAdj(vertex, w)) {
            if (!IsVisited[w]) stk.push(w);
        }  // 依次将未访问的顶点加入栈
        if (!stk.empty()) cout << ' ';
    }
    cout << endl;
}


// 对连通图从顶点v开始进行广度优先访问
void BroadFirstSearch(int v)
{
    memset(IsVisited, 0, sizeof(IsVisited));  // 清空访问标志
    queue<int> que;
    que.push(v);  // 从v顶点开始
    while (!que.empty())
    {
        int vertex = que.front(); que.pop();  // 访问当前顶点
        if (IsVisited[vertex]) continue;
        cout << vertex; IsVisited[vertex] = true;
        for (int w = FirstAdj(vertex); w != 0; w = NextAdj(vertex, w)) {
            if (!IsVisited[w]) que.push(w);
        }  // 依次将未访问的顶点加入队列
        if (!que.empty()) cout << ' ';
    }
    cout << endl;
}


int main()
{
    InitGraph();
    
    int random_vertex = rand() % VertexCount + 1;  // 随机顶点

    cout << "从顶点1开始的深度优先遍历序列：";
    DepthFirstSearch(1);
    cout << "从顶点" << random_vertex << "开始的深度优先遍历序列：";
    DepthFirstSearch(random_vertex);
    cout << "从顶点1开始的广度优先遍历序列：";
    BroadFirstSearch(1);
    cout << "从顶点" << random_vertex << "开始的广度优先遍历序列：";
    BroadFirstSearch(random_vertex);
}
