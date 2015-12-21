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

long long kut( long long n ) {
   long long a = n/2, b = n%2;   
   return (a+1)*a + b*(a+1) + 1;
}

long long roditelj( long long x ) {
   long long lo = 0, hi = 1000000000;
   
   while( lo < hi ) {
      long long mid = (lo+hi)/2;
      if( x > kut(mid) ) lo = mid + 1; else hi = mid;
   }
   
   return kut(max(lo-4, 0LL)) - kut(lo) + x + 1;
}

const int maxN = 200 * 1000 + 7;

int n;
long long room, A[maxN];
vector< pair<int, long long> > G[2 * maxN];

struct Edge {
	long long fr;
	long long to;
	long long weight;
	Edge() : fr(0), to(0), weight(0) {}
	Edge(long long f, long long t, long long w) : fr(f), to(t), weight(w) {}
};

void cleanup() {
	for(int i = 0; i < 2 * maxN; ++i) {
		G[i].clear();
	}
}

bool Read() {
    cleanup();
	if(scanf(LLD "%d", &room, &n) == 2) {
		for(int i = 0; i < n; ++i) {
			scanf(LLD, &A[i]);
		}
		return true;
	}
	return false;
}

long long get_parent(long long x) {
	if(x == 4) return 1;
	long long lo = 1, hi = 100000000, k;
	while(lo <= hi) {
		long long mid = (lo + hi) / 2LL;
		if(4 * mid * mid >= x) {
			k = 2 * mid;
			hi = mid - 1;
		}
		else {
			lo = mid + 1;
		}
	}
	long long sq = k * k;
	if(sq - 1 >= x && x >= sq - k + 2) {
		return x - 3 * (k - 1) - (k - 2);
	}
	if(sq - k >= x && x >= sq - 2 * k + 3) {
		return k + x - 3 * (k - 1) - 2 * (k - 2);
	}
	if(sq - 2 * k + 1 >= x && x >= sq - 3 * k + 4) {
		return x - (k - 1) - 2 * (k - 2) - (k - 3) + 1;
	}
	return 1 + x - 2 * (k - 2) - 2 * (k - 3);
}

void Run() {
	long long tmp;
	sort(A, A + n);
	vector<Edge> edges;
	vector<long long> everything;
	vector<long long> to_add;
	bool is_one = false, is_n = false;
	for(int i = 0; i < n; ++i) {
		tmp = roditelj(A[i]);
		edges.pb(Edge(tmp, A[i], 1));
		everything.pb(A[i]);
		everything.pb(tmp);
		if(A[i] == 1) is_one = true;
		if(A[i] == room) is_n = true;
		to_add.pb(tmp);
		eprintf("parent of " LLD " is " LLD"\n", A[i], tmp);
	}
	for(int i = 0; i < SZ(to_add); ++i) {
		A[n] = to_add[i]; ++n;
	}
	if(!is_one) {
		everything.pb(1);
		A[n] = 1; ++n;
	}
	if(!is_n)  {
		everything.pb(room);
		A[n] = room; ++n;
	}
	sort(A, A + n);
	int room_rank, rank = 0;
	eprintf("A : ");
	for(int i = 0; i < n; ++i) {
		eprintf(LLD" ", A[i]);
	}
	eprintf("\n");
	for(int i = n - 1; i > 0; --i) {
		everything.pb(A[i]);
		everything.pb(A[i - 1]);
		edges.pb(Edge(A[i], A[i - 1], A[i] - A[i - 1]));
	}
	SRT(everything);
	map<long long, int> ranking;
	for(int i = 0; i < SZ(everything); ) {
		long long val = everything[i];
		ranking[val] = rank; 
		eprintf("for %lld---->%d\n", val, rank);
		++rank;
		while(i < SZ(everything) && val == everything[i]) {
			++i;
		}
	}
	int tmp1, tmp2;
	room_rank = ranking[room];
	for(int i = 0; i < SZ(edges); ++i) {
		tmp1 = ranking[edges[i].fr];
		tmp2 = ranking[edges[i].to];
		eprintf("got edge(%d,%d,%lld)\n", tmp1, tmp2, edges[i].weight);
		G[tmp1].pb(mp(tmp2, edges[i].weight));
		G[tmp2].pb(mp(tmp1, edges[i].weight));
	}
	vector<long long> d(rank, LINF);
	d[0] = 0;
	set< pair<long long, int> > q;
	q.insert(mp(0, 0));
	while(!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for(int i = 0; i < SZ(G[v]); ++i) {
			int to = G[v][i].first;
			long long w = G[v][i].second;
			if(d[to] > d[v] + w) {
				q.erase(mp(d[to], to));
				d[to] = d[v] + w;
				q.insert(mp(d[to], to));
			}
		}
	}
	printf(LLD"\n", d[room_rank]);
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