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

const int maxN = 2555;

int n, GLESS[maxN], GTALL[maxN], BLESS[maxN], BTALL[maxN];

void cleanup() {
    FILL(GLESS, 0);
    FILL(BLESS, 0);
    FILL(GTALL, 0);
    FILL(BTALL, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        int x;
        for(int i = 0; i < n; ++i) {
            scanf("%d", &x);
            if(x > 0) {
                BTALL[x]++;
            }
            else {
                BLESS[abs(x)]++;
            }
        }
        for(int i = 0; i < n; ++i) {
            scanf("%d", &x);
            if(x > 0) {
                GTALL[x]++;
            }
            else {
                GLESS[abs(x)]++;
            }
        }
        return true;
    }
    return false;
}

void Run() {
    int answer = 0;
    for(int g = 1500; g <= 2500; ++g) {
        if(GLESS[g]) {
            for(int b = 1500; b < g; ++b) {
                if(BTALL[b]) {
                    int mmin = min(BTALL[b], GLESS[g]);
                    answer += mmin;
                    GLESS[g] -= mmin;
                    BTALL[b] -= mmin;
                }
            }
        }
    }
    for(int g = 2500; g >= 1500; --g) {
        if(GTALL[g]) {
            for(int b = 2500; b > g; --b) {
                if(BLESS[b]) {
                    int mmin = min(GTALL[g], BLESS[b]);
                    GTALL[g] -= mmin;
                    BLESS[b] -= mmin;
                    answer += mmin;
                }
            }
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
