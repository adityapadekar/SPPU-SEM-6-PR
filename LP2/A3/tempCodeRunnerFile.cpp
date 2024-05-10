#include <iostream>
#include <vector>
#include <queue>

#define MAX 5

using namespace std;

int minKey(vector<int> key, vector<bool> mstSet)
{
  int min = INT16_MAX, minIndex;

  for (int v{}; v < MAX; v++)
  {
    if (mstSet[v] == false && key[v] < min)
    {
      min = key[v];
      minIndex = v;
    }
  }
  return minIndex;
}

void printMST(vector<int> parent, vector<vector<int>> graph)
{
  cout << "Edge \tWeight\n";
  for (int i = 1; i < MAX; i++)
    cout << parent[i] << " - " << i << " \t"
         << graph[i][parent[i]] << " \n";
}

void primMST(vector<vector<int>> graph)
{
  vector<int> parent(MAX);
  vector<int> key(MAX, INT32_MAX);
  vector<bool> mstSet(MAX, false);

  key[0] = 0;
  parent[0] = -1;

  for (int count{}; count < MAX; count++)
  {
    int u = minKey(key, mstSet);

    mstSet[u] = true;

    for (int i{}; i < MAX; i++)
    {
      if (graph[u][i] && mstSet[i] == false && graph[u][i] < key[i])
      {
        parent[i] = u;
        key[i] = graph[u][i];
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

  primMST(graph);
  return 0;
}