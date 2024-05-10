#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int weight;
    int src;
    int dest;

    Edge(int w, int s, int d) : weight(w), src(s), dest(d) {}
};

int findParent(vector<int> &parent, int node)
{
    while (parent[node] != node)
        node = parent[node];
    return node;
}

void unionSets(vector<int> &parent, vector<int> &rank, int u, int v)
{
    int pu = findParent(parent, u);
    int pv = findParent(parent, v);
    if (rank[pu] < rank[pv])
        parent[pu] = pv;
    else if (rank[pv] < rank[pu])
        parent[pv] = pu;
    else
    {
        parent[pu] = pv;
        rank[pv]++;
    }
}

vector<Edge> kruskalMST(vector<Edge> &edges, int V)
{

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.weight < b.weight; });

    vector<Edge> result;
    vector<int> parent(V);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; ++i)
        parent[i] = i;

    int edgeCount = 0;
    for (const auto &edge : edges)
    {
        int u = edge.src;
        int v = edge.dest;
        int pu = findParent(parent, u);
        int pv = findParent(parent, v);

        if (pu != pv)
        {
            result.push_back(edge);
            unionSets(parent, rank, pu, pv);
            if (++edgeCount == V - 1)
                break;
        }
    }

    return result;
}

int main()
{
    int V = 4;
    vector<Edge> edges = {
        {10, 0, 1},
        {6, 0, 2},
        {5, 0, 3},
        {15, 1, 3},
        {4, 2, 3}};

    vector<Edge> mst = kruskalMST(edges, V);

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto &edge : mst)
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;

    return 0;
}
