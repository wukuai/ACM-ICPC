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

struct Node {
    int key;
    int hash;
    int next;
};

const int maxN = 200 * 1000 + 7;

char str[maxN];
Node nodes[maxN];
int p = 31, MOD = 200003, hash_table_begin[200003], hash_table_end[200003], n, c;

bool check(int len) {
    while(c > 0) {
        hash_table_end[nodes[c].hash] = -1;
        hash_table_begin[nodes[--c].hash] = -1;
    }
    int hash = 0, pw = 1;
    for(int i = 0; i < len; ++i) {
        hash = (hash * p + str[i] - 'a' + 1) % MOD;
        if(i) {
            pw = (pw * p) % MOD;
        }
    }
    pw = MOD - pw;
    nodes[c].key = 0;
    nodes[c].hash = hash;
    nodes[c].next = -1;
    hash_table_begin[hash] = c, hash_table_end[hash] = c++;
    for(int rem = 0, add = len; add < n; ++add, ++rem) {
        hash = ((hash + pw * (str[rem] - 'a' + 1)) * p + str[add] - 'a' + 1) % MOD;
        for(int curr = hash_table_begin[hash]; curr != -1; curr = nodes[curr].next) {
            int st = nodes[curr].key, ok = 1;
            for(int j = st, i = rem + 1; j <= st + len - 1; ++j, ++i) {
                if(str[j] != str[i]) {
                    ok = 0;
                    break;
                }
            }
            if(ok) {
                return true;
            }
        }
        if(hash_table_begin[hash] == -1) {
            nodes[c].key = rem + 1;
            nodes[c].hash = hash;
            nodes[c].next = -1;
            hash_table_begin[hash] = c, hash_table_end[hash] = c++;
        }
        else {
            nodes[c].key = rem + 1;
            nodes[c].hash = hash;
            nodes[c].next = -1;
            nodes[hash_table_end[hash]].next = c++;
        }
    }
    return false;
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    c = 0;
    scanf("%d%s", &n, str);
    int lo = 1, hi = n - 1, ans = 0;
    memset(hash_table_end, -1, sizeof(hash_table_end));
    memset(hash_table_begin, -1, sizeof(hash_table_begin));
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        if(check(mid)) {
            ans = mid;
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
