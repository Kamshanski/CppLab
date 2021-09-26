#include "../utilities.cpp"
using namespace std;
/*
Описать рекурсивную функцию для вычисления произведения Вычислить :
 */

double product(int step, int end) {
    return ((end == step) ? 1. : product(step + 1, end)) * (pow(step, 2) + log2(step));
}
int main() {

    cout << "product from 2 to 15: " << product(2, 15) << endl;
    return 0;
}