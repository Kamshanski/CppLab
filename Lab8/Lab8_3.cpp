#include "../utilities.cpp"
#include "../string_utils.cpp"
using namespace std;
/*
Описать функцию, вычисляющую количество цифр в тексте. В главной
программе дано 2 строки символов S1 и S2. Выяснить, совпадает ли количество цифр в
этих текстах, используя функцию
 */
int countDigits(string& str) {
    int counter = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            counter++;
        }
    }
    return counter;
}


int main() {
    string s1 = randomString(15);
    string s2 = randomString(15);

    int digits1 = countDigits(s1);
    int digits2 = countDigits(s2);

    cout << "s1 '" << s1 << "'. Digits: " << digits1 << endl;
    cout << "s2 '" << s2 << "'. Digits: " << digits2 << endl;
    cout << "Digits nums are " << ((digits1 != digits2) ? "not " : "") << "equal" << endl;
    return 0;
}