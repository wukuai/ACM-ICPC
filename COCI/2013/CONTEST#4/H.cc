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

namespace Solution {

const int maxL = 36 + 7;
const int maxN = 1000 * 1000 + 7;

int n, m;
char s[maxN], e[maxL];

void cleanup() {
   
}

bool Read() {
    cleanup();
    if(scanf("%s%s", s, e) == 2) {
        n = strlen(s);
        m = strlen(e);
        return true;
    }
    return false;
}

void Run() {
    stack<char> st;
    vector<char> backup;
    for(int i = 0; i < n; ++i) {
        st.push(s[i]);
        if(SZ(st) >= m) {
            backup.clear();
            int cnt = 0;
            while(cnt < m && st.top() == e[m - cnt - 1]) {
                backup.push_back(st.top());
                st.pop();
                cnt++;
            }
            if(cnt < m) {
                for(int i = SZ(backup) - 1; i >= 0; --i) {
                    st.push(backup[i]);
                }
            }
        }
    }
    if(SZ(st) == 0) {
        printf("FRULA\n");
        return ;
    }
    FILL(s, 0);
    int counter = SZ(st) - 1;
    while(!st.empty()) {
        s[counter--] = st.top();
        st.pop();
    }
    printf("%s\n", s);
}

} // Solution

namespace StressTest {

long long GetTime() {
    srand(time(NULL));
    return rand() << 16LL;
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
