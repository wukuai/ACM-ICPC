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

const int maxN = 55;

int n, m;
char grid[maxN][maxN];
int f[maxN][maxN], d[maxN][maxN];

void cleanup() {
    memset(f, -1, sizeof(f));
    memset(d, -1, sizeof(d));
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%s", grid[i]);
        }
        return true;
    }
    return false;
}

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        queue< pair<int, int> > q;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(grid[i][j] == '*') {
                    f[i][j] = 0;
                    q.push(mp(i, j));
                }
            }
        }
        while(!q.empty()) {
            pair<int, int> curr = q.front(); 
            q.pop();
            for(int k = 0; k < 4; ++k) {
                int n_x = curr.first + dx[k];
                int n_y = curr.second + dy[k];
                if(valid(n_x, n_y) && grid[n_x][n_y] != 'D' && grid[n_x][n_y] != 'X' && f[n_x][n_y] == -1) {
                    f[n_x][n_y] = f[curr.first][curr.second] + 1;
                    q.push(mp(n_x, n_y));
                }
            }
        }
        int finX = -1, finY = -1;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(f[i][j] == -1) {
                    f[i][j] = IINF;
                }
                if(grid[i][j] == 'D') {
                    finX = i, finY = j;
                }
                if(grid[i][j] == 'S') {
                    q.push(mp(i, j));
                    d[i][j] = 0;
                }
            }
        }
        while(!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            for(int k = 0; k < 4; ++k) {
                int n_x = curr.first + dx[k];
                int n_y = curr.second + dy[k];
                if(valid(n_x, n_y) && grid[n_x][n_y] != 'X' && f[n_x][n_y] > d[curr.first][curr.second] + 1 && d[n_x][n_y] == -1) {
                    d[n_x][n_y] = d[curr.first][curr.second] + 1;
                    q.push(mp(n_x, n_y));
                }
            }
        }
        if(d[finX][finY] == -1) {
            printf("KAKTUS\n");
        }
        else {
            printf("%d\n", d[finX][finY]);
        }
    }
    
    return 0;
}
