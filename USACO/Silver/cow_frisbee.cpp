//https://usaco.org/index.php?page=viewproblem2&cpid=1183
/*
Monotonic stack. The key is to realize that we can do the same algorithm in both directions to solve. 
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int n;
long long ans = 0;

void solve(const vector<int>& h) {
  stack<int> s;
  for (int i = n - 1; i >= 0; --i) {
    while (!s.empty() && h[s.top()] < h[i])
      s.pop();
    if (!s.empty())
      ans += s.top() - i + 1;

    s.push(i);
  }
}

int main() {
  cin >> n;
  vector<int> h(n);
  for (int &x : h) cin >> x;

  solve(h);
  reverse(h.begin(), h.end());
  solve(h);

  cout<<ans<<endl;
}
