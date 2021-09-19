#include "../utils.cpp"
#include "../matrixes.cpp"
using namespace std;
/*
Создать динамические массивы, используя указатели. Дан двумерный
массив a, размером (nm). Найти минимальный элемент в каждой строке матрицы среди
положительных элементов.
 */
int main() {
    // input
    int n = readInt("Rows num:");
    if (n < 1) {
        cout << "Rows num cannot be less than 1";
        return 0;
    }

    int m = readInt("Columns num:");
    if (m < 1) {
        cout << "Cols num cannot be less than 1";
        return 0;
    }

    double** a = createCMatrix(n, m);

    for (int i = 0; i < n; i++) {
        double* row = a[i];

        // search min val
        double min = 0;
        for (int j = 0; j < m; ++j) {
            if (row[j] > 0 && (min > row[j] || min == 0)) {
                min = row[j];
            }
        }

        // print output
        cout << joinToString(row, m) << "  -> ";
        if (min > 0)
            cout << min;
        else
            cout << "No positive nums";
        cout << endl;
    }

    return 0;
}