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

const int maxL = 21;
const int maxN = 1 << 20;

int n, k, A[maxN];
//B[maxN], LOG[maxN], ST[maxN][maxL];

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &k) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", A + i);
        }
        return true;
    }
    return false;
}

/*int get_min(int l, int r) {
    int kl = LOG[r - l];
    eprintf("for [%d,%d]-->k=%d\n", l, r, kl);
    eprintf("[%d,%d]\n", l, 1 << kl);
    eprintf("[%d,%d]\n", r - (1 << kl) + 1, 1 << kl);
    return min(ST[l][kl], ST[r - (1 << kl) + 1][kl]);
}*/

void Run() {
/*    eprintf("B : ");
    for(int i = 0; i + 1 < n; ++i) {
        B[i] = A[i + 1] - A[i];
        eprintf("%d ", B[i]);
    }
    eprintf("\n");
    LOG[0] = 0;
    for(int i = 2; i <= n; ++i) {
        LOG[i] = LOG[i >> 1] + 1;
    }
    int m = n - 1;
    for(int i = 0; i < m; ++i) {
        ST[i][0] = B[i];
    }
    for(int l = 1; l <= 20; ++l) {
        int len = 1 << l;
        int half = len >> 1;
        for(int i = 0; i + len <= m; ++i) {
            ST[i][l] = min(ST[i][l - 1], ST[i + half][l - 1]);
        }
    }
    eprintf("ST:\n");
    for(int l = 0; l <= 20; ++l) {
        int len = 1 << l;
        if(len > m) break;
        eprintf("len=%d : ", len);
        for(int i = 0; i + len <= m; ++i) {
            eprintf("%d ", ST[i][l]);
        }
        eprintf("\n");
    }
    int answer = IINF + IINF;
    for(int beg = 0; beg <= k; ++beg) {
        int st = beg, en = n - (k - beg) - 1;
//        eprintf("min(%d,%d)=%d\n", st, en, get_min(st, en - 1));
        check_min(answer, A[en] - A[st] + get_min(st, en - 1));
    }
    printf("%d\n", answer);
*/

    sort(A, A + n);
    int answer = 2 * IINF;
    multiset<int> values;
    for(int i = 0; i + 1 < n - k; ++i) {
        values.insert(A[i + 1] - A[i]);
    }
    for(int beg = 0; beg <= k; ++beg) {
        int st = beg, en = n - k + beg - 1;
        check_min(answer, A[en] - A[st] + *values.begin());
        auto it = values.find(A[beg + 1] - A[beg]);
        values.erase(it);
        values.insert(A[en + 1] - A[en]);
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
