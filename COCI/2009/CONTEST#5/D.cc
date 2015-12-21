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

const int maxN = 100007;

int n, X[maxN], Y[maxN], Z[maxN];

void cleanup() {

}

class MyStruct {
private:
    int sz;
    int P[maxN]; // positions in sorted
    pair<int, int> SORTED[maxN];
    char TOOK[maxN];
    set< pair<int, int> > distances;
public:
    MyStruct() {
        sz = 0;
        FILL(P, 0);
        FILL(TOOK, 0);
        FILL(SORTED, 0);
        distances.clear();
    }
    void initialize(int ARR[], int len) {
        for(int i = 0; i < len; ++i) {
            SORTED[i] = mp(ARR[i], i);
        }
        sz = len;
        sort(SORTED, SORTED + len);
        for(int i = 0; i < len; ++i) {
            P[SORTED[i].second] = i;
        }
    }
    int get_min() {
        return distances.begin()->first;
    }
    int get_pos(int x) {
        return P[x];
    }
    int get_min_pos() {
        return SORTED[distances.begin()->second].second;
    }
    void remove(int pos) {
        pos = P[pos];
        assert(!TOOK[pos]);
        if(pos == 0) {
            if(TOOK[pos + 1]) {
                distances.erase(mp(SORTED[pos + 1].first - SORTED[pos].first, pos));
            }
            else {
                distances.insert(mp(SORTED[pos + 1].first - SORTED[pos].first, pos + 1));
            }
            TOOK[pos] = 1;
        }
        else if(pos == sz - 1) {
            if(TOOK[pos - 1]) {
                distances.erase(mp(SORTED[pos].first - SORTED[pos - 1].first, pos));
            }
            else {
                distances.insert(mp(SORTED[pos].first - SORTED[pos - 1].first, pos - 1));
            }
            TOOK[pos] = 1;
        }
        else {
            TOOK[pos] = 1;
            if(!TOOK[pos + 1] && !TOOK[pos - 1]) {
                distances.insert(mp(SORTED[pos].first - SORTED[pos - 1].first, pos - 1));
                distances.insert(mp(SORTED[pos + 1].first - SORTED[pos].first, pos + 1));
            }
            else if(!TOOK[pos - 1] && TOOK[pos + 1]) {
                distances.erase(mp(SORTED[pos + 1].first - SORTED[pos].first, pos));
                distances.insert(mp(SORTED[pos].first - SORTED[pos - 1].first, pos - 1));
            }
            else if(TOOK[pos - 1] && !TOOK[pos + 1]) {
                distances.erase(mp(SORTED[pos].first - SORTED[pos - 1].first, pos));
                distances.insert(mp(SORTED[pos + 1].first - SORTED[pos].first, pos + 1));
            }
            else {
                distances.erase(mp(SORTED[pos + 1].first - SORTED[pos].first, pos));
                distances.erase(mp(SORTED[pos].first - SORTED[pos - 1].first, pos));
            }
        }
    }
};

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d", X + i, Y + i, Z + i);
        }
        return true;
    }
    return false;
}

void Run() {
    MyStruct x, y, z;
    x.initialize(X, n);
    y.initialize(Y, n);
    z.initialize(Z, n);

    x.remove(0);
    y.remove(0);
    z.remove(0);

    long long answer = 0;
    for(int it = 0; it < n - 1; ++it) {
        int x_min = x.get_min();
        int y_min = y.get_min();
        int z_min = z.get_min();
        if(x_min <= y_min && x_min <= z_min) {
            answer += x_min;
            int x_pos = x.get_min_pos();
            x.remove(x_pos);
            y.remove(x_pos);
            z.remove(x_pos);
        }
        else if(y_min <= x_min && y_min <= z_min) {
            answer += y_min;
            int y_pos = y.get_min_pos();
            x.remove(y_pos);
            y.remove(y_pos);
            z.remove(y_pos);
        }
        else {
            answer += z_min;
            int z_pos = z.get_min_pos();
            x.remove(z_pos);
            y.remove(z_pos);
            z.remove(z_pos);
        }
    }
    printf(LLD "\n", answer);
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
