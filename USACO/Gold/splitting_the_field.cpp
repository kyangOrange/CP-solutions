//https://usaco.org/index.php?page=viewproblem2&cpid=645
/*
Notice that in order to split the field into 2 blocks we must have a horizontal or vertical line that separates the 2 blocks. 
Therefore, we can compute the prefix and suffix of minimum and maximum y values to calculate each block's height, 
and iterate through the sorted cows and find a x position to put our line and calculate the area of the blocks. 
*/
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <fstream>
using namespace std;

using ll = long long;

int n;
ll ans = 0;
vector<pair<int, int>> cows;

/** returns the maximum area saved by testing splits along cows[i].first */
ll search() {
  sort(cows.begin(), cows.end());

  vector<pair<int, int>> pref(n), suf(n);

  // returns updated min/maxs when considering a new coordinate
  auto upd = [](pair<int, int> a, int b) -> pair<int, int> {
    return {min(a.first, b), max(a.second, b)};
  };

  // compute prefix/suffix minimums and maximums
  pref[0] = {cows[0].second, cows[0].second};
  for (int i = 1; i < n; ++i) { pref[i] = upd(pref[i - 1], cows[i].second); }

  suf[n - 1] = {cows[n - 1].second, cows[n - 1].second};
  for (int i = n - 2; i >= 0; i--) { suf[i] = upd(suf[i + 1], cows[i].second); }

  // initial area with one enclosure
  ll area = (ll)(cows.back().first - cows.front().first) *
            (pref.back().second - pref.back().first);

  ll best = LLONG_MAX;
  for (int i = 0; i < n - 1; i++) {
    // if it's possible to split
    if (cows[i].first != cows[i + 1].first) {
      ll first_rect =
          (ll)(cows[i].first - cows[0].first) * (pref[i].second - pref[i].first);
      ll second_rect = (ll)(cows.back().first - cows[i + 1].first) *
                       (suf[i + 1].second - suf[i + 1].first);

      best = min(best, first_rect + second_rect);
    }
  }

  return area - best;
}

int main() {
  ifstream cin("split.in");
  ofstream cout("split.out");

  cin >> n;
  cows.resize(n);

  for (pair<int, int> &cow : cows) { cin >> cow.first >> cow.second; }

  // try all splits on x axis
  ans = max(ans, search());

  for (pair<int, int> &cow : cows) { swap(cow.first, cow.second); }

  // try all splits on y axis
  ans = max(ans, search());

  cout << ans << endl;
}
