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

const int maxK = (int) 1e5 + 10;

map<int, int> row_how_many;
map<int, int> col_how_many;

map<int, long long> row_xor;
map<int, long long> column_xor;

map<long long, map<long long, int> > row_cnt;
map<long long, map<long long, int> > col_cnt;

map< pair<int, int>, long long> rooks;

int n, k, p, r[maxK], c[maxK], x[maxK];

void cleanup() {
  rooks.clear();
  row_xor.clear();
  row_cnt.clear();
  col_cnt.clear();
  column_xor.clear();
}

bool Read() {
    cleanup();
    if(scanf("%d%d%d", &n, &k, &p) == 3) {
      for(int i = 0; i < k; ++i) {
        scanf("%d%d%d", r + i, c + i, x + i);
        row_xor[r[i]] ^= x[i];
        column_xor[c[i]] ^= x[i];
        rooks[mp(r[i], c[i])] = x[i];
        row_how_many[r[i]]++;
        col_how_many[c[i]]++;
      }
      return true;
    }
    return false;
}

void Run() {
  int answer = 0;
  for(int i = 0; i < k; ++i) {
    long long C = row_xor[r[i]] ^ column_xor[c[i]];
    if(C != 0) {
      ++answer;
    }
    col_cnt[c[i]][C]++;
    row_cnt[r[i]][C]++;
  }
  for(map<int, int>::iterator it = row_how_many.begin(); it != row_how_many.end(); ++it) {
    if(row_xor[it->first] != 0) {
      answer += n - it->second;
    }
  }
  for(map<int, int>::iterator it = col_how_many.begin(); it != col_how_many.end(); ++it) {
    if(column_xor[it->first] != 0) {
      answer += n - it->second;
    }
  }
  long long tot = n; tot = tot * tot;
  eprintf("%d\n", answer);
  int r1, c1, r2, c2;
  for(int i = 0; i < p; ++i) {
    scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
    // removing from current place
    long long my_power = rooks[mp(r1, c1)];
    long long my_xor = column_xor[c1] ^ row_xor[r1];

    row_cnt[r1][my_xor]--;
    col_cnt[c1][my_xor]--;
    
    if(my_xor != 0) --answer;

    if(row_xor[r1] != 0) {
      answer -= n - row_how_many[r1];
    }
    if(column_xor[c1] != 0) {
      answer -= n - col_how_many[r1];
    }

    row_how_many[r1]--;
    col_how_many[c1]--;
    row_xor[r1] ^= my_power;
    column_xor[c1] ^= my_power;

    if(row_xor[r1] != 0) {
      answer += n - row_how_many[r1];
    }
    if(column_xor[c1] != 0) {
      answer += n - col_how_many[c1];
    }

    if(row_xor[r2] != 0) {
      answer -= n - row_how_many[r2];
    }
    if(column_xor[c2] != 0) {
      answer -= n - col_how_many[c2];
    }

    answer -= row_cnt[r1][my_power];
    answer += row_cnt[r1][0];

    swap(row_cnt[r1][my_power], row_cnt[r1][0]);
    
    answer -= col_cnt[c1][my_power];
    answer += col_cnt[c1][0];
    
    swap(col_cnt[c1][my_power], col_cnt[c1][0]);
    
    answer -= row_cnt[r2][my_power];
    answer += row_cnt[r2][0];
    
    swap(row_cnt[r2][my_power], row_cnt[r2][0]);
    
    answer -= col_cnt[c2][my_power];
    answer += col_cnt[c2][0];
    
    swap(col_cnt[c2][my_power], col_cnt[c2][0]);

    long long t;
    if((t = row_xor[r2] ^ column_xor[c2]) != 0) {
      answer++;
    }
    row_cnt[r2][t]++;
    col_cnt[c2][t]++;
    column_xor[c2] ^= my_power;
    row_xor[r2] ^= my_power;
    if(row_xor[r2] != 0) {
      answer += n - row_how_many[r2];
    }
    if(column_xor[c2] != 0) {
      answer += n - col_how_many[c2];
    }
    printf("%lld\n", tot - answer);
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
