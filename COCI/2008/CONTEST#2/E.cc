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

int a, b, l;
long long secure, insecure, super_secure;

void cleanup() {
   secure = insecure = super_secure = 0;
}

bool Read() {
    cleanup();
	if(scanf("%d%d%d", &a, &b, &l) == 3) {
		return true;
	}
	return false;
}

int gcd(int a, int b) {
	return a == 0 ? b : gcd(b % a, a);
}

int lcm(int a, int b) {
	return a * (b / gcd(a, b));
}

int get_count(int k) {
	if(k == 0) return 1;
	long long answer = 0;
	set<int> st;
	for(int t = 2; t * t <= k; ++t) {
		if(k % t == 0) {
			st.insert(t);
			st.insert(k / t);
			while(k % t == 0) k /= t;
		}
	}
	if(k > 1) {
		st.insert(k);
	}
	vector<int> v(ALL(st));
	int n = SZ(v);
	for(int mask = 1; mask < (1 << n); ++mask) {
		int mul = 1, t = 0;
		for(int i = 0; i < n; ++i) {
			if(mask & (1 << i)) {
				mul *= v[i]; ++t;
			}
		}
		if(t & 1) {
			answer += l / mul;
		}
		else {
			answer -= l / mul;
		}
	}
	return l - answer;
}
		
void solve(int x, int y) {
	long long cnt = 0;
	cnt += get_count(x);
	cnt += get_count(y);
	long long cnt1 = get_count(lcm(x, y));
	cnt -= cnt1;
	insecure += l - cnt;
	super_secure += cnt1;
	secure += l - (l - cnt) - cnt1;
}

void Run() {
for(int row = -a; row <= b; ++row) {
		solve(row + a, b - row);
	}
	printf(LLD"\n"LLD"\n"LLD"\n", insecure, secure, super_secure);
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