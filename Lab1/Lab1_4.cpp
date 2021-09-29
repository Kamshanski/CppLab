#include "../utilities.cpp"

#include <functional>
using namespace std;
/*
Создать динамические массивы, используя указатели. Дан массив b (n) .
Переписать в массив C(n) отрицательные элементы массива b(n) умноженные на 4. (со
сжатием., без пустых элементов внутри) Затем упорядочить методом «выбора и
перестановки» по возрастанию новый массив.
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
    int bSize = readInt("Enter N:");

    double *b = new double[bSize];
    double *c = new double[bSize];

    int cSize = 0;
    for (int i = 0; i < bSize; i++) {
        b[i] = (rand() & 63) - 32;  //-32..31
        if (b[i] < 0) {
            c[cSize] = b[i] * 4;
            cSize++;
        }
    }
    if (cSize == 0) {
        cout << "No negative numbers in the inserted array";
    }
    cout << "Original array: " << joinToString(b, bSize) << endl;

    selectionSort(c, cSize, true, [](const int& a, const int& b) -> bool { return a > b;});

    cout << "Result array: " << joinToString(c, cSize, ", ",4) << endl;
    delete[] b;
    delete[] c;
    return 0;
}