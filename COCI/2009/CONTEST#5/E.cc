#pragma comment(linker, "/STACK:66777216")
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

int n, m;
char S[maxN][maxN], STR[maxN][maxN];
long long COL_COUNT[maxN][maxN], COL_SUM[maxN][maxN], ROW_COUNT[maxN][maxN], ROW_SUM[maxN][maxN], DP[maxN][maxN];

void cleanup() {
   
}

bool Read() {
    cleanup();
	if(scanf("%d%d", &n, &m) == 2) {
		for(int i = 0; i < n; ++i) {
			scanf("%s", S[i]);
		}
		return true;
	}
	return false;
}

long long solve(char GRID[maxN][maxN]) {
	FILL(DP, 0);
	FILL(COL_SUM, 0);
	FILL(ROW_SUM, 0);
	FILL(ROW_COUNT, 0);
	FILL(COL_COUNT, 0);

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			DP[i][j] = COL_COUNT[j][i - 1] * i - COL_SUM[j][i - 1];
			DP[i][j] += ROW_COUNT[i][j - 1] * j - ROW_SUM[i][j - 1];
			if((DP[i - 1][j - 1] == 0 && GRID[i - 1][j - 1] == 'X') || DP[i - 1][j - 1]) {
				DP[i][j] += 1 + DP[i - 1][j - 1];
			}
			if(GRID[i][j] == 'X') {
				COL_SUM[j][i] = COL_SUM[j][i - 1] + i;
				COL_COUNT[j][i] = COL_COUNT[j][i - 1] + 1;

				ROW_SUM[i][j] = ROW_SUM[i][j - 1] + j;
				ROW_COUNT[i][j] = ROW_SUM[i][j - 1] + 1;
			}
			else {
				COL_SUM[j][i] = COL_SUM[j][i - 1];
				COL_COUNT[j][i] = COL_COUNT[j][i - 1];

				ROW_SUM[i][j] = ROW_SUM[i][j - 1];
				ROW_COUNT[i][j] = ROW_SUM[i][j - 1];
			}
			eprintf("DP[%d][%d]=%lld ",// COL_SUM[%d][%d]=%lld, COL_COUNT[%d][%d]=%lld, ROW_SUM[%d][%d]=%lld, ROW_COUNT[%d][%d]=%lld\n",
				i, j, DP[i][j]);// i, j, COL_SUM[i][j], i, j, COL_COUNT[i][j], i, j, ROW_SUM[i][j], i, j, ROW_COUNT[i][j]);
		}
		eprintf("\n");
	}
	long long ret = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			ret += DP[i][j] * (GRID[i][j] == 'X');
		}
	}

	FILL(DP, 0);
	FILL(ROW_SUM, 0);
	FILL(ROW_COUNT, 0);
	eprintf("reverse\n");
	for(int i = 1; i <= n; ++i) {
		for(int j = m; j >= 1; --j) {
			if((DP[i - 1][j + 1] == 0 && GRID[i - 1][j + 1] == 'X') || DP[i - 1][j + 1]) {
				DP[i][j] = DP[i - 1][j + 1] + 1;
			}
			if(GRID[i][j] == 'X') {
				ROW_SUM[i][j] = ROW_SUM[i][j + 1] + j;
				ROW_COUNT[i][j] = ROW_COUNT[i][j + 1] + 1;
			}
			else {
				ROW_SUM[i][j] = ROW_SUM[i][j + 1];
				ROW_COUNT[i][j] = ROW_COUNT[i][j + 1];
				DP[i][j] += ROW_SUM[i][j + 1] - ROW_COUNT[i][j + 1] * j;
			}
			eprintf("DP[%d][%d]=%lld ", i, j, DP[i][j]);
		}
		eprintf("\n");
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			ret += DP[i][j] * (GRID[i][j] == 'X');
		}
	}
	return ret;
}

void Run() {
	FILL(STR, 0);
	eprintf("Solve for M\n");
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(S[i][j] == 'M') {
				STR[i + 1][j + 1] = 'X';
			}
		}
	}
	long long ans_m = solve(STR);
	FILL(STR, 0);
	eprintf("Solve for S\n");
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(S[i][j] == 'S') {
				STR[i + 1][j + 1] = 'X';
			}
		}
	}
	long long ans_s = solve(STR);
	printf(LLD" "LLD"\n", ans_m, ans_s);
}

} // Solution

namespace StressTest {

long long GetTime() {
    srand(time(NULL));
    return rand() << 16LL;
}

void GenerateInput() {
    FILE* output = fopen("C:\\Contests\\Templates\\input.txt", "w");
    srand(GetTime());

    
    fclose(output);
}

void BruteForce() {
    FILE* input = fopen("C:\\Contests\\Templates\\input.txt", "r");
    FILE* output = fopen("C:\\Contests\\Templates\\brute.out", "w");

    fclose(input);
    fclose(output);
}

} // StressTest

int main() {
#ifdef _DEBUG_
    int test_id = 0;
//    StressTest::GenerateInput();
//    StressTest::BruteForce();
    freopen("C:\\Contests\\Templates\\input.txt", "r", stdin);
    freopen("C:\\Contests\\Templates\\output.txt", "w", stdout);
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