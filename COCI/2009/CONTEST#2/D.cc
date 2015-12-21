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

const int maxN = 227;

int D[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int n, m, MAT[maxN][maxN], I[maxN][maxN], SOL5[maxN], SOL73[maxN], SOL[maxN], REV[maxN], MOD = 365, any;

void cleanup() {
    any = 1;
    FILL(I, 0);
    FILL(MAT, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        return true;
    }
    return false;
}

int get_day(int day, int month) {
    --month; --day;
    for(int i = 0; i < month; ++i) {
        day += D[i];
    }
    return day;
}

int get_rev(int num, int p) {
    for(int k = 0; k < p; ++k) {
        if(num * k % p == 1) {
            return k;
        }
    }
    assert(false);
    return -1;
}

void print() {
    eprintf("MAT : \n");
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= m; ++j) {
            eprintf("%d ", MAT[i][j]);
        }
        eprintf("\n");
    }
}

void gauss(int p, int A[]) {
    FILL(REV, 0);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= m; ++j) {
            MAT[i][j] = I[i][j];
        }
    }
    for(int i = 0; i < p; ++i) {
        for(int j = 0; j < p; ++j) {
            if(i * j % p == 1) {
                REV[i] = j;
            }
        }
    }
    int row = 0;

    for(int col = 0; col < m; ++col) {
        int ind = -1;
        for(int i = row; i < n && ind == -1; ++i) {
            if(MAT[i][col] != 0) {
                ind = i; break;
            }
        }
        if(ind == -1) continue;
        if(ind != row) {
            for(int i = 0; i <= m; ++i) {
                swap(MAT[ind][i], MAT[row][i]);
            }
        }
        int pivot = REV[MAT[row][col] % p];
        for(int j = 0; j <= m; ++j) {
            MAT[row][j] = MAT[row][j] * pivot % p;
        }
        for(int i = 0; i < n; ++i) {
            if(i == row) continue;
            int coeff = MAT[i][col];
            for(int j = 0; j <= m; ++j) {
                MAT[i][j] = (MAT[i][j] - coeff * MAT[row][j]) % p;
                if(MAT[i][j] < 0) MAT[i][j] += p;
            }
        }
        ++row;
    }

    for(int col = 0; col < m; ++col) {
        int ind = -1;
        for(int i = 0; i < n; ++i) {
            if(MAT[i][col] != 0) {
                ind = i; break;
            }
        }
        if(ind == -1) {
            if(MAT[ind][m] != 0) {
                any = 0;
            }
        }
        A[col] = MAT[ind][m];
    }
}

void Run() {
    int sd, sm, ed, em, s, e;
    for(int i = 0; i < n; ++i) {
        scanf("%d%d%d%d", &sd, &sm, &ed, &em);
        s = get_day(sd, sm);
        e = get_day(ed, em);
        for(int j = 0; j < m; ++j) {
            scanf("%d", &I[i][j]);
        }
        I[i][m] = (e - s) % MOD;
        if(I[i][m] < 0) I[i][m] += MOD;
    }
    gauss(5, SOL5);
    gauss(73, SOL73);
    if(!any) {
        printf("-1\n");
        return ;
    }
    long long answer = 0;
    for(int i = 0; i < m; ++i) {
        int k = (SOL5[i] * get_rev(73, 5) * 73 + SOL73[i] * get_rev(5, 73) * 5) % 365;
        SOL[i] = k;
        if(k == 0) answer += 365;
        answer += k;
    }
    for(int i = 0; i < n; ++i) {
        int t = 0;
        for(int j = 0; j < m; ++j) {
            t = (t + SOL[j] * I[i][j]) % 365;
        }
        assert(t == I[i][m]);
        eprintf("%d-th row is ok\n", i);
    }

    printf(LLD"\n", answer);
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
