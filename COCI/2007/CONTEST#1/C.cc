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

const int maxN = 1555;

long long x[maxN], y[maxN];
map< pair<long long, long long>, int > cnt[maxN];

long long gcd(long long a, long long b) {
    return a == 0 ? b : gcd(b % a, a);
}

void equation(int i, int j, long long& A, long long& B, long long& C) {
    long long X1 = x[i], Y1 = y[i];
    long long X2 = x[j], Y2 = y[j];
    A = Y2 - Y1, B = X1 - X2, C = Y1 * (X2 - X1) - X1 * (Y2 - Y1);
    if(A < 0) {
        A *= -1, B *= -1, C *= -1;
    }
    long long D = gcd(A, B);
    D = gcd(D, C);
    if(abs(D) != 0)
        A /= D, B /= D, C /= D;
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%lld%lld", x + i, y + i);
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(i != j) {
                long long A, B, C;
                equation(i, j, A, B, C);
                cnt[i][mp(A, B)]++;
            }
        }
    }
  
    long long answer = 0;
 
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(i != j) {
                long long A, B, C;
                equation(i, j, A, B, C);
                long long dx = x[i] +  A;
                long long dy = y[i] +  B;
                x[1511] = dx, y[1511] = dy;
                equation(i, 1511, A, B, C);
                answer += cnt[i][mp(A, B)];
            }
        }
    }
    printf("%lld\n", answer / 2);
    return 0;
}
