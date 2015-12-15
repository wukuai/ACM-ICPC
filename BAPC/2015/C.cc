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

int n, m;
static int q[maxN * maxN];
char board[maxN][maxN], was[maxN][maxN], wasGodzilla[maxN][maxN];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void cleanup() {
   FILL(board, 0);
   FILL(was, 0);
   FILL(wasGodzilla, 0);
}

bool Read() {
  cleanup();
  if(scanf("%d%d", &m, &n) == 2) {
    for(int i = 0; i < n; ++i) {
      scanf("%s", board[i]);
    }
    return true;
  }
  return false;
}

bool valid(int x, int y) {
  return x >= 0 && y >= 0 && x < n && y < m;
}

void Run() {
  int qh = 0, qt = 0;
  int Gx = -1, Gy = -1;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      if(board[i][j] == 'G') {
        Gx = i, Gy = j;
      }
      else if(board[i][j] == 'M') {
        q[qt++] = i * m + j;
        eprintf("Meh(%d, %d)\n", i, j);
        was[i][j] = true;
      }
    }
  }
  int ruined = 0;
  wasGodzilla[Gx][Gy] = 1;
  //eprintf("Godzilla(%d, %d)\n", Gx, Gy);
  for( ; ; ) {
    bool made_move = false;
    for(int k = 0; k < 4; ++k) {
      int nx = Gx + dx[k], ny = Gy + dy[k];
      if(valid(nx, ny) && board[nx][ny] == 'R' && !wasGodzilla[nx][ny]) {
        ++ruined;
        board[nx][ny] = '.';
        made_move = true;
        Gx = nx, Gy = ny; 
        wasGodzilla[Gx][Gy] = 1;
        break;
      }
    }
    if(!made_move) {
      for(int k = 0; k < 4; ++k) {
        int nx = Gx + dx[k], ny = Gy + dy[k];
        if(valid(nx, ny) && !wasGodzilla[nx][ny]) {
          Gx = nx, Gy = ny;
          wasGodzilla[Gx][Gy] = true;
          break;
        }
      }
    }
    //eprintf("Godzilla(%d, %d)\n", Gx, Gy);
    if(qh < qt) {
      int bound = qt;
      while(qh < bound) {
        int nx = q[qh] / m, ny = q[qh] % m;
        qh++;
        for(int k = 0; k < 4; ++k) {
          int nnx = nx + dx[k], nny = ny + dy[k];
          if(valid(nnx, nny) && !was[nnx][nny] && board[nnx][nny] != 'R') {
            eprintf("Discovered(%d, %d)\n", nnx, nny);
            was[nnx][nny] = 1;
            q[qt++] = nnx * m + nny;
          }
        }
      }
    }
    bool killed = false;
    for(int k = 0; k < 4; ++k) {
      int nx = Gx, ny = Gy;
      while(valid(nx, ny)) {
        if(board[nx][ny] == 'R') break;
        if(was[nx][ny]) {
          killed = true; break;
        }
        nx += dx[k], ny += dy[k];
      }
    }
    if(killed) break;
  }
  printf("%d\n", ruined);
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
