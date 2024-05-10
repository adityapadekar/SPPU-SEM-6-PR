#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool isSafe(vector<vector<int>> graph, vector<int> colours, int colour, int vertex)
{
  for (int i{}; i < graph.size(); i++)
  {
    if (graph[vertex][i] && colour == colours[i])
    {
      return false;
    }
  }
  return true;
}

bool graphColouringUtil(vector<vector<int>> graph, vector<int> &colours, int numberOfColours, int vertex)
{
  if (vertex == graph.size())
  {
    return true;
  }
  for (int colour{1}; colour <= numberOfColours; colour++)
  {
    if (isSafe(graph, colours, colour, vertex))
    {
      colours[vertex] = colour;
      if (graphColouringUtil(graph, colours, numberOfColours, vertex + 1))
      {
        return true;
      }
      colours[vertex] = 0;
    }
  }
  return false;
}

void graphColouring(vector<vector<int>> graph, int numberOfColours)
{
  int numberOfVertices = graph.size();
  vector<int> colours(numberOfVertices, 0);

  if (!graphColouringUtil(graph, colours, numberOfColours, 0))
  {
    cout << "Solution does not exist";
    return;
  }

  cout << "Solution exists: Assignments of colors to vertices are:\n";
  for (int i = 0; i < numberOfVertices; ++i)
  {
    cout << "Vertex " << i << ": Color " << colours[i] << endl;
  }
}

int main()
{
  vector<vector<int>> graph = {
      {0, 1, 1, 1},
      {1, 0, 1, 0},
      {1, 1, 0, 1},
      {1, 0, 1, 0}};

  int numberOfColours = 3;

  graphColouring(graph, numberOfColours);
  return 0;
}