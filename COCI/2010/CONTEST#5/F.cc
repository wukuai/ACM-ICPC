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

namespace Solution {

const int maxL = 17;
const int maxA = 37;
const int maxN = 117;

int n, L[maxN], COLOR[maxA], DEG[maxA], G[maxA][maxA], cycle = false;
char C[maxN][maxL];

void cleanup() {
    FILL(DEG, 0);
    FILL(G, 0);
    FILL(COLOR, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%s", C[i]);
            L[i] = strlen(C[i]);
        }
        return true;
    }
    return false;
}

void construct_graph(int l, int r, int pos) {
    if(l > r) return ;
    if(L[l] == pos) { 
        construct_graph(l + 1, r, pos);
        return ;
    }
    vector<char> ordering;
    char ch = '#';
    for(int i = l; i <= r; ++i) {
        if(C[i][pos] != ch) {
            ordering.pb(ch = C[i][pos]);
        }
    }
    for(int i = 0; i < SZ(ordering); ++i) {
        for(int j = i + 1; j < SZ(ordering); ++j) {
            G[ordering[i] - 'a'][ordering[j] - 'a'] = 1;
            eprintf("edge(%c,%c)\n", ordering[i], ordering[j]);
        }
    }
    for(int i = l; i <= r; ) {
        char ch1 = C[i][pos];
        int st = i, fn = i;
        while(fn <= r && ch1 == C[fn][pos]) {
            ++fn;
        }
        construct_graph(st, fn - 1, pos + 1);
        i = fn;
    }
}

void dfs(int v) {
    if(cycle) return ;
    COLOR[v] = 1;
    for(int to = 0; to <= 33; ++to) {
        if(G[v][to] == 0) continue;
        if(COLOR[to] == 1) {
            cycle = true;
        }
        else if(COLOR[to] == 0) {
            dfs(to);
        }
    }
    COLOR[v] = 2;
}

void Run() {
    bool ok = true;
    for(int i = 0; i + 1 < n && ok; ++i) {
        if(L[i] > L[i + 1]) {
            int cnt = 0;
            for(int j = 0; j < L[i + 1] && ok; ++j) {
                if(C[i + 1][j] != C[i][j]) break;
                ++cnt;
            }
            if(cnt == L[i + 1]) {
                ok = false; break;
            }
        }
    }
    if(!ok) {
        printf("!\n");
        eprintf("fullfilled greater\n");
        return ;
    }
    construct_graph(0, n - 1, 0);
    for(int i = 0; i < maxA; ++i) {
        for(int j = 0; j < maxA; ++j) {
            if(G[i][j]) ++DEG[j];
        }
    }
    set<char> ch;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < L[i]; ++j) {
            ch.insert(C[i][j]);
        }
    }
    vector<int> v;
    for(char symbol : ch) {
        v.pb(symbol - 'a');
    }
    cycle = false;
    for(int i = 0; i < SZ(v) && !cycle; ++i) {
        if(COLOR[v[i]] == 0) {
            dfs(v[i]);
        }
    }
    if(cycle) {
        printf("!\n");
        eprintf("cycle exists\n");
        return ;
    }
    queue<int> q;
    string answer = "";
    for(int i = 0; i < SZ(v); ++i) {
        if(DEG[v[i]] == 0) {
            q.push(v[i]);
        }
    }
    ok = true;
    while(!q.empty() && ok) {
        int u = q.front();
        q.pop();
        if(!q.empty() && DEG[q.front()] == 0) {
            ok = false; break;
        }
        answer += string(1, u + 'a');
        for(int to = 0; to <= 33; ++to) {
            if(G[u][to] == 0) continue;
            DEG[to]--;
            if(DEG[to] == 0) {
                q.push(to);
            }
        }
    }
    if(!ok) {
        printf("?\n");
        eprintf("multiple\n");
        return ;
    }
    printf("%s\n", answer.c_str());
}

} // Solution

namespace StressTest {

long long GetTime() {
#ifdef __GNUC__ 
    long long res; 
    asm volatile ("rdtsc" : "=A" (res)); 
    return res;
#else
    int low, hi; 
    __asm { 
        rdtsc
        mov low, eax
        mov hi, edx
    }
    return (((long long)hi) << 32LL) | low;
#endif
}

void GenerateInput() {
    FILE* output = fopen("input.txt", "w");
    srand(GetTime());

    fclose(output);
}

void BruteForce() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("brute.out", "w");

    fclose(input);
    fclose(output);
}

} // StressTest

int main() {
#ifdef _DEBUG_
    int test_id = 0;
//    StressTest::GenerateInput();
//    StressTest::BruteForce();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Solution::Read()) {
#ifdef _DEBUG_
        clock_t startTime = clock();
        eprintf("Begin of test #%d:\n", ++test_id);
#endif

        Solution::Run();

#ifdef _DEBUG_
        clock_t endTime = clock();
        eprintf("Time consumed for test #%d is %lf\n", test_id, (double)(endTime - startTime) / (double)CLOCKS_PER_SEC);
#endif
    }
    return 0;
}
