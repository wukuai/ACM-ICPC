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

const int maxN = 300 * 1000 + 7;

int m, k, n, A[maxN];
long long DP[maxN][2];

void cleanup() {
   FILL(DP, -1);
}

bool Read() {
    cleanup();
	if(scanf("%d%d%d", &m, &k, &n) == 3) {
		for(int i = 1; i <= n; ++i) {
			scanf("%d", A + i);
		}
		return true;
	}
	return false;
}

long long go(int pos, int tp) {
	if(pos > n) return 0;
	long long& ref = DP[pos][tp];
	if(ref != -1) {
		return ref;
	}
	ref = IINF + IINF + 777;
	if(tp) { // at top
		int n_pos = -1;
		int lo = pos, hi = n + 1;
		while(lo <= hi) {
			int mid = (lo + hi) / 2;
			if(A[pos] + k - 1 >= A[mid]) {
				lo = mid + 1;
			}
			else {
				n_pos = mid;
				hi = mid - 1;
			}
		}
		if(n_pos > n) ref = 0;
		check_min(ref, k + go(n_pos, 1));
		check_min(ref, A[n_pos] - (A[pos] + k - 1LL) + go(n_pos, 0));
	}
	else { // at bottom
		if(pos + 1 > n) ref = 0;
		check_min(ref, k + go(pos + 1, 1));
		check_min(ref, A[pos + 1] - (long long)A[pos] + go(pos + 1, 0));
	}
	return ref;
}

void Run() {
	A[0] = -(IINF + IINF + 777);
	A[n + 1] = IINF + IINF + 777;
	sort(A, A + n + 2);
	printf(LLD"\n", go(0, 0));
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