#include<bits/stdc++.h>

using namespace std;

//--------------------------------------------
#define SIZE(x) x.size()
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
#define ALL(X) X.begin(), X.end()
#define SORT(x) sort(ALL(x))
#define REVERSE(x) reverse(ALL(x))
#define FILL(x, value) memset(x, value, sizeof(x))

#define next next1
#define hash hash1
#define rank rank1
#define count count1

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

const double EPS = 1e-9;
const int IINF = 1000000000;
const double PI = acos(-1.0);
const long long LINF = 6000000000000000000LL;
//--------------------------------------------

const int maxN = 500 * 1000 + 7;

int n, d[maxN];

void cleanup() {
    FILL(d, 0);
}

bool Read() {
    cleanup();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", d + i);
        }
        return true;
    }
    return false;
}

void generate(int N) {
    srand(time(NULL));
    ofstream fout("input.txt");
    fout << N << endl;
    for(int i = 0; i < N; ++i) {
        fout << rand() % 30 << endl;
    }
}

long long brute() {
    long long ret = 0;
    for(int i = 0; i + 1 < n; ++i) {
        ret++;
        for(int j = i + 2; j < n; ++j) {
            bool ok = true;
            for(int t = i + 1; t <= j - 1; ++t) {
                if(d[t] > d[i] || d[t] > d[j]) {
                    ok = false; break;
                }
            }
            ret += ok;
        }
    }
    return ret;
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while(Read()) {
        long long answer = 0;
        stack< pair<int, int> > st;
        st.push(mp(d[0], 1));
        for(int i = 1; i < n; ++i) {
            bool pushed = false;
            while(!st.empty()) {
                if(st.top().first < d[i]) {
                    answer += st.top().second;
                    st.pop();
                }
                else if(st.top().first > d[i]) {
                    answer += 1; break;
                }
                else if(st.top().first == d[i]) {
                    answer += st.top().second;
                    pair<int, int> fake = st.top(); st.pop();
                    if(st.empty()) {
                        st.push(mp(fake.first, fake.second + 1));
                    }
                    else {
                        answer += 1;
                        st.push(mp(fake.first, fake.second + 1));
                    }
                    pushed = true; break;
                }
            }
            if(!pushed) {
                st.push(mp(d[i], 1));
            }
        }
        printf("%lld\n", answer);
        //printf("brute=%lld\n my=%lld\n", brute(), answer);
    }
    return 0;
}
