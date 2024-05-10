#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
  int vertices;
  vector<vector<int>> edges;

public:
  Graph(int v) : vertices(v)
  {
    edges.resize(v);
  }

  void printGraph()
  {
    for (auto adj : edges)
    {
      for (auto vertex : adj)
      {
        cout << vertex << " ";
      }
      cout << endl;
    }
  }

  void addEdge(int vertex, int adjVertex)
  {
    edges[vertex].push_back(adjVertex);
  }

  void dfsUtil(int v, vector<bool> &visited)
  {
    visited[v] = true;
    cout << v << " ";
    for (int i : edges[v])
    {
      if (!visited[i])
      {
        dfsUtil(i, visited);
      }
    }
  }

  void dfs(int start)
  {
    vector<bool> visited(vertices, false);
    dfsUtil(start, visited);
    cout << endl;
  }

  void bfsUtil(queue<int> &q, vector<bool> &visited)
  {
    if (q.empty())
      return;

    int v = q.front();
    q.pop();
    cout << v << " ";

    for (int i : edges[v])
    {
      if (!visited[i])
      {
        visited[i] = true;
        q.push(i);
      }
    }

    bfsUtil(q, visited);
  }

  void bfs(int start)
  {
    vector<bool> visited(vertices, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    bfsUtil(q, visited);
    cout << endl;
  }
};

int main()
{
  Graph g(6);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(2, 4);
  g.addEdge(3, 5);
  g.addEdge(4, 5);

  g.printGraph();

  cout << "DFS traversal starting from vertex 0: ";
  g.dfs(0);

  cout << "BFS traversal starting from vertex 0: ";
  g.bfs(0);

  return 0;
}