#include "../utilities.cpp"
#include "../sorting.cpp"
using namespace std;
/*
Описать функцию типа void, сортировки одномерного массива длинной N
по убыванию методом «Выбора и перестановки .max».. В главной программе Дано два
массива а и b. Отсортировать а и, b – по убыванию. Вывести квадрат наибольшего
элемента массива а, если второй наибольший (следующий за максимальным) в массиве
b равен 20.
 */


int main() {
    int N = 10;
    double* a = randomDoubleArray(N);
    double* b = randomDoubleArray(N);

    cout << "a: [" << joinToString(a, N) << "] -> ";
    selectionSort(a, N, false);
    cout << "[" << joinToString(a, N) << "]" << endl;

    cout << "b: [" << joinToString(b, N) << "] -> ";
    selectionSort(b, N, false);
    cout << "[" << joinToString(b, N) << "]" << endl;

    if (b[1] == 20) {
        cout << a[0] * a[0];
    }

    return 0;
}