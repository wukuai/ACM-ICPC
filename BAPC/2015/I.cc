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
#include <unordered_map>
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

int m, n, d[3003], q[3003];
vector<int> g[3003];
unordered_map<string, int> ranks;

void cleanup() {
   n = 0;
   for(int i = 0; i < 3003; ++i) {
     g[i].resize(0);
   }
}

bool Read() {
    cleanup();
    return scanf("%d", &m) == 1;
}

int lookup(string s) {
  if(ranks.find(s) == ranks.end()) {
    ranks[s] = n++;
  }
  return ranks[s];
}

void Run() {
  char bufferu[128], bufferv[128];
  for(int i = 0; i < m; ++i) {
    scanf("%s%s", bufferu, bufferv);
    g[lookup(bufferu)].pb(lookup(bufferv));
    g[lookup(bufferv)].pb(lookup(bufferu));
  }
  int out = 0;
  for(int i = 0; i < n; ++i) {
    int qh = 0, qt = 0, v;
    q[qt++] = i;
    FILL(d, -1);
    d[i] = 0;
    int mmax = 0;
    while(qh < qt) {
      v = q[qh++];
      mmax = max(mmax, d[v]);
      for(int i = 0; i < SZ(g[v]); ++i) {
        if(d[g[v][i]] == -1) {
          d[g[v][i]] = d[v] + 1;
          q[qt++] = g[v][i];
        }
      }
    }
    if(mmax >= 7) {
      ++out;
    }
  }
  if(out * 100 <= 5 * n) {
    printf("YES\n");
  }
  else {
    printf("NO\n");
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
