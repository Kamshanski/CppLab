#include "../utilities.cpp"
#include "../sorting.cpp"
using namespace std;
/*
Создать динамические массивы, используя указатели. Дан массив b (n) .
Переписать в массив C(n) отрицательные элементы массива b(n) умноженные на 4. (со
сжатием., без пустых элементов внутри) Затем упорядочить методом «выбора и
перестановки» по возрастанию новый массив.
 */


int main() {
    int bSize = readInt("Enter N:");

    double *b = new double[bSize];
    double *c = new double[bSize];

    int cSize = 0;
    for (int i = 0; i < bSize; i++) {
        b[i] = (rand() & 63) - 32;  //-32..31
        if (b[i] < 0) {
            c[cSize] = b[i] * 4;
            cSize++;
        }
    }
    if (cSize == 0) {
        cout << "No negative numbers in the inserted array";
    }
    cout << "Original array: " << joinToString(b, bSize) << endl;

    selectionSort(c, cSize);

    cout << "Result array: " << joinToString(c, cSize, ", ",4) << endl;
    return 0;
}