#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
double a[MAXN];
int n;

int main() {
    if (!freopen("TEST.IN", "r", stdin)) return 1;
    if (!freopen("SORT.OUT", "w", stdout)) return 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n) || n < 1 || n >= MAXN) return 1;
    for (int i = 1; i <= n; i++) {
        if (!(cin >> a[i])) return 1;
    }

    auto start = chrono::steady_clock::now();
    sort(a + 1, a + n + 1);
    auto finish = chrono::steady_clock::now();
    double timeMs = chrono::duration<double, milli>(finish - start).count();

    cout << fixed << setprecision(6);
    cout << "THOI_GIAN_MS " << timeMs << '\n';
    cout << n << '\n';
    cout << setprecision(3);
    for (int i = 1; i <= n; i++) cout << a[i] << '\n';
    return 0;
}
