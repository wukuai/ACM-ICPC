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

const int maxN = 55;

int n, m;
char G[maxN][maxN];

int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

void cleanup() {
   
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%s", G[i]);
        }
        return true;
    }
    return false;
}

bool valid(int n_x, int n_y) {
    return n_x >= 0 && n_y >= 0 && n_x < n && n_y < m;
}

void Run() {
    set < pair< pair<int, int>, pair<int, int> > > st;
            for(int ii = 0; ii < n; ++ii) for(int jj = 0; jj < m; ++jj) {
            for(int k = 0; k < 8; ++k) {
                int n_i = ii + dx[k];
                int n_j = jj + dy[k];
                if(valid(n_i, n_j) && G[n_i][n_j] == 'o' && G[ii][jj] == 'o') {
                    st.insert(mp(mp(n_i, n_j), mp(ii, jj)));
                    st.insert(mp(mp(ii, jj), mp(n_i, n_j)));
                }
            }
            }    
    int mmax = SZ(st) / 2;

    eprintf("here : %d", mmax);
    int c = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(G[i][j] == 'o') continue;
            int cnt = 0;
            G[i][j] = 'o';
            for(int k = 0; k < 8; ++k) {
                int n_i = i + dx[k];
                int n_j = j + dy[k];
                if(valid(n_i, n_j) && G[n_i][n_j] == 'o') {
                    cnt++;
                }
            }
            G[i][j] = '.';
            check_max(c, cnt);
        }
    }


    printf("%d\n", mmax + c);
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
