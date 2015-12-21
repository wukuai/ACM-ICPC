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

const int maxN = 100 + 7;
const int maxM = 1000 + 7;

int n, m, D[maxN], A[maxM], B[maxM];

struct Edge {
	int u;
	int v;
	int cap;
	Edge() : u(0), v(0), cap(0) {}
	Edge(int _u, int _v, int _cap) : u(_u), v(_v), cap(_cap) {}
};

struct MaxFlow {
	int sink;
	int source;
	int max_flow;
	vector<Edge> edges;
	vector<bool> used;
	vector< vector<int> > cap;
	MaxFlow() {
		sink = 0;
		max_flow = 0;
		edges.clear();
	}
	void collect_edges(Edge edge) {
		edges.pb(edge);
		check_max(sink, edge.u);
		check_max(sink, edge.v);
		eprintf("edge(%d,%d,%d)\n", edge.u, edge.v, edge.cap);
	}
	void set_source(int _source) {
		source = source;
	}
	int flow(int v, int delta) {
		if(v == sink) return delta;
		used[v] = true;
		for(int i = 0; i <= sink; ++i) {
			if(!used[i] && cap[v][i] > 0) {
				int f = flow(i, min(delta, cap[v][i]));
				if(f != 0) {
					cap[v][i] -= f;
					cap[i][v] += f;
					return f;
				}
			}
		}
		return 0;
	}

	void invoke_flow() {
		used = vector<bool> (sink + 1);
		cap = vector< vector<int> > (sink + 1, vector<int>(sink + 1, 0));
		for(int i = 0; i < SZ(edges); ++i) {
			cap[edges[i].u][edges[i].v] = edges[i].cap;
		}
		while(true) {
			used.assign(sink + 1, 0);
			int f = flow(0, IINF);
			if(f == 0) break;
			max_flow += f;
		}
	}
};

void cleanup() {

}

bool Read() {
    cleanup();
	if(scanf("%d%d", &n, &m) == 2) {
		for(int i = 0; i < n; ++i) {
			scanf("%d", D + i);
		}
		for(int i = 0; i < m; ++i) {
			scanf("%d%d", A + i, B + i);
		}
		return true;
	}
	return false;
}

void Run() {
	int total = 0;
	MaxFlow max_flow;
	for(int i = 0; i < n; ++i) total += D[i];
	total /= 2;
	int source = 0;
	max_flow.set_source(source);
	for(int i = 1; i <= total; ++i) {
		max_flow.collect_edges(Edge(source, i, 2));
	}
	for(int i = 0; i < m; ++i) {
		max_flow.collect_edges(Edge(i + 1, total + A[i], 2));
		max_flow.collect_edges(Edge(i + 1, total + B[i], 2));
	}
	for(int i = m; i < total; ++i) {
		for(int j = 1; j <= n; ++j) {
			max_flow.collect_edges(Edge(i + 1, total + j, 2));
		}
	}
	for(int j = 1; j <= n; ++j) {
		max_flow.collect_edges(Edge(total + j, total + n + 1, D[j - 1]));
	}
	max_flow.invoke_flow();
	printf("%d\n", total);
	vector<int> answer(n + 1, 0);
	for(int i = 1; i <= total; ++i) {
		vector<int> tmp;
		for(int j = 1; j <= n; ++j) {
			int u = i, v = total + j;
			int got = max_flow.cap[v][u];
			if(got == 1) {
				tmp.pb(j);
			}
			else if(got == 2) {
				tmp.pb(j);
			}
		}
		if(SZ(tmp) == 1) {
			answer[tmp[0]] += 2;
			if(i <= m) {
				int fr, sc;
				if(tmp[0] == A[i - 1]) fr = A[i - 1], sc = B[i - 1];
				else fr = B[i - 1], sc = A[i - 1];
				printf("%d %d 2\n", fr, sc);
			}
			else {
				printf("%d %d 2\n", tmp[0], tmp[0] == 1 ? 2 : 1);
			}
		}
		else {
			answer[tmp[0]] += 1;
			answer[tmp[1]] += 1;
			printf("%d %d 1\n", tmp[0], tmp[1]);
		}
	}
	for(int i = 1; i <= n; ++i) {
		eprintf("%d ", answer[i]);
	}
	eprintf("\n");
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