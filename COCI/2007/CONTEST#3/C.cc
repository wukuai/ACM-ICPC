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

const int maxN = 1000 * 1000 + 7;

long long DP[maxN];
int n, A[maxN], B[maxN];

void cleanup() {
    FILL(A, 0);
    FILL(B, 0);
    FILL(DP, 63);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", A + i, B + i);
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
        sort(A, A + n);
        sort(B, B + n);
        DP[0] = 0;
        for(int i = 1; i <= n; ++i) {
            for(int k = 0; k <= 2 && i - k - 1 >= 0; ++k) {
                vector<int> ind;
                vector<int> v1, v2;
                for(int j = 0; j <= k; ++j) {
                    ind.pb(j);
                    v1.pb(A[i - j - 1]);
                    v2.pb(B[i - j - 1]);
                }
                do {
                    int s = 0;
                    bool good = true;
                    for(int j = 0; j <= k; ++j) {
                        if(v1[ind[j]] == v2[j]) {
                            good = false; break;
                        }
                        s += abs(v1[ind[j]] - v2[j]);
                    }
                    if(good) {
                        DP[i] = min(DP[i], DP[i - k - 1] + s);
                    }
                }while(next_permutation(ALL(ind)));
            }
        }
        printf(LLD"\n", DP[n]);
    }
    return 0;
}
