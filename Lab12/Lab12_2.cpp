#include "../utilities.cpp"
using namespace std;
/*
Дано 2 файла вещественных чисел а1.txt и а2.txt. Найти сумму
положительных элементов в двух файлов.
 */
int main() {
    fstream f[] {fstream("..\\Lab12\\a1.txt"), fstream("..\\Lab12\\a2.txt")};
    string s;
    double sum = 0;
    for (int i = 0; i < 2; ++i) {
        while (getline(f[i], s)) {
            double num = stod(s);
            cout << num << ' ';
            if (num > 0) {
                sum += num;
            }
        }
        cout << endl;
        f[i].close();
    }
    cout << "Sum: " << sum;

    return 0;
}