#include "../utilities.cpp"
using namespace std;
/*
Описать подходящую подпрограмму-функцию вычисления суммы элементов
массива

, для облегчения решения задачи: Дано 3 одномерных массива a,b,d длиной
10 элементов каждый. Вычислить
 */
double sum(const double * array, double size) {
    double sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum;
}

double nu(const double* a, const double* b, const double* d) {
    double dSum = sum(d, 10);
    if (dSum > 0) {
        double aSum = sum(a, 10);
        return aSum - dSum;
    } else {
        double bSum = sum(b, 10);
        return dSum / bSum;
    }
}

int main() {
    double* a = randomDoubleArray(10);
    double* b = randomDoubleArray(10);
    double* d = randomDoubleArray(10);

    cout << "a duration: " << joinToString(a, 10) << endl;
    cout << "b duration: " << joinToString(b, 10) << endl;
    cout << "d duration: " << joinToString(d, 10) << endl;

    cout << "nu = " << nu(a,b,d) << endl;
    return 0;
}