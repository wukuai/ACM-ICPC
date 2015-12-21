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

const int maxN = 22;

int n, h, F[maxN], C[maxN];
char S[maxN][maxN];

void cleanup() {
    FILL(F, 0);
    FILL(C, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &h) == 2) {
        for(int i = 0; i < n; ++i) {
            scanf("%s", S[i]);
        }
        return true;
    }
    return false;
}

pair<int, int> next(int mask) {
    int counter = 0, msk = 0;
    for(int i = 0; i < n; ++i) {
        if(mask & (1 << i)) {
            msk ^= F[i];
            counter += C[i];
        }
        else {
            counter += 2 * C[i];
        }
    }
    return mp(msk, counter);
}

void Run() {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(S[i][j] == '1') {
                F[i] |= 1 << j;
                C[i] += 1;
            }
        }
    }
    int temp = F[0];
    for(int i = 0; i < 20; ++i) {
        eprintf("%d ", temp);
        temp = next(temp).first;
    }
    int tortoise = next(F[0]).first;
    int hare = next(tortoise).first;
    while(hare != tortoise) {
        tortoise = next(tortoise).first;
        hare = next(next(hare).first).first;
    }
    int mu = 0;
    tortoise = F[0];
    while(tortoise != hare) {
        tortoise = next(tortoise).first;
        hare = next(hare).first;
        ++mu;
    }
    int lam = 1;
    hare = next(tortoise).first;
    while(tortoise != hare) {
        hare = next(hare).first;
        lam += 1;
    }
    long long answer = C[0];
    if(mu + lam - 1 >= h) {
        int mask = F[0];
        for(int i = 1; i < h; ++i) {
            pair<int, int> curr = next(mask);
            mask = curr.first;
            answer += curr.second;
        }
    }
    else {
        int mask = F[0];
        h--;
        for(int i = 0; i < mu; ++i) {
            pair<int, int> curr = next(mask);
            mask = curr.first;
            answer += curr.second;
        }
        long long s = 0;
        for(int k = mu; k <= mu + lam - 1; ++k) {
            pair<int, int> curr = next(mask);
            mask = curr.first;
            s += curr.second;
        }
        answer += ((h - mu) / lam) * s;
        int rem = (h - mu) % lam;
        for(int i = 0; i < rem; ++i) {
            pair<int, int> curr = next(mask);
            mask = curr.first;
            answer += curr.second;
        }
    }
    printf("%lld\n", answer);
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
