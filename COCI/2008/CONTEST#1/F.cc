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

int n;
vector<int> G[maxN];
map<pair<int, int>, int> memo_dp;
map<pair<int, int>, int> memo_depth;


void cleanup() {
	memo_dp.clear();
	memo_depth.clear();
}

bool Read() {
    cleanup();
	if(scanf("%d", &n) == 1) {
		int u, v;
		for(int i = 0; i < n - 1; ++i) {
			scanf("%d%d", &u, &v);
			G[u - 1].pb(v - 1);
			G[v - 1].pb(u - 1);
		}
		return true;
	}
	return false;
}

int gO(int v, int par) {
	if(memo_depth.find(mp(v, par)) != memo_depth.end()) {
		return memo_depth[mp(v, par)];
	}
	int& ref = memo_depth[mp(v, par)];
	ref = 0;
	for(int i = 0; i < SZ(G[v]); ++i) {
		int to = G[v][i];
		if(to == par) continue;
		check_max(ref, gO(to, v) + 1);
	}
	return ref;
}

int go(int v, int par) {
	if(memo_dp.find(mp(v, par)) != memo_dp.end()) {
		return memo_dp[mp(v, par)];
	}
	int& ref = memo_dp[mp(v, par)];
	ref = 0;
	int child_cnt = 0;
	int mmax1 = -1, mmax2 = -1, dep;
	for(int i = 0; i < SZ(G[v]); ++i) {
		int to = G[v][i];
		if(to == par) continue;
		++child_cnt;
		check_max(ref, go(to, v));
		dep = gO(to, v);
		if(mmax1 == -1) {
			mmax1 = dep;
		}
		else if(mmax2 == -1) {
			mmax2 = dep;
		}
		else {
			if(dep > mmax2 || dep > mmax1) {
				mmax2 = dep;
			}
		}
		if(mmax1 != -1 && mmax2 != -1) {
			if(mmax1 < mmax2) {
				mmax1 ^= mmax2;
				mmax2 ^= mmax1;
				mmax1 ^= mmax2;
			}
		}
	}
	if(child_cnt > 1) {
		check_max(ref, mmax1 + mmax2 + 2);
	}
	if(child_cnt > 0) {
		check_max(ref, mmax1 + 1);
	}
	return ref;
}

void Run() {
	int ret = IINF;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < SZ(G[i]); ++j) {
			int to = G[i][j];
			check_min(ret, (go(to, i) + 1) / 2 + (go(i, to) + 1) / 2 + 1);
		}
	}
	printf("%d\n", ret);
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