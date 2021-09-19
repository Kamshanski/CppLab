#include "../utils.cpp"
using namespace std;
/*
Организовать файл целых чисел. Вычислить количество отрицательных
компонентов файла расположенных на нечётных позициях.
 */
int main() {
    ifstream f("..\\Lab12\\a1.txt");
    string s;

    double count = 0;

    for (int i = 0; getline(f, s); ++i) {
        if (i & 1) {
            double num = stod(s);
            if (num < 0) {
                count++;
            }
        }
    }
    f.close();

    cout << count;
    return 0;
}