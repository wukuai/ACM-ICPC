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

const int maxM = 1000 + 7;
const int maxK = 1000 + 7;
const int maxN = 100 * 1000 + 7;

int n, m, k, D[maxN];
vector<int> G[maxN];
set<int> N[maxM];

void cleanup() {
    for(int i = 0; i < maxN; ++i) {
        D[i] = IINF;
        G[i].clear();
    }
    for(int i = 0; i < maxM; ++i) {
        N[i].clear();
    }
}

bool Read() {
    cleanup();
    if(scanf("%d%d%d", &n, &k, &m) == 3) {
        for(int i = 0; i < m; ++i) {
            int x;
            for(int j = 0; j < k; ++j) {
                scanf("%d", &x);
                G[x - 1].pb(i);
                N[i].insert(x - 1);
            }
        }
        return true;
    }
    return false;
}

void Run() {
    queue<int> q;
    q.push(0);
    D[0] = 0;
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        vector< pair<int, int> > to_delete;
        for(int i = 0; i < SZ(G[v]); ++i) {
            for(set<int>::iterator it = N[G[v][i]].begin(); it != N[G[v][i]].end(); ++it) {
                // grouppa G[v][i]
                // number *it
                //N[*it].erase(G[v][i]);
                to_delete.pb(mp(*it, G[v][i]));
                if(D[*it] == IINF) {
                    D[*it] = D[v] + 1;
                    q.push(*it);
                }
            }
        }
        for(int i = 0; i < SZ(to_delete); ++i) {
            N[to_delete[i].second].erase(to_delete[i].first);
        }
    }
    if(D[n - 1] < IINF) {
        printf("%d\n", 1 + D[n - 1]);
    }
    else {
        printf("-1\n");
    }
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
