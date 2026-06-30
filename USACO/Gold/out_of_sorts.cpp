//https://usaco.org/index.php?page=viewproblem2&cpid=837
/*
Compare the original and the sorted array. For each position i, there is an amount Mi of numbers that is on the left side of i in the original array but is on the right side of i in the sorted array. 
Mi is the same amount vice versa. Now, notice that for each bidirectional bubble sort there is exactly 1 and only 1 pair of elements swapped to the side of i that they should be, therefore for each i the number of swaps it takes to make Mi = 0 is Mi. 
Therefore, all we have to do is to compute the maximum Mi across the whole array and use binary index tree to implement the code. 
*/
#include<algorithm>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

int n;
vector<pair<int, int> > a;
int tree[100001];

int sum(int k) {//calculate the sum of the first k numbers
  int s = 0;
  while (k >= 1){//until reach the end
    s += tree[k];
    k -= k&-k;//remove the last place, goes 1 place back
  }
  return s;
}

void add(int k) {//make an addition of x to one position
  while (k <= n) {
    tree[k] ++;
    k += k&-k;//adds by powers of 2, carry up 1 place
  }
}

int main() {
    ifstream cin("sort.in");
    ofstream cout("sort.out");
    cin >>n;
    a.resize(n+1);
    for (int i = 1; i <= n; i++) {
        cin >>a[i].first;
        a[i].second = i;
    }
    sort(a.begin() + 1, a.end());
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        add(a[i].second);
        //marks original position a[i].second is visited
        ans = max(ans, i - sum(i));
        //sum(i) counts how many numbers in total of the first i numbers with smallest value
        //have been visited, which is how many are in the correct half of the sorted array
    }
    cout<<ans<<endl;
    return 0;
}
