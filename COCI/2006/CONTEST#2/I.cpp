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

const int maxT = 1 << 19;
const int maxN = 200 * 1000 + 7;

struct Student {
    int a;
    int b;
    int real_index;
    int sorted_index;
} S[maxN];

struct Event {
    char type;
    int position;
} E[maxN];

int T[maxT], q, n;

void cleanup() {
    n = 0;
    memset(S, 0, sizeof(S));
    memset(E, 0, sizeof(E));
    memset(T, -1, sizeof(T));
}

bool cmp(const Student& lhs, const Student& rhs) {
    if(lhs.b != rhs.b) {
        return lhs.b < rhs.b;
    }
    return lhs.a < rhs.a;
}

bool revert_cmp(const Student& lhs, const Student& rhs) {
    return lhs.real_index < rhs.real_index;
}

bool Read() {
    cleanup();
    if(scanf("%d", &q) == 1) {
        for(int i = 0; i < q; ++i) {
            scanf(" %c", &E[i].type);
            if(E[i].type == 'D') {
                scanf("%d%d", &S[n].a, &S[n].b);
                S[n].real_index = n;
                E[i].position = n++;
            }
            else {
                scanf("%d", &E[i].position);
                E[i].position--;
            }
        }
        return true;
    }
    return false;
}

int merge(int left_node, int right_node) {
    if(left_node == -1) return right_node;
    if(right_node == -1) return left_node;
    if(S[left_node].a >= S[right_node].a) {
        return left_node;
    }
    return right_node;
}

void update(int v, int tl, int tr, int pos) {
    if(tl == tr) {
        T[v] = pos;
    }
    else {
        int tm = (tl + tr) / 2;
        if(S[pos].sorted_index <= tm) {
            update(v << 1, tl, tm, pos);
        }
        else {
            update((v << 1) | 1, tm + 1, tr, pos);
        }
        T[v] = merge(T[v << 1], T[(v << 1) | 1]);
    }
}

int query(int v, int tl, int tr, int l, int r, int val) {
    if(l > r) {
        return -1;
    }
    if(tl == l && tr == r) {
        if(tl == tr) {
            if(T[v] == -1) {
                return -1;
            }
            if(S[T[v]].a < val) {
                return -1;
            }
            return T[v];
        }
        else {
            int tm = (tl + tr) / 2;
            if(T[v << 1] != -1 && S[T[v << 1]].a >= val) {
                return query(v << 1, tl, tm, l, min(tm, r), val);
            }
            else {
                return query((v << 1) | 1, tm + 1, tr, max(l, tm + 1), tr, val);
            }
        }
    }
    else {
        int tm = (tl + tr) / 2;
        int k1 = query(v << 1, tl, tm, l, min(tm, r), val);
        if(k1 != -1) {
            return k1;
        }
        return query((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r, val);
    }
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        sort(S, S + n, cmp);
        for(int i = 0; i < n; ++i) {
            S[i].sorted_index = i;
        }
        sort(S, S + n, revert_cmp);
        for(int i = 0; i < q; ++i) {
            if(E[i].type == 'D') {
                update(1, 0, n - 1, E[i].position);
            }
            else {
                int k = query(1, 0, n - 1, S[E[i].position].sorted_index + 1, n - 1, S[E[i].position].a);
                if(k == -1) {
                    printf("NE\n");
                }
                else {
                    printf("%d\n", k + 1);
                }
            }
        }
    }
    
    return 0;
}
