#include <iostream>
#include <vector>

using namespace std;

vector<vector<double>> matrixMatrixMultiplication(vector<vector<double>>& matrix1, vector<vector<double>>& matrix2) {
    int matrix1Rows = matrix1.size();
    int matrix1Columns = matrix1[0].size();
    int matrix2Rows = matrix2.size();
    int matrix2Columns = matrix2[0].size();

    vector<vector<double>> result(matrix1Rows, vector<double>(matrix2Columns, 0));

    for (int i = 0; i < matrix1Rows; i++) {
        for (int j = 0; j < matrix2Columns; j++) {
            for (int k = 0; k < matrix1Columns; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

int main() {
    vector<vector<double>> matrix1 = {{1, 2, 3}, {4, 5, 6}};
    vector<vector<double>> matrix2 = {{7, 8}, {9, 10}, {11, 12}};

    vector<vector<double>> result = matrixMatrixMultiplication(matrix1, matrix2);

    cout << "Result: " << endl;
    for (const auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
