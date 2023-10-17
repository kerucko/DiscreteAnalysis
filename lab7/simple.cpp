#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<long long>>& matrix, long long i, long long j, long long res, long long& mn) {
    if (i == matrix.size() - 1) {
        if (mn == -1 || res + matrix[i][j] < mn) {
            mn = res + matrix[i][j];
        }
        return;
    }

    if (j == matrix[0].size() - 1) {
        dfs(matrix, i + 1, j - 1, res + matrix[i][j], mn);
        dfs(matrix, i + 1, j, res + matrix[i][j], mn);
    } else if (j == 0) {
        dfs(matrix, i + 1, j + 1, res + matrix[i][j], mn);
        dfs(matrix, i + 1, j, res + matrix[i][j], mn);
    } else {
        dfs(matrix, i + 1, j - 1, res + matrix[i][j], mn);
        dfs(matrix, i + 1, j, res + matrix[i][j], mn);
        dfs(matrix, i + 1, j + 1, res + matrix[i][j], mn);
    }
}

int main() {
    long long n, m;
    cin >> n >> m;

    vector<vector<long long>> matrix(n, vector<long long>(m, 0));

    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    long long mn = -1;
    for (long long j = 0; j < m; j++) {
        dfs(matrix, 0, j, 0, mn);
    }

    cout << mn << "\n";

    return 0;
}