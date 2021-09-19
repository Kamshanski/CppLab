#include "../utils.cpp"
using namespace std;
/*
Описать рекурсивную функцию для вычисления n –го члена ряда 1, 2, 4, 8,….256
 */

int f(int n) {
    return (n == 0) ? 1 : f(n-1) << 1;
}
int main() {
    for (int i = 0; i < 11; ++i) {
        cout << "f(" << i << ") = " << f(i) << endl;
    }
    return 0;
}