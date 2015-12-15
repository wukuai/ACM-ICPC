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

const int maxN = 100 + 7;
const int maxW = 500 + 7;

int BUBEN = 10000;

int N, W, start[maxN], finish[maxN], pos[maxN], direction[maxN], canMove[maxW];

int simulate() {
  int x = 0, i;
  for(int i = 0; i < N; ++i) {
    pos[i] = start[i];
    direction[i] = 1;
  }
  for(i = 0; i < BUBEN && x < W; ++i) {
    FILL(canMove, 0);
    for(int i = 0; i < N; ++i) {
      pos[i] += direction[i];
      if(direction[i] == 1) canMove[pos[i] - direction[i]] = 1;
      if(pos[i] == start[i] || pos[i] == finish[i]) direction[i] *= -1;
    }
    if(canMove[x]) ++x;
    else if(!canMove[x - 1]) --x;
  }
  if(x != W) return -1;
  return i;
}

void cleanup() {
   
}

bool Read() {
  cleanup();
  if(scanf("%d%d", &N, &W) == 2) {
    for(int i = 0; i < N; ++i) {
      scanf("%d%d", start + i, finish + i);
    }
    return true;
  }
  return false;
}

void Run() {
  int ans = simulate();
  if(ans == -1) {
    printf("IMPOSSIBLE\n");
  }
  else {
    printf("%d\n", ans);
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
