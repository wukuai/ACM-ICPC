#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>
#include <sstream>
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

const int maxN = 1000 + 7;

bool was[maxN][maxN][1 << 3];
set< pair<int, int> > masks[1 << 3];
int n, k, a[maxN][3];
int dp[maxN][maxN][1 << 3];

void generate(int currMask1, int currMask2, int column, int initMask1, int initMask2) {
    if(column >= 3) return ;
    masks[initMask1].insert(mp(currMask1, currMask2));
    generate(currMask1, currMask2, column + 1, initMask1, initMask2);
    for(int i = column; i < 3; ++i) {
        // putting vertically
        if(!(currMask1 & (1 << i)) && !(currMask2 & (1 << i))) {
            generate(currMask1 ^ (1 << i), currMask2 ^ (1 << i), column + 1, initMask1, initMask2);
        }
        // putting horizontally
        if(i + 1 < 3 && !(currMask2 & (1 << i)) && !(currMask2 & (1 << (i + 1)))) {
            generate(currMask1, currMask2 ^ (1 << i) ^ (1 << (i + 1)), column + 2, initMask1, initMask2);
        }
    }
}

void cleanup() {
   FILL(was, false);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &k) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
        }
        return true;
    }
    return false;
}

int go(int row, int left, int mask) {
    if(left < 0) {
        return -IINF;
    }
    if(left == 0) {
        return 0;
    }
    if(row == n) {
        return -IINF;
    }
    int& ref = dp[row][left][mask];
    if(was[row][left][mask]) {
        return ref;
    }
    ref = -IINF;
    was[row][left][mask] = true;
    for(auto it = masks[mask].begin(); it != masks[mask].end(); ++it) {
        int s = 0, cnt = 0;
        if(it->second & (1 << 0)) { s += a[row][0]; ++cnt; }
        if(it->second & (1 << 1)) { s += a[row][1]; ++cnt; }
        if(it->second & (1 << 2)) { s += a[row][2]; ++cnt; }
        if((it->first & (1 << 0)) && !(mask & (1 << 0))) { s += a[row - 1][0]; ++cnt; }
        if((it->first & (1 << 1)) && !(mask & (1 << 1))) { s += a[row - 1][1]; ++cnt; }
        if((it->first & (1 << 2)) && !(mask & (1 << 2))) { s += a[row - 1][2]; ++cnt; }
        check_max(ref, s + go(row + 1, left - cnt / 2, it->second));
    }
    return ref;
}

void Run() {
    for(int mask1 = 0; mask1 < (1 << 3); ++mask1) {
        generate(mask1, 0, 0, mask1, 0);
//        eprintf("%d : ", mask1);
//        for(auto it : masks[mask1]) {
//            eprintf("(%d, %d) ", it.first, it.second);
//        }
//        eprintf("\n");
    }
    printf("%d\n", go(0, k, (1 << 3) - 1));
}

} // Solution

namespace StressTest {

long long GetTime() {
    srand(time(NULL));
    return rand() << 16LL;
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
