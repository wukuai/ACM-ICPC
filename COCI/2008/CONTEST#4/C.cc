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

const int maxN = 107;

int n, m, A[maxN][maxN], D[maxN][maxN];

void cleanup() {
    FILL(A, 0);
    FILL(D, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < m; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            A[x][y] = 1;
        }
        return true;
    }
    return false;
}

int get_sum(int x1, int y1, int x2, int y2) {
    int ret = D[x2][y2];
    ret -= D[x1 - 1][y2];
    ret -= D[x2][y1 - 1];
    ret += D[x1 - 1][y1 - 1];
    return ret;
}

int get_min(int w, int h) {
    int answer = IINF;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(i + w - 1 <= n && j + h - 1 <= n) {
                check_min(answer, m - get_sum(i, j, i + w - 1, j + h - 1));
            }
        }
    }
    return answer;
}

void Run() {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            D[i][j] = D[i - 1][j] + D[i][j - 1] - D[i - 1][j - 1] + A[i][j];
        }
    }
    int answer = IINF;
    for(int k = 1; k <= m; ++k) {
        if(m % k == 0) {
            check_min(answer, get_min(k, m / k));
            check_min(answer, get_min(m / k, k));
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
