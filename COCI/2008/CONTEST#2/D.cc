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

const int maxN = 5555;
const int MOD = 1000000007;

vector< pair<int, int> > P[maxN];
int n, m, D[maxN], ANS[maxN], DP_TO[maxN], DP_FROM[maxN], DEG[maxN];
vector<int> G[maxN], W[maxN], N[maxN], TO[maxN], NUM[maxN];

void cleanup() {
	
}

bool Read() {
    cleanup();
	if(scanf("%d%d", &n, &m) == 2) {
		int u, v, w;
		for(int i = 0; i < m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[u - 1].pb(v - 1); W[u - 1].pb(w); N[u - 1].pb(i);
		}
		return true;
	}
	return false;
}

void solve(int v) {
	int source = v;
	for(int i = 0; i < n; ++i) {
		DEG[i] = 0;
		D[i] = IINF;
		P[i].clear();
		DP_TO[i] = 0;
		TO[i].clear();
		NUM[i].clear();
		DP_FROM[i] = 0;
	}
	int to, w, nm;
	D[v] = 0;
	set< pair<int, int> > q;
	q.insert(mp(0, v));
	while(!q.empty()) {
		v = q.begin()->second;
		q.erase(q.begin());
		for(int i = 0; i < SZ(G[v]); ++i) {
			to = G[v][i];
			w = W[v][i];
			nm = N[v][i];
			if(D[to] > D[v] + w) {
				q.erase(mp(D[to], to));
				D[to] = D[v] + w;
				q.insert(mp(D[to], to));
				P[to].clear();
				P[to].pb(mp(v, nm));
			}
			else if(D[to] == D[v] + w) {
				P[to].pb(mp(v, nm));
			}
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < SZ(P[i]); ++j) {
			DEG[P[i][j].first]++;
			eprintf("edge(%d,%d)\n", P[i][j].first, i);
			TO[P[i][j].first].pb(i);
			NUM[P[i][j].first].pb(P[i][j].second);
		}
	}
	DP_TO[source] = 1;
	queue<int> qu;
	qu.push(source);
	vector<int> order;
	while(!qu.empty()) {
		v = qu.front();
		qu.pop();
		order.pb(v);
		for(int i = 0; i < SZ(TO[v]); ++i) {
			DP_TO[TO[v][i]] += DP_TO[v];
			if(DP_TO[TO[v][i]] >= MOD) DP_TO[TO[v][i]] -= MOD;
			qu.push(TO[v][i]);
		}
	}
	RVRS(order);
	for(int i = 0; i < SZ(order); ++i) {
		DP_FROM[order[i]] = 1;
		for(int j = 0; j < SZ(TO[order[i]]); ++j) {
			DP_FROM[order[i]] += DP_FROM[TO[order[i]][j]];
			if(DP_FROM[order[i]] >= MOD) DP_FROM[order[i]] -= MOD;
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < SZ(TO[i]); ++j) {
			ANS[NUM[i][j]] = (ANS[NUM[i][j]] + DP_TO[i] * (long long)DP_FROM[TO[i][j]] % MOD) % MOD;
		}
	}

}

void Run() {
	for(int i = 0; i < n; ++i) {
		solve(i);
	}
	for(int i = 0; i < m; ++i) {
		printf("%d\n", ANS[i]);
	}
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