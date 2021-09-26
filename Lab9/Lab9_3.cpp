#include "../utilities.cpp"
using namespace std;
/*
Описать функцию типа void с передачей параметров по ссылке или
указателю, заменяющую в тексте все малые буквы после точки и пробела на большие . В
главной программе Дано 2 строки символов S1 и S2. Применить функцию для строк
S1 и S2.
 */
void toUppercase(string& str) {
    for (int i = 0; i < str.size()-2; ++i) {
        if (str[i] == '.' && str[i+1] == ' ') {
            str[i+2] = toupper(str[i+2]);
        }
    }
}

int main() {
    string s1 = "word one. word two..word three";
    cout << "s1: '" << s1;
    toUppercase(s1);
    cout << "' -> '" << s1 << "'\n";

    string s2 = "low low. up. Up. hi.  bye";
    cout << "s2: '" << s2;
    toUppercase(s2);
    cout << "' -> '" << s2 << "'\n";

    return 0;
}