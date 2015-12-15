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

int n, m, dp[1 << 16];
vector<int> g[16];

void cleanup() {
   for(int i = 0; i < 20; ++i) {
     g[i].resize(0);
   }
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
      int u, v;
      for(int i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        g[u].pb(v);
        g[v].pb(u);
      }
      return true;
    }
    return false;
}

void Run() {
  dp[0] = 0;
  int to = 0;
  for(int mask = 1; mask < (1 << n); ++mask) {
    dp[mask] = IINF;
    bool one_colorable = true;
    for(int i = 0; i < n && one_colorable; ++i) {
      if(mask & (1 << i)) {
        for(int j = 0; j < SZ(g[i]) && one_colorable; ++j) {
          to = g[i][j];
          if(mask & (1 << to)) {
            one_colorable = false;
          }
        }
      }
    }
    if(one_colorable) {
      dp[mask] = 1;
    }
    else {
      for(int msk = mask; msk; msk = mask & (msk - 1)) {
        if(dp[msk] == 1) {
          dp[mask] = min(dp[mask], dp[mask ^ msk] + 1);
        }
      }
    }
  }
  if(dp[(1 << n) - 1] <= 4) {
    printf("%d\n", dp[(1 << n) - 1]);
  }
  else {
    printf("many\n");
  }


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
//    StressTest::GenerateInput();
//    StressTest::BruteForce();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int test_cases;
    scanf("%d", &test_cases);

    for(int test_id = 1; test_id <= test_cases; ++test_id) {
#ifdef _DEBUG_
        clock_t startTime = clock();
        eprintf("Begin of test #%d:\n", test_id);
#endif

        Solution::Read();
        Solution::Run();

#ifdef _DEBUG_
        clock_t endTime = clock();
        eprintf("Time consumed for test #%d is %lf\n", test_id, (double)(endTime - startTime) / (double)CLOCKS_PER_SEC);
#endif
    }
    return 0;
}
