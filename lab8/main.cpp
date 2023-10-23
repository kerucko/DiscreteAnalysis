#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n;
    cin >> n;

    vector<long long> array(n);
    vector<long long> count(3, 0);

    for (long long i = 0; i < n; i++) {
        cin >> array[i];
        count[array[i] % 4 - 1]++;
    }

    vector<vector<long long>> countInArea(3, vector<long long>(3, 0));
    for (long long i = 0; i < count[0]; i++) {
        countInArea[0][array[i] % 4 - 1]++;
    }
    for (long long i = count[0]; i < count[1] + count[0]; i++) {
        countInArea[1][array[i] % 4 - 1]++;
    }
    for (long long i = count[1] + count[0]; i < n; i++) {
        countInArea[2][array[i] % 4 - 1]++;
    }

    long long res = 0;
    while (countInArea[0][1] > 0) {
        if (countInArea[1][0] > 0) {
            countInArea[0][1] -= countInArea[1][0];
            res += countInArea[1][0];
            countInArea[1][0] = 0;
        } else {
            countInArea[2][0] -= countInArea[0][1];
            res += countInArea[0][1];
            countInArea[0][1] = 0;
        }
    }
    while (countInArea[0][2] > 0) {
        if (countInArea[1][0] > 0) {
            countInArea[1][2] += countInArea[1][0];
            countInArea[0][2] -= countInArea[1][0];
            res += countInArea[1][0];
            countInArea[1][0] = 0;
        } else {
            countInArea[2][0] -= countInArea[0][2];
            res += countInArea[0][2];
            countInArea[0][2] = 0;
        }
        
    }
    res += countInArea[1][2];

    cout << res << endl;

    return 0;
}