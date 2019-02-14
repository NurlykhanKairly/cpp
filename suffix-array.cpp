#include <bits/stdc++.h>

#define pb push_back

using namespace std;

const int N = (int) 1e5 + 1;

string s;
int n;
vector<int> v;
int ncol[N], col[N], suff[N], head[N], nsuff[N];

bool cmp(int x, int y) {
   return v[x] < v[y];
}

void suffix_array() {
    for (int i = 0; i < n; i++) {
        suff[i] = i;
    }
    sort(suff, suff + n, cmp);
    int cn = 0;
    for (int i = 0; i < n; i++) {
        if (!i || v[suff[i]] != v[suff[i - 1]]) {
            col[suff[i]] = cn++;
            head[cn - 1] = i;
        } else {
            col[suff[i]] = cn - 1;
        }
    }
    for (int i = 1; i < n; i += i) {
        for (int j = 0; j < n; j++) {
            int k = (suff[j] - i + n) % n;
            nsuff[head[col[k]]++] = k;
        }
        cn = 0;
        for (int j = 0; j < n; j++)
            suff[j] = nsuff[j];
        for (int j = 0; j < n; j++) {
            if (!j || col[suff[j]] != col[suff[j - 1]] || col[(suff[j] + i) % n] != col[(suff[j - 1] + i) % n]) {
                ncol[suff[j]] = cn++, head[cn - 1] = j;
            } else {
                ncol[suff[j]] = cn - 1;
            }
        }
        for (int j = 0; j < n; j++)
            col[j] = ncol[j];
    }
}

int main() {
    freopen("suffaray.in", "r", stdin);
    freopen("suffaray.out", "w", stdout);
    getline(cin, s);
    for(int i = 0; i < s.size(); i++) {
        v.pb(s[i] + N);
    }
    v.pb(1);
    n = v.size();
    suffix_array();
    for(int j = 1; j < n; j++) {
        cout << suff[j] + 1 << ' ';
    }
    return 0;
}
