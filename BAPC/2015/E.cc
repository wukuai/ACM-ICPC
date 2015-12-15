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

const int maxN = 5000 + 7;

int n, X1, Y1, X2, Y2, dp[2][maxN], MOD = 5318008;

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int test_cases;
    scanf("%d", &test_cases);
    for(int test_id = 1; test_id <= test_cases; ++test_id) {
      scanf("%d", &n);
      scanf("%d%d%d%d", &X1, &Y1, &X2, &Y2);
      {
        bool ok = false;
        int dx1 = -1, dy1 = -1, dx2 = -1, dy2 = 1;
        int x1 = X1, y1 = Y1, x2 = X1, y2 = Y1;
        FILL(dp[0], 0);
        dp[0][Y1] = 1;
        int curr = 0, next = curr ^ 1;
        for(int i = 0; i < X1; ++i) {
          if(x1 < 1) break;
          if(x1 == X2 && y1 <= Y2 && Y2 <= y2) {
            ok = true; break;
          }
          FILL(dp[next], 0);
          int nx1 = x1 + dx1, ny1 = max(1, y1 + dy1), nx2 = x2 + dx2, ny2 = min(y2 + dy2, n);
          for(int j = y1; j <= y2; ++j) {
            if(j - 1 >= ny1) {
              dp[next][j - 1] += dp[curr][j];
              if(dp[next][j - 1] >= MOD) dp[next][j - 1] -= MOD;
            }
            dp[next][j] += dp[curr][j];
            if(dp[next][j] >= MOD) dp[next][j] -= MOD;
            if(j + 1 <= ny2) {
              dp[next][j + 1] += dp[curr][j];
              if(dp[next][j + 1] >= MOD) dp[next][j + 1] -= MOD;
            }
          }
          x1 = nx1, x2 = nx2, y1 = ny1, y2 = ny2;
          curr ^= 1, next ^= 1;
        }
        if(ok) {
          printf("%d\n", dp[curr][Y2]);
          continue;
        }
      }
      { //(is_in_direction(X1, Y1, -1, -1, 1, -1)) {
        bool ok = false;
        int dx1 = -1, dy1 = -1, dx2 = 1, dy2 = -1;
        int x1 = X1, y1 = Y1, x2 = X1, y2 = Y1;
        FILL(dp[0], 0);
        dp[0][X1] = 1;
        int curr = 0, next = curr ^ 1;
        for(int i = 0; i < Y1; ++i) {
          if(y1 < 1) break;
          if(y1 == Y2 && x1 <= X2 && X2 <= x2) {
            ok = true; break;
          }
          FILL(dp[next], 0);
          int nx1 = max(1, x1 + dx1), nx2 = min(n, x2 + dx2), ny1 = y1 + dy1, ny2 = y2 + dy2;
          for(int j = x1; j <= x2; ++j) {
            if(j - 1 >= nx1) {
              dp[next][j - 1] += dp[curr][j];
              if(dp[next][j - 1] >= MOD) dp[next][j - 1] -= MOD;
            }
            dp[next][j] += dp[curr][j];
            if(dp[next][j] >= MOD) dp[next][j] -= MOD;
            if(j + 1 <= nx2) {
              dp[next][j + 1] += dp[curr][j];
              if(dp[next][j + 1] >= MOD) dp[next][j + 1] -= MOD;
            }
          }
          x1 = nx1, x2 = nx2, y1 = ny1, y2 = ny2;
          curr ^= 1, next ^= 1;
        }
        if(ok) {
          printf("%d\n", dp[curr][X2]);
          continue;
        }
      }
      swap(X1, X2);
      swap(Y1, Y2);
      {
        bool ok = false;
        int dx1 = -1, dy1 = -1, dx2 = -1, dy2 = 1;
        int x1 = X1, y1 = Y1, x2 = X1, y2 = Y1;
        FILL(dp[0], 0);
        dp[0][Y1] = 1;
        int curr = 0, next = curr ^ 1;
        for(int i = 0; i < X1; ++i) {
          if(x1 < 1) break;
          if(x1 == X2 && y1 <= Y2 && Y2 <= y2) {
            ok = true; break;
          }
          FILL(dp[next], 0);
          int nx1 = x1 + dx1, ny1 = max(1, y1 + dy1), nx2 = x2 + dx2, ny2 = min(y2 + dy2, n);
          for(int j = y1; j <= y2; ++j) {
            if(j - 1 >= ny1) {
              dp[next][j - 1] += dp[curr][j];
              if(dp[next][j - 1] >= MOD) dp[next][j - 1] -= MOD;
            }
            dp[next][j] += dp[curr][j];
            if(dp[next][j] >= MOD) dp[next][j] -= MOD;
            if(j + 1 <= ny2) {
              dp[next][j + 1] += dp[curr][j];
              if(dp[next][j + 1] >= MOD) dp[next][j + 1] -= MOD;
            }
          }
          x1 = nx1, x2 = nx2, y1 = ny1, y2 = ny2;
          curr ^= 1, next ^= 1;
        }
        if(ok) {
          printf("%d\n", dp[curr][Y2]);
          continue;
        }
      }
      { //(is_in_direction(X1, Y1, -1, -1, 1, -1)) {
        bool ok = false;
        int dx1 = -1, dy1 = -1, dx2 = 1, dy2 = -1;
        int x1 = X1, y1 = Y1, x2 = X1, y2 = Y1;
        FILL(dp[0], 0);
        dp[0][X1] = 1;
        int curr = 0, next = curr ^ 1;
        for(int i = 0; i < Y1; ++i) {
          if(y1 < 1) break;
          if(y1 == Y2 && x1 <= X2 && X2 <= x2) {
            ok = true; break;
          }
          FILL(dp[next], 0);
          int nx1 = max(1, x1 + dx1), nx2 = min(n, x2 + dx2), ny1 = y1 + dy1, ny2 = y2 + dy2;
          for(int j = x1; j <= x2; ++j) {
            if(j - 1 >= nx1) {
              dp[next][j - 1] += dp[curr][j];
              if(dp[next][j - 1] >= MOD) dp[next][j - 1] -= MOD;
            }
            dp[next][j] += dp[curr][j];
            if(dp[next][j] >= MOD) dp[next][j] -= MOD;
            if(j + 1 <= nx2) {
              dp[next][j + 1] += dp[curr][j];
              if(dp[next][j + 1] >= MOD) dp[next][j + 1] -= MOD;
            }
          }
          x1 = nx1, x2 = nx2, y1 = ny1, y2 = ny2;
          curr ^= 1, next ^= 1;
        }
        if(ok) {
          printf("%d\n", dp[curr][X2]);
          continue;
        }
      }    
    }
    return 0;
}
