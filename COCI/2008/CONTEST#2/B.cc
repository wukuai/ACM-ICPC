#include<bits/stdc++.h>

using namespace std;

//--------------------------------------------
#define SIZE(x) ((int)x.size())
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define ALL(X) X.begin(), X.end()
#define SORT(x) sort(ALL(x))
#define REVERSE(x) reverse(ALL(x))
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

const int maxP = 57;
const int maxN = 30007;

char S[maxN][maxP], ch;
int n, k, m, P[maxN], C[maxP];

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &k) == 2) {
        for(int i = 0; i < k; ++i) {
            scanf(" %c%d", &ch, &P[0]);
            C[ch - 'A'] += P[0];
        }
        scanf("%d", &m);
        for(int i = 0; i < m; ++i) {
            scanf("%d", P + i); P[i]--;
        }
        return true;
    }
    return false;
}

void Run() {
    int cnt = 0;
    for(int i = 0; i < 26; ++i) {
        cnt += 2 * (C[i] / 2);
    }
    if(cnt != n * n - n) {
        printf("IMPOSSIBLE\n");
        return ;
    }
    int x = 0, y = 0;
    vector<int> dioganls;
    for(int i = 0; i < 26; ++i) {
        if(C[i] & 1) {
            dioganls.pb(i);
            C[i] -= 1;
        }
    }
    REVERSE(dioganls);
    int ptr = 0, need = n * n;
    for(int it = 0; it < n; ++it) {
        for(int i = 0; i < m; ++i) {
            if(P[i] == y) {
                S[x][y] = dioganls.back() + 'A';
            }
        }
        dioganls.pop_back();
        if(need == 0) break;
        while(!C[ptr] && ptr < 26) ++ptr;




}

} // Solution

namespace StressTest {

void GenerateInput() {
    FILE* output = fopen("input.txt", "w");

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
    srand(time(NULL));
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
