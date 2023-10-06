#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;

    vector<vector<long long>> matrix(n, vector<long long>(m, 0));
    vector<vector<long long>> cost(n, vector<long long>(m, 0));
    vector<vector<long long>> path(n, vector<long long>(m, 0));
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    for (long long j = 0; j < m; j++) {
        cost[0][j] = matrix[0][j];
    }

    for (long long i = 1; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            if (m == 1) {
                cost[i][j] = cost[i - 1][j] + matrix[i][j];
                path[i][j] = 0;
            }else if (j == 0) {
//                cost[i][j] = min(cost[i-1][j], cost[i-1][j+1]) + matrix[i][j];
                if (cost[i - 1][j] < cost[i - 1][j + 1]) {
                    cost[i][j] = cost[i - 1][j] + matrix[i][j];
                    path[i][j] = 0;
                } else {
                    cost[i][j] = cost[i - 1][j + 1] + matrix[i][j];
                    path[i][j] = 1;
                }
            } else if (j == m - 1) {
//                cost[i][j] = min(cost[i-1][j], cost[i-1][j-1]) + matrix[i][j];
                if (cost[i - 1][j] < cost[i - 1][j - 1]) {
                    cost[i][j] = cost[i - 1][j] + matrix[i][j];
                    path[i][j] = 0;
                } else {
                    cost[i][j] = cost[i - 1][j - 1] + matrix[i][j];
                    path[i][j] = -1;
                }
            } else {
//                cost[i][j] = min(cost[i-1][j], min(cost[i-1][j+1], cost[i-1][j-1])) + matrix[i][j];
                long long mn = min(cost[i - 1][j], min(cost[i - 1][j + 1], cost[i - 1][j - 1]));
                if (cost[i - 1][j - 1] == mn) {
                    cost[i][j] = cost[i - 1][j - 1] + matrix[i][j];
                    path[i][j] = -1;
                } else if (cost[i - 1][j] == mn) {
                    cost[i][j] = cost[i - 1][j] + matrix[i][j];
                    path[i][j] = 0;
                } else {
                    cost[i][j] = cost[i - 1][j + 1] + matrix[i][j];
                    path[i][j] = 1;
                }
            }
        }
    }

//    cout << "\n";
//    for (long long i = 0; i < n; i++) {
//        for (long long j = 0; j < m; j++) {
//            cout << cost[i][j] << " ";
//        }
//        cout << "\n";
//    }
//    cout << "\n";
//    for (long long i = 0; i < n; i++) {
//        for (long long j = 0; j < m; j++) {
//            cout << path[i][j] << " ";
//        }
//        cout << "\n";
//    }
//    cout << "\n";


    vector<pair<long long, long long>> result(n);
    long long i = n - 1;
    long long last = cost[n-1][0];
    result[i].first = n - 1;
    result[i].second = 0;
    for (long long j = 1; j < m; j++) {
        if (cost[n-1][j] < last) {
            last = cost[n-1][j];
            result[i].first = n - 1;
            result[i].second = j;
        }
    }
    i--;

    for (i; i >= 0; i--) {
        result[i].first = i;
        result[i].second = result[i + 1].second + path[result[i + 1].first][result[i + 1].second];
    }

    cout << last << "\n";
    for (i = 0; i < n; i++) {
        cout << "(" << result[i].first + 1 << "," << result[i].second + 1 << ") ";
    }
    cout << "\n";

    return 0;
}