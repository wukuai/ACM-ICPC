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
#define SIZE(x) ((int)x.size())
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

const int maxN = 100007;
const int maxT = 4 * maxN;

class SegmentTree {
private:
    long long T[maxT];
public:
    SegmentTree() {
        FILL(T, 0);
    }  
    long long query(int v, int tl, int tr, int pos) {
        if(tl == tr) {
            return T[v];
        }
        else {
            int tm = (tl + tr) / 2;
            long long ans = T[v];
            if(pos <= tm) {
                ans += query(v << 1, tl, tm, pos);
            }
            else {
                ans += query((v << 1) | 1, tm + 1, tr, pos);
            }
            return ans;
        }
    }
    void update(int v, int tl, int tr, int l, int r, long long delta) {
        if(l > r) return ;
        if(tl == l && tr == r) {
            T[v] += delta;
        }
        else {
            int tm = (tl + tr) / 2;
            update(v << 1, tl, tm, l, min(r, tm), delta);
            update((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r, delta);
        }
    }
};

int n;

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        return true;
    }
    return false;
}

void Run() {
    int N = 100000;
    SegmentTree tree;
    for(int i = 0; i < n; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        long long c = tree.query(1, 0, N, l - 1);
        long long w = tree.query(1, 0, N, r - 1);
        printf("%lld\n", c + w);
        tree.update(1, 0, N, l - 1, l - 1, -c);
        tree.update(1, 0, N, r - 1, r - 1, -w);
        tree.update(1, 0, N, l, r - 2, 1);
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
