#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

//--------------------------------------------
#define SZ(x) ((int)x.size())
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define ALL(X) X.begin(), X.end()
#define SRT(x) sort(ALL(x))
#define RVRS(x) reverse(ALL(x))
#define FILL(x, value) memset(x, value, sizeof(x))

#define next next1
#define hash hash1
#define rank rank1

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

template <class T> inline void check_max(T& actual, T check) {
    if(actual < check) {
        actual = check;
    }
}

template <class T> inline void check_min(T& actual, T check) {
    if(actual > check) {
        actual = check;
    }
}   

const double EPS = 1e-9;
const int IINF = 1000000000;
const double PI = acos(-1.0);
const long long LINF = 6000000000000000000LL;
//--------------------------------------------

int n, m;
long long F[1 << 20], D[1 << 20], MOD = 1000 * 1000 * 1000 + 7;

int main() {
    int k, x;
    scanf("%d%d", &n, &m);
    D[0] = 1;
    for(int i = 0; i < n; ++i) {
        scanf("%d", &k);
        int mask = 0;
        for(int j = 0; j < k; ++j) {
            scanf("%d", &x);
            mask |= 1 << (x - 1);
        }
        D[mask]++;
    }
    for(int mask = 0; mask < (1 << m); ++mask) {
        for(int s = mask; s; s = (s - 1) & mask) {
            D[mask] = (D[mask] + D[s] * D[mask ^ s]) % MOD;
        }
    }
    printf(LLD"\n", D[(1 << m) - 1]);

    return 0;
}
