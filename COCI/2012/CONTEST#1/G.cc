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

const int maxM = 1555;

long long k;
int n, m, G[maxM], R[maxM], T[maxM];

void cleanup() {
   FILL(G, 0);
   FILL(R, 0);
}

bool Read() {
    cleanup();
	if(scanf(LLD "%d%d", &k, &m, &n) == 3) {
		int u;
		for(int i = 0; i < n; ++i) {
			scanf("%d", &u);
			G[u] = 1;
		}
		return true;
	}
	return false;
}

void mul(int F1[maxM], int F2[maxM]) {
	FILL(T, 0);
	for(int i = 0; i < m; ++i) {
		if(F1[i]) {
			for(int j = 0; j < m; ++j) {
				if(F2[j]) {
					T[(i * j) % m] += 1;
				}
			}
		}
	}
	for(int i = 0; i < m; ++i) {
		F1[i] = min(T[i], 1);
	}
}

void Run() {
	R[1] = 1;
	for (unsigned long long mask = (1ll<<63); mask; mask >>=1) {
		if(mask & k) {
			mul(R, G);
		}
		mul(G, G);
	}
	for(int i = 0; i < m; ++i) {
		if(R[i]) {
			printf("%d ", i);
		}
	}
	printf("\n");
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