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
#define SIZE(x) ((int)x.size())
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define ALL(X) X.begin(), X.end()
#define SORT(x) sort(ALL(x))
#define REVERSE(x) reverse(ALL(x))
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

const int maxC = 207;
const int maxR = 2007;

vector< pair<int, int> > G[2 * maxR];
int n, m, A[maxR][maxC], D[2 * maxR][2 * maxR], SUM[maxR][maxC];

void cleanup() {
    FILL(D, 63);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                scanf("%d", &A[i][j]);
            }
        }
        return true;
    }
    return false;
}

void Dijkstra(int v) {
    D[v][v] = 0;
    priority_queue< pair<int, int> > q;
    q.push(mp(0, v));
    while(!q.empty()) {
        int u = q.top().second, l = -q.top().first;
        q.pop();
        if(l > D[v][u]) continue;
        for(int i = 0; i < SIZE(G[u]); ++i) {
            int to = G[u][i].first, w = G[u][i].second;
            if(D[v][to] > D[v][u] + w) {
                D[v][to] = D[v][u] + w;
                q.push(mp(-D[v][to], to));
            }
        }
    }
}

inline int get_sum(int idx, int l, int r) {
    if(l > r) return 0;
    int ret = SUM[idx][r];
    if(l - 1 >= 0) {
        ret -= SUM[idx][l - 1];
    }
    return ret;
}

void Run() {
    for(int i = 0; i < n; ++i) {
        SUM[i][0] = A[i][0];
        for(int j = 1; j < m; ++j) {
            SUM[i][j] = SUM[i][j - 1] + A[i][j];
        }
    }
    for(int i = 0; i < n; ++i) {
        if(i + 1 < n) {
            G[i].pb(mp(i + 1, A[i + 1][0]));
            G[n + i].pb(mp(n + i + 1, A[i + 1][m - 1]));
        }
        if(i - 1 >= 0) {
            G[i].pb(mp(i - 1, A[i - 1][0]));
            G[n + i].pb(mp(n + i - 1, A[i - 1][m - 1]));
        }
        G[i].pb(mp(n + i, SUM[i][m - 1] - A[i][0]));
        G[n + i].pb(mp(i, SUM[i][m - 1] - A[i][m - 1]));
    }
    for(int i = 0; i < n; ++i) {
        Dijkstra(i);
        Dijkstra(n + i);
    }
    int currX = 0;
    int currY = 0;
    int queries, x, y;
    long long answer = A[0][0];
    scanf("%d", &queries);
    for(int i = 0; i < queries; ++i) {
        int mmin = IINF;
        scanf("%d%d", &x, &y); --x, --y;
        if(x == currX) {
            if(currY < y) {
                check_min(mmin, get_sum(x, currY + 1, y));
            }
            else {
                check_min(mmin, get_sum(x, y, currY - 1));
            }
        }
        int sumToLeft = get_sum(currX, 0, currY - 1);
        int sumToRight = get_sum(currX, currY + 1, m - 1);
        int sumFromLeft = get_sum(x, 1, y);
        int sumFromRight = get_sum(x, y, m - 2);
        check_min(mmin, sumToLeft + D[currX][x] + sumFromLeft);
        check_min(mmin, sumToLeft + D[currX][n + x] + sumFromRight);
        check_min(mmin, sumToRight + D[currX + n][x + n] + sumFromRight);
        check_min(mmin, sumToRight + D[currX + n][x] + sumFromLeft);
        answer += mmin;
        currX = x, currY = y;
    }
    printf(LLD"\n", answer);
}

} // Solution

namespace StressTest {

void GenerateInput() {
    FILE* output = fopen("input.txt", "w");

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
    srand(time(NULL));
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
