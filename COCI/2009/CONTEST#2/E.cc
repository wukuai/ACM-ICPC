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

const int maxN = 107;
const int maxT = 1000007;

int n, A[maxN], T[maxT];

void cleanup() {
    FILL(T, 0);
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

void Run() {
    for(int i = 0; i < n; ++i) {
        int x = A[i];
        for(int j = 2; j * j <= x; ++j) {
            while(x % j == 0) {
                T[j]++;
                x /= j;
            }
        }
        T[x]++;
    }
    eprintf("%d\n", T[439]);
    int d = 1;
    vector< pair<int, int> > factorization;
    for(int p = 2; p < maxT; ++p) {
        if(T[p] > 0) {
            eprintf("%d %d\n", p, T[p]);
        }
        if(T[p] >= n) {
            int ppow = T[p] / n;
         //   eprintf("%d %d\n", p, ppow);
            for(int k = 0; k < ppow; ++k) {
                d *= p;
            }
            factorization.pb(mp(p, ppow));
        }
    }
    if(d == 1) {
        printf("1 0\n");
        return ;
    }
    printf("%d ", d);
    int cost = 0;
    for(int i = 0; i < n; ++i) {
        int x = A[i];
        vector< pair<int, int> > f;
        for(int j = 2; j * j <= x; ++j) {
            if(x % j == 0) {
                int cnt = 0;
                while(x % j == 0) {
                    cnt++;
                    x /= j;
                }
                f.pb(mp(j, cnt));
            }
        }
        if(x > 1) {
            f.pb(mp(x, 1));
        }
        for(int j = 0; j < SZ(factorization); ++j) {
            bool found = false;
            for(int k = 0; k < SZ(f); ++k) {
                if(factorization[j].first == f[k].first) {
                    found = true;
                    if(factorization[j].second > f[k].second) {
                        cost += factorization[j].second - f[k].second;
                    }
                    break;
                }
            }
            if(!found) {
                cost += factorization[j].second;
            }
        }
    }
    printf("%d\n", cost);
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
