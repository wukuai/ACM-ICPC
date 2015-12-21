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

const int maxC = 10000 + 7;

int n, c, dp[2][maxC], MOD = 1000000007;

void cleanup() {

}

int get_sum(int ind, int l, int r) {
    int s = dp[ind][r];
    if(l - 1 >= 0) {
        s -= dp[ind][l - 1];
    }
    if(s < MOD) {
        s += MOD;
    }
    return s;
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &c) == 2) {
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
        memset(dp[0], 0, sizeof(dp[0]));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i) {
            int curr = i & 1;
            int prev = curr ^ 1;
            memset(dp[curr], 0, sizeof(dp[curr]));
            for(int cnt = 0; cnt <= c; ++cnt) {
                int mmin = 0, mmax = min(i - 1, c);
                dp[curr][cnt] += get_sum(prev, cnt - mmax, cnt - mmin);
                if(dp[curr][cnt] >= MOD) {
                    dp[curr][cnt] -= MOD;
                }
            }
            for(int cnt = 1; cnt <= c; ++cnt) {
                dp[curr][cnt] += dp[curr][cnt - 1];
                if(dp[curr][cnt] >= MOD) {
                    dp[curr][cnt] -= MOD;
                }
            }
        }
        printf("%d\n", dp[n & 1][c]);
    }
    
    return 0;
}
