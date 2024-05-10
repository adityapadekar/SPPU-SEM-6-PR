#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> dijkstra(vector<vector<pair<int, int>>> graph, int source)
{
  int n = graph.size();
  vector<int> dist(n, INT32_MAX);
  dist[source] = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, source});

  while (!pq.empty())
  {
    int u = pq.top().second;
    pq.pop();

    for (pair<int, int> edge : graph[u])
    {
      int v = edge.first;
      int weight = edge.second;
      if (dist[u] + weight < dist[v])
      {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});
      }
    }
  }

  return dist;
}

int main()
{
  int V = 5; 
  vector<vector<pair<int, int>>> graph(V);

  graph[0].push_back({1, 10});
  graph[0].push_back({2, 5});
  graph[1].push_back({2, 3});
  graph[1].push_back({3, 1});
  graph[2].push_back({1, 2});
  graph[2].push_back({3, 9});
  graph[2].push_back({4, 2});
  graph[3].push_back({4, 4});
  graph[4].push_back({3, 6});

  int source = 0;

  vector<int> distances = dijkstra(graph, source);

  cout << "Shortest distances from source vertex " << source << ":\n";
  for (int i = 0; i < V; ++i)
  {
    cout << "Vertex " << i << ": " << distances[i] << endl;
  }

  return 0;
}
