#include "../utilities.cpp"
using namespace std;
/*
Описать рекурсивную функцию для вычисления n –го члена ряда по
формуле
 */

double R(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return 2*R(n-1) - 5*R(n-2) + pow(R(n-1), 2);
    }
}
int main() {
    for (int i = 0; i < 5; ++i) {
        cout << "R(" << i <<  ") = " << R(i) << endl;
    }
    return 0;
}