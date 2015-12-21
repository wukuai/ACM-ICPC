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

template <class Type> inline void check_min(Type& actual, const Type& new_value) {
    if(actual > new_value) {
        actual = new_value;
    }
}

template <class Type> inline void check_max(Type& actual, const Type& new_value) {
    if(actual < new_value) {
        actual = new_value;
    }
}
//--------------------------------------------

const int maxN = 100 * 1000 + 7;

set< pair<int, int> > bridges;
unordered_set<int> S[maxN];
vector<int> G[maxN], CH[maxN], MARK[maxN];
int n, m, timer, TIN[maxN], TOUT[maxN], FUP[maxN], CUT[maxN], UP[maxN][20]; 

void cleanup() {
    timer = 1;
    FILL(UP, -1);
    for(int i = 0; i < maxN; ++i) {
        G[i].clear();
        S[i].clear();
        CH[i].clear();
        MARK[i].clear();
        TIN[i] = TOUT[i] = FUP[i] = CUT[i] = 0;
    }
}

void detect_bridges(int v, int parent = -1) {
    TIN[v] = timer++;
    FUP[v] = TIN[v];
    for(int i = 0; i < G[v].size(); ++i) {
        int to = G[v][i];
        if(to == parent) continue;
        if(TIN[to] == 0) {
            detect_bridges(to, v);
            if(FUP[to] > TIN[v]) {
                bridges.insert(mp(v, to));
                bridges.insert(mp(to, v));
            }
            check_min(FUP[v], FUP[to]);
        }
        else {
            check_min(FUP[v], TIN[to]);
        }
    }
    TOUT[v] = timer++;
}

void detect_cut_points(int v, int parent) {
    TIN[v] = timer++;
    FUP[v] = TIN[v];
    int childeren = 0;
    UP[v][0] = parent == -1 ? 0 : parent;
    for(int i = 1; i < 20; ++i) {
        UP[v][i] = UP[UP[v][i - 1]][i - 1];
    }
    for(int i = 0; i < G[v].size(); ++i) {
        int to = G[v][i];
        if(to == parent) continue;
        if(TIN[to] == 0) {
            ++childeren;
            detect_cut_points(to, v);
            CH[v].pb(to);
            MARK[v].pb(0);
            if(FUP[to] >= TIN[v] && parent != -1) {
                CUT[v] = 1;
                MARK[v].back() = 1;
            }
            check_min(FUP[v], FUP[to]);
        }
        else {
            check_min(FUP[v], TIN[to]);
        }
    }
    if(childeren > 1 && parent == -1) {
        CUT[v] = 1;
        for(int i = 0; i < MARK[v].size(); ++i) {
            MARK[v][i] = 1;
        }
    }
    TOUT[v] = timer++;
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        int u, v;
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            G[u - 1].pb(v - 1);
            G[v - 1].pb(u - 1);
        }
        return true;
    }
    return false;
}

inline bool is_bridge(int g1, int g2) {
    return bridges.find(mp(g1, g2)) != bridges.end();
}

inline bool is_child(int g1, int v) {
    return TIN[g1] <= TIN[v] && TOUT[g1] >= TOUT[v];
}

int get_parent(int v, int forbidden) {
    for(int i = 19; i >= 0; --i) {
        if(!is_child(UP[v][i], forbidden)) {
            v = UP[v][i];
        }
    }
    return v;
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        detect_bridges(0);
        timer = 1;
        FILL(TIN, 0);
        FILL(FUP, 0);
        FILL(TOUT, 0);
        detect_cut_points(0, -1);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < CH[i].size(); ++j) {
                int v = i, to = CH[i][j], mark = MARK[i][j];
                if(mark) {
                    S[v].insert(to);
                }
            }
        }
        int queries;
        scanf("%d", &queries);
        int type, a, b, c, g1, g2;
        for(int tid = 0; tid < queries; ++tid) {
            scanf("%d", &type);
            if(type == 1) {
                scanf("%d%d%d%d", &a, &b, &g1, &g2);
                --a, --b, --g1, --g2;
                if(is_child(g2, g1)) swap(g1, g2);
                if(!is_bridge(g1, g2)) {
                    printf("yes\n");
                }
                else {
                    if(is_child(g2, a) == is_child(g2, b)) {
                        printf("yes\n");
                    }
                    else {
                        printf("no\n");
                    }
                }
            }
            else {
                scanf("%d%d%d", &a, &b, &c);
                --a, --b, --c;
                if(TIN[a] > TIN[b]) {
                    swap(a, b);
                }
                if(CUT[c] == false || (!is_child(c, a) && !is_child(c, b))) {
                    printf("yes\n");
                }
                else if(!is_child(c, a)) {
                    int parent = get_parent(b, c);
                    if(parent != c && S[c].find(parent) == S[c].end()) {
                        printf("yes\n");
                    }
                    else {
                        printf("no\n");
                    }
                }
                else if(!is_child(c, b)) {
                    int parent = get_parent(a, c);
                    if(parent != c && S[c].find(parent) == S[c].end()) {
                        printf("yes\n");
                    }
                    else {
                        printf("no\n");
                    }
                }
                else {
                    int parent_a = get_parent(a, c);
                    int parent_b = get_parent(b, c);
                    if(parent_a == parent_b) {
                        if(parent_a == c) {
                            printf("no\n");
                        }
                        else {
                            printf("yes\n");
                        }
                    }
                    else {
                        if(S[c].find(parent_a) != S[c].end() || S[c].find(parent_b) != S[c].end()) {
                            printf("no\n");
                        }
                        else {
                            printf("yes\n");
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}
