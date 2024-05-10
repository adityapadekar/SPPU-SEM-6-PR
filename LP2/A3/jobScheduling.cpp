#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job
{
  int deadline;
  int profit;

  Job(int d, int p) : deadline(d), profit(p) {}
};

int lastDeadline(vector<Job> jobs)
{
  if (jobs.empty())
  {
    return -1;
  }
  int maxDeadline = jobs[0].deadline;
  for (Job job : jobs)
  {
    maxDeadline = max(maxDeadline, job.deadline);
  }

  return maxDeadline;
}

vector<Job> jobScheduling(vector<Job> jobs)
{
  int maxDeadline = lastDeadline(jobs);
  if (maxDeadline == -1)
  {
    return {};
  }

  sort(jobs.begin(), jobs.end(), [](Job a, Job b)
       { return a.profit > b.profit; });

  vector<bool> slot(maxDeadline, false);
  vector<Job> selectedJobs;

  for (Job job : jobs)
  {
    for (int j = min(maxDeadline, job.deadline) - 1; j >= 0; j--)
    {
      if (!slot[j])
      {
        slot[j] = true;
        selectedJobs.push_back(job);
        break;
      }
    }
  }

  return selectedJobs;
}

int main()
{
  // Example usage
  vector<Job> jobs = {{1, 5}, {1, 20}, {2, 15}, {3, 10}, {2, 25}};

  vector<Job> selectedJobs = jobScheduling(jobs);

  cout << "Selected Jobs:\n";
  for (size_t i = 0; i < selectedJobs.size(); i++)
  {
    cout << "Deadline : " << selectedJobs[i].deadline << " Profit : " << selectedJobs[i].profit << endl;
  }

  return 0;
}