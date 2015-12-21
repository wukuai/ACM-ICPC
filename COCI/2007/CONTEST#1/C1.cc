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

const double EPS = 1e-6 - 1e-7;
const int IINF = 1000000000;
const double PI = acos(-1.0);
const long long LINF = 6000000000000000000LL;
//--------------------------------------------

const int maxN = 1555;

double dg[maxN];
int x[maxN], y[maxN];

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", x + i, y + i);
    }
    long long answer = 0;
    for(int i = 0; i < n; ++i) {
        int c = 0;
        int shiftX = x[i], shiftY = y[i];
        for(int j = 0; j < n; ++j) {
            if(i != j) {
                int X = x[j] - shiftX;
                int Y = y[j] - shiftY;
                double tmp = atan2(Y, X);
                if(tmp < 0)
                    tmp += 2 * PI;
                dg[c] = tmp * 180.0 / PI; 
                if(fabs(dg[c]) < EPS)  { ++c, dg[c] = 360.0;}
                ++c;
            }
        }
        sort(dg, dg + c);
        int ptr1 = 0, ptr2 = 1;
        while(ptr1 < c && ptr2 < c) {
            if(fabs(dg[ptr2] - dg[ptr1] - 90.0) < EPS) {
                int t = 0;
                while(ptr2 < c && fabs(dg[ptr2] - dg[ptr1] - 90.0) < EPS) {
                    ++t;
                    ptr2++;
                }
                double v = dg[ptr1];
                while(ptr1 < c && fabs(v - dg[ptr1]) < EPS) {
                    answer += t;
                    ++ptr1;
                }
            }
            else {
                if(dg[ptr2] - dg[ptr1] > 90.0 + EPS) {
                    ptr1++;
                }
                else {
                    ptr2++;
                }
            }
        }
    }
    printf("%lld\n", answer);
    return 0;
}
