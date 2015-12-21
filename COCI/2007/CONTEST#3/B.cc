#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

//--------------------------------------------
#define SIZE(x) ((int)x.size())
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define ALL(X) X.begin(), X.end()
#define SORT(x, cmp) sort(ALL(x), cmp)
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

const int maxN = 100007;

char S[maxN];
int n, m, X[maxN], Y[maxN];

void cleanup() {

}

bool Read() {
    cleanup();
    if(scanf("%d%d", &n, &m) == 2) {
        scanf("%s", S);
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", X + i, Y + i);
        }
        return true;
    }
    return false;
}

    bool cmp_summation (const pair<int, int>& lhs, const pair<int, int>& rhs) {
        if(lhs.first + lhs.second == rhs.first + rhs.second) {
            return lhs < rhs;
        }
        return lhs.first + lhs.second < rhs.first + rhs.second;
    }

    bool cmp_difference (const pair<int, int>& lhs, const pair<int, int>& rhs) {
        if(lhs.first - lhs.second == rhs.first - rhs.second) {
            return lhs < rhs;
        }
        return lhs.first - lhs.second < rhs.first - rhs.second;
    }


void Run() {
    map< pair<int, int>, list< pair<int, int> >::iterator* > ITER_SUM;
    map< pair<int, int>, list< pair<int, int> >::iterator* > ITER_DIFF;  
    list< pair<int, int> > sum_sorted, diff_sorted;
    for(int i = 0; i < n; ++i) {
        sum_sorted.pb(mp(X[i], Y[i]));
        diff_sorted.pb(mp(X[i], Y[i]));
    }
    sum_sorted.sort(cmp_summation);
    diff_sorted.sort(cmp_difference);
    for(auto it = sum_sorted.begin(); it != sum_sorted.end(); ++it) {
        ITER_SUM[*it] = &it;
    }
    for(auto it = diff_sorted.begin(); it != diff_sorted.end(); ++it) {
        ITER_DIFF[*it] = &it;
    }
    list< pair<int, int> >::iterator* it_sum = ITER_SUM[mp(X[0], Y[0])];
    list< pair<int, int> > ::iterator* it_diff = ITER_DIFF[mp(X[0], Y[0])];
    for(int i = 0; i < m; ++i) {
        if(S[i] == 'A') { // searching in difference
            list< pair<int, int> >::iterator tmp = *it_diff; tmp++;
            if(tmp != diff_sorted.end() && (*it_diff)->first < tmp->first && (*it_diff)->second < tmp->second && tmp->first - (*it_diff)->first == tmp->second - (*it_diff)->second) {
                diff_sorted.erase(*it_diff);
                sum_sorted.erase(*it_sum);
                it_diff = &tmp;
                it_sum = ITER_SUM[*(*it_sum)];
            }
        }
        else if(S[i] == 'B') { // searching in sum
            list< pair<int, int> >::iterator tmp = *it_sum; tmp++;
            if(tmp != sum_sorted.end() && (*it_sum)->first < tmp->first && (*it_sum)->second > tmp->second && tmp->first - (*it_sum)->first == (*it_sum)->second - tmp->second) {
                sum_sorted.erase(*it_sum);
                diff_sorted.erase(*it_diff);
                it_sum = &tmp;
                it_diff = ITER_DIFF[*(*it_diff)];
            }
        }
        else if(S[i] == 'C') { // searching in sum 
            list< pair<int, int> >::iterator tmp = *it_sum; tmp++;
            if(tmp != sum_sorted.end() && (*it_sum)->first > tmp->first && (*it_sum)->second < tmp->second && -1*(tmp->first) + (*it_sum)->first == -1*((*it_sum)->second) + tmp->second) {
                sum_sorted.erase(*it_sum);
                it_sum = &tmp;
                diff_sorted.erase(*it_diff);
                it_diff = ITER_DIFF[*(*it_diff)];
            }
        }
        else if(S[i] == 'D') { // searching in difference
            list< pair<int, int> >::iterator tmp = *it_diff; tmp++;
            if(tmp != diff_sorted.end() && (*it_diff)->first > tmp->first && (*it_diff)->second > tmp->second && -1*(tmp->first) + (*it_diff)->first == -1*(tmp->second) + (*it_diff)->second) {
                diff_sorted.erase(*it_diff);
                it_diff = &tmp;
                sum_sorted.erase(*it_sum);
                it_sum = ITER_SUM[*(*(it_sum))];
            }
        }
    }
    printf("%d %d\n", (*it_sum)->first, (*it_sum)->second);
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
