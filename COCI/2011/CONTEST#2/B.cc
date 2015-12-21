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

const int maxN = 100000 + 7;
const int maxM = 300000 + 7;

char S[maxM];
long long SX[maxN], SY[maxN];
int n, m, dx[255], dy[255], X[maxN], Y[maxN];

void cleanup() {
    FILL(SX, 0);
    FILL(SY, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", X + i, Y + i);
        }
        scanf("%s", S);
        return true;
    }
    return false;
}

void precalc(int E[], long long SM[]) {
    SM[0] = E[0];
    for(int i = 1; i < n; ++i) {
        SM[i] = SM[i - 1] + E[i];
    }
}

long long get_sum(int l, int r, long long SP[]) {
    long long ret = SP[r];
    if(l - 1 >= 0) {
        ret -= SP[l - 1];
    }
    return ret;
}

long long solve(long long p, int P[], long long SP[]) {
    int lo = 0, hi = n - 1, pos = -1;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        if(P[mid] <= p) {
            pos = mid;
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    long long answer = 0;
    if(pos == -1) {
        answer += get_sum(0, n - 1, SP) - p * n;
    }
    else if(pos == n - 1) {
        answer += p * n - get_sum(0, n - 1, SP);
    }
    else {
        answer += p * (pos + 1) - get_sum(0, pos, SP);
        answer += get_sum(pos + 1, n - 1, SP) - p * (n - pos - 1);
    }
    return answer;
}

void Run() {
    int x = 0, y = 0;
    dx['S'] = 0, dy['S'] = 1;
    dx['I'] = 1, dy['I'] = 0;
    dx['J'] = 0, dy['J'] = -1;
    dx['Z'] = -1, dy['Z'] = 0;
    sort(X, X + n);
    sort(Y, Y + n);
    precalc(X, SX);
    precalc(Y, SY);
    for(int i = 0; i < m; ++i) {
        x += dx[S[i]];
        y += dy[S[i]];
        printf(LLD"\n", solve(x, X, SX) + solve(y, Y, SY));
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
