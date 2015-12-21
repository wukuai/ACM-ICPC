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

int n, e;
int listen[maxN][maxN];

void cleanup() {
    memset(listen, 0, sizeof(listen));
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &e) == 2) {
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
        int new_song_id = 1;
        for(int i = 0; i < e; ++i) {
            int k;
            scanf("%d", &k);
            vector<int> v(k);
            bool is_here = false;
            for(int j = 0; j < k; ++j) {
                scanf("%d", &v[j]);
                if(v[j] == 1) {
                    is_here = true;
                }
            }
            if(is_here) {
                for(int j = 0; j < k; ++j) {
                    listen[v[j]][new_song_id] = 1;
                    eprintf("villager=%d knows=%d\n", v[j], new_song_id);
                }
                new_song_id++;
            }
            else {
                set<int> everything;
                for(int j = 0; j < k; ++j) {
                    eprintf("%d knows : ", v[j]);
                    for(int s = 1; s <= new_song_id; ++s) {
                        if(listen[v[j]][s]) {
                            eprintf("%d ", s);
                            everything.insert(s);
                        }
                    }
                    eprintf("\n");
                }
                for(int j = 0; j < k; ++j) {
                    for(set<int>::const_iterator it = everything.begin(); it != everything.end(); ++it) {
                        listen[v[j]][*it] = 1;
                    }
                }
            }
        }
        vector<int> answer;
        answer.pb(1);
        for(int i = 2; i <= n; ++i) {
            bool ok = true;
            for(int j = 1; j < new_song_id; ++j) {
                if(listen[i][j] == 0) {
                    ok = false;
                }
            }
            if(ok) {
                answer.pb(i);
            }
        }
        for(int i = 0; i < answer.size(); ++i) {
            printf("%d\n", answer[i]);
        }
    }
    return 0;
}

















