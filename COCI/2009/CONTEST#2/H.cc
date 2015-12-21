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

const int maxN = 1100107;

template <typename T> class MonotoneQueue {
private:
    int head;
    int tail;
    T comparator;
    int value[maxN];
    int index[maxN];

public:
    MonotoneQueue() : head(0), tail(-1) {}

    void push(int val, int ind) {
        while(head <= tail && comparator(value[tail], val)) {
            --tail;
        }
        ++tail;
        value[tail] = val;
        index[tail] = ind;
    }

    void pop(int ind) {
        if(head <= tail && index[head] == ind) {
            head++;
        }
    }

    int top() {
        if(head > tail) return -1;
        return value[head];
    }

    void clear() {
        head = 0, tail = -1;
    }

    void show_cerr() {
        for(int i = head; i <= tail; ++i) {
            eprintf("%d ", value[i]);
        }
        eprintf("\n");
    }
};

int n, x, H[maxN], L[maxN], OPT[maxN];
MonotoneQueue< greater<int> > great_Q;
MonotoneQueue< less<int> > less_Q;

void cleanup() {
    great_Q.clear();
    less_Q.clear();
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &x) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", H + i);
        }
        return true;
    }
    return false;
}

void Run() {
    for(int i = n; i < n + x; ++i) {
        H[i] = IINF;
    }
    for(int i = 0; i < n + x; ++i) {
        if(i >= x) {
            L[i - x] = great_Q.top();
            great_Q.pop(i - x);
        }
        great_Q.push(H[i], i);
    }
    for(int i = 0; i < n + x; ++i) {
        //less_Q.show_cerr();
        if(i >= x) less_Q.pop(i - x);
        if(i <= n - x) less_Q.push(L[i], i);
        OPT[i] = less_Q.top();
    }
    int stroke = 0, last = -1, border = -1;
    long long answer = 0;
    for(int i = 0; i < n; ++i) {
        answer += H[i] - OPT[i];
        if(OPT[i] != last || i > border) {
            stroke++;
            last = OPT[i];
            border = i + x - 1;
        }
    }
    printf(LLD "\n%d\n", answer, stroke);
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
