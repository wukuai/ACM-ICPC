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
const int IINF = 10000000;
const double PI = acos(-1.0);
const long long LINF = 6000000000000000000LL;
//--------------------------------------------

namespace Solution {

const int maxN = 507;

char M[maxN][maxN];
bool USED[maxN][maxN];
int n, m, D[maxN][maxN], DUL[maxN][maxN], DUR[maxN][maxN], DDL[maxN][maxN], DDR[maxN][maxN];

int dxUL[] = {-1, 0};
int dyUL[] = {0, -1};

int dxUR[] = {-1, 0};
int dyUR[] = {0, 1};

int dxDL[] = {1, 0};
int dyDL[] = {0, -1};

int dxDR[] = {1, 0};
int dyDR[] = {0, 1};

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

int goUL(int x, int y) {
    if(M[x][y] == '+') {
        DUL[x][y] = 0;
        return 0;
    }
    int& ref = DUL[x][y];
    if(ref != -1) {
        return ref;
    }
    ref = IINF;
    for(int k = 0; k < 2; ++k) {
        int n_x = x + dxUL[k];
        int n_y = y + dyUL[k];
        if(valid(n_x, n_y)) {
            ref = min(ref, 1 + goUL(n_x, n_y));
        }
    }
    return ref;
}

int goUR(int x, int y) {
    if(M[x][y] == '+') {
        DUR[x][y] = 0;
        return 0;
    }
    int& ref = DUR[x][y];
    if(ref != -1) {
        return ref;
    }
    ref = IINF;
    for(int k = 0; k < 2; ++k) {
        int n_x = x + dxUR[k];
        int n_y = y + dyUR[k];
        if(valid(n_x, n_y)) {
            ref = min(ref, 1 + goUR(n_x, n_y));
        }
    }
    return ref;
}

int goDL(int x, int y) {
    if(M[x][y] == '+') {
        DDL[x][y] = 0;
        return 0;
    }
    int& ref = DDL[x][y];
    if(ref != -1) {
        return ref;
    }
    ref = IINF;
    for(int k = 0; k < 2; ++k) {
        int n_x = x + dxDL[k];
        int n_y = y + dyDL[k];
        if(valid(n_x, n_y)) {
            ref = min(ref, 1 + goDL(n_x, n_y));
        }
    }
    return ref;
}

int goDR(int x, int y) {
    if(M[x][y] == '+') {
        DDR[x][y] = 0;
        return 0;
    }
    int& ref = DDR[x][y];
    if(ref != -1) {
        return ref;
    }
    ref = IINF;
    for(int k = 0; k < 2; ++k) {
        int n_x = x + dxDR[k];
        int n_y = y + dyDR[k];
        if(valid(n_x, n_y)) {
            ref = min(ref, 1 + goDR(n_x, n_y));
        }
    }
    return ref;
}

int go(int x, int y) {
    if(M[x][y] == '+') {
        D[x][y] = 0;
        return 0;
    }
    D[x][y] = IINF;
    D[x][y] = min(D[x][y], goUL(x, y));
    D[x][y] = min(D[x][y], goUR(x, y));
    D[x][y] = min(D[x][y], goDR(x, y));
    D[x][y] = min(D[x][y], goDL(x, y));
    return D[x][y];
}

void cleanup() {
    FILL(D, -1);
    FILL(DUL, -1);
    FILL(DUR, -1);
    FILL(DDL, -1);
    FILL(DDR, -1);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%s", M[i]);
        }
        return true;
    }
    return false;
}

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool check(int x, int y, int dist) {
    if(M[x][y] == 'J') {
        return true;
    }
    bool ans = false;
    USED[x][y] = 1;
    for(int k = 0; k < 4; ++k) {
        int n_x = x + dx[k];
        int n_y = y + dy[k];
        if(valid(n_x, n_y) && !USED[n_x][n_y] && D[n_x][n_y] >= dist) {
            ans = max(ans, check(n_x, n_y, dist));
        }
    }
    return ans;
}

void Run() {
    int x = -1, y = -1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(M[i][j] == 'V') {
                x = i, y = j;
            }
            goUL(i, j);
            goUR(i, j);
            goDL(i, j);
            goDR(i, j);
            go(i, j);
            eprintf("D(%d,%d)=%d\n", i, j, D[i][j]);
        }
    }
    int answer = 0;
    int lo = 0, hi = 3000;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        FILL(USED, false);
        if(D[x][y] >= mid && check(x, y, mid)) {
            answer = mid;
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    printf("%d\n", answer);
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
