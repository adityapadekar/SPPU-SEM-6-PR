#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Puzzle
{
public:
  vector<vector<int>> state;
  vector<vector<int>> finalState;
  int zeroRow, zeroCol;
  int g;
  int h;
  int n;

  bool operator<(const Puzzle &other) const
  {
    return (g + h) > (other.g + other.h);
  }

  Puzzle(int n) : n(n), state(n, vector<int>(n, 0)), finalState(n, vector<int>(n, 0)), g(0), h(0), zeroRow(0), zeroCol(0)
  {
    int count = 1;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (i == n - 1 && j == n - 1)
        {
          continue;
        }
        finalState[i][j] = count++;
      }
    }
  }

  // int calculateHeuristicValue()
  // {
  //   int heuristic = 0;
  //   for (int i = 0; i < n; i++)
  //   {
  //     for (int j = 0; j < n; j++)
  //     {
  //       if (state[i][j] != 0)
  //       {
  //         int value = state[i][j];
  //         if (value)
  //         {
  //           int targetRow = (value - 1) / n;
  //           int targetCol = (value - 1) % n;
  //           heuristic += abs(i - targetRow) + abs(j - targetCol);
  //         }
  //       }
  //     }
  //   }
  //   return heuristic;
  // }
  int calculateHeuristicValue()
  {
    int heuristic = 0;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (state[i][j] != finalState[i][j])
        {
          heuristic++;
        }
      }
    }
    return heuristic;
  }

  bool isEqual()
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (state[i][j] != finalState[i][j])
          return false;
      }
    }
    return true;
  }

  bool isValid(int row, int col)
  {
    return (row >= 0 && row < n && col >= 0 && col < n);
  }

  void getPuzzleInitialState()
  {
    cout << "Enter the initial state of the puzzle (0 represents the empty tile):\n";
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        cout << "Enter value at position (" << i << ", " << j << "): ";
        cin >> state[i][j];

        if (state[i][j] == 0)
        {
          zeroRow = i;
          zeroCol = j;
        }
      }
    }

    h = calculateHeuristicValue();
  }

  void printPuzzleFinalState()
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        cout << finalState[i][j] << " ";
      }
      cout << endl;
    }
    cout << "-----\n";
  }

  void printPuzzleCurrentState()
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        cout << state[i][j] << " ";
      }
      cout << endl;
    }
    cout << "-----\n";
  }
};

vector<Puzzle> generateNextStates(Puzzle puzzle)
{
  vector<Puzzle> nextStates;
  const int moves[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

  for (int k = 0; k < 4; k++)
  {
    int nextZeroRow = puzzle.zeroRow + moves[k][0];
    int nextZeroCol = puzzle.zeroCol + moves[k][1];

    if (puzzle.isValid(nextZeroRow, nextZeroCol))
    {
      Puzzle nextState = puzzle;
      swap(nextState.state[puzzle.zeroRow][puzzle.zeroCol], nextState.state[nextZeroRow][nextZeroCol]);
      nextState.zeroRow = nextZeroRow;
      nextState.zeroCol = nextZeroCol;
      nextState.g = puzzle.g + 1;
      nextState.h = nextState.calculateHeuristicValue();
      nextStates.push_back(nextState);
    }
  }

  return nextStates;
}

bool isSolvable(Puzzle puzzle)
{

  vector<int> flattenedState;
  for (int i = 0; i < puzzle.n; ++i)
  {
    for (int j = 0; j < puzzle.n; ++j)
    {
      flattenedState.push_back(puzzle.state[i][j]);
    }
  }

  int inversions = 0;
  int n = flattenedState.size();

  for (int i = 0; i < n - 1; ++i)
  {
    for (int j = i + 1; j < n; ++j)
    {

      if (flattenedState[i] && flattenedState[j] && flattenedState[i] > flattenedState[j])
      {
        ++inversions;
      }
    }
  }

  return (inversions % 2 == 0);
}

void aStarSearch(Puzzle puzzle)
{
  priority_queue<Puzzle> pq;

  unordered_set<int> visited;

  pq.push(puzzle);

  while (!pq.empty())
  {

    Puzzle current = pq.top();
    pq.pop();

    cout << "Current State:\n";
    current.printPuzzleCurrentState();
    cout << "Number of moves: " << current.g << endl;
    cout << "Heuristic cost: " << current.h << endl;
    cout << "-------------------\n";

    if (current.isEqual())
    {
      cout << "Goal State Reached!\n";
      cout << "Number of moves: " << current.g << endl;
      cout << "Heuristic cost: " << current.h << endl;
      break;
    }

    vector<Puzzle> nextStates = generateNextStates(current);

    for (Puzzle nextState : nextStates)
    {
      int hash = 0;
      for (int i = 0; i < puzzle.n; i++)
        for (int j = 0; j < puzzle.n; j++)
          hash = hash * 10 + nextState.state[i][j];

      if (visited.find(hash) == visited.end())
      {
        pq.push(nextState);
        visited.insert(hash);
      }
    }
  }
}

int main()
{
  Puzzle puzzle = Puzzle(3);
  puzzle.getPuzzleInitialState();

  cout << "Initial State:\n";
  puzzle.printPuzzleCurrentState();

  cout << "Goal State:\n";
  puzzle.printPuzzleFinalState();

  if (!isSolvable(puzzle))
  {
    cout << "The puzzle is not solvable.\n";
    return 0;
  }

  aStarSearch(puzzle);

  return 0;
}