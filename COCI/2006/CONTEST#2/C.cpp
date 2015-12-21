#include<bits/stdc++.h>

using namespace std;

// Template
#define mp(a, b) make_pair(a, b)
#define pb(x) push_back(x)
#define ALL(X) X.begin(), X.end()
#define SORT(x) sort(ALL(x))
#define next ___next
#define hash ___hash
#define rank ___rank
#define get _____get
#define count __count
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

const double EPS = 1e-9;
const int IINF = 1000000000;
const double PI = acos(-1.0);
const long long LINF = 6000000000000000000LL;

// End of template

const int maxN = 444;

char grid[maxN][maxN];
int n, m, sum[maxN][maxN];

void cleanup() {
    memset(grid, 0, sizeof(grid));
    memset(sum, 0, sizeof(sum));
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 1; i <= n; ++i) {
            scanf("%s", grid[i] + 1);
        }
        return true;
    }
    return false;
}

int get_sum(int X1, int Y1, int X2, int Y2) {
    int s = sum[X2][Y2];
    s -= sum[X1 - 1][Y2];
    s -= sum[X2][Y1 - 1];
    s += sum[X1 - 1][Y1 - 1];
    return s;
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                int add = 0;
                if(grid[i][j] == 'X') {
                    add += 1;
                }
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + add;
            }
        }
        int answer = 0;
        for(int s1 = 1; s1 <= n; ++s1) {
            for(int s2 = s1; s2 <= n; ++s2) {
                for(int j = 1; j <= m; ) {
                    if(grid[s1][j] == 'X') {
                        ++j;
                    }
                    else {
                        if(get_sum(s1, j, s2, j) != 0) {
                            ++j; continue;
                        }
                        int st = j;
                        while(j <= m && get_sum(s1, st, s2, j) == 0) {
                            if(answer < 2 * (s2 - s1 + j - st + 2)) {
                                answer = 2 * (s2 - s1 + j - st + 2);
                                eprintf("(%d,%d), (%d,%d) sum=%d\n", s1, st, s2, j, get_sum(s1, st, s2, j));
                            }
                            ++j;
                        }
                    }
                }
            }
        }
        eprintf("######\n");
        printf("%d\n", answer - 1);
    }
    return 0;
}
