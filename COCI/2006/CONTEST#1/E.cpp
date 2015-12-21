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

const int maxN = 22;
const int maxM = 1 << 20;

int n;
double dp[maxM], p[maxN][maxN];

void cleanup() {
    for(int i = 0; i < maxM; ++i) {
        dp[i] = 0.0;
    }
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                scanf("%lf", &p[i][j]);
                p[i][j] /= 100.0;
            }
        }
        return true;
    }
    return false;
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        dp[0] = 1.0;
        for(int mask = 1; mask < (1 << n); ++mask) {
            int msk = mask, btcnt = 0;
            for( ; msk; msk &= msk - 1) ++btcnt;
            for(int j = 0; j < n; ++j) {
                if(mask & (1 << j)) {
                    dp[mask] = max(dp[mask], dp[mask ^ (1 << j)] * p[j][btcnt - 1]);
                }
            }
        }
        printf("%.13lf\n", 100.0 * dp[(1 << n) - 1]);
    }
    return 0;
}
