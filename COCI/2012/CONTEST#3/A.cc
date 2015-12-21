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

const int maxN = 500 + 7;
const int maxV = 3 * maxN * maxN;

int n, numbering, D[maxN][maxN + maxN], N[maxN][maxN + maxN], W[maxV];
vector< pair<int, int> > G[maxV];

void cleanup() {
   FILL(D, -1);
   FILL(W, 63);
   numbering = 0;
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int it = 0; it < n; ++it) {
            if((it + 1) & 1) {
                int u, v;
                for(int i = 0; i < n; ++i) {
                    scanf("%d%d", &u, &v);
                    D[it][i * 2] = u, D[it][i * 2 + 1] = v;
                    N[it][i * 2] = numbering++; N[it][i * 2 + 1] = numbering++;
                    G[N[it][i * 2]].pb(mp(N[it][i * 2 + 1], 0));
                    G[N[it][i * 2 + 1]].pb(mp(N[it][i * 2], 0));
                }
            }
            else {
                int u, v;
                for(int i = 1; i < n; ++i) {
                    scanf("%d%d", &u, &v);
                    D[it][i * 2 - 1] = u, D[it][i * 2] = v;
                    N[it][i * 2 - 1] = numbering++; N[it][i * 2] = numbering++;
                    G[N[it][i * 2 - 1]].pb(mp(N[it][i * 2], 0));
                    G[N[it][i * 2]].pb(mp(N[it][i * 2 - 1], 0));
                }
            }
        }
        return true;
    }
    return false;
}

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < 2 * n;
}

void dijkstra() {
    W[0] = 0;
    set< pair<int, int> > d;
    d.insert(mp(0, 0));
    while(!d.empty()) {
        pair<int, int> curr = *d.begin();
        d.erase(d.begin());
        int v = curr.second;
        for(int i = 0; i < SZ(G[v]); ++i) {
            int to = G[v][i].first, len = G[v][i].second;
            if(W[to] > W[v] + len) {
                d.erase(mp(W[to], to));
                W[to] = W[v] + len;
                d.insert(mp(W[to], to));
            }
        }
    }
}

void Run() {
    eprintf("D:\n");
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 2 * n; ++j) {
            eprintf("%d ", D[i][j]);
        }
        eprintf("\n");
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 2 * n; ++j) {
            if(D[i][j] == -1) continue;
            for(int k = 0; k < 4; ++k) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(valid(nx, ny) && D[i][j] == D[nx][ny]) {
                    G[N[nx][ny]].pb(mp(N[i][j], 1));
                    G[N[i][j]].pb(mp(N[nx][ny], 1));
                }
            }
        }
    }
    dijkstra();
    for(int i = numbering - 1; i >=0; --i) {
        if(W[i] < 1000000) {
            printf("%d\n", 1 + W[i]);
            break;
        }
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
