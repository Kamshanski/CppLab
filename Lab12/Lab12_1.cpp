#include "../utils.cpp"
using namespace std;
/*
Дан файл вещественных чисел a.txt Найти количество элементов равных 5
и сумму положительных элементов.
 */
int main() {
    ifstream f("..\\Lab12\\a.txt");
    string s;
    int fives = 0;
    int positivesSum = 0;

    while (getline(f, s)) {
        int num = stoi(s);
        cout << num << ' ';
        if (num == 5) {
            fives++;
        }
        if (num > 0) {
            positivesSum += num;
        }
    }

    cout << endl << "Fives: " << fives << endl << "Sum of positives: " << positivesSum;
    f.close();
    return 0;
}