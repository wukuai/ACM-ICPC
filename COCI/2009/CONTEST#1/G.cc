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

struct TrieNode {
    bool was;
    TrieNode* links[13];
    TrieNode() {
        ans = 0;
        was = false;
        for(int i = 0; i < 13; ++i) {
            links[i] = NULL;
        }
    }
};

TrieNode* root = new TrieNode();

void add(const vector<int>& v) {
    TrieNode* curr = root;
    for(int i = 0; i < v.size(); ++i) {
        if(curr->links[v[i]] == NULL) {
            curr->links[v[i]] = new TrieNode();
        }
        curr = curr->links[v[i]];
    }
    curr->was = true;
}

bool have(const vector<int>& v) {
    TrieNode* curr = root;
    for(int i = 0; i < v.size(); ++i) {
        if(curr->links[v[i]] == NULL) {
            return false;
        }
        curr = curr->links[v[i]];
    }
    return curr->was;
}

int n, m, SWX[77], SWY[77], P[12], I[12];

bool Read() {
    if(scanf("%d%d", &n, &m) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", P + i);
            P[i]--;
            I[i] = i;
        }
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", SWX + i, SWY + i);
            --SWX[i], --SWY[i];
        }
        return true;
    }
    return false;
}

void Run() {
    bool ok = true;
    for(int i = 0; i < n; ++i) {
        if(I[i] != P[i]) {
            ok = false;
        }
    }
    if(ok) {
        printf("0\n");
        return ;
    }
    vector<int> p, q;
    for(int i = 0; i < n; ++i) {
        p.pb(P[i]);
        q.pb(I[i]);
    }
    int d;
    queue<int> f, b;
    queue< vector<int> > fwd, bwd;
    f.push(0), b.push(0);
    fwd.push(p), bwd.push(q);
    add(p, 0);
    add(q, 0);
    while(!fwd.empty() || !bwd.empty()) {
        if(!fwd.empty()) {
            d = f.front(), f.pop();
            p = fwd.front(), fwd.pop();
            for(int i = 0; i < m; ++i) {
                swap(p[SWX[i]], p[SWY[i]]);
                if(!have(p)) {
                    f.push(d + 1);
                    add(p);
                    fwd.push(p);
                }
                swap(p[SWX[i]], p[SWY[i]]);
            }
        }
    }




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
