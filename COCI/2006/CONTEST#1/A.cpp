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

int a[44];

void cleanup() {
    memset(a, 0, sizeof(a));
}

bool Read() {
    cleanup();
    int x;
    if(scanf("%d", &x) == 1) {
        a[x % 42]++;
        for(int i = 0; i < 9; ++i) {
            scanf("%d", &x);
            a[x % 42]++;
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
        int ans = 0;
        for(int i = 0; i < 44; ++i) {
            if(a[i])++ans;
        }
        printf("%d\n", ans);
    }
    
    return 0;
}

















