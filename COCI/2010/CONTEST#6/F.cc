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

const int maxS = 87000;
const int maxN = 100000 + 7;

int n;
long long S[maxS];

struct TimeInterval {
    int startH, endH;
    int startM, endM;
    int startS, endS;

    int end_timestamp;
    int start_timestamp;

    TimeInterval() : startH(0), endH(0), startM(0), endM(0), startS(0), endS(0), end_timestamp(0), start_timestamp(0) {}

    void read() {
        scanf("%d:%d:%d - %d:%d:%d", &startH, &startM, &startS, &endH, &endM, &endS);
        end_timestamp = endS + endM * 60 + endH * 60 * 60;
        start_timestamp = startS + startM * 60 + startH * 60 * 60;
    }
} D[maxN];

void cleanup() {
    FILL(S, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            D[i].read();
        }
        return true;
    }
    return false;
}

void update(int l, int r) {
    S[l]++;
    S[r + 1]--;
}

double get_sum(int l, int r) {
    double ret = S[r];
    if(l - 1 >= 0) {
        ret -= S[l - 1];
    }
    return ret;
}

void Run() {
    int mmax_timestamp = 59 + 59 * 60 + 23 * 60 * 60;
    for(int i = 0; i < n; ++i) {
        if(D[i].end_timestamp < D[i].start_timestamp) {
            update(0, D[i].end_timestamp);
            update(D[i].start_timestamp, mmax_timestamp);
        }
        else {
            update(D[i].start_timestamp, D[i].end_timestamp);
        }
    }
    for(int i = 1; i < maxS; ++i) {
        S[i] += S[i - 1];
    }
    for(int i = 1; i < maxS; ++i) {
        S[i] += S[i - 1];
    }
    int q;
    scanf("%d", &q);
    TimeInterval current_interval;
    for(int i = 0; i < q; ++i) {
        current_interval.read();
        if(current_interval.end_timestamp < current_interval.start_timestamp) {
            double sum = get_sum(0, current_interval.end_timestamp);
            sum += get_sum(current_interval.start_timestamp, mmax_timestamp);
            double counter = current_interval.end_timestamp + 1;
            counter += mmax_timestamp - current_interval.start_timestamp + 1;
            printf("%.7lf\n", sum / counter);
        }
        else {
            double sum = get_sum(current_interval.start_timestamp, current_interval.end_timestamp);
            double counter = current_interval.end_timestamp - current_interval.start_timestamp + 1;
            printf("%.7lf\n", sum / counter);
        }
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
