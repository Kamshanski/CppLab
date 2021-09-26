#include "../utilities.cpp"
#include "../matrixes.cpp"
#include "../sorting.cpp"
using namespace std;
/*
Создать динамические массивы, используя указатели. Дан двумерный
массив a, размером (nn). Упорядочить по убыванию главную диагональ.
 */
int main() {
    // input
    int n = readInt("Matrix _size:");
    if (n < 1) {
        cout << "Matrix _size cannot be less than 1";
        return 0;
    }

    // create matrix
    double **a = createCppMatrix(n, n);
    cout << "Original matrix:" << endl << joinToString(a, n, n) << endl;

    // extract main diagonal
    double *col = new double[n];
    for (int i = 0; i < n; ++i) {
        col[i] = a[i][i];
    }

    // sort it
    selectionSort(col, n, false);

    // replace matrix main diagonal with sorted one
    for (int i = 0; i < n; ++i) {
        a[i][i] = col[i];
    }

    cout << "Original matrix:" << endl << joinToString(a, n, n) << endl;

    return 0;
}