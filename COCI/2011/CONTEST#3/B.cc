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

const int maxL = 4 * 4 + 7;
const int maxN = 100 * 1000 + 7;

char BUFFER[maxL];
int n, D[27][27], S[maxN], F[maxN];

void cleanup() {
    FILL(D, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        int l;
        for(int i = 0; i < n; ++i) {
            scanf("%s", BUFFER);
            l = strlen(BUFFER);
            S[i] = BUFFER[0] - 'A';
            F[i] = BUFFER[l - 1] - 'A';
            D[S[i]][F[i]]++;
        }
        return true;
    }
    return false;
}

void Run() {
    long long answer = 0, mul;
    for(int i = 0; i < n; ++i) {
        // put upper horizontal
        int once = 0;
        for(int k = 0; k < 26; ++k) {
            for(int j = 0; j < 26; ++j) {
                mul = D[S[i]][F[i]];
                D[S[i]][F[i]]--;
                mul *= D[F[i]][j];
                D[F[i]][j]--;
                mul *= D[k][j];
                D[k][j]--;
                mul *= D[S[i]][k];
                D[k][j]++;
                D[F[i]][j]++;
                D[S[i]][F[i]]++;
                if(k == j) {
                    if(once) continue;
                    ++once;
                    answer += mul;
                }
                else {
                    answer += mul;
                }
                if(mul > 0) {
                    eprintf("upper horizontal : k=%d j=%d mul=%lld\n", k, j, mul);
                }
            }
        }
        // put lower horizontal
        once = 0;
        for(int k = 0; k < 26; ++k) {
            for(int j = 0; j < 26; ++j) {
                mul = D[j][F[i]];
                D[j][F[i]]--; 
                mul *= D[S[i]][F[i]];
                D[S[i]][F[i]]--;
                mul *= D[k][S[i]];
                D[k][S[i]]--;
                mul *= D[k][j];
                D[S[i]][F[i]]++;
                D[k][S[i]]++;
                D[j][F[i]]++;
                if(j == k) {
                    if(once) continue;
                    ++once;
                    answer += mul;
                }   
                else {
                    answer += mul;
                }
                if(mul > 0) {
                    eprintf("lower horizontal : k=%d j=%d mul=%lld\n", k, j, mul);
                }
            }
        }
        // put rightmost vertical
        once = 0;
        for(int k = 0; k < 26; ++k) {
            for(int j = 0; j < 26; ++j) {
                mul = D[S[i]][F[i]];
                D[S[i]][F[i]]--;
                mul *= D[S[i]][k];
                D[S[i]][k]--;
                mul *= D[F[i]][j];
                D[F[i]][j]--;
                mul *= D[k][j];
                D[S[i]][F[i]]++;
                D[S[i]][k]++;
                D[F[i]][j]++;
                if(j == k) {
                    if(once) continue;
                    ++once;
                    answer += mul;
                }
                else {
                    answer += mul;
                }
                if(mul > 0) {
                    eprintf("rightmost vertical : k=%d j=%d mul=%lld\n", k, j, mul);
                }
            }
        }
        // put leftmost vertical
        once = 0;
        for(int k = 0; k < 26; ++k) {
            for(int j = 0; j < 26; ++j) {
                mul = D[S[i]][F[i]];
                D[S[i]][F[i]]--;
                mul *= D[k][S[i]];
                D[k][S[i]]--;
                mul *= D[k][j];
                D[k][j]--;
                mul *= D[j][F[i]];
                D[S[i]][F[i]]++;
                D[k][S[i]]++;
                D[k][j]++;
                if(j == k) {
                    if(once) continue;
                    ++once;
                    answer += mul;
                }
                else {
                    answer += mul;
                }
                if(mul > 0) {
                    eprintf("leftmost vertical : k=%d j=%d mul=%lld\n", k, j, mul);
                }
            }
        }
    }
    printf(LLD"\n", answer / 4);
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
