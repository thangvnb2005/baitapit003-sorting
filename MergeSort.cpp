#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
double a[MAXN], b[MAXN];
int n;

void merge(int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) b[k++] = a[i++];
        else b[k++] = a[j++];
    }
    while (i <= mid) b[k++] = a[i++];
    while (j <= r) b[k++] = a[j++];

    for (int x = l; x <= r; x++) a[x] = b[x];
}

void mergeSort(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);
    merge(l, mid, r);
}

int main() {
    if (!freopen("TEST.IN", "r", stdin)) return 1;
    if (!freopen("MERGESORT.OUT", "w", stdout)) return 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n) || n < 1 || n >= MAXN) return 1;
    for (int i = 1; i <= n; i++) {
        if (!(cin >> a[i])) return 1;
    }

    auto start = chrono::steady_clock::now();
    mergeSort(1, n);
    auto finish = chrono::steady_clock::now();
    double timeMs = chrono::duration<double, milli>(finish - start).count();

    cout << fixed << setprecision(6);
    cout << "THOI_GIAN_MS " << timeMs << '\n';
    cout << n << '\n';
    cout << setprecision(3);
    for (int i = 1; i <= n; i++) cout << a[i] << '\n';
    return 0;
}
