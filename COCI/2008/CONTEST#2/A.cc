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

char board[11][11];

void cleanup() {

}

bool Read() {
    cleanup();
    for(int i = 0; i < 9; ++i) {
        if(scanf("%s", board[i]) != 1) {
            return false;
        }
    }
    return true;
}

bool check() {
    eprintf("checking board : \n");
    for(int i = 0; i < 9; ++i) {
        eprintf("%s\n", board[i]);
    }
    for(int i = 0; i < 9; ++i) {
        set<int> row, col;
        for(int j = 0; j < 9; ++j) {
            if(board[i][j] != '.') {
                int num = board[i][j] - '0';
                if(row.find(num) != row.end()) {
                    eprintf("problem with (%d,%d)\n", i, j);
                    return false;
                }
                row.insert(num);
            }
            if(board[j][i] != '.') {
                int num = board[j][i];
                if(col.find(num) != col.end()) {
                    eprintf("problem with (%d,%d)\n", j, i);
                    return false;
                }
                col.insert(num);
            }
        }
    }
    for(int i = 0; i < 9; i += 3) {
        for(int j = 0; j < 9; j += 3) {
            set<int> numbers;
            for(int k = i; k <= i + 2; ++k) {
                for(int l = j; l <= j + 2; ++l) {
                    if(board[k][l] != '.') {
                        int num = board[k][l] - '0';
                        if(numbers.find(num) != numbers.end()) {
                            eprintf("problem with block (%d,%d, %d, %d)\n", i, j, i + 2, j + 2);
                            return false;
                        }
                        numbers.insert(num);
                    }
                }
            }
        }
    }
    return true;
}

void Run() {
        bool deduced = false;
        bool columns[9], rows[9];
        do {
            if(!check()) {
                printf("ERROR\n"); return ;
            }
            deduced = false;
            for(int i = 0; i < 9; ++i) {
                for(int j = 0; j < 9; ++j) {
                    if(board[i][j] != '.') {
                        FILL(rows, 0);
                        FILL(columns, 0);
                        for(int k = 0; k < 9; ++k) {
                            for(int l = 0; l < 9; ++l) {
                                if(board[i][j] == board[k][l]) {
                                    rows[k] = true;
                                    columns[l] = true;
                                }
                            }
                        }
                        for(int k = 0; k < 9; k += 3) {
                            for(int l = 0; l < 9; l += 3) {
                                bool am = true;
                                int cnt = 0, av = 0;
                                for(int s = k; s <= k + 2; ++s) {
                                    for(int t = l; t <= l + 2; ++t) {
                                        if(board[i][j] == board[s][t]) {
                                            am = false;
                                            break;
                                        }
                                        if(board[s][t] == '.') {
                                            cnt++;
                                        }
                                        if(board[s][t] == '.' && !rows[s] && !columns[t]) {
                                            av++;
                                        }
                                    }
                                }
                                if(am == false) continue;
                                int x = -1, y = -1;
                                bool only_one_spot = false;
                                for(int s = k; s <= k + 2; ++s) {
                                    for(int t = l; t <= l + 2; ++t) {
                                        if(board[s][t] == '.' && !rows[s] && !columns[t]) {
                                            if(x == -1 && y == -1) {
                                                only_one_spot = true;
                                                x = s, y = t;
                                            }
                                            else {
                                                only_one_spot = false; break;
                                            }
                                        }
                                    }
                                }
                                if(only_one_spot) {
                                    deduced = true;
                                    board[x][y] = board[i][j];
                                }
                            }
                        }
                    }
                }
            }
        }while(deduced);
    for(int i = 0; i < 9; ++i) {
        printf("%s\n", board[i]);
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
