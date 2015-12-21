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

const int maxM = 100 * 1000 + 7;
const int maxN = 3 * 100 * 1000 + 7;

int n, k, DP[maxN], MAXX[maxM], MAXY[maxM], IND[maxN], X[maxN], Y[maxN], C[maxN];

void cleanup() {
    FILL(X, 0);
    FILL(Y, 0);
    FILL(C, 0);
    FILL(DP, 0);
    FILL(IND, 0);
    FILL(MAXX, 0);
    FILL(MAXY, 0);
}

bool cmp(const int& lhs, const int& rhs) {
    if(X[lhs] != X[rhs]) {
        return X[lhs] < X[rhs];
    }
    return Y[lhs] < Y[rhs];
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &k) == 2) {
        for(int i = 1; i <= n; ++i) {
            scanf("%d%d%d", X + i, Y + i, C + i);
            IND[i] = i;
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
        sort(IND + 1, IND + n + 1, cmp);

        DP[0] = -IINF;
        int answer = -1;
        for(int i = 0; i < n; ++i) {
            int ind = IND[i + 1];
            if(ind == 1) {
                DP[ind] = C[ind];
            }
            if(ind == n) {
                answer = ind;
            }
            int x = MAXX[X[ind]];
            int y = MAXY[Y[ind]];
            if(DP[x] >= k && DP[x] - k + C[ind] > DP[ind]) {
                DP[ind] = DP[x] - k + C[ind];
            }
            if(DP[y] >= k && DP[y] - k + C[ind] > DP[ind]) {
                DP[ind] = DP[y] - k + C[ind];
            }
            if(DP[MAXX[X[ind]]] < DP[ind]) {
                MAXX[X[ind]] = ind;
            }
            if(DP[MAXY[Y[ind]]] < DP[ind]) {
                MAXY[Y[ind]] = ind;
            }
        }
        eprintf("DP : ");
        for(int i = 0; i <= n; ++i) {
            eprintf("F[%d,%d]=%d ", X[IND[i]], Y[IND[i]], DP[i]);
        }
        eprintf("\n####################\n");
        printf("%d\n", DP[answer]);
    }
    return 0;
}
