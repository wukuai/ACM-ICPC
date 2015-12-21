#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>
#include <sstream>
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


const int maxN = 1000 + 7;

char word[maxN];
int n, x, res[maxN], a[maxN], c[maxN];

void cleanup() {
   
}

bool Read() {
    cleanup();
    if(scanf("%d", &x) == 1) {
        scanf("%s", word);
        n = strlen(word);
        return true;
    }
    return false;
}

void mul(int l[], int r[]) {
    FILL(c, 0);
    for(int i = 0; i < n; ++i) {
        c[i] = r[l[i]];
    }
    for(int i = 0; i < n; ++i) {
        l[i] = c[i];
    }
}

void Run() {
    int it = 0, start = 0, finish = n - 1, cnt = n;
    while(cnt) {
        a[it++] = start++; cnt--;
        if(cnt == 0) break;
        a[it++] = finish--; cnt--;
    }
    for(int i = 0; i < n; ++i) {
        res[i] = i;
    }
    for(int i = 0; i < n; ++i) {
        c[a[i]] = i;
    }
    for(int i = 0; i < n; ++i) {
        a[i] = c[i];
    }
    while(x) {
        if(x & 1) {
            mul(res, a);
        }
        mul(a, a);
        x >>= 1;
    }
    for(int i = 0; i < n; ++i) {
        printf("%c", word[res[i]]);
    }
    printf("\n");
}


int main() {
    Read();
    Run();

    return 0;
}
