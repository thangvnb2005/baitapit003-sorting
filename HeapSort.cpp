#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
double a[MAXN];
int n;

void heapify(int size, int i) {
    int largest = i;
    int l = 2 * i;
    int r = 2 * i + 1;

    if (l <= size && a[l] > a[largest]) largest = l;
    if (r <= size && a[r] > a[largest]) largest = r;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(size, largest);
    }
}

void heapSort() {
    for (int i = n / 2; i >= 1; i--) heapify(n, i);
    for (int i = n; i >= 2; i--) {
        swap(a[1], a[i]);
        heapify(i - 1, 1);
    }
}

int main() {
    if (!freopen("TEST.IN", "r", stdin)) return 1;
    if (!freopen("HEAPSORT.OUT", "w", stdout)) return 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n) || n < 1 || n >= MAXN) return 1;
    for (int i = 1; i <= n; i++) {
        if (!(cin >> a[i])) return 1;
    }

    auto start = chrono::steady_clock::now();
    heapSort();
    auto finish = chrono::steady_clock::now();
    double timeMs = chrono::duration<double, milli>(finish - start).count();

    cout << fixed << setprecision(6);
    cout << "THOI_GIAN_MS " << timeMs << '\n';
    cout << n << '\n';
    cout << setprecision(3);
    for (int i = 1; i <= n; i++) cout << a[i] << '\n';
    return 0;
}
