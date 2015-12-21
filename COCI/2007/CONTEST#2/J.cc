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

const int maxL = 32;
const int maxN = 30007;

char A[maxN][maxL], SORTED[maxN][maxL], W[maxL];
int n, begin[maxL], end[maxL], id[maxN], before[maxN][maxL], counter[maxN][maxL];

void cleanup() {
    FILL(A, 0);
    FILL(SORTED, 0);
    FILL(begin, 0);
    FILL(end, 0);
    FILL(W, 0);
    FILL(id, 0);
    FILL(before, 0);
    FILL(counter, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%s", A[i]);
            memcpy(SORTED[i], A[i], sizeof A[i]);
        }
        return true;
    }
    return false;
}

int cmp(const void* lhs, const void* rhs) {
    return strcmp((const char *)lhs, (const char *)rhs);
}

int find_lower(char my_char, int col, int lo, int hi) {
    int ret = -1;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        if(SORTED[mid][col] == my_char) {
            ret = mid;
            hi = mid - 1;
        }
        else if(SORTED[mid][col] > my_char) {
            hi = mid - 1;
        }
        else if(SORTED[mid][col] < my_char) {
            lo = mid + 1;
        }
    }
    return ret;
}

int find_upper(char my_char, int col, int lo, int hi) {
    int ret = -1;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        if(SORTED[mid][col] == my_char) {
            ret = mid + 1;
            lo = mid + 1;
        }
        else if(SORTED[mid][col] > my_char) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }
    return ret;
}

int search(const char* s, int col, int left, int right) {
    begin[col] = end[col] = -1;
    if(s[col] == 0) return SORTED[left][col] == 0 ? left : -1;
    begin[col] = find_lower(s[col], col, left, right - 1);
    end[col] = find_upper(s[col], col, left, right - 1);
    return search(s, col + 1, begin[col], end[col]);
}

void Run() {
    qsort(SORTED, n, 32, cmp);
    for(int i = 0; i < n; ++i) {
        int row = search(A[i], 0, 0, n);
        id[row] = i + 1;
        for(int col = 0; begin[col] < end[col]; ++col) {
            before[row][col] = ++counter[begin[col]][col];
        }
    }
    int queries;
    scanf("%d", &queries);
    for(int it = 0; it < queries; ++it) {
        scanf("%s", W);
        int answer = 0;
        int pos = search(W, 0, 0, n);
        if(pos == -1) {
            answer += n;
            for(int col = 0; begin[col] < end[col]; ++col) {
                answer += counter[begin[col]][col];
            }
        }
        else {
            answer += id[pos];
            for(int col = 0; begin[col] < end[col]; ++col) {
                answer += before[pos][col];
            }
        }
        printf("%d\n", answer);
    }
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
