#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Evaluation
{
private:
  string name;
  vector<pair<string, vector<int>>> competencies;
  vector<pair<string, vector<int>>> performance;

public:
  Evaluation()
  {
    cout << "Enter name of employee: ";
    cin >> name;
    competencies = {
        {"Communication", {0, 0, 0}},
        {"Productivity", {0, 0, 0}},
        {"Creativity", {0, 0, 0}},
        {"Integrity", {0, 0, 0}},
        {"Punctuality", {0, 0, 0}}};
    performance = {
        {"Goal 1", {0, 0, 0}},
        {"Goal 2", {0, 0, 0}},
        {"Goal 3", {0, 0, 0}},
        {"Goal 4", {0, 0, 0}},
        {"Goal 5", {0, 0, 0}}};
  }

  void printTable(vector<pair<string, vector<int>>> &goals, int type)
  {
    cout << (type == 1 ? "Competency Goals" : "Performance Goals") << endl;
    cout << "Goals\t\tRating\tWeightage\tWeighted Score" << endl;
    for (const auto &goal : goals)
    {
      cout << goal.first << "\t\t" << goal.second[0] << "\t" << goal.second[1] << "\t\t" << goal.second[2] << endl;
    }
    cout << endl;
  }

  void input()
  {
    cout << "Enter rating from 1-3" << endl;
    cout << "Weightage should be equal to 100" << endl;
    int weightTotal = 0;
    for (auto &competency : competencies)
    {
      cout << "Enter rating for " << competency.first << ": ";
      cin >> competency.second[0];
      cout << "Enter weightage(" << 100 - weightTotal << " remaining): ";
      cin >> competency.second[1];
      weightTotal += competency.second[1];
    }
    for (auto &goal : performance)
    {
      cout << "Enter rating for " << goal.first << ": ";
      cin >> goal.second[0];
      cout << "Enter weightage(" << 100 - weightTotal << " remaining): ";
      cin >> goal.second[1];
      weightTotal += goal.second[1];
    }
  }

  void calcScore()
  {
    for (auto &competency : competencies)
    {
      competency.second[2] = competency.second[0] * competency.second[1] / 100;
    }
    for (auto &goal : performance)
    {
      goal.second[2] = goal.second[0] * goal.second[1] / 100;
    }
  }

  void calculate()
  {
    input();
    cout << endl;
    calcScore();
    printTable(competencies, 1);

    double sumCompetency = 0;
    for (const auto &competency : competencies)
    {
      sumCompetency += competency.second[2];
    }
    cout << "Sum of weighted scores-Comptency = " << sumCompetency << endl
         << endl;

    printTable(performance,0);
    double sumPerformance = 0;
    for (const auto &goal : performance)
    {
      sumPerformance += goal.second[2];
    }
    cout << "Sum of weighted scores-Performance = " << sumPerformance << endl
         << endl;

    double total = sumCompetency + sumPerformance;

    if (total >= 2.7)
    {
      printf("Overall Rating of %s (out of 3): %.2f\n", name.c_str(), total);
      cout << "Employee Exceeds expectations" << endl;
    }
    else if (total >= 1.7 && total < 2.7)
    {
      printf("Overall Rating of %s (out of 3): %.2f\n", name.c_str(), total);
      cout << "Employee meets expectations" << endl;
    }
    else
    {
      printf("Overall Rating of %s (out of 3): %.2f\n", name.c_str(), total);
      cout << "Employee fails expectations" << endl;
    }
  }
};

int main()
{
  Evaluation obj;
  obj.calculate();
  return 0;
}
