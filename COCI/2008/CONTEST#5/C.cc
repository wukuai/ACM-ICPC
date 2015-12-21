#include <cstdio>
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
#include <unordered_set>
#include <unordered_map>
using namespace std;

//--------------------------------------------
#define SIZE(x) ((int)x.size())
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define ALL(X) X.begin(), X.end()
#define SORT(x) sort(ALL(x))
#define REVERSE(x) reverse(ALL(x))
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

const int maxN = 28;

int n, m; 
char M[maxN][maxN];
vector<pair< pair<int, int>, string> > D[255];

void cleanup() {
    for(int i = 0; i < 28; ++i) {
        M[0][i] = '.';
        M[27][i] = '.';
        M[i][0] = '.';
        M[i][27] = '.';
    }
    for(int i = 0; i < 255; ++i) {
        D[i].clear();
    }
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 1; i <= n; ++i) {
            scanf("%s", M[i] + 1);
        }
        return true;
    }
    return false;
}

bool check() {
    int m_x, m_y, z_x, z_y;
    vector<int> deg(maxN * maxN, 0);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(M[i][j] == 'M') m_x = i, m_y = j;
            if(M[i][j] == 'Z') z_x = i, z_y = j;
            if(M[i][j] != '.') {
                for(int k = 0; k < SIZE(D[M[i][j]]); ++k) {
                    int n_i = i + D[M[i][j]][k].first.first;
                    int n_j = j + D[M[i][j]][k].first.second;
                    if(M[n_i][n_j] == '.' && M[i][j] != 'M' && M[i][j] != 'Z'){ return false;}
                    int w;
                    if((w = D[M[i][j]][k].second.find(M[n_i][n_j])) != string::npos) {
                        deg[(i - 1) * m + j - 1]++;
                        if(M[i][j] == 'M' || M[i][j] == 'Z') {
                            deg[(n_i - 1) * m + n_j - 1]++;
                        }
                    }
                }
            }
        }
    }
    vector< pair<int, int> > odds;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            int v = (i - 1) * m + j - 1;
            if(deg[v] & 1) {
                odds.pb(mp(i, j));
            }
        }
    }
    if(deg[(m_x - 1) * m + m_y - 1] != 1 || deg[(z_x - 1) * m + z_y - 1] != 1) {
        return false;
    }
    if(odds.size() > 2) { return false;}
    if(odds.size() == 1) { return false;}
    if(odds.size() == 2) {
        for(int k = 0; k < SIZE(odds); ++k) {
            if(odds[k] != mp(m_x, m_y) && odds[k] != mp(z_x, z_y)) {
                return false;
            }
        }
    }
    return true;
}

void Run() {
    string s = "|-+1234";
    D['M'].pb(mp(mp(0, -1), "1+-2"));
    D['M'].pb(mp(mp(0, 1), "-+34"));
    D['M'].pb(mp(mp(1, 0), "|+23"));
    D['M'].pb(mp(mp(-1, 0), "|1+4"));
    D['Z'].pb(mp(mp(0, -1), "1+-2"));
    D['Z'].pb(mp(mp(0, 1), "-+34"));
    D['Z'].pb(mp(mp(1, 0), "|+23"));
    D['Z'].pb(mp(mp(-1, 0), "|1+4"));
    D['|'].pb(mp(mp(-1, 0), "|+14"));
    D['|'].pb(mp(mp(1, 0), "|+23"));
    D['-'].pb(mp(mp(0, 1), "-+34"));
    D['-'].pb(mp(mp(0, -1), "-+12"));
    D['+'].pb(mp(mp(0, 1), "+-34"));
    D['+'].pb(mp(mp(0, -1), "+-12"));
    D['+'].pb(mp(mp(1, 0), "|+23"));
    D['+'].pb(mp(mp(-1, 0), "|+14"));
    D['1'].pb(mp(mp(0, 1), "+-34"));
    D['1'].pb(mp(mp(1, 0), "+|23"));
    D['2'].pb(mp(mp(-1, 0), "|+14"));
    D['2'].pb(mp(mp(0, 1), "+-34"));
    D['3'].pb(mp(mp(0, -1), "+-12"));
    D['3'].pb(mp(mp(-1, 0), "+|14"));
    D['4'].pb(mp(mp(0, -1), "+-21"));
    D['4'].pb(mp(mp(1, 0), "|+23"));
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(M[i][j] == '.') {
                for(int k = 0; k < SIZE(s); ++k) {
                    M[i][j] = s[k];
                    if(check()) {
                        printf("%d %d %c\n", i, j, s[k]); return ;
                    }
                }
                M[i][j] = '.';
            }
        }
    }
}

} // Solution

namespace StressTest {

void GenerateInput() {
    FILE* output = fopen("input.txt", "w");

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
    srand(time(NULL));
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
