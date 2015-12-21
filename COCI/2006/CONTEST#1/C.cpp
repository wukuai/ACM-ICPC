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

string s;
char ch[500][500];

void cleanup() {

}

bool Read() {
    cleanup();
    if(cin >> s) {
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
        int col = 5;
        ch[0][0] = '.', ch[0][1] = '.', ch[0][2] = '#', ch[0][3] = '.', ch[0][4] = '.';
        ch[1][0] = '.', ch[1][1] = '#', ch[1][2] = '.', ch[1][3] = '#', ch[1][4] = '.';
        ch[2][0] = '#', ch[2][1] = '.', ch[2][2] = s[0], ch[2][3] = '.', ch[2][4] = '#';
        ch[3][0] = '.', ch[3][1] = '#', ch[3][2] = '.', ch[3][3] = '#', ch[3][4] = '.';
        ch[4][0] = '.', ch[4][1] = '.', ch[4][2] = '#', ch[4][3] = '.', ch[4][4] = '.';
        for(int i = 1; i < s.size(); ++i, col += 4) {
            char chr = '#';
            if(i % 3 == 2) {
                chr = '*';
                ch[2][col - 1] = chr;
            }
            ch[0][col] = '.', ch[0][col + 1] = chr, ch[0][col + 2] = '.', ch[0][col + 3] = '.';
            ch[1][col] = chr, ch[1][col + 1] = '.', ch[1][col + 2] = chr, ch[1][col + 3] = '.';
            ch[2][col] = '.', ch[2][col + 1] = s[i], ch[2][col + 2] = '.', ch[2][col + 3] = chr;
            ch[3][col] = chr, ch[3][col + 1] = '.', ch[3][col + 2] = chr, ch[3][col + 3] = '.';
            ch[4][col] = '.', ch[4][col + 1] = chr, ch[4][col + 2] = '.', ch[4][col + 3] = '.';
        }
        for(int i = 0; i < 5; ++i) {
            for(int j = 0; j < col; ++j) {
                putchar(ch[i][j]);
            }
            putchar('\n');
        }
    }
    
    return 0;
}
