#include "../utils.cpp"
using namespace std;
/*
 * Ввести значение 2-х вещественных переменных а и b. Направить два
указателя на эти переменные. Если а>b, то с помощью указателя увеличить значение
переменной а на 3 и b уменьшить в 3 раза, в противном случае а уменьшить в 2 раза и b
увеличить на 3.
 */

int main() {
    double a = readDouble("Enter a:");
    double b = readDouble("Enter b:");;

    double *aPointer = &a;
    double *bPointer = &b;

    if (*aPointer > *bPointer) {
        *aPointer += 3.;
        *bPointer /= 3.;
    } else {
        *aPointer /= 2.;
        *bPointer += 3.;
    }
    cout << "a = " << *aPointer << endl << "b = " << *bPointer;

    return 0;
}
