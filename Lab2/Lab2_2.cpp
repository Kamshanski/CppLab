#include "../utilities.cpp"
#include "../matrixes.cpp"
using namespace std;
/*
Создать динамические массивы, используя указатели. Дан двумерный
массив a, размером (nn)(или квадратная матрица а). Найти сумму номеров
минимального и максимального элементов её побочной диагонали
 */
int main() {
    // input
    int n = readInt("Matrix _size:");
    if (n < 1) {
        cout << "Matrix _size cannot be less than 1";
        return 0;
    }

    // create matrix
    double **matrix = createCppMatrix(n,n);

    cout << "Input matrix:" << endl << joinToString(matrix, n, n) << endl;

    // search min & max val on secondary diagonal and their indexes
    double min = matrix[0][n-1];
    double max = min;
    int maxIndex = n-1;
    int minIndex = maxIndex;
    for (int i = 1, j = n - 2; i < n; ++i, --j) {
        double item = matrix[i][j];
        if (min > item) {
            minIndex = i * n + j;
            min = item;
        } else if (max < item) {
            maxIndex = i * n + j;
            max = item;
        }
    }

    cout << "Min: " << min << " on " << minIndex << " index" << endl;
    cout << "Max: " << max << " on " << maxIndex << " index" << endl;
    cout << "Index sum: " << minIndex + maxIndex;
    return 0;
}