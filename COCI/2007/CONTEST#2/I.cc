#include<bits/stdc++.h>

using namespace std;

//--------------------------------------------
#define SIZE(x) (x.size())
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

const int maxB = 33;
const int maxAlphabet = 26;

int n, q;
char buffer[maxB];

struct TrieNode {
    int cnt;
    int terminal;
    TrieNode* links[maxAlphabet];

    TrieNode() {
        cnt = 0;
        terminal = 0;
        for(int i = 0; i < maxAlphabet; ++i) {
            links[i] = NULL;
        }
    }
};

void delete_tree(TrieNode* current_node) {
    if(current_node == NULL) return ;
    for(int i = 0; i < maxAlphabet; ++i) {
        if(current_node->links[i] != NULL) {
            delete_tree(current_node->links[i]);
        }
    }
    delete current_node;
}

TrieNode* root = NULL;

void add(TrieNode* current_node, char buff[], int pos, int len, int index) {
    if(pos == 0) {
        if(current_node->links[buff[0] - 'a'] == NULL) {
            current_node->links[buff[0] - 'a'] = new TrieNode();
        }
        add(current_node->links[buff[0] - 'a'], buff, pos + 1, len, index);
    }
    else {
        current_node->cnt++;
        if(pos + 1 == len) {
            current_node->terminal = index + 1;
            return ;
        }
        if(current_node->links[buff[pos + 1] - 'a'] == NULL) {
            current_node->links[buff[pos + 1] - 'a'] = new TrieNode();
        }
        add(current_node->links[buff[pos + 1] - 'a'], buff, pos + 1, len, index);
    }
}

void search(TrieNode* current_node, char buff[], int pos, int len, int& answer, int prev, bool& found) {
    if(pos == 0) {
        if(current_node->links[buff[0] - 'a'] == NULL) {
            return ;
        }
        search(current_node->links[buff[0] - 'a'], buff, pos + 1, len, answer, prev, found);
    }
    else {
        if(current_node->cnt < prev) {
            answer += (prev - current_node->cnt) * pos;
        }
        prev = current_node->cnt;
        if(pos + 1 == len) {
            answer += prev * (pos + 1);
            if(current_node->terminal) {
                found = true;
                answer += current_node->terminal;
            }
        }
        if(pos + 1 < len) {
            if(current_node->links[buffer[pos + 1] - 'a'] == NULL) {
                answer += prev * pos;
            }
            else {
                search(current_node->links[buffer[pos + 1] - 'a'], buff, pos + 1, len, answer, prev, found);
            }
        }
    }
}

void cleanup() {
    delete_tree(root);
}

bool Read() {
    cleanup();
    root = new TrieNode();
    if(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i) {
            scanf("%s", buffer);
            add(root, buffer, 0, strlen(buffer), i);
        }
        return true;
    }
    return false;
}

int main() {
#ifdef _DEBUG_
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    while(Read()) {
        scanf("%d", &q);
        for(int i = 0; i < q; ++i) {
            int answer = 0;
            scanf("%s", buffer);
            bool found = false;
            search(root, buffer, 0, strlen(buffer), answer, 0, found);
            printf("%d\n", answer + (!found) * n);
        }
    }
    
    return 0;
}
