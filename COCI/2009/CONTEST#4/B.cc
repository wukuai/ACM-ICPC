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

const int maxN = 11;

unordered_set<int> damaged;
unordered_set<int> reserve;
int n, r, s, DP[maxN][1 << maxN];

void cleanup() {
    FILL(DP, -1);
    damaged.clear();
    reserve.clear();
}

bool Read() {
    cleanup();
    if(scanf("%d%d%d", &n, &s, &r) == 3) {
        int x;
        for(int i = 0; i < s; ++i) {
            scanf("%d", &x);
            damaged.insert(x - 1);
        }
        for(int i = 0; i < r; ++i) {
            scanf("%d", &x);
            reserve.insert(x - 1);
        }
        return true;
    }
    return false;
}

int go(int pos, int mask) {
    if(pos == n) {
        return 0;
    }
    int& ref = DP[pos][mask];
    if(ref != -1) {
        return ref;
    }
    ref = IINF;
    if(damaged.find(pos) == damaged.end()) { // current is not damaged
        check_min(ref, go(pos + 1, mask));
    }
    else { // current is damaged
        if(reserve.find(pos) == reserve.end()) { // do not have reserve
            check_min(ref, 1 + go(pos + 1, mask));
            if(pos - 1 >= 0 && reserve.find(pos - 1) != reserve.end() && !(mask & (1 << (pos - 1)))) {
                check_min(ref, go(pos + 1, mask ^ (1 << (pos - 1))));
            }
            if(pos + 1 < n && reserve.find(pos + 1) != reserve.end() && damaged.find(pos + 1) == damaged.end()) {
                check_min(ref, go(pos + 1, mask ^ (1 << (pos + 1))));
            }
        }
        else { // have reserve
            check_min(ref, go(pos + 1, mask ^ (1 << pos)));
        }
    }
    return ref;
}

void Run() {
    printf("%d\n", go(0, 0));
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
