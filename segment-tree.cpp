#include <bits/stdc++.h>
 
#define pii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define ll long long 
#define ld long double
#define sz(v) int(v.size())
#define all(v) v.begin(), v.end()
 
#define y1 what

using namespace std;
 
const int N = (int) 1e5 + 10;
const int M = (int) 1e8 + 7;
const ll LINF = (ll) 1e18;
const int INF = (int) 1e9 + 7;
const double EPS = (double) 1e-9;

int n, k, q;
int a[N], x[N], y[N];
vector<int> id[N];

struct node {
	int l, r, sum;

	node() {

	}

	node(int _l, int _r, int _sum) {
		l = _l;
		r = _r;
		sum = _sum;
	}
};

int sz;
node t[N * 20];
int rt[N];

int get(int v, int l, int r, int L, int R) {
	if (!v)
		return 0;
	if (L > r || l > R)
		return 0;
	if (L <= l && r <= R) 
		return t[v].sum;
	int m = (l + r) / 2;
	return get(t[v].l, l, m, L, R) + get(t[v].r, m + 1, r, L, R);
}

void upd(int vv, int v, int l, int r, int id, int val) {
	if (l == r) {
		t[v].sum = val;
		return;
	}
	int m = (l + r) / 2;
	if (id <= m) {
		t[v].l = ++sz;
		t[v].r = t[vv].r;
		upd(t[vv].l, t[v].l, l, m, id, val);	
	} else {
		t[v].r = ++sz;
		t[v].l = t[vv].l;
		upd(t[vv].r, t[v].r, m + 1, r, id, val);	
	}
	t[v].sum = (t[v].l ? t[t[v].l].sum : 0) + (t[v].r ? t[t[v].r].sum : 0);
}

void build(int v, int l, int r) {
	if (l == r) {
		t[v].sum = 1;
		return;
	}
	int m = (l + r) / 2;
	t[v].l = ++sz;
	t[v].r = ++sz;
	build(t[v].l, l, m);
	build(t[v].r, m + 1, r);
	t[v].sum = (t[v].l ? t[t[v].l].sum : 0) + (t[v].r ? t[t[v].r].sum : 0);
}

int main() {
    cin >> n >> k;
    build(rt[0] = 0, 1, n);
    for (int i = 1; i <= n; i++) {
    	cin >> a[i];
    	id[a[i]].pb(i);
    	if (sz(id[a[i]]) - 1 - k >= 0) 
    		upd(rt[i - 1], rt[i] = ++sz, 1, n, id[a[i]][sz(id[a[i]]) - 1 - k], 0);
    	else 
    		upd(rt[i - 1], rt[i] = ++sz, 1, n, i, 1);
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
    	cin >> x[i] >> y[i];
    }
    int last = 0;
    for (int i = 1; i <= q; i++) {
    	int l = (x[i] + last) % n + 1;
    	int r = (y[i] + last) % n + 1;
    	if (l > r) 
        swap(l, r);
    	cout << (last = get(rt[r], 1, n, l, r)) << endl;
    }
    return 0;
}
