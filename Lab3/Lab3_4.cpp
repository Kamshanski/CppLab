#include "../utils.cpp"
#include "../string_utils.cpp"
using namespace std;
/*
Задан текст из символов латинского алфавита, содержащий букву «а».
Напечатать все символы, расположенные за первой буквой «а» до ее второго
вхождения или до конца текста. (не использовать find )
 */
int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wstring input;
    //input = readWstring();
    wstring output;
    input = randomWstring(40, 0);
    wcout << "Input: " << input << endl;
    //getline(wcin, input);

    int i = 0;
    while (input[i++] != L'a') {
        if (i == input.size()) {
            wcout << L"Символ 'a' не был найден";
            return 0;
        }
    }

    while (input[i] != L'a') {
        output += input[i];
        if (i == input.size()) {
            wcout << L"Второй символ 'a' не был найден";
            return 0;
        }
        ++i;
    }

    wcout << L"Результат: " << output;

    return 0;
}