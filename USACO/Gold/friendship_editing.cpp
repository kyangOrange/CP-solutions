//https://usaco.org/index.php?page=viewproblem2&cpid=1499
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int INF = 1e9 + 7;
 
int adj[16][16];
 
int dp[1 << 16];
int N, M;
int flip[1 << 16]; 
int main() {
  cin >> N >> M;
  for (int i = 0; i < M; i++) {
    int U, V;
    cin >> U >> V;
    U--, V--;
    adj[U][V] = adj[V][U] = 1;
  }
  for (int mask = 0; mask < (1 << N); mask++) {
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        if ((mask & (1 << i)) && (mask & (1 << j))) {
          if (adj[i][j]) {
            flip[mask]++;
            //complementary graph not connected, need to connect
          } 
          else {
            flip[mask]--;
            //complementary graph already connected, minus 1 for net change
          }
        }
      }
    }
  }
  dp[0] = N * (N - 1) / 2 - M;//cost to make all pairs connected in complementary graph
  for (int mask = 1; mask < (1 << N); mask++) {
    dp[mask] = INF;
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
      dp[mask] = min(dp[mask], dp[mask & ~sub] + flip[sub]);            
      //mask & ~sub is mask without sub, already connected
    }
  }
  cout << dp[(1 << N) - 1] << endl;
}
