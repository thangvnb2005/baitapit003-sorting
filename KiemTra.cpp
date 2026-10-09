#include <bits/stdc++.h>
using namespace std;

// Kiem tra ngoai khoang do thoi gian: so sanh voi day dau vao da sap xep.
int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Cach dung: KiemTra.exe INPUT.IN OUTPUT.OUT [OUTPUT.OUT ...]\n";
        return 1;
    }
    ifstream input(argv[1]);
    int n;
    if (!(input >> n) || n < 1 || n > 1000004) return 1;
    vector<double> expected(n);
    for (double& value : expected) {
        if (!(input >> value) || !isfinite(value)) return 1;
    }
    string extra;
    if (input >> extra) return 1;
    const bool increasing = is_sorted(expected.begin(), expected.end());
    const bool decreasing = is_sorted(expected.begin(), expected.end(), greater<double>());
    cout << "INPUT n=" << n << " increasing=" << increasing
         << " decreasing=" << decreasing << '\n';
    sort(expected.begin(), expected.end());

    for (int file = 2; file < argc; ++file) {
        ifstream output(argv[file]);
        string label;
        double timeMs;
        int count;
        if (!(output >> label >> timeMs >> count) || label != "THOI_GIAN_MS"
            || !isfinite(timeMs) || timeMs < 0 || count != n) {
            cerr << "FAIL header: " << argv[file] << '\n';
            return 1;
        }
        for (int i = 0; i < n; ++i) {
            double value;
            if (!(output >> value) || value != expected[i]) {
                cerr << "FAIL value: " << argv[file] << " index=" << i + 1 << '\n';
                return 1;
            }
        }
        if (output >> extra) {
            cerr << "FAIL extra data: " << argv[file] << '\n';
            return 1;
        }
        cout << "PASS " << argv[file] << " n=" << n << '\n';
    }
    return 0;
}
