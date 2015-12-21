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

const int maxN = 100 * 1000 + 7;
const int maxT = 1000 * 1000 + 7;

int n, q, X[3 * maxN], Y[3 * maxN], TYPE[maxQ], VALUE[maxQ], ANSWER[maxQ], F[maxT], CNT[maxT];

struct Event {
    bool type;
    int v1, v2, idx;
}E[5 * maxN];

bool operator < (const Event& lhs, const Event& rhs) {
    if(lhs.type && rhs.type) {
        return mp(lhs.v1, lhs.v2) < mp(rhs.v1, rhs.v2);
    }
    else if(!lhs.type && rhs.type) {
        return rhs.v1 > lsh.v1;
    }
    else if(lhs.type && !rhs.type) {
        return lhs.v1 <= rhs.v1;
    }
    else if(!lhs.type && !rhs.type) {
        return lhs.v1 < rhs.v1;
    }
}

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        int x1, y1, x2, y2, x3, y3;
        for(int i = 0; i < n; ++i) {
            scanf("%d%d %d%d %d%d", &x1, &y1, &x2, &y2, &x3, &y3);
            X[3 * i] = x1, Y[3 * i] = y1;
            X[3 * i + 1] = x2, Y[3 * i + 1] = y2;
            X[3 * i + 2] = x3, Y[3 * i + 2] = x3;
        }
        int val;
        char ax, eq;
        scanf("%d", &q);
        for(int i = 0; i < q; ++i) {
            scanf(" %c %c%d", &ax, &eq, &val);
            if(ax == 'x') {
                TYPE[i] = 0;
                VALUE[i] = val;
            }
            else {
                TYPE[i] = 1;
                VALUE[i] = val;
            }
        }
        return true;
    }
    return false;
}

void Run() {
    FILL(F, 0);
    FILL(CNT, 0);
    int m = 0;
    for(int i = 0; i < n; ++i) {
        if(X[i] == X[i + 1]) {
            CNT[X[i]]++;
        }
        else {
            E[m].type = 1;
            E[m].v1 = X[i];
            E[m].v2 = X[i + 1];
            if(E[m].v1 < E[m].v2) swap(E[m].v1, E[m].v2);
            ++m;
        }
        if(X[i] == X[i + 2]) {
            CNT[X[i]]++;
        }
        else {
            E[m].type = 1;
            E[m].v1 = X[i];
            E[m].v2 = X[i + 2]; 
            if(E[m].v1 < E[m].v2) swap(E[m].v1, E[m].v2);
            ++m;
        }
        if(X[i + 1] == X[i + 2]) {
            CNT[X[i + 1]]++;
        }
        else {
            E[m].type = 1;
            E[m].v1 = X[i + 1];
            E[m].v2 = X[i + 2];
            if(E[m].v1 < E[m].v2) swap(E[m].v1, E[m].v2);
            ++m;
        }
    }
    for(int i = 0; i < q; ++i) {
        if(TYPE[i] == 0) {
            E[m].type = 0;
            E[m].v1 = VALUE[i];
            E[m].idx = i;
            ++m;
        }
    }
    solve(m);







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
