#include<bits/stdc++.h>

using namespace std;

//--------------------------------------------
#define SIZE(x) (x.size())
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define ALL(X) X.begin(), X.end()
#define SORT(x) sort(ALL(x))
#define REVERSE(x) reverse(ALL(x))
#define FILL(x, value) memset(x, value, sizeof(x))

#define next next1
#define hash hash1
#define rank rank1
#define count count1

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
//--------------------------------------------

const int maxN = 100 * 1000 + 7;

int n, A[maxN], T[maxN], P[maxN];

void cleanup() {
    FILL(P, 0);
    FILL(T, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", A + i);
        }
        return true;
    }
    return false;
}

void update(int pos, int delta) {
    for( ; pos < n; pos |= pos + 1) {
        T[pos] += delta;
    }
}

int query(int pos) {
    int ret = 0;
    for( ; pos >= 0; pos = (pos & (pos + 1)) - 1) {
        ret += T[pos];
    }
    return ret;
}

int sum(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        int l = 0, r = n - 1;
        for(int i = 0; i < n; ++i) {
            P[A[i] - 1] = i;
            update(i, 1);
        }
        for(int i = 0; i < n; ++i) {
            if((i + 1) & 1) {
                update(P[l], -1);
                printf("%d\n", sum(0, P[l]));
                l++;
            }
            else {
                update(P[r], -1);
                printf("%d\n", sum(P[r], n - 1));
                r--;
            }
        }
    }
    return 0;
}
