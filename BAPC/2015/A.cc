//Includes updated
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

const int maxN = 10000 + 7;  

int n, w, l, a[maxN];

void cleanup() {
   
}

bool Read() {
    cleanup();
    if(scanf("%d%d%d", &n, &w, &l) == 3) {
      for(int i = 0; i < w; ++i) {
        scanf("%d", a + i);
      }
      return true;
    }
    return false;
}

bool can(int len) {
  int current = 1, ptr = 0;
  int cnt = 0;
  while(ptr < w) {
    if(a[ptr] - current + 1 > len) {
      ++cnt;
      current = a[ptr];
    }
    else {
      while(ptr < w && a[ptr] - current + 1 <= len) {
        ++ptr;
      }
      --ptr;
      int additional = len - (a[ptr] - current + 1);
      ++cnt;
      current = a[ptr] + additional + 1;
      ++ptr;
    }
  }
  if(current <= n) ++cnt;
  return cnt <= l;
}

void Run() {
  int answer = IINF;
  int lo = 1, hi = n;
  while(lo <= hi) {
    int mid = (lo + hi) / 2;
    if(can(mid)) {
      answer = mid;
      hi = mid - 1;
    }
    else {
      lo = mid + 1;
    }
  }
  printf("%d\n", answer);
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
