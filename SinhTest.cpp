#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;
double a[N + 5];

int main() {
    mt19937 rng(20261009);

    for (int test = 1; test <= 10; test++) {
        for (int i = 1; i <= N; i++) {
            // So thuc trong [-1000000, 1000000], co 3 chu so thap phan.
            a[i] = ((int)(rng() % 2000000001U) - 1000000000) / 1000.0;
        }

        if (test == 1) sort(a + 1, a + N + 1);
        if (test == 2) sort(a + 1, a + N + 1, greater<double>());

        string fileName = "TEST" + to_string(test) + ".IN";
        ofstream fout(fileName);
        if (!fout) return 1;
        fout << N << '\n';
        fout << fixed << setprecision(3);
        for (int i = 1; i <= N; i++) fout << a[i] << '\n';
        if (!fout) return 1;

        cout << "Da tao " << fileName << '\n';
    }
    return 0;
}
