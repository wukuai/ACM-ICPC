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

const int maxN = 100 * 1000 + 7;

vector<int> G[maxN];
int n, FREQ[maxN][3], A[3][maxN], USED[maxN];

void cleanup() {
    for(int i = 0; i < maxN; ++i) {
        G[i].clear();
        USED[i] = 0;
        A[0][i] = A[1][i] = A[2][i] = 0;
        FREQ[i][0] = FREQ[i][1] = FREQ[i][2] = 0;
    }
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < 3; ++i) {
            for(int j = 1; j <= n; ++j) {
                scanf("%d", &A[i][j]);
                FREQ[A[i][j]][i]++;
                G[A[i][j]].pb(j);
            }
        }
        return true;
    }
    return false;
}

void Run() {
    int answer = 0;
    stack<int> remove;
    for(int i = 1; i <= n; ++i) {
        if(FREQ[i][0] == 0 || FREQ[i][1] == 0 || FREQ[i][2] == 0) {
            eprintf("%d ", i);
            remove.push(i);
        }
    }
    eprintf("\n");
    while(!remove.empty()) {
        int num = remove.top(); remove.pop();
        for(int i = 0; i < SIZE(G[num]); ++i) {
            int col = G[num][i];
            if(USED[col]) continue;
            ++answer;
            USED[col] = true;
            --FREQ[A[0][col]][0];
            --FREQ[A[1][col]][1];
            --FREQ[A[2][col]][2];

            if(FREQ[A[0][col]][0] == 0) remove.push(A[0][col]);
            if(FREQ[A[1][col]][1] == 0) remove.push(A[1][col]);
            if(FREQ[A[2][col]][2] == 0) remove.push(A[2][col]);
        }
    }
    printf("%d\n", answer);
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
