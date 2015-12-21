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

int len;
long long a, b;
vector<int> digits;
long long DP[18][2222][2][11];


void cleanup() {
   
}

bool Read() {
    cleanup();
	if(scanf(LLD LLD, &a, &b) == 2) {
		return true;
	}
	return false;
}

int get_sign(int pos, int digit, int len) {
	for(int k = pos; k <= pos + len - 1; ++k) {
		if(digits[k] != digit) {
			if(digits[k] < digit) {
				return -1;
			}
			return 1;
		}
	}
	return 0;
}

int tt;

long long go(int pos, int sm, int smaller, int last) {
	if(sm < 0) return 0;
	if(pos == len) {
		if(sm == 0) return 1;
		return 0;
	}
	long long& ref = DP[pos][sm][smaller][last];
	if(ref != -1) return ref;
	ref = 0;
	int start = 0;
	if(pos == 0) start = 1;
	if(smaller) {
		for(int d = start; d <= 9; ++d) {
			if(d == last) continue;
			for(int k = 1; k <= 15 && pos + k <= len; ++k) {
				if(sm < (tt = k * k * d)) break;
				ref += go(pos + k, sm - tt, smaller, d);
			}
		}
	}
	else {
		for(int d = start; d <= 9; ++d) {
			if(d == last) continue;
			for(int k = 1; k <= 15 && pos + k <= len; ++k) {
				int sgn = get_sign(pos, d, k);
				if(sm < (tt = k * k * d)) break;
				if(sgn == -1) continue;
				ref += go(pos + k, sm - tt, sgn, d);
			}
		}
	}
	return ref;
}

long long precalc[] = {0, 45, 945, 14400, 193500, 2430000, 29250000, 342000000, 3915000000, 44100000000, 490500000000, 5400000000000, 58950000000000, 639000000000000, 6885000000000000, 73800000000000000, 787499999999988480};

long long solve(long long x) {
	if(x == 0) return 0;
	long long answer = 0;
	digits.clear();
	while(x) {
		digits.pb(x % 10);
		x /= 10;
	}
	RVRS(digits);
	for(len = 1; len < SZ(digits); ++len) {
		answer += precalc[len];
	}
	FILL(DP, -1);
	for(int sm = 1; sm <= 2100; ++sm) {
		answer += sm * go(0, sm, 0, 10);
	}
	return answer;
}

void Run() {
	printf(LLD"\n", solve(b) - solve(a - 1));
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