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

int n, m, t;
string s1, s2;
void cleanup() {

}

bool Read() {
    cleanup();
    if(cin >> n >> m) {
        cin >> s1 >> s2 >> t;
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
        vector<int> id(255, -1);
        for(int i = 0; i < s1.size(); ++i) {
            id[s1[i]] = 1;
        }
        for(int i = 0; i < s2.size(); ++i) {
            id[s2[i]] = 2;
        }
        reverse(ALL(s1));
        string s = s1 + s2;
        eprintf("initial=%s\n", s.c_str());
        while(t--) {
            eprintf("T=%d\n", t);
            for(int i = 0; i < s.size(); ) {
                if(i + 1 < s.size()) {
                    if(id[s[i]] == 1 && id[s[i + 1]] == 2) {
                        eprintf("swapping (%c, %c)\n", s[i], s[i + 1]);
                        swap(s[i], s[i + 1]);
                        i += 2;
                    }
                    else {
                        ++i;
                    }
                }
                else {
                    ++i;
                }
            }
            eprintf("s=%s\n", s.c_str());
        }
        printf("%s\n", s.c_str());
        eprintf("#####\n");
    }
    return 0;
}
