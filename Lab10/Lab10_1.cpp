#include "../utils.cpp"
#include "../matrixes.cpp"
using namespace std;
/*
Дано два одномерных массива x и y одинаковой длины n. Описать функцию
типа void, которая присваивает третьему массиву z сумму векторов (массивов) x и y.
Применить функцию типа void для двух разных пар массивов а и b; с и d.
 */
void sum(double* x, double* y, double* z, int size) {
    for (int i = 0; i < size; ++i) {
        z[i] = x[i] + y[i];
    }
}

int main() {
    double* a = randomDoubleArray(4);
    double* b = randomDoubleArray(4);
    double* sum1 = randomDoubleArray(4);
    sum(a, b, sum1, 4);

    double* c = randomDoubleArray(7);
    double* d = randomDoubleArray(7);
    double* sum2 = randomDoubleArray(7);
    sum(c, d, sum2, 7);

    cout << "a: [" << joinToString(a, 4) << "]" << endl;
    cout << "b: [" << joinToString(b, 4) << "]" << endl;
    cout << "a + b = [" << joinToString(sum1, 4) << "]" << endl;
    cout << "c: [" << joinToString(c, 7) << "]" << endl;
    cout << "d: [" << joinToString(d, 7) << "]" << endl;
    cout << "c + d = [" << joinToString(sum2, 7) << "]" << endl;
    return 0;
}