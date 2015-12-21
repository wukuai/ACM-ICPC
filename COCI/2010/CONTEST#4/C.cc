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

string s1, s2, s3, s4;

int FC[66], SC[66];

void cleanup() {
    FILL(FC, -1);
    FILL(SC, -1);
}

bool Read() {
    cleanup();
    if(cin >> s1 >> s2 >> s3 >> s4) {
        return true;
    }
    return false;
}

void Run() {
    char foo;
    int first_h, first_m;
    int second_h, second_m;
    int first_interval_h, first_interval_m;
    int second_interval_h, second_interval_m;
    sscanf(s1.c_str(), "%d%c%d", &first_h, &foo, &first_m);
    sscanf(s2.c_str(), "%d%c%d", &second_h, &foo, &second_m);
    sscanf(s3.c_str(), "%d%c%d", &first_interval_h, &foo, &first_interval_m);
    sscanf(s4.c_str(), "%d%c%d", &second_interval_h, &foo, &second_interval_m);

    int first_timestamp = first_h * 60 + first_m, first_delta = first_interval_h * 60 + first_interval_m;
    int second_timestamp = second_h * 60 + second_m, second_delta = second_interval_h * 60 + second_interval_m;

    vector<int> first_cycle, second_cycle;

    int curr_timestamp = first_timestamp % 60;
    while(FC[curr_timestamp] == -1) {
        FC[curr_timestamp] = 1;
        first_cycle.pb(curr_timestamp);
        curr_timestamp = (curr_timestamp + first_delta) % 60;
    }
    curr_timestamp = second_timestamp % 60;
    while(SC[curr_timestamp] == -1) {
        SC[curr_timestamp] = 1;
        second_cycle.pb(curr_timestamp);
        curr_timestamp = (curr_timestamp + second_delta) % 60;
    }
    int first_position = -1;
    int second_position = -1;
    for(int i = 0; i < SZ(first_cycle) && first_position == -1; ++i) {
        for(int j = 0; j < SZ(second_cycle) && first_position == -1; ++j) {
            if(first_cycle[i] == second_cycle[j]) {
                first_position = i, second_position = j;
            }
        }
    }
    if(first_position == -1) {
        printf("Never\n");
    }
    else {
        curr_timestamp = first_timestamp;
        for(int k = 0; k < first_position; ++k) {
            curr_timestamp += first_delta;
        }
        int days_passed = curr_timestamp / (24 * 60 + 60);
        int curr_day = (6 + days_passed) % 7;
        string names[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "“Thursday", "Friday", "Saturday"};
        printf("%s\n", names[curr_day].c_str());
        curr_timestamp = curr_timestamp % (24 * 60 + 60);
        printf("%.2d:%.2d\n", curr_timestamp / 60, curr_timestamp % 60);
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
