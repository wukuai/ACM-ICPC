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


long long d[100007];
pair<int, int> floors[100007];
int e, f, n, rem[107], mod[107], type[107], nextMine[100007], prevMine[100007], who[100007];

class Comparator {
public:
  bool operator() (int lhs, int rhs) {
    if(d[lhs] != d[rhs]) {
      return d[lhs] < d[rhs];
    }
    return lhs < rhs;
  }
};

void check_answer(long long& answer, int& answerFloor, long long d, int floor1) {
  if(d > answer) {
    answer = d;
    answerFloor = floor1;
  }
  else if(d == answer && floor1 < answerFloor) {
    answerFloor = floor1;
  }
}

int main() {
  int test_cases;
  scanf("%d", &test_cases);
  for(int test_id = 1; test_id <= test_cases; ++test_id) {
    scanf("%d%d", &f, &e);
    for(int i = 0; i < e; ++i) {
      scanf("%d%d", rem + i, mod + i);
    }
    n = 0;
    for(int i = 0; i < e; ++i) {
      int start = rem[i];
      while(start < f) {
        floors[n] = mp(start, i); 
        n = n + 1;
        start += mod[i];
      }
    }
    sort(floors, floors + n);
    FILL(type, -1);
    FILL(d, 63);
    FILL(nextMine, -1);
    FILL(prevMine, -1);
    FILL(who, -1);
    eprintf("Floors : ");
    for(int i = 0; i < n; ++i) {
      eprintf("%d ", floors[i].first);
      if(who[floors[i].second] != -1) {
        prevMine[i] = who[floors[i].second];
      }
      who[floors[i].second] = i;
    }
    FILL(who, -1);
    for(int i = n - 1; i >= 0; --i) {
      if(who[floors[i].second] != -1) {
        nextMine[i] = who[floors[i].second];
        eprintf("nextMine[%d]=%d\n", i, nextMine[i]);
      }
      who[floors[i].second] = i;
    }
    set<int, Comparator> q;
    d[0] = floors[0].first;
    q.insert(0);
    int ind;
    while(!q.empty()) {
      ind = *q.begin();
      q.erase(q.begin());
      if(nextMine[ind] != -1 && d[nextMine[ind]] > d[ind]) {
        q.erase(nextMine[ind]);
        d[nextMine[ind]] = d[ind];
        q.insert(nextMine[ind]);
      }
      if(prevMine[ind] != -1 && d[prevMine[ind]] > d[ind]) {
        q.erase(prevMine[ind]);
        d[prevMine[ind]] = d[ind];
        q.insert(prevMine[ind]);
      }
      if(ind + 1 < n) {
        if(d[ind + 1] > d[ind] + floors[ind + 1].first - floors[ind].first) {
          q.erase(ind + 1);
          d[ind + 1] = d[ind] + floors[ind + 1].first - floors[ind].first;
          q.insert(ind + 1);
        }
      }
      if(ind - 1 >= 0) {
        if(d[ind - 1] > d[ind] + floors[ind].first - floors[ind - 1].first) {
          q.erase(ind - 1);
          d[ind - 1] = d[ind] + floors[ind].first - floors[ind - 1].first;
          q.insert(ind - 1);
        }
      }
    }
    for(int i = 0; i < n; ++i) {
      eprintf("d[%d]=%lld\n", floors[i].first, d[i]);
    }
    long long answer = -1;
    int answerFloor = -1;
    int prev = 0;
    long long w = 0;
    for(int i = 0; i < n; ++i) {
      check_answer(answer, answerFloor, d[i], floors[i].first);
      int len = floors[i].first - prev - 1;
      if(len >= 1) {
        int lo = 1, hi = len;
        while(lo <= hi) {
          int mid = (lo + hi) / 2;
          if(w + mid <= d[i] + (len - mid) + 1) {
            check_answer(answer, answerFloor, w + mid, prev + mid);
            lo = mid + 1;
          }
          else {
            hi = mid - 1;
          }
        }
      }
      prev = floors[i].first;
      w = d[i];
    }
    if(prev != f - 1) {
      check_answer(answer, answerFloor, w + (f - 1) - prev, f - 1);
    }
    printf("%lld %d\n", answer, answerFloor);
  }
  return 0;
}
