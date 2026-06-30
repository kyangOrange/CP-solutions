//https://usaco.org/index.php?page=viewproblem2&cpid=1426
/*
Use fenwick tree, key observation is that we only consider for each query intervals with length longer than k
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int MAXN = 200005;
const int MAXT = 4 * MAXN + 5;

int N;
int l[MAXN], r[MAXN], k[MAXN];

// Coordinate compression
map<int, int> cc;
vector<int> coords;

// keys: sorted by interval length (r - l)
// queries: sorted by k
pair<int, pair<int, int>> keys[MAXN];
pair<pair<int,int>, pair<int,int>> queries[MAXN];

int ans[MAXN];

// Fenwick Trees
int lbit[MAXT], rbit[MAXT];
int f; // Fenwick size after compression

// sum of first k elements
int sum(int tree[], int k) {
  int s = 0;
  while (k >= 1) {
    s += tree[k];
    k -= k & -k;
  }
  return s;
}

// add x to position k
void add(int tree[], int k, int x) {
  while (k <= f) {
    tree[k] += x;
    k += k & -k;
  }
}

int main() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> l[i] >> r[i] >> k[i];
  }

  // Coordinate compression
  for (int i = 0; i < N; i++) {
    coords.push_back(l[i]);
    coords.push_back(r[i]);
    coords.push_back(l[i] + k[i] - 1);
    coords.push_back(r[i] - k[i] + 1);
  }
  sort(coords.begin(), coords.end());
  f = 1;
  for (int x : coords) {
    if (!cc.count(x)) cc[x] = f++;
  }
  // Prepare keys and queries
  for (int i = 0; i < N; i++) {
    keys[i] = {r[i] - l[i], {cc[l[i]], cc[r[i]]}};
    queries[i] = {
      {k[i], i},
      {cc[l[i] + k[i] - 1], cc[r[i] - k[i] + 1]}
    };
  }
  sort(keys, keys + N);
  sort(queries, queries + N);

  int q = N - 1;

  // Sweep from large intervals to small
  for (int i = N - 1; i >= 0; i--) {
    //queries with k that are too large to fit in current interval
    //have to be answered now or else other intervals even shorter
    while (q >= 0 && queries[q].first.first > keys[i].first) {
      int j = queries[q].first.second;

      // Start with all remaining intervals
      ans[j] += (N - 2 - i);

      // Remove intervals ending too early
      ans[j] -= sum(rbit, queries[q].second.first);

      // Remove intervals starting too late
      ans[j] -= (sum(lbit, f) -
                  sum(lbit, queries[q].second.second - 1));
      q--;
    }

    // Activate current interval
    // Enforces rule that only intervals of length >= k are counted
    add(lbit, keys[i].second.first, 1);
    add(rbit, keys[i].second.second, 1);
  }

  // Remaining queries
  //these are the queries with k small enough to fit in all intervals
  while (q >= 0) {
    int j = queries[q].first.second;

    ans[j] += (N - 1);
    ans[j] -= sum(rbit, queries[q].second.first);
    ans[j] -= (sum(lbit, f) -
                sum(lbit, queries[q].second.second - 1));

    q--;
  }

  // Output
  for (int i = 0; i < N; i++) {
    cout << ans[i] << endl;
  }
}
