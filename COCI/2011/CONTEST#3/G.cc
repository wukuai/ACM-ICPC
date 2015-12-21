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

const int maxN = 100 * 1000 + 7;

int R[maxN], G[maxN], B[maxN], S[259][259][259], n, kk;

void cleanup() {
    FILL(S, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &kk) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d", R + i, G + i, B + i);
            S[R[i] + 1][G[i] + 1][B[i] + 1]++;
        }
        return true;
    }
    return false;
}

int sum(int r1, int g1, int b1, int r2, int g2, int b2) {
    int ret = S[r2][g2][b2];
    ret -= S[r2][g2][b1 - 1];
    ret -= S[r2][g1 - 1][b2];
    ret -= S[r1 - 1][g2][b2];
    ret += S[r2][g1 - 1][b1 - 1];
    ret += S[r1 - 1][g2][b1 - 1];
    ret += S[r1 - 1][g1 - 1][b2];
    ret -= S[r1- 1][g1 - 1][b1 - 1];
    return ret;
}

bool check(int difference) {
    for(int r = 1; r + difference <= 256; ++r) {
        for(int g = 1; g + difference <= 256; ++g) {
            for(int b = 1; b + difference <= 256; ++b) {
                if(sum(r, g, b, r + difference, g + difference, b + difference) >= kk) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Run() {
    for(int i = 1; i <= 256; ++i) {
        for(int j = 1; j <= 256; ++j) {
            for(int k = 1; k <= 256; ++k) {
                S[i][j][k] += S[i - 1][j][k];
                S[i][j][k] += S[i][j - 1][k];
                S[i][j][k] += S[i][j][k - 1];
                S[i][j][k] -= S[i - 1][j - 1][k];
                S[i][j][k] -= S[i - 1][j][k - 1];
                S[i][j][k] -= S[i][j - 1][k - 1];
                S[i][j][k] += S[i - 1][j - 1][k - 1];
            }
        }
    }
    int answer;
    int lo = 0, hi = 256;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        if(check(mid)) {
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
