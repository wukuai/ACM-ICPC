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

const int maxN = 300007;

int n, q, ANSWER[maxN], TO[maxN], USED[maxN], COLOR[maxN], OUT[maxN], TYPE[maxN], VERT[maxN], P[maxN], PARENT[maxN], DESTINATION[maxN];

void cleanup() {
    FILL(P, -1);
    FILL(OUT, -1);
    FILL(USED, 0);
    FILL(COLOR, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        int x;
        for(int i = 0; i < n; ++i) {
            scanf("%d", &x);
            TO[i] = OUT[i] = x - 1;
            
        }
        scanf("%d", &q);
        for(int i = 0; i < q; ++i) {
            scanf("%d%d", TYPE + i, VERT + i);
            --VERT[i];
        }
        return true;
    }
    return false;
}

void detect_cycle(int s, int e) {
    eprintf("cycle: st=%d en=%d\n", s, e);
    while(e != s) {
        DESTINATION[e] = -1;
        PARENT[e] = e;
        e = P[e];
    }
    DESTINATION[s] = -1;
    PARENT[s] = s;
}

void dfs(int v) {
    COLOR[v] = 1;
    if(OUT[v] != -1) {
        if(COLOR[OUT[v]] == 1) {
            detect_cycle(OUT[v], v);
        }
        else if(COLOR[OUT[v]] == 0) {
            P[OUT[v]] = v;
            dfs(OUT[v]);
        }
    }
    COLOR[v] = 2;
}

int set_parent(int v) {
    if(USED[v] == true) {
        return PARENT[v];
    }
    USED[v] = true;
    if(OUT[v] == -1) {
        return PARENT[v] = v;
    }
    return PARENT[v] = set_parent(OUT[v]);
}

int get_parent(int v) {
    if(PARENT[v] == v) {
        return v;
    }
    return PARENT[v] = get_parent(PARENT[v]);
}

void Run() {
    for(int i = 0; i < n; ++i) {
        PARENT[i] = i;
        DESTINATION[i] = i;
    }
    for(int i = 0; i < q; ++i) {
        if(TYPE[i] == 2) {
            OUT[VERT[i]] = -1;
        }
    }
    for(int i = 0; i < n; ++i) {
        if(COLOR[i] == 0) {
            dfs(i);
        }
    }
    for(int i = 0; i < n; ++i) {
        if(DESTINATION[i] != -1) {
            set_parent(i);
        }
    }
    for(int i = q - 1; i >= 0; --i) {
        if(TYPE[i] == 1) {
            int k = get_parent(VERT[i]);
            ANSWER[i] = DESTINATION[k];
        }
        else {
            int k = get_parent(TO[VERT[i]]);
            if(k == VERT[i]) {
                DESTINATION[k] = -1;
            }
            else {
                PARENT[VERT[i]] = k;
            }
        }
    }
    for(int i = 0; i < q; ++i) {
        if(TYPE[i] == 2) continue;
        if(ANSWER[i] == -1) {
            printf("CIKLUS\n");
        }
        else {
            printf("%d\n", ANSWER[i] + 1);
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
