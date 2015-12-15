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
const int IINF = 36 * 10000 + 7;
const double PI = acos(-1.0);
const long long LINF = 6000000000000000000LL;
//--------------------------------------------

namespace Solution {

struct Edge {
  int u;
  int v;
  int w;
  bool init;
  Edge() : u(0), v(0), w(0), init(false) {}
  Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w), init(true) {}
  bool initialized() {
    return init;
  }
};

struct Node {
  int v;
  bool must;
  Edge inE1;
  Edge inE2;
  Edge outE1;
  Edge outE2;
  Edge mustE;
  Node() : v(0), must(false) {}
  void setMust(int to) {
    must = true;
    if(outE1.v == to) {
      mustE = outE1;
    }
    if(outE2.initialized() && outE2.v == to) {
      mustE = outE2;
    }
  }
  void unsetMust() {
    must = false;
  }
  bool hasMust() {
    return must;
  }
};

const int maxN = 44;

int n, m;
Node e[maxN];

void cleanup() {
  FILL(e, 0);
}

void add_edge(int u, int v, int w) {
  if(!e[u].outE1.initialized()) {
    e[u].outE1 = Edge(u, v, w);
  }
  else {
    e[u].outE2 = Edge(u, v, w);
  }
  if(!e[v].inE1.initialized()) {
    e[v].inE1 = Edge(u, v, w);
  }
  else {
    e[v].inE2 = Edge(u, v, w);
  }
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
      for(int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
      }
      return true;
    }
    return false;
}

void take(Edge edge) {
  int u = edge.u, v = edge.v, otherTo = -1;
  if(e[u].outE1.v != v) {
    otherTo = e[u].outE1.v;
  }
  else if(e[u].outE2.initialized() && e[u].outE2.v != v) {
    otherTo = e[u].outE2.v;
  }
  if(otherTo != -1) {
    if(e[otherTo].inE1.u != u) {
      e[e[otherTo].inE1.u].setMust(otherTo);
    }
    if(e[otherTo].inE2.initialized() && e[otherTo].inE2.u != u) {
      e[e[otherTo].inE2.u].setMust(otherTo);
    }
  }
}

void untake(Edge edge) {
  int u = edge.u, v = edge.v, otherTo = -1;
  if(e[u].outE1.v != v) {
    otherTo = e[u].outE1.v;
  }
  else if(e[u].outE2.initialized() && e[u].outE2.v != v) {
    otherTo = e[u].outE2.v;
  }
  if(otherTo != -1) {
    if(e[otherTo].inE1.u != u) {
      e[e[otherTo].inE1.u].unsetMust();
    }
    if(e[otherTo].inE2.initialized() && e[otherTo].inE2.u != u) {
      e[e[otherTo].inE2.u].unsetMust();
    }
  }
} 

int findCircuit(int v, long long mask) {
  if(v != 0 && (mask & (1ll << v))) {
    return IINF;
  }
  if(mask == (1ll << n) - 1) {
    if(v == 0) return 0;
    return IINF;
  }
  int mmin = IINF;
  if(e[v].hasMust()) {
    take(e[v].mustE);
    mmin = min(mmin, e[v].mustE.w + findCircuit(e[v].mustE.v, mask | (1ll << v)));
    untake(e[v].mustE);
  }
  else {
    take(e[v].outE1);
    mmin = min(mmin, e[v].outE1.w + findCircuit(e[v].outE1.v, mask | (1ll << v)));
    untake(e[v].outE1);
    if(e[v].outE2.initialized()) {
      take(e[v].outE2);
      mmin = min(mmin, e[v].outE2.w + findCircuit(e[v].outE2.v, mask | (1ll << v)));
      untake(e[v].outE2);
    }
  }
  return mmin;
}

void Run() {
  printf("%d\n", findCircuit(0, 0));
}

} // Solution

namespace StressTest {

long long GetTime() {
    srand(time(NULL));
    return rand() << 16LL;
}

void GenerateInput() {
    FILE* output = fopen("input.txt", "w");
    srand(GetTime());

    
    fclose(output);
}

void BruteForce() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("brute.out", "w");

    fclose(input);
    fclose(output);
}

} // StressTest

int main() {
#ifdef _DEBUG_
//    StressTest::GenerateInput();
//    StressTest::BruteForce();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int test_cases;
    scanf("%d", &test_cases);

    for(int test_id = 1; test_id <= test_cases; ++test_id) {
#ifdef _DEBUG_
        clock_t startTime = clock();
        eprintf("Begin of test #%d:\n", test_id);
#endif

        Solution::Read();
        Solution::Run();

#ifdef _DEBUG_
        clock_t endTime = clock();
        eprintf("Time consumed for test #%d is %lf\n", test_id, (double)(endTime - startTime) / (double)CLOCKS_PER_SEC);
#endif
    }
    return 0;
}
