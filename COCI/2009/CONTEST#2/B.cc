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

const int maxL = 18;
const int maxN = 100007;

pair<int, int> A[maxN];
int n, m, ST[maxN][maxL], LOG[maxN];

void cleanup() {
    FILL(ST, -1);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d %d", &A[i].first, &A[i].second);
        }
        return true;
    }
    return false;
}

int rmq(int l, int r) {
    int k = LOG[r - l];
    int left = ST[l][k];
    int right = ST[r - (1 << k) + 1][k];
    if(A[left].second < A[right].second) {
        return left;
    }
    else {
        return right;
    }
}

long long solve(int l, int r, long long detected) {
    if(l > r) return 0;
    if(l == r) {
        return A[l].second - detected;
    }
    int pos = rmq(l, r);
    return solve(l, pos - 1, A[pos].second) + solve(pos + 1, r, A[pos].second) + A[pos].second - detected;
}

void Run() {
    sort(A, A + n);
    for(int i = 0; i < n; ++i) {
        ST[i][0] = i;
    }
    LOG[1] = 0;
    for(int i = 2; i < maxN; ++i) {
        LOG[i] = LOG[i >> 1] + 1;
    }
    int len, half, left_side, right_side;
    for(int l = 1; l < maxL; ++l) {
        len = 1 << l;
        half = len >> 1;
        for(int i = 0; i + len <= n; ++i) {
            left_side = ST[i][l - 1];
            right_side = ST[i + half][l - 1];
            if(A[left_side].second < A[right_side].second) {
                ST[i][l] = left_side;
            }
            else {
                ST[i][l] = right_side;
            }
        }
    }
    printf(LLD "\n", solve(0, n - 1, 0));
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
