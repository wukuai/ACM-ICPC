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

template <class T> inline void check_min(T& actual, T& check) {
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

const int maxN = 1507;

int n, r, c, A[maxN][maxN], DP[maxN][maxN];

struct Data {
    vector< pair<int, int> > bests;
    Data() {
        bests = {mp(-1, -1), mp(-1, -1), mp(-1, -1), mp(-1, -1)};
    }
    void update(int& row, int& col, int& val) {
        int min_pos = -1;
        DP[row][col] = val;
        for(int i = 0; i < SIZE(bests); ++i) {
            if(bests[i].first == -1) {
                bests[i] = mp(row, col);
                return ;
            }
            if(DP[bests[i].first][bests[i].second] > val) {
                continue;
            }
            if(min_pos == -1 || DP[bests[min_pos].first][bests[min_pos].second] < DP[bests[i].first][bests[i].second]) {
                min_pos = i;
            }
        }
        if(min_pos != -1) {
            bests[min_pos] = mp(row, col);
        }
    }
    int query(int& idx, int& tp) {
        int mmax = 0;
        for(int i = 0; i < SIZE(bests); ++i) {
            if(bests[i].first == -1) continue;
            if(tp == 0) {
                if(abs(bests[i].second - idx) > 1) {
                    check_max(mmax, DP[bests[i].first][bests[i].second]);
                }
            }
            else {
                if(abs(bests[i].first - idx) > 1) {
                    check_max(mmax, DP[bests[i].first][bests[i].second]);
                }
            }
        }
        return mmax;
    }
};

Data ROW[maxN], COL[maxN];

void cleanup() {
    FILL(DP, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d%d%d", &n, &r, &c) == 3) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                scanf("%d", &A[i][j]);
            }
        }
        return true;
    }
    return false;
}

class Comparator {
public:
    bool operator () (const pair<int, int>& lhs, const pair<int, int>& rhs) {
        if(A[lhs.first][lhs.second] == A[rhs.first][rhs.second]) {
            return lhs < rhs;
        }
        return A[lhs.first][lhs.second] > A[rhs.first][rhs.second];
    }
};

void Run() {
    set<pair<int, int>, Comparator> st;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            st.insert(mp(i, j));
        }
    }
    int mmax;
    pair<int, int> val;
    vector<int> update_vals;
    vector< pair<int, int> > need_to_update;
    while(!st.empty()) {
        update_vals.resize(0);
        need_to_update.resize(0);
        val = A[st.begin()->first][st.begin()->second];
        while(!st.empty()) {
            if(val == A[st.begin()->first][st.begin()->second]) {
                need_to_update.pb(*st.begin());
                st.erase(st.begin());
            }
            else {
                break;
            }
        }
        for(int i = 0; i < SIZE(need_to_update); ++i) {
            mmax = 0;
            if(need_to_update[i].first - 1 >= 0) {
                check_max(mmax, ROW[need_to_update[i].first - 1].query(need_to_update[i].second, 0));
            }
            if(need_to_update[i].first + 1 < n) {
                check_max(mmax, ROW[need_to_update[i].first + 1].query(need_to_update[i].second, 0));
            }
            if(need_to_update[i].second - 1 >= 0) {
                check_max(mmax, COL[need_to_update[i].second - 1].query(need_to_update[i].first, 1));
            }
            if(need_to_update[i].second + 1 < n) {
                check_max(mmax, COL[need_to_update[i].second + 1].query(need_to_update[i].first, 1));
            }
            update_vals.pb(1 + mmax);
        }
        for(int i = 0; i < SIZE(need_to_update); ++i) {
            ROW[need_to_update[i].first].update(need_to_update[i].first, need_to_update[i].second, update_vals[i]);
            COL[need_to_update[i].second].update(need_to_update[i].first, need_to_update[i].second, update_vals[i]);
        }
    }
    printf("%d\n", DP[r - 1][c - 1]);
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
