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

const int maxN = 77;
const int MOD = 5557;

vector<int> G[maxN], MSK[maxN];
int n, m, t, R[maxN][maxN], A[maxN][maxN], C[maxN][maxN], L[255];

void cleanup() {
	L['B'] = 0;
	L['J'] = 1;
	L['M'] = 2;
	L['P'] = 3;
	for(int i = 0; i < maxN; ++i) {
		G[i].clear();
		MSK[i].clear();
	}
}

bool Read() {
    cleanup();
	if(scanf("%d%d", &n, &m) == 2) {
		int len, u, v, mask = 0;
		char command[11];
		for(int i = 0; i < m; ++i) {
			mask = 0;
			scanf("%d%d%s", &u, &v, command);
			len = strlen(command);
			for(int j = 0; j < len; ++j) {
				mask |= 1 << L[command[j]];
			}
			G[v - 1].pb(u - 1);
			MSK[v - 1].pb(mask);
		}
		scanf("%d", &t);
		return true;
	}
	return false;
}

void mul(int M1[maxN][maxN], int M2[maxN][maxN]) {
	for(int i = 0; i <= 2 * n; ++i) {
		for(int j = 0; j <= 2 * n; ++j) {
			C[i][j] = 0;
			for(int k = 0; k <= 2 * n; ++k) {
				C[i][j] += M1[i][k] * M2[k][j];
				C[i][j] %= MOD;
			}
		}
	}
	for(int i = 0; i <= 2 * n; ++i) {
		for(int j = 0; j <= 2 * n; ++j) {
			M1[i][j] = C[i][j];
		}
	}
}

int solve(int mask) {
	memset(A, 0, sizeof(A));
	memset(R, 0, sizeof(R));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < SZ(G[i]); ++j) {
			int to = G[i][j], msk = MSK[i][j];
			A[2 * i][2 * to] = 1;
			if((mask & msk) != 0) {
				A[2 * i][2 * to + 1] = 1;
			}
		}
		A[2 * i + 1][2 * i] = 1;
	}
	for(int j = 0; j <= 2 * n; ++j) {
		A[2 * n][j] = A[0][j];
	}
	A[2 * n][2 * n] = 1;
	eprintf("A : \n");
	for(int i = 0; i <= 2 * n; ++i) {
		for(int j = 0; j <= 2 * n; ++j) {
			eprintf("%d ", A[i][j]);
		}
		eprintf("\n");
	}
	for(int i = 0; i <= 2 * n; ++i) {
		R[i][i] = 1;
	}
	int pw = t;
	while(pw) {
		if(pw & 1) {
			mul(R, A);
		}
		mul(A, A);
		pw >>= 1;
	}
	eprintf("R : \n");
	for(int i = 0; i <= 2 * n; ++i) {
		for(int j = 0; j <= 2 * n; ++j) {
			eprintf("%d ", R[i][j]);
		}
		eprintf("\n");
	}
	eprintf("ANS:%d\n", (R[2 * n][0] + R[2 * n][2 * n]) % MOD);
	return (R[2 * n][0] + R[2 * n][2 * n]) % MOD;
}

void Run() {
	int answer = 0;
	for(int mask = 0; mask < (1 << 4); ++mask) {
		int mul = 1;
		for(int j = 0; j < 4; ++j) {
			if(mask & (1 << j)) {
				mul *= -1;
			}
		}
		answer += mul * solve(mask);
		answer = (answer % MOD + MOD) % MOD;
	}
	printf("%d\n", answer);
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