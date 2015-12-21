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

const int maxN = 300 * 1000 + 7;

int A[maxN], C[maxN], D[maxN], n;

void cleanup() {
	FILL(A, 0);
	FILL(C, 0);
	FILL(D, 0);
}

bool Read() {
    cleanup();
	if(scanf("%d", &n) == 1) {
		for(int i = 0; i < n; ++i) {
			scanf("%d", A + i); --A[i];
		}
		return true;
	}
	return false;
}

void Run() {
	printf("%d\n", 0);
	set<int> nodes;
	nodes.insert(A[0]);
	for(int i = 1; i < n; ++i) {
		set<int>::iterator it1 = nodes.lower_bound(A[i]);
		set<int>::iterator it2 = nodes.upper_bound(A[i]);
		if(it1 == nodes.end() && it2 == nodes.end()) {
			int par = *nodes.rbegin();
			D[A[i]] = D[par] + 1;
			nodes.insert(A[i]);
			printf("%d\n", D[A[i]]);
		}
		else if(it1 != nodes.end() && it2 == nodes.end()) {
			D[A[i]] = D[*it1] + 1;
			printf("%d\n", D[A[i]]);
			nodes.insert(A[i]);
		}
		else if(it1 == nodes.end() && it2 != nodes.end()) {
			D[A[i]] = D[*it2] + 1;
			printf("%d\n", D[A[i]]);
			nodes.insert(A[i]);
		}
		else {
			if(D[*it1] > D[*it2]) {
				D[A[i]] = D[*it2] + 1;
			}
			else {
				D[A[i]] = D[*it1] + 1;
			}
			printf("%d\n", D[A[i]]);
			nodes.insert(A[i]);
		}
	}
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