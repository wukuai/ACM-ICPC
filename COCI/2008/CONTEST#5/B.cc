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

const int maxN = 55;

int rounds, friends;
char S[maxN], F[maxN][maxN];

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d", &rounds) == 1) {
        scanf("%s", S);
        scanf("%d", &friends);
        for(int i = 0; i < friends; ++i) {
            scanf("%s", F[i]);
        }
        return true;
    }
    return false;
}

int score(char ch1, char ch2) {
    if(ch1 == ch2) return 1;
    if(ch1 == 'S' && ch2 == 'P') return 2;
    if(ch1 == 'P' && ch2 == 'R') return 2;
    if(ch1 == 'R' && ch2 == 'S') return 2;
    return 0;
}

void Run() {
    int total = 0, best = 0;
    for(int i = 0; i < rounds; ++i) {
        int s = 0, p = 0, r = 0;
        for(int j = 0; j < friends; ++j) {
            total += score(S[i], F[j][i]);
            s += score('S', F[j][i]);
            p += score('P', F[j][i]);
            r += score('R', F[j][i]);
        }
        best += max(s, max(p, r));
    }
    printf("%d\n%d\n", total, best);
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
