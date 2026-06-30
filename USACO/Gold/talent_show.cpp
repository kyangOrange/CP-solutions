//https://usaco.org/index.php?page=viewproblem2&cpid=839
/*
Knapsack dp
Notice if we follow formula dp[i][j] i is first i values j is weight, dp[i][j] is max value, then it would be too big as j times i is too large(j is the total weights possible, 10^6 * 250)
Therefore, we can reverse the roles, where j is a fixed talent and we try to minimize the weight. Then the time limit won't exceed, and after everything all we do is to go over values where weight >= W and find max ratio. 
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

const int inf = 2e9;
const int total_talent = 250000;
int n, w;
double ans = 0;

int main() {
  ifstream cin("talent.in");
  ofstream cout("talent.out");
  cin >> n >> w;
  vector<pair<int, int>> cows(n);
  for (int i = 0; i < n; i++) cin >> cows[i].first >> cows[i].second;
  vector<int> talent(1e6 + 10, inf);
  talent[0] = 0;
  for (auto cow : cows)
    for (int i = total_talent; i >= 0; i--)
      if (talent[i] != inf)
        talent[i + cow.second] = min(talent[i + cow.second], talent[i] + cow.first);
  for (double T = 1; T < talent.size(); T++)
    if (talent[T] >= w && T / talent[T] > ans) ans = T / talent[T];
  cout << (int)(1000 * ans) << endl;
}
