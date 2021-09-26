#include "../utilities.cpp"
using namespace std;
/*
Организовать текстовый файл. Преобразовать файл, удалив в нем лишние
пробелы.(создавая новый дополнительный файл)
 */
int main() {
    ifstream input("..\\Lab12\\lowercase.txt");
    ofstream output("..\\Lab12\\uppercase.txt");

    string s;
    while (getline(input, s)) {
        for (int i = 0; i < s.size() - 1; ++i) {
            if (s[i] == ' ' && s[i+1] == ' ') {
                continue;
            }
            output << s[i];
        }
        output << s[s.size() - 1];
    }
    input.close();
    output.close();
    return 0;
}