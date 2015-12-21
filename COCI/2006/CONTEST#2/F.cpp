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

const int maxN = 10000 + 7;

int n, m, dp[maxN], c[maxN];
bool used[maxN], marked[maxN];
vector<int> g[maxN], gt[maxN];

void cleanup() {
    memset(c, 0, sizeof(c));
    memset(dp, 0, sizeof(dp));
    memset(used, false, sizeof(used));
    memset(marked, false, sizeof(marked));
    for(int i = 0; i < maxN; ++i) {
        g[i].clear();
        gt[i].clear();
    }
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        int u, v;
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            g[u - 1].pb(v - 1);
            gt[v - 1].pb(u - 1);
        }
        return true;
    }
    return false;
}

void dfs(int v) {
    used[v] = true;
    marked[v] = true;
    for(int i = 0; i < gt[v].size(); ++i) {
        int to = gt[v][i];
        if(used[to] == false) {
            dfs(to);
        }
    }
}

bool cycle;

void detect_cycle(int v) {
    if(cycle) return ;
    c[v] = 1;
    for(int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if(!marked[to]) continue;
        if(c[to] == 0) {
            detect_cycle(to);
        }
        else if(c[to] == 1) {
            cycle = true; return ;
        }
    }
    c[v] = 2;
}

bool grt[maxN];
int MOD = 1000000000;

void go(int v) {
    for(int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if(!marked[to]) continue;
        dp[to] += dp[v];
        if(dp[to] >= MOD) {
            dp[to] -= MOD;
            grt[to] = true;
        }
        go(to);
    }
}

vector<int> order;

void top_sort(int v) {
    used[v] = true;
    for(int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if(!marked[to]) continue;
        if(!used[to]) {
            top_sort(to);
        }
    }
    order.pb(v);
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        dfs(1);
        if(!marked[0]) {
            printf("0\n");
            continue;
        }
        cycle = false;
        detect_cycle(0);
        if(cycle) {
            printf("inf\n");
            continue;
        }
        order.clear();
        memset(grt, false, sizeof(grt));
        memset(used, false, sizeof(used));
        top_sort(0);
        eprintf("ordder=");
        for(int i = 0; i < order.size(); ++i) {
            eprintf("%d ", order[i]);
        }
        eprintf("####\n");
        reverse(ALL(order));
        dp[0] = 1;
        for(int i = 0; i < order.size(); ++i) {
            int v = order[i];
            for(int j = 0; j < g[v].size(); ++j) {
                int to = g[v][j];
                if(!marked[to]) continue;
                dp[to] += dp[v];
                if(dp[to] >= MOD) {
                    dp[to] -= MOD;
                    grt[to] = true;
                }
                if(grt[v]) grt[to] = true;
            }
        }
        if(grt[1]) {
            printf("%.9d\n", dp[1]);
        }
        else {
            printf("%d\n", dp[1]);
        }
    }   
    return 0;
}
