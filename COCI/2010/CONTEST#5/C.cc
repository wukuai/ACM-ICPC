#include <stack>
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

const int maxN = 100007;

int n, A[maxN], ANS[maxN], RES[maxN];
long long S[maxN], s;

void cleanup() {
    FILL(ANS, 0);
    FILL(RES, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d%lld", &n, &s) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", A + i);
        }
        return true;
    }
    return false;
}

long long get_sum(int l, int r) {
    long long ret = S[r];
    if(l - 1 >= 0) {
        ret -= S[l - 1];
    }
    return ret;
}

void Run() {
    S[0] = A[0];
    for(int i = 1; i < n; ++i) {
        S[i] = S[i - 1] + A[i];
    }
    for(int i = 0; i < n; ++i) {
        int len_left = 0;
        int len_right = 0;
        int lo = 0, hi = i + 1;
        while(lo <= hi) {
            int mid = (lo + hi) / 2;
            if(get_sum(i, i - mid + 1) <= s) {
                len_left = mid;
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        lo = 0, hi = n - i - 1;
        while(lo <= hi) {
            int mid = (lo + hi) / 2;
            if(get_sum(i + 1, i + mid) <= s) {
                len_right = mid;
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        int k = min(len_left, len_right);
        if(k == 0) continue;
        check_max(ANS[i - k + 1], k);
    }
    RES[0] = ANS[0];
    stack< pair<int, int> > st;
    if(ANS[0] > 0) {
        st.push(mp(0, ANS[0]));
    }
    for(int i = 1; i < n; ++i) {
        while(!st.empty() && st.top().first + st.top().second - 1 < i) {
            st.pop();
        }
        RES[i] = ANS[i];
        if(!st.empty()) {
            int l = st.top().second - (i - st.top().first);
            check_max(RES[i], l);
        }
        if(RES[i] > 0) {
            st.push(mp(i, RES[i]));
        }
    }
    for(int i = 0; i < n; ++i) {
        printf("%d\n", RES[i] + RES[i]);
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
