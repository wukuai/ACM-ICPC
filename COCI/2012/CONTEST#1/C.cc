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

long long gcd(long long a, long long b) {
    return a == 0 ? b : gcd(b % a, a);
}

long long lcm(long long a, long long b) {
    return a * (b / gcd(a, b));
}

int strength(int n) {
//    eprintf("%d ", n);
    if(n == 2) return 1;
    for(int d = 1; d <= n; ++d) {
        if(n % d != 0) {
            return strength(d) + 1;
        }
    }
    return strength(n + 1) + 1;
}

void cleanup() {

}

long long a, b;
int len[55];

bool Read() {
    cleanup();
    if(scanf(LLD LLD, &a, &b) == 2) {
        return true;
    }
    return false;
}

long long get_count(long long x) {
    return b / x - (a - 1) / x;
}

long long get_count(long long m, long long k) {
    return get_count(m) - get_count(lcm(m, k));
}

void Run() {
    int k;
    long long l = 1;
    for(k = 1; k < 100; ++k) {
        l = lcm(l, k);
        if(l > b) {
            break;
        }
    }
    --k;
    for(int i = 2; i <= k + 1; ++i) {
        len[i] = strength(i);
    }
    l = 1;
    long long answer = 0;
    for(int i = 2; i <= k + 1; ++i) {
        long long l_new = lcm(i, l);
        answer += get_count(l, i) * (len[i] + 1LL);
        l = l_new;
    }
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

    for(int i = 1000; i <= 1200; ++i) {
        for(int j = i + 1; j <= 1300; ++j) {
            fprintf(output, "%d %d\n", i, j);
        }
    }

    fclose(output);
}

void BruteForce() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("brute.out", "w");

    int x, y;
    while(fscanf(input, "%d %d", &x, &y) == 2) {
        int answer = 0;
        for(int i = x; i <= y; ++i) {
            answer += Solution::strength(i);
        }
        fprintf(output, "%d\n", answer);
    }

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
int s = 0;
    vector<int> v;
    eprintf("sequence(1, 1000) : ");
    for(int i = 1; i <= 1300; ++i) {
        if(Solution::strength(i) == 4) {
            eprintf("i=%d\n", i);
        }
    }
    eprintf("\nlcm : ");
    long long bound = 100000000000000000LL;
    for(int i = 4; i <= 50; ++i) {
        long long l = 1; 
        for(int j = 1; j <= i; ++j) {
            l = Solution::lcm(l, j);
            if(l > bound) break;
        }
        if(l > bound) {
            eprintf("for i=%d greater. lcm=%lld\n", i, l);
            break;
        }
    }
    eprintf("\n");
    return 0;
}
