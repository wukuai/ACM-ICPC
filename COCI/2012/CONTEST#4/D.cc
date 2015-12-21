#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <iostream>
using namespace std;

//--------------------------------------------
#define SZ(x) ((int)x.size())
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define ALL(X) X.begin(), X.end()
#define SRT(x) sort(ALL(x))
#define RVRS(x) reverse(ALL(x))
#define FILL(x, value) memset(x, value, sizeof(x))

#define next next1
#define hash hash1
#define rank rank1

#ifdef _DEBUG_
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

#if((_WIN32 || __WIN32__) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

template <class T> inline void check_max(T& actual, T check) {
    if(actual < check) {
        actual = check;
    }
}

template <class T> inline void check_min(T& actual, T check) {
    if(actual > check) {
        actual = check;
    }
}   

const double EPS = 1e-9;
const int IINF = 1000000000;
const double PI = acos(-1.0);
const long long LINF = 6000000000000000000LL;
//--------------------------------------------

namespace Solution {

const int maxN = 1000 + 7;

int n, d[maxN][maxN], boss[maxN], parent[maxN], rank[maxN];

void cleanup() {
  for(int i = 0; i < maxN; ++i) {
    parent[i] = i;
    rank[i] = 1;
  }
}

int get_parent(int v) {
  if(parent[v] != v) {
    return parent[v] = get_parent(parent[v]);
  }
  return v;
}

void unite(int a, int b) {
  a = get_parent(a);
  b = get_parent(b);
  if(a == b) return ;
  if(rank[a] > rank[b]) {
    parent[b] = a;
    rank[a] += rank[b];
  }
  else {
    parent[a] = b;
    rank[b] += rank[a];
  }
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
      for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
          scanf("%d", &d[i][j]);
        }
      }
      for(int i = 0; i < n; ++i) {
        scanf("%d", boss + i);
      }
      return true;
    }
    return false;
}

void Run() {
  vector< tuple<long long, int, int> > edges;

  for(int i = 0; i < n; ++i) {
    edges.pb(make_tuple(boss[i] * 1LL, i, i));
    for(int j = i + 1; j < n; ++j) {
      edges.pb(make_tuple(d[i][j] * 1LL, i, j));
    }
  }
  SRT(edges);
  long long answer = 0;
  for(int i = 0; i < SZ(edges); ++i) {


}

} // Solution

namespace StressTest {

long long GetTime() {
    srand(time(NULL));
    return rand() << 16LL;
}

void GenerateInput() {
    FILE* output = fopen("input.txt", "w");
    srand(GetTime());

    
    fclose(output);
}

void BruteForce() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("brute.out", "w");

    fclose(input);
    fclose(output);
}

} // StressTest

int main() {
#ifdef _DEBUG_
    int test_id = 0;
//    StressTest::GenerateInput();
//    StressTest::BruteForce();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Solution::Read()) {
#ifdef _DEBUG_
        clock_t startTime = clock();
        eprintf("Begin of test #%d:\n", ++test_id);
#endif

        Solution::Run();

#ifdef _DEBUG_
        clock_t endTime = clock();
        eprintf("Time consumed for test #%d is %lf\n", test_id, (double)(endTime - startTime) / (double)CLOCKS_PER_SEC);
#endif
    }
    return 0;
}
