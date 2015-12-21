#include<bits/stdc++.h>

using namespace std;

namespace old {

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

template<class Type> inline void check_max(Type& actual, const Type& check) {
    if(actual < check) {
        actual = check;
    }
}

//--------------------------------------------

const int maxN = 222;

int n;
char str[maxN];
bool got_greater[maxN][maxN];
long long MOD = 100000, dp[maxN][maxN];

bool Read() {
    if(scanf("%d", &n) == 1) {
        scanf("%s", str);
        return true;
    }
    return false;
}

int solve(bool& got_g) {
    got_g = false;
    FILL(dp, 0);
    FILL(got_greater, false);
    for(int i = 0; i + 1 < n; ++i) {
        dp[i + 1][i] = 1;
        if(str[i] == '?' && str[i + 1] == '?') {
            dp[i][i + 1] = 3;
        }
        else if(str[i] == '?') {
            if(str[i + 1] == ')' || str[i + 1] == ']' || str[i + 1] == '}') {
                dp[i][i + 1] = 1;
            }
        }
        else if(str[i + 1] == '?') {
            if(str[i] == '(' || str[i] == '[' || str[i] == '{') {
                dp[i][i + 1] = 1;
            }
        }
        else {
            if(str[i] == '(' && str[i + 1] == ')') {
                dp[i][i + 1] = 1;
            }
            else if(str[i] == '[' && str[i + 1] == ']') {
                dp[i][i + 1] = 1;
            }
            else if(str[i] == '{' && str[i + 1] == '}') {
                dp[i][i + 1] = 1;
            }
        }
    }
    for(int len = 4; len <= n; len += 2) {
        for(int i = 0; i + len <= n; ++i) {
            int st = i, fn = i + len - 1;
            if(str[st] == ')' || str[st] == ']' || str[st] == '}') {
                continue;
            }
            if(str[fn] == '(' || str[fn] == '[' || str[fn] == '{') {
                continue;
            }
            if(str[st] == '?') {
                if(str[fn] == '?') {
                    dp[st][fn] += dp[st + 1][fn - 1] * 3;
                    check_max(got_greater[st][fn], got_greater[st + 1][fn - 1]);
                }
                else {
                    dp[st][fn] += dp[st + 1][fn - 1];
                    check_max(got_greater[st][fn], got_greater[st + 1][fn - 1]);
                }
            }
            else if(str[fn] == '?') {
                if(str[st] == '(') {
                    dp[st][fn] = dp[st + 1][fn - 1];
                    check_max(got_greater[st][fn], got_greater[st + 1][fn - 1]);
                }
                else if(str[st] == '[') {
                    dp[st][fn] = dp[st + 1][fn - 1];
                    check_max(got_greater[st][fn], got_greater[st + 1][fn - 1]);
                }
                else if(str[st] == '{') {
                    dp[st][fn] = dp[st + 1][fn - 1];
                    check_max(got_greater[st][fn], got_greater[st + 1][fn - 1]);
                }
            }
            else {
                if(str[st] == '(' || str[fn] == ')') {
                    dp[st][fn] = dp[st + 1][fn - 1];
                    check_max(got_greater[st][fn], got_greater[st + 1][fn - 1]);
                }
                else if(str[st] == '[' || str[fn] == ']') {
                    dp[st][fn] = dp[st + 1][fn - 1];
                    check_max(got_greater[st][fn], got_greater[st + 1][fn - 1]);
                }
                else if(str[st] == '{' || str[fn] == '}') {
                    dp[st][fn] = dp[st + 1][fn - 1];
                    check_max(got_greater[st][fn], got_greater[st + 1][fn - 1]);
                }
            }
            for(int k = st + 1; k <= fn - 1; ++k) {
                int length = k - st + 1;
                if(length & 1) continue;
                if(str[st] == '?' && str[k] == '?') {
                    dp[st][fn] += 3 * dp[st + 1][k - 1] * dp[k + 1][fn];
                    if(dp[st + 1][k - 1] || got_greater[st + 1][k - 1]) {
                        if(dp[k + 1][fn] || got_greater[st + 1][k - 1]) {
                            check_max(got_greater[st][fn], got_greater[st + 1][k - 1]);
                            check_max(got_greater[st][fn], got_greater[k + 1][fn]);
                        }
                    }
                }
                else if(str[st] == '?' && (str[k] == ')' || str[k] == ']' || str[k] == '}')) {
                    dp[st][fn] += dp[st + 1][k - 1] * dp[k + 1][fn];
                    if(dp[st + 1][k - 1] || got_greater[st + 1][k - 1]) {
                        if(dp[k + 1][fn] || got_greater[st + 1][k - 1]) {
                            check_max(got_greater[st][fn], got_greater[st + 1][k - 1]);
                            check_max(got_greater[st][fn], got_greater[k + 1][fn]);
                        }
                    }
                }
                else if(str[k] == '?') {
                    if(str[st] == '(') {
                        dp[st][fn] += dp[st + 1][k - 1] * dp[k + 1][fn];
                        if(dp[st + 1][k - 1] || got_greater[st + 1][k - 1]) {
                            if(dp[k + 1][fn] || got_greater[st + 1][k - 1]) {
                                check_max(got_greater[st][fn], got_greater[st + 1][k - 1]);
                                check_max(got_greater[st][fn], got_greater[k + 1][fn]);
                            }
                        }
                    }
                    else if(str[st] == '[') {
                        dp[st][fn] += dp[st + 1][k - 1] * dp[k + 1][fn];
                        if(dp[st + 1][k - 1] || got_greater[st + 1][k - 1]) {
                            if(dp[k + 1][fn] || got_greater[st + 1][k - 1]) {
                                check_max(got_greater[st][fn], got_greater[st + 1][k - 1]);
                                check_max(got_greater[st][fn], got_greater[k + 1][fn]);
                            }
                        }
                    }
                    else if(str[st] == '{') {
                        dp[st][fn] += dp[st + 1][k - 1] * dp[k + 1][fn];
                        if(dp[st + 1][k - 1] || got_greater[st + 1][k - 1]) {
                            if(dp[k + 1][fn] || got_greater[st + 1][k - 1]) {
                                check_max(got_greater[st][fn], got_greater[st + 1][k - 1]);
                                check_max(got_greater[st][fn], got_greater[k + 1][fn]);
                            }
                        }
                    }
                }
                else if(str[st] == '(' && str[k] == ')') {
                    dp[st][fn] += dp[st + 1][k - 1] * dp[k + 1][fn];
                    if(dp[st + 1][k - 1] || got_greater[st + 1][k - 1]) {
                        if(dp[k + 1][fn] || got_greater[st + 1][k - 1]) {
                            check_max(got_greater[st][fn], got_greater[st + 1][k - 1]);
                            check_max(got_greater[st][fn], got_greater[k + 1][fn]);
                        }
                    }
                }
                else if(str[st] == '[' && str[k] == ']') {
                    dp[st][fn] += dp[st + 1][k - 1] * dp[k + 1][fn];
                    if(dp[st + 1][k - 1] || got_greater[st + 1][k - 1]) {
                        if(dp[k + 1][fn] || got_greater[st + 1][k - 1]) {
                            check_max(got_greater[st][fn], got_greater[st + 1][k - 1]);
                            check_max(got_greater[st][fn], got_greater[k + 1][fn]);
                        }
                    }
                }
                else if(str[st] == '{' && str[k] == '}') {
                    dp[st][fn] += dp[st + 1][k - 1] * dp[k + 1][fn];
                    if(dp[st + 1][k - 1] || got_greater[st + 1][k - 1]) {
                        if(dp[k + 1][fn] || got_greater[st + 1][k - 1]) {
                            check_max(got_greater[st][fn], got_greater[st + 1][k - 1]);
                            check_max(got_greater[st][fn], got_greater[k + 1][fn]);
                        }
                    }
                }
            }
            if(dp[st][fn] >= MOD) {
                dp[st][fn] %= MOD;
                got_greater[st][fn] = true;
            }
        }
    }
    got_g = got_greater[0][n - 1];
eprintf("dp : \n");
for(int len = 2; len <= n; len += 2) {
for(int i = 0; i + len <= n; ++i) {
eprintf("dp(%d,%d)=%lld ", i, i + len - 1, dp[i][i + len - 1]);
}
eprintf("\n");
}
    return dp[0][n - 1];
}

int main2() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        if(str[0] == '?') {
            int ans = 0;
            bool tp1 = false, tp2 = false, tp3 = false;
            str[0] = '{', ans += solve(tp1);
            str[0] = '(', ans += solve(tp2);
            str[0] = '[', ans += solve(tp3); ans %= MOD;
            bool tp = max(max(tp1, tp2), tp3);
            if(tp) {
                printf("%.5d\n", ans);
            }
            else {
                printf("%d\n", ans);
            }
        }
        else {
            bool tp = false;
            int ans = solve(tp);
            if(tp) {
                printf("%.5d\n", ans);
            }
            else {
                printf("%d\n", ans);
            }
        }
    }
    
    return 0;
}

} // old

#define MAX 200
#define MOD 100000

int n;
char s[MAX+1];

typedef long long llint;

char *otvorena  = "([{";
char *zatvorena = ")]}";

llint mod( llint a ) {
   if( a >= MOD ) return MOD + a%MOD;
   return a;
}

llint memo[MAX][MAX];

llint rec( int lo, int hi ) {
   if( lo > hi ) return 1;
   
   llint &ret = memo[lo][hi];
   if( ret >= 0 ) return ret;

   ret = 0;
   for( int mid = lo+1; mid <= hi; mid += 2 )
      for( int tip = 0; tip < 3; ++tip ) 
         if( s[lo] == otvorena[tip] || s[lo] == '?' )
            if( s[mid] == zatvorena[tip] || s[mid] == '?' )
               ret = mod( ret + rec(lo+1,mid-1) * rec(mid+1,hi) );

   return ret;
}

int main( void ) {
   scanf( "%d", &n );
   scanf( "%s", s );

   memset( memo, -1, sizeof memo );
   llint ret = rec( 0, n-1 );

   if( ret < MOD ) printf( "%lld\n", ret );
   else printf( "%05lld\n", ret-MOD );

   return 0;
}
