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

const int maxN = 500 + 7;

char S[maxN][maxN];
int n, m, U[maxN][maxN][7], pos_x, pos_y;

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

bool cycle;

void cleanup() {
    cycle = false;
    FILL(U, 0);
}

// UP, RIGHT, DOWN, LEFT
int dx[] = {0, -1, 0, 1, 0};
int dy[] = {0, 0, 1, 0, -1};

void dfs(int x, int y, int direction) {
    U[x][y][direction] = 1;
    if(S[x][y] == 'C' || cycle) {
        U[x][y][direction] = 2;
        return ;
    }
    if(S[x][y] == '.') {
        int n_x = x + dx[direction];
        int n_y = y + dy[direction];
        if(valid(n_x, n_y)) {
            if(U[n_x][n_y][direction] == 0) {
                dfs(n_x, n_y, direction);
            }
            else if(U[n_x][n_y][direction] == 1) {
                cycle = true;
            }
        }
    }
    else if(S[x][y] == '\\') {
        if(direction == 1) {
            int n_x = x, n_y = y - 1, n_d = 4;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    dfs(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
        else if(direction == 2) {
            int n_x = x + 1, n_y = y, n_d = 3;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    dfs(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }  
        }
        else if(direction == 3) {
            int n_x = x, n_y = y + 1, n_d = 2;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    dfs(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
        else if(direction == 4) {
            int n_x = x - 1, n_y = y, n_d = 1;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    dfs(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
    }
    else if(S[x][y] == '/') {
        if(direction == 1) {
            int n_x = x, n_y = y + 1, n_d = 2;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    dfs(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
        else if(direction == 2) {
            int n_x = x - 1, n_y = y, n_d = 1;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    dfs(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
        else if(direction == 3) {
            int n_x = x, n_y = y - 1, n_d = 4;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    dfs(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
        else if(direction == 4) {
            int n_x = x + 1, n_y = y, n_d = 3;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    dfs(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
    }
    U[x][y][direction] = 2;
}
////

int dfs1(int x, int y, int direction) {
    U[x][y][direction] = 1;
    if(S[x][y] == 'C' || cycle) {
        U[x][y][direction] = 2;
        return 0;
    }
    int answer = 0;
    if(S[x][y] == '.') {
        int n_x = x + dx[direction];
        int n_y = y + dy[direction];
        if(valid(n_x, n_y)) {
            if(U[n_x][n_y][direction] == 0) {
                answer = 1 + dfs1(n_x, n_y, direction);
            }
            else if(U[n_x][n_y][direction] == 1) {
                cycle = true;
            }
        }
    }
    else if(S[x][y] == '\\') {
        if(direction == 1) {
            int n_x = x, n_y = y - 1, n_d = 4;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    answer = 1 + dfs1(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
        else if(direction == 2) {
            int n_x = x + 1, n_y = y, n_d = 3;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    answer = 1 + dfs1(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }  
        }
        else if(direction == 3) {
            int n_x = x, n_y = y + 1, n_d = 2;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    answer = 1 + dfs1(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
        else if(direction == 4) {
            int n_x = x - 1, n_y = y, n_d = 1;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    answer = 1 + dfs1(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
    }
    else if(S[x][y] == '/') {
        if(direction == 1) {
            int n_x = x, n_y = y + 1, n_d = 2;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    answer = 1 + dfs1(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
        else if(direction == 2) {
            int n_x = x - 1, n_y = y, n_d = 1;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    answer = 1 + dfs1(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
        else if(direction == 3) {
            int n_x = x, n_y = y - 1, n_d = 4;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    answer = 1 + dfs1(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
        else if(direction == 4) {
            int n_x = x + 1, n_y = y, n_d = 3;
            if(valid(n_x, n_y)) {
                if(U[n_x][n_y][n_d] == 0) {
                    answer = 1 + dfs1(n_x, n_y, n_d);
                }
                else if(U[n_x][n_y][n_d] == 1) {
                    cycle = true;
                }
            }
        }
    }
    U[x][y][direction] = 2;
    return answer;
}
///
bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%s", S[i]);
        }
        scanf("%d%d", &pos_x, &pos_y);
        return true;
    }
    return false;
}

void Run() {
    pos_x--, pos_y--;
    if(valid(pos_x - 1, pos_y)) {
        dfs(pos_x - 1, pos_y, 1);
        if(cycle) {
            printf("U Voyager\n");
            return ;
        }
    }
    if(valid(pos_x, pos_y + 1)) {
        dfs(pos_x, pos_y + 1, 2);
        if(cycle) {
            printf("R Voyager\n");
            return ;
        }
    }
    if(valid(pos_x + 1, pos_y)) {
        dfs(pos_x + 1, pos_y, 3);
        if(cycle) {
            printf("D Voyager\n");
            return ;
        }
    }
    if(valid(pos_x, pos_y - 1)) {
        dfs(pos_x, pos_y - 1, 4);
        if(cycle) {
            printf("L Voyager\n");
            return ;
        }
    }
    FILL(U, 0);
    char dir;
    int answer = 0;
    if(valid(pos_x - 1, pos_y)) {
        int k = 1 + dfs1(pos_x -1, pos_y, 1);
        if(k > answer) {
            answer = k, dir = 'U';
        }
    }
    if(valid(pos_x, pos_y + 1)) {
        int k = 1 + dfs1(pos_x, pos_y + 1, 2);
        if(k > answer) {
            answer = k, dir = 'R';
        }
    }
    if(valid(pos_x + 1, pos_y)) {
        int k = 1 + dfs1(pos_x + 1, pos_y, 3);
        if(k > answer) {
            answer = k, dir = 'D';
        }
    }
    if(valid(pos_x, pos_y - 1)) {
        int k = 1 + dfs1(pos_x, pos_y - 1, 4);
        if(k > answer) {
            answer = k, dir = 'L';
        }
    }
    printf("%c %d\n", dir, 1 + answer);
}

} // Solution

namespace StressTest {

long long GetTime() {
#ifdef __GNUC__ 
    long long res; 
    asm volatile ("rdtsc" : "=A" (res)); 
    return res;
#else
    int low, hi; 
    __asm { 
        rdtsc
        mov low, eax
        mov hi, edx
    }
    return (((long long)hi) << 32LL) | low;
#endif
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
