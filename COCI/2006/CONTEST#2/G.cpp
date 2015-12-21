#include<bits/stdc++.h>

using namespace std;

struct Node {
    int value;
    Node* next;
    Node* prev;
    Node() : value(0), next(NULL), prev(NULL) {}
    Node(int v) : value(v), next(NULL), prev(NULL) {}
};

// Template
#define mp(a, b) make_pair(a, b)
#define pb(x) push_back(x)
#define ALL(X) X.begin(), X.end()
#define SORT(x) sort(ALL(x))
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

const int maxN = 500000 + 7;

int fw[maxN];
int dp[maxN];
Node pointers[maxN];

void update(int i, int delta) {
    for( ; i < maxN; i = (i | ( i + 1))) {
        fw[i] = max(fw[i], delta);
    }
}

int get_max(int i) {
    int ret = 0;
    for( ; i >= 0; i = (i & (i + 1)) - 1) {
        ret = max(ret, fw[i]);
    }
    return ret;
}

void erase(int val) {
    pointers[val].prev->next = pointers[val].next;
    pointers[val].next->prev = pointers[val].prev;
    pointers[val].next = pointers[val].prev = NULL;
}

void insert1(int x, int y) {
    pointers[x].next = &pointers[y];
    pointers[x].prev = pointers[y].prev;
    pointers[y].prev->next = &pointers[x];
    pointers[y].prev = &pointers[x];
}

void insert2(int x, int y) {
    pointers[x].next = pointers[y].next;
    pointers[y].next->prev = &pointers[x];
    pointers[y].next = &pointers[x];
    pointers[x].prev = &pointers[y];
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);
    pointers[0].value = 0;
    pointers[0].next = &pointers[1];

    pointers[n + 1].value = n + 1;
    pointers[n + 1].prev = &pointers[n];

    for(int i = 1; i <= n; ++i) {
        pointers[i].value = i;
        pointers[i].prev = &pointers[i - 1];
        pointers[i].next = &pointers[i + 1];
    }
    int x, y;
    char command;
    for(int i = 0; i < m; ++i) {
        scanf(" %c%d%d", &command, &x, &y);
        if(command == 'A') {
            erase(x);
            insert1(x, y);
        }
        else {
            erase(x);
            insert2(x, y);
        }
    }
    int curr = 0;
    vector<int> v;
    while(pointers[curr].next != NULL) {
        if(pointers[curr].value != 0) {
            v.pb(pointers[curr].value);
        }
        curr = pointers[curr].next->value;
    }
    eprintf("sequence : ");
    for(int i = 0; i < v.size(); ++i) {
        eprintf("%d ", v[i]);
    }
    eprintf("\n");
    dp[v[0]] = 1;
    update(v[0], 1);
    int answer = 1;
    for(int i = 1; i < v.size(); ++i) {
        dp[i] = 1;
        dp[i] = max(dp[i], 1 + get_max(v[i] - 1));
        update(v[i], dp[i]);
        answer = max(answer, dp[i]);
    }
    printf("%d\n", n - answer);
    return 0;
}
