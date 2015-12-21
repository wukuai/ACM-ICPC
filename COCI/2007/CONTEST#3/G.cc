#pragma comment(linker, "/STACK:66777216")
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

set<int> was;
map<int, int> nums;
vector<int> required;

void gen(long long x) {
	if(x > IINF || was.find(x) != was.end()) return ;
	was.insert(x);
	nums[x] = SZ(required);
	required.pb(x);
	gen(x * 2);
	gen(x * 3);
	gen(x * 7);
	gen(x * 5);
}

const int maxB = 20;
const int maxC = 5222;

long long a, b, DP[maxB][maxC][2];

void cleanup() {

}

bool Read() {
    cleanup();
	if(scanf(LLD LLD, &a, &b) == 2) {
		return true;
	}
	return false;
}

int n;
vector<int> digits;

long long go(int pos, int prod, int is_l) {
	if(pos == n) {
		if(prod == 1) return 1;
		return 0;
	}
	long long& ref = DP[pos][nums[prod]][is_l];
	if(ref != -1) {
		return ref;
	}
	ref = 0;
	if(is_l) {
		for(int k = 1; k <= 9; ++k) {
			if(prod % k == 0) {
				ref += go(pos + 1, nums[prod / k], is_l);
			}
		}
	}
	else {
		for(int k = 1; k <= 9; ++k) {
			if(digits[pos] >= k && prod % k == 0) {
				ref += go(pos + 1, nums[prod / k], digits[pos] > k);
			}
		}
	}
	return ref;
}

long long solve(long long bound) {
	digits.clear();
	while(bound) {
		digits.pb(bound % 10);
		bound /= 10;
	}
	RVRS(digits);
	long long answer = 0;
	for(int len = 1; len <= SZ(digits); ++len) {
		n = len;
		FILL(DP, -1);
		for(int i = 0; i < SZ(required); ++i) {
			answer += go(0, required[i], len < SZ(digits));
		}
	}
	return answer;
}

void Run() {
	if(SZ(required) == 0) {
		gen(1);
		eprintf("required=%d\n", SZ(required));
	}
	long long answer = solve(b) - solve(a - 1);
	printf(LLD"\n", answer);
}

} // Solution

namespace StressTest {

long long GetTime() {
    srand(time(NULL));
    return rand() << 16LL;
}

void GenerateInput() {
    FILE* output = fopen("C:\\Contests\\Templates\\input.txt", "w");
    srand(GetTime());

    
    fclose(output);
}

void BruteForce() {
    FILE* input = fopen("C:\\Contests\\Templates\\input.txt", "r");
    FILE* output = fopen("C:\\Contests\\Templates\\brute.out", "w");

    fclose(input);
    fclose(output);
}

} // StressTest

int main() {
#ifdef _DEBUG_
    int test_id = 0;
//    StressTest::GenerateInput();
//    StressTest::BruteForce();
    freopen("C:\\Contests\\Templates\\input.txt", "r", stdin);
    freopen("C:\\Contests\\Templates\\output.txt", "w", stdout);
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