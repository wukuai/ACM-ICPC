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

int n, L[maxN], A[maxN], S[maxN];

void cleanup() {
    FILL(S, 0);
    FILL(L, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", A + i);
        }
        return true;
    }
    return false;
}

void update(int l, int r) {
    S[l]++;
    S[r + 1]--;
}

int get_sum(int l, int r) {
    int ret = S[r];
    if(l - 1 >= 0) {
        ret -= S[l - 1];
    }
    return ret;
}

void Run() {
    for(int i = 0; i < n; ) {
        if(A[i] >= 0) {
            ++i;
        }
        else {
            int st = i;
            while(i < n && A[i] < 0) {
                ++i;
                ++L[st];
            }
        }
    }
    int mmax = 0;
    for(int i = 1; i < n; ++i) {
        if(L[i] > 0) {
            update(max(0, i - 2 * L[i]), i - 1);
        }
    }
    eprintf("L : ");
    for(int i = 0; i < n; ++i) {
        if(i) {
            S[i] += S[i - 1];
        }
        check_max(mmax, L[i]);
        eprintf("%d ", L[i]);
    }
    eprintf("\n");
    if(mmax == 0) {
        printf("0\n");
        return ;
    }
    int answer = 0;
    eprintf("S : ");
    for(int i = 0; i < n; ++i) {
        if(S[i] > 0) {
            ++answer;
            S[i] = 1;
            eprintf("1 ");
        }
        else {
            eprintf("0 ");
            S[i] = 0;
        }
    }
    eprintf("\n");
    eprintf("S : ");
    for(int i = 0; i < n; ++i) {
        if(i) {
            S[i] += S[i - 1];
        }
        eprintf("%d ", S[i]);
    }
    eprintf("\n");
    int add = 0;
    eprintf("mmax=%d\n", mmax);
    for(int i = 1; i < n; ++i) {
        if(L[i] == mmax) {
            int l = max(0, i - 3 * L[i]);
            int r = i - 1;
            check_max(add, r - l + 1 - get_sum(l, r));
            eprintf("for i=%d l=%d r=%d sum=%d\n", i, l, r, get_sum(l, r));
        }
    }
    printf("%d\n", answer + add);
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
