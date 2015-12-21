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

const int maxT = 1 << 19;
const int maxN = 250 * 1000 + 7;

char S[maxN];
int n, m, T[maxT][10], ADD[maxT], H[10];

void cleanup() {
    FILL(T, 0);
    FILL(ADD, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        scanf("%s", S);
        return true;
    }
    return false;
}

void update(int v, int lc, int rc) {
    for(int i = 0; i <= 9; ++i) {
        T[v][i] = T[lc][i] + T[rc][i];
    }
}

void build_tree(int v, int tl, int tr) {
    if(tl == tr) {
        T[v][S[tl] - '0']++;
    }
    else {
        int tm = (tl + tr) / 2;
        build_tree(v << 1, tl, tm);
        build_tree((v << 1) | 1, tm + 1, tr);
        update(v, v << 1, (v << 1) | 1);
    }
}

void push(int v, int l = -1, int r = -1) {
    int delta = ADD[v]; ADD[v] = 0;
    if(delta == 0) return ;
    FILL(H, 0);
    for(int k = 0; k <= 9; ++k) {
        H[(k + delta) % 10] += T[v][k];
    }
    for(int k = 0; k <= 9; ++k) {
        T[v][k] = H[k];
    }
    if(l != -1) {
        ADD[l] += delta;
    }
    if(r != -1) {
        ADD[r] += delta;
    }
}

int query(int v, int tl, int tr, int l, int r) {
    if(l > r) {
        return 0;
    }
    if(tl == l && tr == r) {
        if(tl == tr) {
            push(v, -1, -1);
        }
        else {
            push(v, v << 1, (v << 1) | 1);
        }
        int ret = 0;
        for(int k = 0; k <= 9; ++k) {
            ret += T[v][k] * k;
        }
        return ret;
    }
    else {
        push(v, v << 1, (v << 1) | 1);
        int tm = (tl + tr) / 2;
        return query(v << 1, tl, tm, l, min(r, tm)) +
               query((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r);
    }
}

void update(int v, int tl, int tr, int l, int r, int delta) {
    if(l > r) return ;
    if(tl == l && tr == r) {
        ADD[v] += delta;
        if(tl == tr) {
            push(v, -1, -1);
        }
        else {
            push(v, v << 1, (v << 1) | 1);
        }
    }
    else {
        push(v, v << 1, (v << 1) | 1);
        int tm = (tl + tr) / 2;
        update(v << 1, tl, tm, l, min(r, tm), delta);
        update((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r, delta);
        if(ADD[v << 1]) {
            int ll = tl, rr = tm;
            if(ll == rr) {
                push(v << 1, -1, -1);
            }
            else {
                push(v << 1, (v << 1) << 1, ((v << 1) << 1) | 1);
            }
        }
        if(ADD[(v << 1) | 1]) {
            int ll = tm + 1, rr = tr;
            if(ll == rr) {
                push((v << 1) | 1, -1, -1);
            }
            else {
                push((v << 1) | 1, ((v << 1) | 1) << 1, (((v << 1) | 1) << 1) | 1);
            }
        }
        update(v, v << 1, (v << 1) | 1);
    }
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        int l, r;
        build_tree(1, 0, n - 1);
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &l, &r);
            printf("%d\n", query(1, 0, n - 1, l - 1, r - 1));
            update(1, 0, n - 1, l - 1, r - 1, 1);
        }
    }
    
    return 0;
}
