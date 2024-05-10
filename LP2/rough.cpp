#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge
{
  int src;
  int dest;
  int weight;

  Edge(int w, int s, int d) : weight(w), src(s), dest(d) {}
};

int findParent(vector<int> parent, int node)
{
  if (parent[node] != node)
  {
    node = parent[node];
  }

  return node;
}

void util(vector<int> &rank, vector<int> &parent, int src, int dest)
{
  int pSrc = findParent(parent, src);
  int pDest = findParent(parent, dest);

  if (rank[pSrc] < rank[pDest])
  {
    parent[pSrc] = pDest;
  }
  else if (rank[pDest] < rank[pSrc])
  {
    parent[pDest] = pSrc;
  }
  else
  {
    parent[pSrc] = pDest;
    rank[pDest]++;
  }
}

vector<Edge> kruskalMST(vector<Edge> edges, int numberOfVertices)
{
  sort(edges.begin(), edges.end(), [](Edge a, Edge b)
       { return a.weight < b.weight; });

  vector<int> parent(numberOfVertices);
  vector<int> rank(numberOfVertices, 0);
  vector<Edge> result;

  for (int i{}; i < numberOfVertices; i++)
  {
    parent[i] = i;
  }

  int edgeCount = 0;
  for (Edge edge : edges)
  {
    int src = edge.src;
    int dest = edge.dest;

    int pSrc = findParent(parent, src);
    int pDest = findParent(parent, dest);

    if (pSrc != pDest)
    {
      result.push_back(edge);
      util(rank, parent, pSrc, pDest);
      if (++edgeCount == numberOfVertices - 1)
      {
        break;
      }
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