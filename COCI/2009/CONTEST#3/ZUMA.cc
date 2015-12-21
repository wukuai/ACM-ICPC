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

const int maxN = 107;

int n, k, A[maxN], DP[maxN][maxN][7];

void cleanup() {
    FILL(DP, 63);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &k) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", A + i);
        }
        return true;
    }
    return false;
}

void Run() {
    for(int i = 0; i < maxN; ++i) {
        for(int j = 0; j < maxN; ++j) {
            if(i > j) {
                for(int l = 0; l < 7; ++l) {
                    DP[i][j][l] = 0;
                }
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int add = 0; add <= k; ++add) {
            DP[i][i][add] = max(0, k - 1 - add);
        }
    }
    for(int i = 0; i + 1 < n; ++i) {
        if(A[i] == A[i + 1]) {
            for(int add = 0; add <= k; ++add) {
                DP[i][i + 1][add] = max(0, k - 2 - add);
            }
        }
        else {
            for(int add = 0; add <= k; ++add) {
                DP[i][i + 1][add] = 2 * k - 2 - add;
            }
        }
    }
    for(int len = 3; len <= n; ++len) {
        for(int i = 0; i + len <= n; ++i) {
            int st = i, fn = i + len - 1, curr = 0;
            for(int t = st; t <= fn && A[t] == A[st]; ++t) {
                ++curr;
            }
            for(int add = 0; add <= k; ++add) {
                check_min(DP[st][fn][add], DP[st + curr][fn][0] + max(0, k - add - curr));
                for(int j = st; j <= fn; ++j) {
                    if(A[st] == A[j] && j >= st + curr) {
                        check_min(DP[st][fn][add], DP[st + curr][j - 1][0] + DP[j][fn][min(k, curr + add)]);
                    }
                }
            }
        }
    }
    printf("%d\n", DP[0][n - 1][0]);
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
