#include <cstdio>
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
#include <unordered_set>
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

const int maxN = 1000 + 7;

int n, m, A[maxN], B[maxN], grt;
long long MOD = 1000000000, answer = 1;

void cleanup() {
    grt = 0;
    answer = 1;
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", A + i);
        }
        scanf("%d", &m);
        for(int i = 0; i < m; ++i) {
            scanf("%d", B + i);
        }
        return true;
    }
    return false;
}

void bin_pow(long long a, long long k) {
    bool grt1 = false;
    while(k) {
        if(k & 1) {
            answer = answer * a;
            if(grt1) {
                grt = 1;
            }
            if(answer >= MOD) {
                grt = 1;
                answer %= MOD;
            }
        }
        a = a * a;
        if(a >= MOD) {
            a %= MOD;
            grt1 = true;
        }
        k >>= 1;
    }
}

void factorize(int cnt, int T[], vector<int>& ans) {
    ans.reserve(cnt);
    for(int j = 0; j < cnt; ++j) {
        int x = T[j];
        for(int i = 2; i * i <= x; ++i) {
            if(x % i == 0) {
                while(x % i == 0) {
                    ans.pb(i); x /= i;
                }
            }
        }
        if(x > 1) {
            ans.pb(x);
        }
    }
}

void Run() {
    vector<int> fa, fb;
    factorize(n, A, fa);
    factorize(m, B, fb);
    SRT(fa); SRT(fb);
    int ptr = 0;
    for(int i = 0; i < SZ(fa); ++i) {
        while(ptr < SZ(fb) && fb[ptr] < fa[i]) {
            ++ptr;
        }
        if(ptr < SZ(fb) && fb[ptr] == fa[i]) {
            int cnt1 = 0, cnt2 = 0, val = fa[i];
            while(ptr < SZ(fb) && fb[ptr] == val) {
                ++cnt1;
                ++ptr;
            }
            while(i < SZ(fa) && fa[i] == val) {
                ++cnt2;
                ++i;
            }
            --i;
            int cnt = min(cnt1, cnt2);
            bin_pow(val, cnt);
        }
    }
    if(grt) {
        printf("%.9d\n", (int)answer);
    }
    else {
        printf("%d\n", (int)answer);
    }
}

} // Solution

namespace StressTest {

long long GetTime() {
#ifdef __GNUC__ 
    long long res; 
    asm volatile ("rdtsc" : "=A" (res)); 
    return res;
#else
    int low, hi; 
    __asm { 
        rdtsc
        mov low, eax
        mov hi, edx
    }
    return (((long long)hi) << 32LL) | low;
#endif
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
