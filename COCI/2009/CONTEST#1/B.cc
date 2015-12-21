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
#define SORT(x) sort(ALL(x))
#define REVERSE(x) reverse(ALL(x))
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

const int maxA = 107;

int n, A[maxA], B[maxA], C[maxA], D[maxA];

void cleanup() {
    FILL(A, 0);
    FILL(B, 0);
    FILL(C, 0);
    FILL(D, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        return true;
    }
    return false;
}

void Run() {
    int a, b, p1, p2, mmax;
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &a, &b);
        A[a]++, B[b]++;
        memcpy(C, A, sizeof(A));
        memcpy(D, B, sizeof(D));
        p1 = 1, p2 = 100, mmax = 0;
        while(p1 <= 100 && p2 >= 1) {
            if(A[p1] == B[p2]) {
                if(A[p1] > 0) {
                    check_max(mmax, p1 + p2);
                }
                A[p1] = 0, B[p2] = 0;
                p1++, --p2;
            }
            else if(A[p1] > B[p2]) {
                if(B[p2] > 0) {
                    check_max(mmax, p1 + p2);
                }
                A[p1] -= B[p2]; --p2;
            }
            else if(A[p1] < B[p2]) {
                if(A[p1] > 0) {
                    check_max(mmax, p1 + p2);
                }
                B[p2] -= A[p1]; ++p1;
            }
        }
        memcpy(A, C, sizeof(C));
        memcpy(B, D, sizeof(D));
        printf("%d\n", mmax);
    }
}

} // Solution

namespace StressTest {

void GenerateInput() {
    FILE* output = fopen("input.txt", "w");

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
    srand(time(NULL));
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
