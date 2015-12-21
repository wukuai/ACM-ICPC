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

const int maxN = 111;

int n, a[maxN], odd;
int dp[maxN][maxN][maxN][2];

void cleanup() {
    odd = 0;
    memset(dp, -1, sizeof(dp));
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", a + i);
            odd += (a[i] & 1);
        }
        return true;
    }
    return false;
}

inline int convert(int x) {
    if(x < 0) x += n;
    if(x >= n) x -= n;
    return x;
}

int go(int l, int r, int c, int t) {
    if(l == r) {
        int C = c;
        if(t == 0) {
            C += a[l] & 1;
        }
        if(C > odd - C) {
            return 0;
        }
        return 1;
    }
    int& ref = dp[l][r][c][t];
    if(ref != -1) {
        return ref;
    }
    ref = t ^ 1;
    if(t == 0) {
        if(go(convert(l - 1), r, c + (a[l] & 1), t ^ 1) == 0) {
            ref = 0;
        }
        if(go(l, convert(r + 1), c + (a[r] & 1), t ^ 1) == 0) {
            ref = 0;
        }
    }
    else {
        if(go(convert(l - 1), r, c, t ^ 1) == 1) {
            ref = 1;
        }
        if(go(l, convert(r + 1), c, t ^ 1) == 1) {
            ref = 1;
        }
    }
    return ref;
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        if(n == 1) {
            if(a[0] & 1) {
                printf("1\n");
            }
            else {
                printf("0\n");
            }
        }
        else {
            int cnt = 0;
            for(int i = 0; i < n; ++i) {
                if(go(convert(i - 1), convert(i + 1), a[i] & 1, 1) == 0) {
                    ++cnt;
                }
            }
            printf("%d\n", cnt);
        }
    }
    
    return 0;
}
