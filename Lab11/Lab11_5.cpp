#include "../utils.cpp"
using namespace std;
/*
Описать рекурсивную функцию для вычисления n –го члена ряда по
формуле
 */

double f(int n, int step = 1) {
    return sqrt(3*step + ((step == n) ? 0 : f(n, step+1)));
}
int main() {
    for (int i = 1; i < 5; ++i) {
        cout << "f(" << i <<  ") = " << f(i) << endl;
    }
    return 0;
}