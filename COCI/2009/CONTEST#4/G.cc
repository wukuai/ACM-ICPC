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

vector<int> G[maxN];
int n, m, k, EVIDENCE[maxN], USED[maxN], TOOK[maxN], TIMEIN[maxN], TIMEOUT[maxN];

void cleanup() {
	timer = 0;
	for(int i = 0; i < maxN; ++i) {
		DEG[i] = 0;
		G[i].clear();
		TOOK[i] = 0;
		USED[i] = 0;
		EVIDENCE[i] = 0;
	}
}

bool Read() {
    cleanup();
	if(scanf("%d%d%d", &n, &m, &k) == 3) {
		int u, v;
		for(int i = 0; i < m; ++i) {
			scanf("%d%d", &u, &v);
			G[u - 1].pb(v - 1);
			DEG[u - 1]++;
		}
		for(int i = 0; i < k; ++i) {
			scanf("%d", &u);
			EVIDENCE[u - 1] = 1;
		}
		return true;
	}
	return false;
}

void dfs(int v) {
	USED[v] = 1;
	TOOK[v] = 1;
	for(int i = 0; i < SZ(G[v]); ++i) {
		if(!USED[G[v][i]]) dfs(G[v][i]);
	}
}

void dfs1(int v) {
	TIMEIN[v] = timer++;
	USED[v] = 1;
	for(int i = 0; i < SZ(G[v]); 

void Run() {
	for(int i = 0; i < n; ++i) {
		if(EVIDENCE[i]) dfs(i);
	}
	for(int i = 0; i < n; ++i) {
		if(TOOK[i]) G[i].clear();
	}
	FILL(USED, 0);

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