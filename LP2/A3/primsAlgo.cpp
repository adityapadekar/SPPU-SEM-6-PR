#include <iostream>
#include <vector>

using namespace std;

int minKey(vector<int> key, vector<bool> mstSet)
{
  int minValue = INT32_MAX, minIndex;
  for (int i{}; i < key.size(); i++)
  {
    if (!mstSet[i] && key[i] < minValue)
    {
      minValue = key[i];
      minIndex = i;
    }
  }

  return minIndex;
}

void printMST(vector<int> parent, vector<vector<int>> graph)
{
  cout << "Edge \tWeight\n";
  for (int i = 1; i < graph.size(); i++)
    cout << parent[i] << " - " << i << " \t"
         << graph[i][parent[i]] << " \n";
}

void primMST(vector<vector<int>> graph, int numberOfVertices)
{
  vector<int> parent(numberOfVertices);
  vector<int> key(numberOfVertices, INT32_MAX);
  vector<bool> mstSet(numberOfVertices, false);

  parent[0] = -1;
  key[0] = 0;

  for (int count{}; count < numberOfVertices; count++)
  {
    int u = minKey(key, mstSet);
    mstSet[u] = true;

    for (int vertex{}; vertex < numberOfVertices; vertex++)
    {
      if (graph[u][vertex] && !mstSet[vertex] && graph[u][vertex] < key[vertex])
      {
        parent[vertex] = u;
        key[vertex] = graph[u][vertex];
      }
    }
  }

  printMST(parent, graph);
}

int main()
{
  vector<vector<int>> graph = {{0, 2, 0, 6, 0},
                               {2, 0, 3, 8, 5},
                               {0, 3, 0, 0, 7},
                               {6, 8, 0, 0, 9},
                               {0, 5, 7, 9, 0}};

  primMST(graph, 5);
  return 0;
}