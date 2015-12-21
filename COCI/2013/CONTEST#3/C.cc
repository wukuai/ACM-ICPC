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

const int maxN = 100 * 1000 + 7;
const int maxM = 300 * 1000 + 7;

bool ok;
vector<int> g[maxN];
int n, m, color[maxM], u[maxM], v[maxM];

void cleanup() {
   
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", u + i, v + i);
            --u[i], --v[i];
        }
        return true;
    }
    return false;
}

void dfs(int v, int c) {
    if(!ok) return ;
    color[v] = c;
    for(int to : g[v]) {
        if(color[to] == -1) {
            dfs(to, c ^ 1);
        }
        else if(color[to] == c) {
            ok = false;
        }
    }
}

void Run() {
    int answer = -1;
    int lo = 0, hi = m - 1;
    while(lo <= hi) {
        ok = true;
        int mid = (lo + hi) / 2;
        eprintf("checking mid=%d ", mid);
        for(int i = 0; i < n; ++i) {
            color[i] = -1;
            g[i].clear();
        }
        for(int i = 0; i <= mid; ++i) {
            g[u[i]].pb(v[i]);
            g[v[i]].pb(u[i]);
        }
        for(int i = 0; i < n; ++i) {
            if(color[i] == -1) {
                dfs(i, 0);
            }
        }
        eprintf("res=%d\n", ok ? 1 : 0);
        if(ok) {
            answer = mid;
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    assert(answer != -1);
    printf("%d\n", answer + 2);
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
