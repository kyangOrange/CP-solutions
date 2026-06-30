//https://usaco.org/index.php?page=viewproblem2&cpid=1499
/*
 If a and c are friends, at least 1 of them must be connected to b. Therefore, if ab no connect and cb no connect, then ac no connect. A complement graph is a graph where everything is flipped, if there originally was connection now there is not and vice versa. Therefore, in the complement graph if ab connect and cb connect then ac connnect. 
Therefore we think of adding edges in the complement graph instead of removing them in the original graph. 
Now, we should perform dp over different combinations of subsets in the graph, where in the complementary graph all the subsets should be fully connected. 
dp[mask] = min(dp[mask], dp[mask & ~sub] + flip[sub]);
flip[sub] is the net amount of changes required to go from current subset to fully connected subset. 
*/
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
