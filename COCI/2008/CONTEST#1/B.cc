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

const int maxN = 107;

int n;
char S[maxN];

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        scanf("%s", S);
        return true;
    }
    return false;
}

int get_correct(string V) {
    int cnt = 0;
    for(int i = 0; i < min(n, SIZE(V)); ++i) {
        cnt += S[i] == V[i];
    }
    return cnt;
}

void Run() {
    string A, B, C;
    while(SIZE(A) < n) {
        A += "ABC";
    }
    while(SIZE(B) < n) {
        B += "BABC";
    }
    while(SIZE(C) < n) {
        C += "CCAABB";
    }
    int mmax = get_correct(A);
    check_max(mmax, get_correct(B));
    check_max(mmax, get_correct(C));
    printf("%d\n", mmax);
    vector<string> names;
    if(mmax == get_correct(A)) {
        names.pb("Adrian");
    }
    if(mmax == get_correct(B)) {
        names.pb("Bruno");
    }
    if(mmax == get_correct(C)) {
        names.pb("Goran");
    }
    SORT(names);
    for(int i = 0; i < SIZE(names); ++i) {
        printf("%s\n", names[i].c_str());
    }
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
