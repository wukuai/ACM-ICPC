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

const int maxN = 111;

int n, m;
long long t, A[maxN], B[maxN], C[maxN], D[maxN];

void cleanup() {
   
}

bool Read() {
    cleanup();
	if(scanf(LLD, &t) == 1) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			scanf(LLD LLD, A + i, B + i);
		}
		scanf("%d", &m);
		for(int i = 0; i < m; ++i) {
			scanf(LLD LLD, C + i, D + i);
		}
		return true;
	}
	return false;
}

long long get_time(int len, long long X[], long long Y[], long long cnt) {
	long long ret = -1;
	long long lo = 0, hi = 1000000000000000000LL;
	while(lo <= hi) {
		bool ok = false;
		long long tm = (lo + hi) / 2;
		long long sm = 0;
		for(int i = 0; i < len; ++i) {
			if(tm >= X[i]) {
				sm += 1 + (tm - X[i]) / Y[i];
			}
			if(sm >= cnt) {
				ok = true; break;
			}
		}
		if(ok) {
			ret = tm;
			hi = tm - 1;
		}
		else {
			lo = tm + 1;
		}
	}
	return ret;
}

void Run() {
	long long answer = 0;
	long long lo = 0, hi = 1000000000LL;
	while(lo <= hi) {
		long long x = (lo + hi) / 2LL;
		long long t1 = get_time(n, A, B, x);
		long long t2 = get_time(m, C, D, x);
		if(t1 + t2 >= t) {
			if(t1 + t2) {
				answer = t1;
			}
			hi = x - 1;
		}
		else {
			lo = x + 1;
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