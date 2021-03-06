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

const int maxN = 207;
const int maxL = 1007;

int w, n, l, A[maxN][maxL], W[maxN][maxL];

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d%d%d", &w, &l, &n) == 3) {
        for(int i = 0; i < 2 * n; ++i) {
            for(int j = 0; j < l; ++j) {
                scanf("%d", &W[i][j]);
            }
        }
        return true;
    }
    return false;
}

void Run() {
    eprintf("A : \n");
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < l; ++j) {
            A[i][j] = (w - W[i * 2][j]) - W[i * 2 + 1][j];
            eprintf("%d ", A[i][j]);
        }
        eprintf("\n");
    }
    int answer = 0;
    for(int i = 0; i < n; ++i) {
        bool found = false;
        for(int j = 0; j < i && !found; ++j) {
            bool ok = true;
            for(int k = 0; k < l && ok; ++k) {
                if(A[i][k] != A[j][k]) {
                    ok = false;
                }
            }
            if(ok) {
                found = true;
            }
            else {
                ok = true;
                for(int k = 0, t = l - 1; k < l && t >= 0 && ok; ++k, --t) {
                    if(A[i][k] != A[j][t]) {
                        ok = false;
                    }
                }
                if(ok) {
                    found = true;
                }
            }
        }
        answer += !found;
    }
    printf("%d\n", answer);
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
