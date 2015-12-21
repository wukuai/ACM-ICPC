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

map<string, int> mp;

void init() {
    mp["c="] = 1;
    mp["c-"] = 1;
    mp["dz="] = 1;
    mp["d-"] = 1;
    mp["lj"] = 1;
    mp["nj"] = 1;
    mp["s="] = 1;
    mp["z="] = 1;
}

string str;

void cleanup() {

}

bool Read() {
    cleanup();
    if(cin >> str) {
        return true;
    }
    return false;
}

void Run() {
    int answer = 0;
    for(int i = 0; i < SIZE(str); ) {
        bool any = true;
        if(i + 1 < SIZE(str)) {
            if(mp.find(str.substr(i, 2)) != mp.end()) {
                i += 2;
                any = false;
                answer += 1;
            }
        }
        if(i + 2 < SIZE(str)) {
            if(mp.find(str.substr(i, 3)) != mp.end()) {
                i += 3;
                any = false;
                answer += 1;
            }
        }
        answer += any;
        if(any) {
            ++i;
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

    Solution::init();

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
