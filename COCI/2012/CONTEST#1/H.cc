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

const int blockS = (int)3;
const int maxN = (int)1e5 + 10;

struct Line {
  long long slope;
  long long coefficient;
  Line() : slope(0.0), coefficient(0.0) {}
  Line(long long s, long long c) : slope(s), coefficient(c) {}
  long long evaluate(long long x) {
    return slope * x + coefficient;
  }
};

bool operator < (const Line& lhs, const Line& rhs) {
  return mp(lhs.slope, lhs.coefficient) < mp(rhs.slope, rhs.coefficient);
}

struct Block {
  long long ccw(Line& a, Line& b, Line& c) {
    return (b.coefficient - a.coefficient) * (a.slope - c.slope) - (c.coefficient - a.coefficient) * (a.slope - b.slope);
  }
  int hull_size;
  int pointer;
  int current_lines;
  Line l[blockS];
  int sorted[blockS];
  int convex_hull[blockS];
  Block() : hull_size(0), pointer(0), current_lines(0) {}
  int get_hull_size() {
    return hull_size;
  }
  long long get_max(long long x) {
    if(current_lines == 0) return -LINF;
    while(pointer + 1 < hull_size && l[convex_hull[pointer]].evaluate(x) <= l[convex_hull[pointer + 1]].evaluate(x)) {
      ++pointer;
    }
    return l[convex_hull[pointer]].evaluate(x);
  }
  void update(int ind, Line new_line) {
    int i;
    for(i = 0; i < current_lines; ++i) {
      if(sorted[i] == ind) {
        break;
      }
    }
    if(i < current_lines) {
      while(i + 1 < current_lines) {
        swap(sorted[i], sorted[i + 1]);
        ++i;
      }
      current_lines--;
    }
    l[ind] = new_line;
    sorted[current_lines++] = ind;
    i = current_lines - 1;
    while(i - 1 >= 0 && l[sorted[i - 1]] < l[sorted[i]]) {
      swap(sorted[i], sorted[i - 1]);
      --i;
    }
    pointer = hull_size = 0;
    for(i = 0; i < current_lines; ++i) {
      while(hull_size >= 2 && ccw(l[convex_hull[hull_size - 1]], l[convex_hull[hull_size - 2]], l[sorted[i]]) >= 0) {
        --hull_size;
      }
      convex_hull[hull_size++] = sorted[i];
    }
  }
} bl[maxN / blockS + 7];

int n, m;
long long move_in_day[maxN], profit[maxN], balance[maxN];

long long calc(int k, int t) {
  if(move_in_day[k] == 0) return -LINF;
  return (t - move_in_day[k]) * profit[k] + balance[k];
}

void cleanup() {
   
}

bool Read() {
    cleanup();
    return scanf("%d%d", &n, &m) == 2;
}

void Run() {
  int type, tm, a, b, k;
  long long t, z, s;
  for(int i = 0; i < m; ++i) {
    scanf("%d", &type);
    if(type == 1) {
      scanf(LLD "%d" LLD LLD, &t, &k, &z, &s);
      --k;
      move_in_day[k] = t;
      profit[k] = z;
      balance[k] = s;
      bl[k / blockS].update(k % blockS, Line(z, s - t * z));
    }
    else {
      long long answer = -LINF;
      scanf("%d%d%d", &tm, &a, &b);
      --a, --b;
      if(a > b) swap(a, b);
      while(a % blockS != 0 && a <= b) {
        answer = max(answer, calc(a, tm)); ++a;
      }
      while(a + blockS - 1 <= b) {
        answer = max(answer, bl[a / blockS].get_max(tm));
        a += blockS;
      }
      while(a <= b) {
        answer = max(answer, calc(a, tm)); ++a;
      }
      if(answer == -LINF) {
        printf("nema\n");
      }
      else {
        printf(LLD"\n", answer);
      }
    }
  }
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
    int test_id = 0;
//    StressTest::GenerateInput();
//    StressTest::BruteForce();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
