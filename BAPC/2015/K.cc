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

long long R, S, Q;

void cleanup() {
   
}

bool Read() {
    cleanup();
    if(scanf("%lld%lld%lld", &R, &S, &Q) == 3) {
      return true;
    }
    return false;
}

long long gcd(long long a, long long b, long long& x, long long& y) {
  if(a == 0) {
    x = 0, y = 1;
    return b;
  }
  long long x1, y1;
  long long d = gcd(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

void Run() {
  long long G, X, Y;
  G = gcd(R, S, X, Y);
  X *= Q / G;
  Y *= Q / G;
  long long T = S / G;
  long long W = -R / G;
  long long Z = (1 - X) / T, U = (1 - Y) / W, A = -1, B = -1;
  for(long long I = Z - 5; I <= Z + 5; ++I) {
    long long tmp1 = X + I * T;
    long long tmp2 = Y + I * W;
    if(tmp1 >= 1 && tmp2 >= 1) {
      if(A == -1 || mp(tmp1, tmp2) < mp(A, B)) {
        A = tmp1, B = tmp2;
      }
    }
  }
  for(long long I = U - 5; I <= U + 5; ++I) {
    long long tmp1 = X + I * T;
    long long tmp2 = Y + I * W;
    if(tmp1 >= 1 && tmp2 >= 1) {
      if(A == -1 || mp(tmp1, tmp2) < mp(A, B)) {
        A = tmp1, B = tmp2;
      }
    }
  }
  printf(LLD " " LLD"\n", A, B);
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
