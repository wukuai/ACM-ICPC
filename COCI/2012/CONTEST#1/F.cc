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

const int maxN = 500 * 1000 + 7;

pair<int, int> D[maxN];
int n, PREF[maxN], SUFF[maxN];
long long S[maxN];

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", &D[i].first, &D[i].second);
        }
        return true;
    }
    return false;
}

bool cmp(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.second < rhs.second;
}

void Run() {
    long long ans = 0;
    sort(D, D + n, cmp);
    S[0] = D[0].second;
    for(int i = 1; i < n; ++i) {
        S[i] = S[i - 1] + D[i].second;
    }
    PREF[0] = D[0].first - D[0].second;
    for(int i = 1; i < n; ++i) {
        PREF[i] = D[i].first - D[i].second;
        check_min(PREF[i], PREF[i - 1]);
    }
    SUFF[n - 1] = D[n - 1].first;
    for(int i = n - 2; i >= 0; --i) {
        SUFF[i] = D[i].first;
        check_min(SUFF[i], SUFF[i + 1]);
    }
    long long v, r;
    for(int k = 1; k <= n; ++k) {
        v = 0;
        if(k - 2 >= 0) {
            v = S[k - 2];
        }
        ans = v + SUFF[k - 1];
        check_min(ans, S[k - 1] + PREF[k - 1]);
        printf(LLD"\n", ans);
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
