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

const int maxN = 200007;
const int maxT = maxN << 2;

struct Data {
    int best;
    int prefix;
    int suffix;
} T[maxT];

int n, q;
char S[maxN];

void cleanup() {
    FILL(T, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &q) == 2) {
        return true;
    }
    return false;
}

void merge_nodes(int v, int l, int tll, int trl, int r, int tlr, int trr) {
    int len_left = trl - tll + 1;
    int len_right = trr - tlr + 1;
    T[v].prefix = T[l].prefix;
    if(T[l].prefix == len_left) {
        if(S[trl] != S[trl + 1]) {
            T[v].prefix = T[l].prefix + T[r].prefix;
        }
    }
    T[v].suffix = T[r].suffix;
    if(T[r].suffix == len_right) {
        if(S[trl] != S[trl + 1]) {
            T[v].suffix = T[r].suffix + T[l].suffix;
        }
    }
    T[v].best = max(T[v].suffix, T[v].prefix);
    T[v].best = max(T[v].best, T[l].best);
    T[v].best = max(T[v].best, T[r].best);
    if(S[trl] != S[trl + 1]) {
        T[v].best = max(T[v].best, T[l].suffix + T[r].prefix);
    }
}

void update(int v, int tl, int tr, int pos) {
    if(tl == tr) {
        S[tl] = S[tl] == 'L' ? 'R' : 'L';
        T[v].best = 1;
        T[v].prefix = 1;
        T[v].suffix = 1;
    }
    else {
        int tm = (tl + tr) / 2;
        if(pos <= tm) {
            update(v << 1, tl, tm, pos);
        }
        else {
            update((v << 1) | 1, tm + 1, tr, pos);
        }
        merge_nodes(v, v << 1, tl, tm, (v << 1) | 1, tm + 1, tr);
    }
}

void Run() {
    for(int i = 0; i < n; ++i) {
        S[i] = 'L';
    }
    for(int i = 0; i < maxT; ++i) {
        T[i].best = 1;
        T[i].prefix = 1;
        T[i].suffix = 1;
    }
    int x;
    for(int i = 0; i < q; ++i) {
        scanf("%d", &x);
        update(1, 0, n - 1, x - 1);
        printf("%d\n", T[1].best);
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
