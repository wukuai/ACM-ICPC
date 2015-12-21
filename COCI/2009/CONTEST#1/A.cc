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

const int maxA = 27;
const int maxN = 107;

int n, c1, c2, c3;
char S[maxN];
long long DP[maxN][maxA][maxA][2];

int is_vowel(int c) {
    char ch = c + 'A';
    return ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U';
}

long long go(int pos, int p1, int p2, int l) {
    if(pos == n) {
        return l;
    }
    long long& ref = DP[pos][p1][p2][l];
    if(ref != -1) {
        return ref;
    }
    ref = 0;
    if(S[pos] == '_') {
        for(int i = 0; i < 26; ++i) {
            c1 = is_vowel(p1);
            c2 = is_vowel(p2);
            c3 = is_vowel(i);
            if(c1 == c2 && c2 == c3) continue;
            ref += go(pos + 1, p2, i, l || (i + 'A') == 'L');
        }
    }
    else {
        c1 = is_vowel(p1);
        c2 = is_vowel(p2);
        c3 = is_vowel(S[pos] - 'A');
        if(c1 == c2 && c2 == c3) return 0;
        ref += go(pos + 1, p2, S[pos] - 'A', l || S[pos] == 'L'); 
    }
    return ref;
}

void cleanup() {
    FILL(DP, -1);
}

bool Read() {
    cleanup();
    if(scanf("%s", S) == 1) {
        n = strlen(S);
        return true;
    }
    return false;
}

void Run() {
    if(n == 0) {
        printf("0\n"); return ;
    }
    if(n == 1) {
        if(S[0] == '_' || S[0] == 'L') {
            printf("1\n");
        }
        else {
            printf("0\n");
        }
        return ;
    }
    long long answer = 0;
    if(S[0] == '_') {
        if(S[1] == '_') {
            for(int i = 0; i < 26; ++i) {
                //answer += go(2, i, i, (i + 'A') == 'L');
                for(int j = 0; j < 26; ++j) {
                    answer += go(2, i, j, (i + 'A') == 'L' || (j + 'A') == 'L');
                }
            }
        }
        else {
            for(int i = 0; i < 26; ++i) {
                answer += go(2, i, S[1] - 'A', (i + 'A') == 'L' || S[1] == 'L');
            }
        }
    }
    else {
        if(S[1] == '_') {
            for(int i = 0; i < 26; ++i) {
                answer += go(2, S[0] - 'A', i, (i + 'A') == 'L' || S[0] == 'L');
            }
        }
        else {
            answer += go(2, S[0] - 'A', S[1] - 'A', S[0] == 'L' || S[1] == 'L');
        }
    }
    printf(LLD"\n", answer);
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
