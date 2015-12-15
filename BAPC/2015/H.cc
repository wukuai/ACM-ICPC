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

const double EPS = 1e-4;
const int IINF = 1000000000;
const double PI = acos(-1.0);
const long long LINF = 6000000000000000000LL;
//--------------------------------------------

namespace Solution {

struct Point {
  double x;
  double y;
  Point() : x(0.0), y(0.0) {}
  Point(double _x, double _y) : x(_x), y(_y) {}
};

double det(double a11, double a12, double a21, double a22) {
  return a11 * a22 - a12 * a21;
}

struct Segment {
  double A;
  double B;
  double C;
  Point p0;
  Point p1;
  Segment() : A(0.0), B(0.0), C(0.0) {}
  Segment(double x1, double y1, double x2, double y2) :
    p0(x1, y1),
    p1(x2, y2),
    A(y2 - y1),
    B(x1 - x2),
    C(-y1 * B - x1 * A) {
      //empty
    }
};

bool intersect(const Segment& lhs, const Segment& rhs) {
  double d = det(lhs.A, lhs.B, rhs.A, rhs.B);
  if(fabs(d) < EPS) {
    return false;
  }
  double d1 = det(lhs.A, -lhs.C, rhs.A, -rhs.C);
  double d2 = det(-lhs.C, lhs.B, -rhs.C, rhs.B);
  double y = d1 / d, x = d2 / d;
  return min(lhs.p0.x, lhs.p1.x) <= x && x <= max(lhs.p0.x, lhs.p1.x) && min(lhs.p0.y, lhs.p1.y) <= y && y <= max(lhs.p0.y, lhs.p1.y) && min(rhs.p0.x, rhs.p1.x) <= x && x <= max(rhs.p0.x, rhs.p1.x) && min(rhs.p0.y, rhs.p1.y) <= y && y <= max(rhs.p0.y, rhs.p1.y);
}

double L, W, x, y, ws;

vector<Point> points;
void cleanup() {
  points.resize(0); 
}

bool Read() {
    cleanup();
    return scanf("%lf%lf%lf%lf%lf", &L, &W, &x, &y, &ws) == 5;
}

void Run() {
  Segment s1(x, y, x + ws, y);
  Segment s2(x + ws, y, x + ws, y + ws);
  Segment s3(x, y + ws, x + ws, y + ws);
  Segment s4(x, y, x, y + ws);
  for(double i = 0; i <= L; i += 1.0) {
    points.pb(Point(i, 0));
  }
  for(double i = 1; i <= W; i += 1.0) {
    points.pb(Point(L, i));
  }
  for(double i = 0; i <= L - 1; i += 1.0) {
    points.pb(Point(i, W));
  }
  for(double i = 1; i <= W - 1; i += 1.0) {
    points.pb(Point(0, i));
  }
  int counter = 0;
  for(int i = 0; i < SZ(points); ++i) {
    for(int j = i + 1; j < SZ(points); ++j) {
      for(int k = j + 1; k < SZ(points); ++k) {
        if(fabs(points[i].x - points[j].x) < EPS && fabs(points[j].x - points[k].x) < EPS) continue;
        if(fabs(points[i].y - points[j].y) < EPS && fabs(points[j].y - points[k].y) < EPS) continue;
        Segment s(points[i].x, points[i].y, points[j].x, points[j].y);
        if(intersect(s, s1) || intersect(s, s2) || intersect(s, s3) || intersect(s, s4)) {
          continue;
        }
        s = Segment(points[i].x, points[i].y, points[k].x, points[k].y);
        if(intersect(s, s1) || intersect(s, s2) || intersect(s, s3) || intersect(s, s4)) {
          continue;
        }
        s = Segment(points[j].x, points[j].y, points[k].x, points[k].y);
        if(intersect(s, s1) || intersect(s, s2) || intersect(s, s3) || intersect(s, s4)) {
          continue;
        }
        ++counter;
      }
    }
  }
  printf("%d\n", counter);
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
#endif

        Solution::Read();
        Solution::Run();

#ifdef _DEBUG_
        clock_t endTime = clock();
#endif
    }
    return 0;
}
