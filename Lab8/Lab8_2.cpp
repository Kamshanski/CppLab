#include "../utils.cpp"
using namespace std;
/*
Оформить функцию поиска минимального элемента среди положительных
в одномерном массиве, В главной программе Дано 4 одномерных массива a,b,c,d
длиной 10 элементов каждый. применить функцию для каждого из 4-х заданных
массивов. найти сумму найденных минимальных элементов. (в функции не должно быть
операторов ввода или вывода)
 */
int countMinPositive(int* array, int size) {
    int minPositive = -1;
    for (int i = 0; i < size; ++i) {
        if (array[i] > 0 && (minPositive > array[i] || minPositive < 0)) {
            minPositive = array[i];
        }
    }
    return minPositive;
}

int main() {
    int a[10], b[10], c[10], d[10];
    for (int i = 0; i < 10; ++i) {
        a[i] = (rand() & 63) - 32; //-4..3
        b[i] = (rand() & 63) - 32;
        c[i] = (rand() & 63) - 32;
        d[i] = (rand() & 63) - 32;
    }
    int aMin = countMinPositive(a, 10);
    int bMin = countMinPositive(b, 10);
    int cMin = countMinPositive(c, 10);
    int dMin = countMinPositive(d, 10);

    cout << "a [" << joinToString(a, 10) << "]. Min positive: " << aMin << endl;
    cout << "b [" << joinToString(b, 10) << "]. Min positive: " << bMin << endl;
    cout << "c [" << joinToString(c, 10) << "]. Min positive: " << cMin << endl;
    cout << "d [" << joinToString(d, 10) << "]. Min positive: " << dMin << endl;

    cout << "Sum of min vals: " <<  aMin + bMin + cMin + dMin << endl;

    return 0;
}