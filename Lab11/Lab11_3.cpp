#include "../utilities.cpp"
using namespace std;
/*
Описать рекурсивную функцию для вычисления суммы первых k
слагаемых. Входные параметры функции: х – вещественное и k – целое
 */

double s(double x, int k) {
    return ((k == 1) ? 0 : s(x, k-1)) + (exp(-x*k) / (k+1));
}

int main() {
    double x = 2;
    for (int i = 1; i < 5; ++i) {
        cout << "s(" << x << ", " << i << ") = " << s(x, i) << endl;
    }
    return 0;
}