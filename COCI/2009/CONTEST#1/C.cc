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

const int maxN = 500007;

int n, P[maxN], c, d, L[maxN], USED[maxN];
long long a, b;

long long gcd(long long aa, long long bb) {
    return aa == 0 ? bb : gcd(bb % aa, aa);
}

long long lcm(long long aa, long long bb) {
    return aa * (bb / gcd(aa, bb));
}

void cleanup() {
    FILL(L, 0);
    FILL(USED, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d" LLD LLD "%d%d", &n, &a, &b, &c, &d) == 5) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", P + i); P[i]--;
        }
        return true;
    }
    return false;
}

void Run() {
    int st;
    vector<int> processing;
    for(int i = 0; i < n; ++i) {
        if(USED[i]) continue;
        processing.clear();
        st = i;
        while(!USED[st]) {
            processing.pb(st);
            USED[st] = true;
            st = P[st];
        }
        for(int j = 0; j < SIZE(processing); ++j) {
            L[processing[j]] = SIZE(processing);
        }
    }
    long long answer = 0, lc = 1;
    for(int i = c; i < n - d; ++i) {
        lc = lcm(lc, L[P[i]]);
        if(lc > b) { printf("0\n"); return ; }
    }
    long long l = (a - 1 + lc - 1) / lc;
    long long r = (b - 1) / lc;
    answer += r - l + 1;
    printf(LLD "\n", max(0LL, answer));
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
