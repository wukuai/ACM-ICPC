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

const int maxN = 1000 + 7;

int n, m, a, b, k, g, T[maxN][maxN], U[maxN], D[maxN], C[maxN], G[maxN][maxN];

void cleanup() {
    FILL(C, 0);
    FILL(U, 0);
    FILL(G, 63);
    FILL(T, 63);
    FILL(D, 63);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        scanf("%d%d%d%d", &a, &b, &k, &g);
        for(int i = 0; i < g; ++i) {
            scanf("%d", C + i);--C[i];
        }
        int u, v, w;
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            G[u - 1][v - 1] = w;
            G[v - 1][u - 1] = w;
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
        int t = 0;
        for(int i = 1; i < g; ++i) {
            T[C[i]][C[i - 1]] = t;
            T[C[i - 1]][C[i]] = t;
            t += G[C[i - 1]][C[i]];
        }
        a--, b--;
        D[a] = k;
        for(int i = 0; i < n; ++i) {
            int mmin = -1;
            for(int j = 0; j < n; ++j) {
                if(!U[j]) {
                    if(mmin == -1 || D[mmin] > D[j]) {
                        mmin = j;
                    }
                }
            }
            if(mmin == -1) break;
            U[mmin] = true;
            for(int j = 0; j < n; ++j) {
                if(D[mmin] < T[mmin][j]) {
                    D[j] = min(D[j], D[mmin] + G[mmin][j]);
                }
                else {
                    D[j] = min(D[j], max(D[mmin], T[mmin][j] + G[mmin][j]) + G[mmin][j]);
                }
            }
        }
        printf("%d\n", D[b] - k);
    }
    return 0;
}
