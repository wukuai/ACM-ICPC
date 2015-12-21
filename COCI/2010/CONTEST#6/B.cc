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

const int maxN = 55;

int n, D[maxN][maxN];
char MAP[maxN][maxN], USED[maxN][maxN];

int dx[] = {0, 0, 1, -1, 1, -1, -1, 1};
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%s", MAP[i]);
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                scanf("%d", &D[i][j]);
            }
        }
        return true;
    }
    return false;
}

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n;
}

void dfs(int x, int y, int mmin, int mmax) {
    USED[x][y] = 1;
    for(int k = 0; k < 8; ++k) {
        int n_x = x + dx[k];
        int n_y = y + dy[k];
        if(valid(n_x, n_y) && !USED[n_x][n_y]) {
            if(D[n_x][n_y] >= mmin && D[n_x][n_y] <= mmax) {
                dfs(n_x, n_y, mmin, mmax);
            }
        }
    }
}

bool solve(int mmin, int mmax) {
    int p_x, p_y, cnt = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(MAP[i][j] == 'P') {
                p_x = i, p_y = j;
            }
            if(MAP[i][j] == 'K') {
                cnt++;
            }
        }
    }
    if(D[p_x][p_y] < mmin || D[p_x][p_y] > mmax) {
        return false;
    }
    FILL(USED, false);
    dfs(p_x, p_y, mmin, mmax);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(MAP[i][j] == 'K' && USED[i][j]) {
                --cnt;
            }
        }
    }
    return cnt == 0;
}

void Run() {
    int res = IINF;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            int answer = -1;
            int lo = 0, hi = D[i][j];
            while(lo <= hi) {
                int mid = (lo + hi) / 2;
                if(solve(mid, D[i][j])) {
                    lo = mid + 1;
                    answer = mid;
                }
                else {
                    hi = mid - 1;
                }
            }
            if(answer != -1) {
                check_min(res, D[i][j] - answer);
            }
        }
    }
    printf("%d\n", res);
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
