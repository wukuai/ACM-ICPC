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

const int maxB = 10;
const int maxN = 1024;

int n, total, A[maxN][maxN], L[maxN], POS[maxN], R[maxN][maxN][maxB];

struct Data {
    int row;
    int col;
    long long rank;
    Data() : row(0), col(0), rank(0) {}
    Data(int r, int c, long long rn) : row(r), col(c), rank(rn) {}
} W[maxN * maxN];

bool operator < (const Data& lhs, const Data& rhs) {
    return lhs.rank < rhs.rank;
}

void cleanup() {
    FILL(L, 0);
    FILL(R, 0);
    total = 0;
    FILL(POS, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", L + i);
            eprintf("L[i]=%d\n", L[i]);
            total += L[i];
            for(int j = 0; j < L[i]; ++j) {
                scanf("%d", &A[i][j]);
            }
        }
        return true;
    }
    return false;
}

class Comparator {
public:
    bool operator () (int lhs, int rhs) {
        int posl = POS[lhs];
        int posr = POS[rhs];
        for(int b = 9; b >= 0; --b) {
            if(posl + (1 << b) > L[lhs] || posr + (1 << b) > L[rhs]) continue;
            if(R[lhs][posl][b] != R[rhs][posr][b]) {
                return R[lhs][posl][b] < R[rhs][posr][b];
            }
            else {
                posl += 1 << b;
                posr += 1 << b;
            }
        }
        if(L[lhs] - posl != L[rhs] - posr) {
            return L[lhs] - posl > L[rhs] - posr;
        }
        return lhs < rhs;
    }
};

set<int, Comparator> q;

void Run() {
    q.clear();
    for(int b = 0; (1 << b) <= 1000; ++b) {
        long long val = 0;
        int len = 1 << b, cnt = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j + len <= L[i]; ++j) {
                if(len == 1) {
                    val = A[i][j];
                }
                else {
                    val = R[i][j][b - 1] * 10000100LL + R[i][j + len / 2][b - 1];
                }
                W[cnt] = Data(i, j, val); cnt++;
            }
        }
        sort(W, W + cnt);
        int rank = 0;
        for(int i = 0; i < cnt; ) {
            int pos = i;
            while(i < cnt && W[i].rank == W[pos].rank) {
                R[W[i].row][W[i].col][b] = rank; ++i;
            }
            rank++;
        }
    }
    for(int i = 0; i < n; ++i) {
        q.insert(i);
    }
    while(!q.empty()) {
        --total;
        int pos = *q.begin(); q.erase(q.begin());
        printf("%d ", A[pos][POS[pos]]);
        POS[pos]++;
        if(POS[pos] < L[pos]) {
            q.insert(pos);
        }
    }
    exit(0);
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
