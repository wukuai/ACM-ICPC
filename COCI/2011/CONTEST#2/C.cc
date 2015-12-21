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

const int maxN = 500000 + 7;
const int maxT = 8 * maxN;

int n, m, c, A[maxN], F[maxN], S[maxN], U[maxN], L[maxT];
vector<int> G[maxN];
int T[maxT];

void cleanup() {
    c = 0;
    FILL(F, 0);
    FILL(S, 0);
    FILL(U, 0);
}

bool Read() {
    cleanup();
    int x;
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", A + i);
            if(i) {
                scanf("%d", &x);
                G[x - 1].pb(i);
            }
        }
        return true;
    }
    return false;
}

void dfs(int v) {
    U[v] = true;
    L[c] = v;
    F[v] = c; 
    ++c;
    eprintf("%d ", v);
    for(int to : G[v]) {
        if(!U[to]) {
            dfs(to);
        }
    }
    eprintf("%d ", v);
    L[c] = v;
    S[v] = c;
    ++c;
}

void update(int v, int tl, int tr, int l, int r, int delta) {
    if(l > r) return ;
    if(tl == l && r == tr) {
        T[v] += delta;
    }
    else {
        int tm = (tl + tr) / 2;
        update(v << 1, tl, tm, l, min(r, tm), delta);
        update((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r, delta);
    }
}

int get_it(int v, int tl, int tr, int pos) {
    if(tl == tr) {
        return T[v];
    }
    else {
        int tm = (tl + tr) / 2;
        if(pos <= tm) {
            return T[v] + get_it(v << 1, tl, tm, pos);
        }
        else {
            return T[v] + get_it((v << 1) | 1, tm + 1, tr, pos);
        }
    }
}

void Run() {
    int u, x;
    dfs(0);
    eprintf("\nc=%d\n", c);
    char command;
    for(int i = 0; i < m; ++i) {
        scanf(" %c", &command);
        if(command == 'p') {
            scanf("%d%d", &u, &x);
            --u;
            update(1, 0, c - 1, F[u] + 1, S[u] - 1, x);
        }
        else {
            scanf("%d", &u);
            --u;
            printf("%d\n", A[u] + get_it(1, 0, c - 1, F[u]));
        }
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
