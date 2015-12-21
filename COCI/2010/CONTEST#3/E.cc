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
#include <stack>
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

const int maxN = 300007;

int n, A[maxN], PMINL[maxN], PMINR[maxN], PMAXL[maxN], PMAXR[maxN];

void cleanup() {

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

void calc(int L[], int R[], bool(*cmp1)(int, int), bool(*cmp2)(int, int)) {
    stack<int> st;
    L[0] = 0;
    st.push(0);
    for(int i = 1; i < n; ++i) {
        while(!st.empty() && (*cmp1)(A[st.top()], A[i])) {
            st.pop();
        }
        if(st.empty()) {
            L[i] = 0;
        }
        else {
            L[i] = st.top() + 1;
        }
        st.push(i);
    }
    while(!st.empty()) {
        st.pop();
    }
    R[n - 1] = n - 1;
    st.push(n - 1);
    for(int i = n - 2; i >= 0; --i) {
        while(!st.empty() && (*cmp2)(A[st.top()], A[i])) {
            st.pop();
        }
        if(st.empty()) {
            R[i] = n - 1;
        }
        else {
            R[i] = st.top() - 1;
        }
        st.push(i);
    }
}

bool cmp_less1(int a, int b) {
    return a < b;
}

bool cmp_less2(int a, int b) {
    return a <= b;
}

bool cmp_greater1(int a, int b) {
    return a > b;
}

bool cmp_greater2(int a, int b) {
    return a >= b;
}

void Run() {
    calc(PMAXL, PMAXR, cmp_less1, cmp_less2);
    calc(PMINL, PMINR, cmp_greater1, cmp_greater2);
    long long mins = 0, maxs = 0;
    for(int i = 0; i < n; ++i) {
        long long l = i - PMINL[i], r = PMINR[i] - i;
        eprintf("for min i=%d can go l=%lld r=%lld\n", i, l, r);
        mins += (l + r + l * r) * A[i];
        l = i - PMAXL[i], r = PMAXR[i] - i;
        eprintf("for max i=%d can go l=%lld r=%lld\n", i, l, r);
        maxs += (l + r + l * r) * A[i];
    }
    printf(LLD "\n", maxs - mins);
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
