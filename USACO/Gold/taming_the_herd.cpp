//https://usaco.org/index.php?page=viewproblem2&cpid=815
/*
Let dp[i][j] be the the minimum number of changes that must be made to the first j entries so that there are i breakouts among the first j entries. 
Define dp state, remove excess!!!!!notice how small n is!!!!(note i and j can also be other way around to make the loops easier to understand)
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("taming.in");
    ofstream fout("taming.out");

    int n;
    fin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }

    // precompute cost[l][r]:
    //number of mismatches if a breakout starts at l and ends at r
    vector<vector<int>> cost(n, vector<int>(n, 0));
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            if (r == l) {
                cost[l][r] = (a[r] == 0 ? 0 : 1);
            } else {
                cost[l][r] = cost[l][r - 1] + (a[r] == r - l ? 0 : 1);
            }
        }
    }

    // dp[k][d] = min changes using k breakouts covering days [0..d]
    vector<vector<int>> dp(n + 1, vector<int>(n, INT_MAX));

    for (int k = 1; k <= n; k++) {
        for (int d = k - 1; d < n; d++) {

            if (d == 0) {//initialize
                dp[k][d] = (a[0] == 0 ? 0 : 1);
                continue;
            }

            // Case 1: log was tampered with and the cows would NOT breakout
            //breakout num same, but change current log to correct days(not 0)
            if (dp[k][d - 1] != INT_MAX) {
                dp[k][d] = dp[k][d - 1] + 1;
            }

            // Case 2: log was tampered with and the cows would breakout
            //breakout num +1, change curr log to 0
            if (a[d] > 0 && dp[k - 1][d - 1] != INT_MAX) {
                dp[k][d] = min(dp[k][d], dp[k - 1][d - 1] + 1);
            }

            // Case 3: log was NOT tampered with
            //i-th breakout would be on the (j−a[j])-th day
            //use dp[i - 1][j−a[j]-1] + cost of change vals on j−a[j] to j to correct ones
            int start = d - a[d];
            if (start - 1 >= 0 && dp[k - 1][start - 1] != INT_MAX) {
                dp[k][d] = min(dp[k][d],
                               dp[k - 1][start - 1] + cost[start][d]);
            }

            // Special case: prev breakout starts at day 0
            if (start == 0 && k == 1) {
                dp[k][d] = min(dp[k][d], cost[0][d]);
            }
        }
    }

    for (int k = 1; k <= n; k++) {
        fout << dp[k][n - 1] << '\n';
    }

    return 0;
}
