#include "../utils.cpp"
using namespace std;
/*
Описать 2 указателя на логический тип. Выделить для них динамическую
память. Присвоить значения true и false в выделенную память.
 */
int main() {
    bool *a;
    bool *b;

    a = new bool;
    b = new bool;

    *a = true;
    *b = false;

    cout << "a = " << *a << "; b = " << *b << endl;

    return 0;
}