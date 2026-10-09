#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
double a[MAXN];
int n;

void quickSort(int l, int r) {
    int i = l, j = r;
    double pivot = a[(l + r) / 2];

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (l < j) quickSort(l, j);
    if (i < r) quickSort(i, r);
}

int main() {
    if (!freopen("TEST.IN", "r", stdin)) return 1;
    if (!freopen("QUICKSORT.OUT", "w", stdout)) return 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n) || n < 1 || n >= MAXN) return 1;
    for (int i = 1; i <= n; i++) {
        if (!(cin >> a[i])) return 1;
    }

    auto start = chrono::steady_clock::now();
    quickSort(1, n);
    auto finish = chrono::steady_clock::now();
    double timeMs = chrono::duration<double, milli>(finish - start).count();

    cout << fixed << setprecision(6);
    cout << "THOI_GIAN_MS " << timeMs << '\n';
    cout << n << '\n';
    cout << setprecision(3);
    for (int i = 1; i <= n; i++) cout << a[i] << '\n';
    return 0;
}
