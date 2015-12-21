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

const int maxN = (int) 1e6 + 10;

bool pos[maxN];
int n, a[maxN], who[maxN], last_cnt[maxN], mmax[maxN];

void cleanup() {
  for(int i = 0; i < maxN; ++i) {
    pos[i] = false;
    who[i] = mmax[i] = last_cnt[i] = -1;
  }
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
      for(int i = 0; i < n; ++i) {
        scanf("%d", a + i);
      }
      return true;
    }
    return false;
}

void Run() {
  long long answer = 0;
  for(int i = 0; i < n; ++i) {
    if(pos[a[i]] == false && pos[a[i] + 1] == false) {
      who[a[i]] = a[i];
      mmax[a[i]] = 1;
      last_cnt[a[i]] = 1;
      pos[a[i]] = true;
    }
    else if(pos[a[i]] != false && pos[a[i] + 1] == false) {
      if(who[a[i]] != a[i]) {
        if(last_cnt[a[i]] + 1 < mmax[a[i]]) {
          last_cnt[a[i]]++;
        }
        else if(last_cnt[a[i]] + 1 == mmax[a[i]]) {
          who[a[i]] = a[i];
          last_cnt[a[i]] = mmax[a[i]];
        }
      }
      else {
        mmax[a[i]]++;
        last_cnt[a[i]]++;
      }
    }
    else if(pos[a[i]] == false && pos[a[i] + 1] != false) {
      if(mmax[a[i] + 1] == 1) {
        who[a[i]] = a[i];
        last_cnt[a[i]] = 1;
        mmax[a[i]] = 1;
        pos[a[i]] = true;
        pos[a[i] + 1] = false;
      }
      else {
        who[a[i]] = who[a[i] + 1];
        mmax[a[i]] = mmax[a[i] + 1];
        last_cnt[a[i]] = 1;
        pos[a[i]] = true;
        pos[a[i] + 1] = false;
      }
    }
    else if(pos[a[i]] && pos[a[i] + 1]) {
      if(last_cnt[a[i]] + 1 < mmax[a[i]]) { // go group a[i]
        last_cnt[a[i]]++;
      }
      else if(last_cnt[a[i]] + 1 == mmax[a[i]]) { // group a[i]
        last_cnt[a[i]]++;
        who[a[i]] = a[i];
      }
      else { // go group a[i] + 1
        answer += mmax[a[i]];
        last_cnt[a[i]] = 1;
        mmax[a[i]] = mmax[a[i] + 1];
        pos[a[i] + 1] = false;
        if(mmax[a[i] + 1] == 1) {
          who[a[i]] = a[i];
        }
        else {
          who[a[i]] = who[a[i] + 1];
        }
      }
    }
  }
  for(int i = 0; i < maxN; ++i) {
    if(pos[i]) answer += mmax[i];
  }
  printf("%lld\n", answer);
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
