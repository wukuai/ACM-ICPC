#define _CRT_SECURE_NO_WARNINGS
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
	if (actual < check) {
		actual = check;
	}
}

template <class T> inline void check_min(T& actual, T check) {
	if (actual > check) {
		actual = check;
	}
}

const double EPS = 1e-9;
const int IINF = 10000000;
const double PI = acos(-1.0);
const long long LINF = 6000000000000000000LL;
//--------------------------------------------

const int maxN = (int)2e5 + 10;

template<typename F> class SegmentTree {
private:
	int n;
	int defaultValue;
	F funcPtr;
	vector<int> tree;
	int getValue(int v, int tl, int tr, int l, int r) {
		if (l > r) {
			return defaultValue;
		}
		if (tl == l && r == tr) {
			return tree[v];
		}
		else {
			int tm = (tl + tr) / 2;
			return funcPtr(
				getValue(v << 1, tl, tm, l, min(tm, r)),
				getValue((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r));
		}
	}
	void setValue(int v, int tl, int tr, int pos, int delta) {
		if (tl == tr) {
			tree[v] = delta;
		}
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) {
				setValue(v << 1, tl, tm, pos, delta);
			}
			else {
				setValue((v << 1) | 1, tm + 1, tr, pos, delta);
			}
			tree[v] = funcPtr(tree[v << 1], tree[(v << 1) | 1]);
		}
	}
public:
	SegmentTree(int n_, int defaultValue_, F funcPtr_) {
		funcPtr = funcPtr_;
		defaultValue = defaultValue_;
		tree.resize(maxN << 2);
		for (int i = 0; i < (maxN << 2); ++i) {
			tree[i] = defaultValue;
		}
		n = n_;
	}
	int getValue(int l, int r) {
		return getValue(1, 0, n - 1, l, r);
	}
	void setValue(int pos, int delta) {
		setValue(1, 0, n - 1, pos, delta);
	}
	void swap(int l, int r) {
		int lValue = getValue(1, 0, n - 1, l, l);
		int rValue = getValue(1, 0, n - 1, r, r);
		setValue(1, 0, n - 1, l, rValue);
		setValue(1, 0, n - 1, r, lValue);
	}
};

int n, m, a[maxN];

typedef int(*Comparator)(int, int);

int getMin(int x, int y) {
	return x > y ? y : x;
}

int getMax(int x, int y) {
	return x < y ? y : x;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i); --a[i];
	}
	SegmentTree<Comparator> minTree(n, IINF, getMin);
	SegmentTree<Comparator> maxTree(n, -IINF, getMax);
	for (int i = 0; i < n; ++i) {
		minTree.setValue(a[i], i);
		maxTree.setValue(a[i], i);
	}
	int qType, l, r, mmin, mmax;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", &qType, &l, &r);
		--l, --r;
		if (qType == 1) {
			minTree.swap(a[l], a[r]);
			maxTree.swap(a[l], a[r]);
			swap(a[l], a[r]);
		}
		else {
			mmin = minTree.getValue(l, r);
			mmax = maxTree.getValue(l, r);
			if (mmax - mmin + 1 == r - l + 1) {
				printf("YES\n");
			}
			else {
				printf("NO\n");
			}
		}
	}
	return 0;
}
/*
5 3
2 4 1 3 5
2 2 5
1 3 1
2 2 5

7 7
4 7 3 5 1 2 6
2 1 7
1 3 7
2 4 6
2 4 7
2 1 4
1 1 4
2 1 4

*/