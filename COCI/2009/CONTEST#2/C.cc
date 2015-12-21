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
const int maxT = 4 * maxN;

int n, c, m, COLORS[maxN];
vector<int> MERGE_TREE[maxT];
struct Data {
    int candidate;
    int counter;
    Data() : candidate(0), counter(0) {}
    Data(int ccc, int cc) : candidate(ccc), counter(cc) {}
} T[maxT];

bool Read() {
    if(scanf("%d%d", &n, &c) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", COLORS + i);
        }
        return true;
    }
    return false;
}

void build_tree(int v, int tl, int tr) {
    if(tl == tr) {
        T[v].counter = 1;
        T[v].candidate = COLORS[tl];
    }
    else {
        int tm = (tl + tr) / 2;
        build_tree(v << 1, tl, tm);
        build_tree((v << 1) | 1, tm + 1, tr);
        if(T[v << 1].candidate == T[(v << 1) | 1].candidate) {
            T[v] = T[v << 1];
            T[v].counter += T[(v << 1) | 1].counter;
        }
        else if(T[v << 1].counter > T[(v << 1) | 1].counter) {
            T[v].candidate = T[v << 1].candidate;
            T[v].counter = T[v << 1].counter - T[(v << 1) | 1].counter;
        }
        else {
            T[v].candidate = T[(v << 1) | 1].candidate;
            T[v].counter = T[(v << 1) | 1].counter - T[v << 1].counter;
        }
    }
}

Data query_tree(int v, int tl, int tr, int l, int r) {
    if(l > r) {
        return Data();
    }
    if(tl == l && tr == r) {
        return T[v];
    }
    else {
        int tm = (tl + tr) / 2;
        Data q1 = query_tree(v << 1, tl, tm, l, min(r, tm));
        Data q2 = query_tree((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r);
        if(q1.candidate == q2.candidate) {
            return Data(q1.candidate, q1.counter + q2.counter);
        }
        else if(q1.counter > q2.counter) {
            return Data(q1.candidate, q1.counter - q2.counter);
        }
        else {
            return Data(q2.candidate, q2.counter - q1.counter);
        }
    }
}

void build_merge_tree(int v, int tl, int tr) {
    if(tl == tr) {
        MERGE_TREE[v].pb(COLORS[tl]);
    }
    else {
        int tm = (tl + tr) / 2;
        build_merge_tree(v << 1, tl, tm);
        build_merge_tree((v << 1) | 1, tm + 1, tr);
        MERGE_TREE[v].resize(tr - tl + 1);
        merge(MERGE_TREE[v << 1].begin(), MERGE_TREE[v << 1].end(), MERGE_TREE[(v << 1) | 1].begin(), MERGE_TREE[(v << 1) | 1].end(), MERGE_TREE[v].begin());
    }
}


int query_merge_tree(int v, int tl, int tr, int l, int r, int val) {
    if(l > r) return 0;
    if(tl == l && tr == r) {
        int l_bound = -1;
        int u_bound = -1;
        int lo = 0, hi = SZ(MERGE_TREE[v]) - 1;
        if(hi == 0) {
            if(MERGE_TREE[v][0] == val) {
                l_bound = 0;
            }
        }
        else {
            while(lo <= hi) {
                int mid = (lo + hi) / 2;
                if(MERGE_TREE[v][mid] == val) {
                    l_bound = mid;
                    hi = mid - 1;
                }
                else if(MERGE_TREE[v][mid] > val) {
                    hi = mid - 1;
                }
                else {
                    lo = mid + 1;
                }
            }
        }
        if(l_bound == -1) return 0;
        lo = 0, hi = SZ(MERGE_TREE[v]) - 1;
        if(hi == 0) {
            if(MERGE_TREE[v][0] == val) {
                u_bound = 0;
            }
        }
        else {
            while(lo <= hi) {
                int mid = (lo + hi) / 2;
                if(MERGE_TREE[v][mid] == val) {
                    u_bound = mid;
                    lo = mid + 1;
                }
                else if(MERGE_TREE[v][mid] < val) {
                    lo = mid + 1;
                }
                else {
                    hi = mid - 1;
                }
            }
        }
        return u_bound - l_bound + 1;
    }
    else {
        int tm = (tl + tr) / 2;
        return query_merge_tree(v << 1, tl, tm, l, min(r, tm), val) + query_merge_tree((v << 1) | 1, tm + 1, tr, max(l,tm + 1), r, val);
    }
}

void Run() {
    int l, r;
    build_tree(1, 0, n - 1);
    build_merge_tree(1, 0, n - 1);
    scanf("%d", &m);
    for(int i = 0; i < m; ++i) {
        scanf("%d%d", &l, &r);
        int len = (r - l + 1) / 2;
        int cand = query_tree(1, 0, n - 1, l - 1, r - 1).candidate;
        int count_appearances = query_merge_tree(1, 0, n - 1, l - 1, r - 1, cand);
        if(count_appearances > len) {
            printf("da %d\n", cand);
        }
        else {
            printf("ne\n");
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
