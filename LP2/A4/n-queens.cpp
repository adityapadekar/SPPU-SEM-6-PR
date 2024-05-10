#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool isSafe(int row, int col, vector<string> board)
{
  int sizeOfBoard = board.size();
  for (int i{}; i < row; i++)
  {
    if (board[i][col] == 'Q')
    {
      return false;
    }
  }

  int i = row, j = col;
  while (i >= 0 && j < sizeOfBoard)
  {
    if (board[i][j] == 'Q')
    {
      return false;
    }
    i--;
    j++;
  }

  i = row, j = col;
  while (i >= 0 && j >= 0)
  {
    if (board[i][j] == 'Q')
    {
      return false;
    }
    i--;
    j--;
  }

  return true;
}

void backtrack(int row, vector<string> &board, vector<vector<string>> &result)
{
  if (row == board.size())
  {
    result.push_back(board);
    return;
  }

  for (int col{}; col < board.size(); col++)
  {
    if (isSafe(row, col, board))
    {
      board[row][col] = 'Q';
      backtrack(row + 1, board, result);
      board[row][col] = '.';
    }
  }
}

vector<vector<string>> solveNQueens(int numberOfQueens)
{
  vector<vector<string>> result;

  vector<string> board(numberOfQueens, string(numberOfQueens, '.'));

  backtrack(0, board, result);

  return result;
}

void printSolutions(const vector<vector<string>> &boards)
{
  for (size_t i = 0; i < boards.size(); ++i)
  {
    cout << "Solution " << i + 1 << ":" << endl;
    for (const auto &row : boards[i])
    {
      for (char col : row)
      {
        cout << col << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
}

int main()
{
  vector<vector<string>> boards = solveNQueens(4);
  printSolutions(boards);
  return 0;
}