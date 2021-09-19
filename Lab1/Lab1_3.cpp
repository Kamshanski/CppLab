#include "../utils.cpp"
using namespace std;
/*
Создать динамические массивы, используя указатели. Дан массив p(n).
Каждый положительный элемент в нем возвести в квадрат. Остальные элементы
оставить прежними.
 */
int main() {
    int arraySize = readInt("Enter N:");

    double *inputArray = new double[arraySize];
    double *outputArray = new double[arraySize];

    double *p = &(inputArray[0]);
    for (int i = 0; i < arraySize; i++) {
        *p = (rand() & 63) - 32;  //-32..31
        outputArray[i] = (*p > 0) ? *p * *p : *p;
        p++;
    }
    cout << "output:" << endl;
    for (int i = 0; i < arraySize; i++) {
        cout << inputArray[i] << "\t->\t" << outputArray[i] << endl;
    }


    return 0;
}