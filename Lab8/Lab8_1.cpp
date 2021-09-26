#include "../utilities.cpp"
using namespace std;
/*
Оформить функцию поиска количества нулевых элементов массива. В
главной программе дано 3 одномерных массива arr1,arr2,arr3 длиной 10 элементов
каждый. Применить функцию для каждого из 3-х заданных массивов. (в функции не
должно быть операторов ввода или вывода)
 */
int countZeros(int* array, int size) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (array[i] == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr1[10], arr2[10], arr3[10];
    for (int i = 0; i < 10; ++i) {
        arr1[i] = (rand() & 7) - 4; //-4..3
        arr2[i] = (rand() & 7) - 4;
        arr3[i] = (rand() & 7) - 4;
    }
    cout << "Arr1 [" << joinToString(arr1, 10, ", ", 2) << "] has " << countZeros(arr1, 10) << " zeros" << endl;
    cout << "Arr2 [" << joinToString(arr2, 10, ", ", 2) << "] has " << countZeros(arr2, 10) << " zeros" << endl;
    cout << "Arr3 [" << joinToString(arr3, 10, ", ", 2) << "] has " << countZeros(arr3, 10) << " zeros" << endl;

    return 0;
}