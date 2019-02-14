#include <bits/stdc++.h>

using namespace std;

const int N = 4100;
const int K = 810;
const int INF = (int) 1e9 + 7;

int n, k;
int a[N][N], cost[N][N];
int dp[K][N];

int readint() {
    char c;
    while (!isdigit(c = getchar()));
    int res = c - '0';
    while (isdigit(c = getchar()))
        (res *= 10) += c - '0';
    return res;
}

void solve(int k, int l, int r, int optl, int optr) {
  if (l > r) {
        return;
    }
    int m = (l + r) / 2;
    int cpos = -1;
    int ans = INF;
    for (int i = optl; i <= min(m, optr); i++) {
        if (cpos == -1 || dp[k - 1][i - 1] + cost[i][m] < ans) {
            cpos = i;
            ans = dp[k - 1][i - 1] + cost[i][m];
        }
    }
    dp[k][m] = ans;
    solve(k, l, m - 1, optl, cpos);
    solve(k, m + 1, r, cpos, optr);
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = readint();
            a[i][j] += a[i - 1][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        int cur = 0;
        for (int j = i; j <= n; j++) {
            cur += a[j][j] - a[i - 1][j];
            cost[i][j] = cur;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        dp[0][i] = INF;
    for (int parts = 1; parts <= k; parts++) {
        solve(parts, 1, n, 1, n);
    }
    printf("%d", dp[k][n]);
    return 0;
}
