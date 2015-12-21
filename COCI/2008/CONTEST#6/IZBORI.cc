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

const int maxN = 100 + 7;

int v, n, m, s, a[maxN];
int votes[maxN], ans[maxN], c, d[maxN], where[maxN], wwhere[20 + 7];


void cleanup() {
  s = 0; 
  c = 0;
}

bool Read() {
    cleanup();
    if(scanf("%d%d%d", &v, &n, &m) == 3) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", a + i);
            s += a[i];
        }
        return true;
    }
    return false;
}

int get_max(int who) {
    FILL(votes, 0);
    for(int it = 0; it < m; ++it) {
        int ind = -1, num = -1, denum = 1;
        for(int j = 0; j < n; ++j) {
            if(a[j] * 100 < 5 * v) continue;
            if(a[j] * denum  > num * (votes[j] + 1)) {
                ind = j;
                num = a[j];
                denum = votes[j] + 1;
            }
        }
        assert(ind != -1);
        votes[ind]++;
    }
    return votes[who];
}

int dp[2][200 + 7];

int get_min_to_win(int num1, int denum1, int pos1, int num2, int denum2, int pos2) {
    int cc = (denum2 * num1) / denum1 - num2;
    if((denum2 * num1) % denum1 == 0 && pos1 < pos2) ++cc;
    if(cc < 0) cc = 0;
    return cc;
}

bool can(int pos, vector<int>& w, int additional, int numerator, int denumerator) {
    FILL(dp[0], 63);
    dp[0][0] = 0;
    for(int i = 1; i <= SZ(w); ++i) {
        int curr = i & 1;
        int prev = curr ^ 1;
        FILL(dp[curr], 63);
        for(int j = 0; j <= m; ++j) {
            dp[curr][j] = dp[prev][j];
            for(int k = 0; k <= j; ++k) {
                dp[curr][j] = min(dp[curr][j], dp[prev][j - k] + get_min_to_win(numerator, denumerator, pos, w[i - 1], k, wwhere[i]));
            }
            eprintf("%d ", dp[curr][j]);
        }
        eprintf("\n");
    }
    if(dp[SZ(w) & 1][m - denumerator + 1] <= additional) {
        return false;
    }
    return true;
}

void Run() {
    int additional = v - s;
    for(int i = 0; i < n; ++i) {
        a[i] += additional;
        printf("%d ", get_max(i));
        a[i] -= additional;
    }
    printf("\n");
    for(int i = 0; i < n; ++i) {
        if(a[i] * 100 < 5 * v) continue;
        d[c] = a[i];
        where[c] = i; c++;
    }
    for(int i = 0; i < c; ++i) {
        vector<int> w;
        for(int j = 0; j < c; ++j) {
            if(i == j) continue;
            w.pb(d[j]);
            wwhere[SZ(w) - 1] = where[j];
        }
        int answer = 0;
        int lo = 1, hi = m;
        while(lo <= hi) {
            int mid = (lo + hi) / 2;
            if(can(where[i], w, additional, d[i], mid)) {
                answer = mid;
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        ans[where[i]] = answer;
    }
    for(int i = 0; i < n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
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
