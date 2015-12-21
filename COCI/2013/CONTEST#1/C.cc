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

const int maxN = 55;

int n, A[maxN][maxN], S[maxN][maxN];
vector<int> LEFT_DOWN[maxN][maxN], RIGHT_DOWN[maxN][maxN];

void cleanup() {
   
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                scanf("%d", &A[i][j]);
            }
        }
        return true;
    }
    return false;
}

int get_sum(int x1, int y1, int x2, int y2) {
    assert(x1 <= x2 && y1 <= y2 && "Condition failed");
    int answer = S[x2][y2];
    answer -= S[x2][y1 - 1];
    answer -= S[x1 - 1][y2];
    answer += S[x1 - 1][y1 - 1];
#ifdef _DEBUG_
    int cum = 0;
    for(int i = x1; i <= x2; ++i) {
        for(int j = y1; j <= y2; ++j) {
            cum += A[i][j];
        }
    }
    assert(cum == answer && "Logic error");
#endif
    return answer;
}

int get_count(vector<int>& v, int sm) {
    int lower = -1, upper = -1;
    int lo = 0, hi = SZ(v) - 1;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        if(v[mid] == sm) {
            lower = mid;
            hi = mid - 1;
        }
        else if(v[mid] > sm) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }
    if(lower == -1) return 0;
    lo = 0, hi = SZ(v) - 1;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        if(v[mid] == sm) {
            upper = mid;
            lo = mid + 1;
        }
        else if(v[mid] > sm) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }
    return upper - lower + 1;
}

void Run() {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + A[i][j];
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            for(int len_i = 1; len_i <= n; ++len_i) {
                for(int len_j = 1; len_j <= n; ++len_j) {
                    // checking right down
                    if(i + len_i - 1 <= n && j + len_j - 1 <= n) {
                        RIGHT_DOWN[i][j].pb(get_sum(i, j, i + len_i - 1, j + len_j - 1));
                    }
                    // checking left down
                    if(i + len_i - 1 <= n && j - len_j + 1 >= 1) {
                        LEFT_DOWN[i][j].pb(get_sum(i, j - len_j + 1, i + len_i - 1, j));
                    }
                    // checking left up
                    if(i - len_i + 1 >= 1 && j - len_j - 1 >= 1) {
                    //    LEFT_UP[i][j][get_sum(i - len_i + 1, j - len_j + 1, i, j)]++;
                    }
                    // checking right up
                    if(i - len_i + 1 >= 1 && j + len_j - 1 <= n) {
                    //    RIGHT_UP[i][j][get_sum(i - len_i + 1, j, i, j + len_j - 1)]++;
                    }
                }
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            SRT(RIGHT_DOWN[i][j]);
            SRT(LEFT_DOWN[i][j]);
        }
    }
    long long answer = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            for(int len_i = 1; i + len_i - 1 <= n; ++len_i) {
                for(int len_j = 1; j + len_j - 1 <= n; ++len_j) {
                    int x1 = i, y1 = j, x2 = i + len_i - 1, y2 = j + len_j - 1;
                    int sm = get_sum(x1, y1, x2, y2);
                    if(x2 + 1 <= n && y2 + 1 <= n)  {
                        answer += get_count(RIGHT_DOWN[x2 + 1][y2 + 1], sm);
                        eprintf("right_down(%d,%d,%d,%d)=%d\n", i, j, len_i, len_j, RIGHT_DOWN[x2 + 1][y2 + 1][sm]);
                    }
                    x2 = i + len_i - 1, y2 = j;
                    if(x2 + 1 <= n && y2 - 1 >= 1) {
                        answer += get_count(LEFT_DOWN[x2 + 1][y2 - 1], sm);
                        eprintf("left_down(%d,%d,%d,%d)=%d\n", i, j, len_i, len_j, LEFT_DOWN[x2 + 1][y2 - 1][sm]);
                    }
                    x2 = i, y2 = j;
                    if(x2 - 1 >= 1 && y2 - 1 >= 1) {
                    //    answer += LEFT_UP[x2 - 1][y2 - 1][sm];
                    //    eprintf("left_up(%d,%d,%d,%d)=%d\n", i, j, len_i, len_j, LEFT_UP[x2 - 1][y2 - 1][sm]);
                    }
                    x2 = i, y2 = j + len_j - 1;
                    if(x2 - 1 >= 1 && y2 + 1 <= n) {
                    //    answer += RIGHT_UP[x2 - 1][y2 + 1][sm];
                    //    eprintf("right_up(%d,%d,%d,%d)=%d\n", i, j, len_i, len_j, RIGHT_UP[x2 - 1][y2 + 1][sm]);
                    }
                }
            }
        }
    }
    printf(LLD"\n", answer);
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
