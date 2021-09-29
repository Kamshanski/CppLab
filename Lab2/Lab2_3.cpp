#include "../utilities.cpp"
#include "../matrixes.cpp"
#include <functional>
using namespace std;
/*
Создать динамические массивы, используя указатели. Дан двумерный
массив a, размером (nn). Упорядочить по возрастанию первый столбец матрицы
 */

template <typename T, typename Comparator>
void selectionSort(T *arr,
                   int size,
                   bool asc = true,
                   Comparator comparator = [](const T& a, const T& b) -> bool { return a > b; }){
    if (size < 2) {
        return;
    }

    for (int i = 0; i < size; ++i) {
        T extremum = arr[i]; // max for asc or extremum for desc
        int index = i;
        for (int j = i + 1; j < size; ++j) {
            if ((asc && comparator(extremum, arr[j])) || (!asc && !comparator(extremum, arr[j]))) {
                extremum = arr[j];
                index = j;
            }
        }
        T temp = arr[i];
        arr[i] = extremum;
        arr[index] = temp;
    }
}

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

    // extract first col
    double *col = new double[n];
    for (int i = 0; i < n; ++i) {
        col[i] = a[i][0];
    }

    // sort it
    selectionSort(col, n, true, [](const double & a, const double& b) -> bool { return a > b;});

    // replace matrix col with sorted one
    for (int i = 0; i < n; ++i) {
        a[i][0] = col[i];
    }

    cout << "Original matrix:" << endl << joinToString(a, n, n) << endl;
    delete[] col;
    return 0;
}