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

const int maxN = 300000 + 7;

int n, A[maxN], B[maxN], C[maxN];

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", A + i);
        }
        for(int i = 0; i < n; ++i) {
            scanf("%d", B + i);
        }
        return true;
    }
    return false;
}

void Run() {
    for(int i = 0; i < n; ++i) {
        if(i == 0) {
            if(A[i] > A[i + 1]) {
                C[i] = 1;
            }
            else {
                C[i] = -1;
            }
        }
        else if(i == n - 1) {
            if(A[i] > A[i - 1]) {
                C[i] = 1;
            }
            else {
                C[i] = -1;
            }
        }
        else {
            if(A[i] > A[i + 1] && A[i] > A[i - 1]) {
                C[i] = 2;
            }
            else if(A[i] < A[i + 1] && A[i] < A[i - 1]) {
                C[i] = -2;
            }
            else {
                C[i] = 0;
            }
        }
    }
    sort(B, B + n);
    deque<int> dq;
    for(int i = 0; i < n; ++i) {
        dq.push_back(B[i]);
    }
    for(int i = 0; i < n; ++i) {
        if(C[i] == 2) {
            B[i] = dq.back();
            dq.pop_back();
        }
        else if(C[i] == -2) {
            B[i] = dq.front();
            dq.pop_front();
        }
    }
    for(int i = 0; i < n; ++i) {
        if(C[i] == 1) {
            B[i] = dq.back();
            dq.pop_back();
        }
        else if(C[i] == -1) {
            B[i] = dq.front();
            dq.pop_front();
        }
    }
    for(int i = 0; i < n; ) {
        if(C[i] != 0) {
            ++i;
        }
        else {
            while(i < n && C[i] == 0) {
                B[i] = dq.front();
                dq.pop_front();
                ++i;
            }
        }
    }
    long long answer = 0;
    for(int i = 1; i < n; ++i) {
        answer += abs(B[i] - B[i - 1]);
    }
    eprintf("B : ");
    for(int i = 0; i < n; ++i) {
        eprintf("%d ", B[i]);
    }
    eprintf("\n");
    printf(LLD"\n", answer);
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
