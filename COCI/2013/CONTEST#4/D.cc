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

const int maxN = 300 * 1000 + 7;

int n;
long long a[maxN], b[maxN];

void cleanup() {
   
}

inline long long ABS(long long x) {
    return x < 0 ? -x : x;
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf(LLD, a + i);
        }
        for(int i = 0; i < n; ++i) {
            scanf(LLD, b + i);
        }
        return true;
    }
    return false;
}

long long f(long long x) {
    long long s = 0;
    for(int i = 0; i < n / 2; ++i) {
        s += ABS(x - i - a[i]) + ABS(x - i - b[i]);
    }
    s += ABS(x - n / 2 - a[n / 2]) + ABS(x - n / 2 - b[n / 2]);
    int cnt = n / 2 - 1;
    for(int i = n / 2 + 1; i < n; ++i) {
        s += ABS(x - cnt - a[i]) + ABS(x - cnt - b[i]);
        --cnt;
    }
    return s;
}

void Run() {
    long long lo = 0, hi = 1000LL * 1000LL * 1000LL * 1000LL + 100000000LL;
    while(hi - lo > 3) {
        long long m1 = lo + (hi - lo) / 3;
        long long m2 = hi - (hi - lo) / 3;
        long long f1 = f(m1), f2 = f(m2);
        if(f1 > f2) {
            lo = m1;
        }
        else {
            hi = m2;
        }
    }
    long long answer = LINF;
    for( ; lo <= hi; ++lo) {
        check_min(answer, f(lo));
    }
    printf(LLD"\n", answer);
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
