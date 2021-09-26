#include "../utilities.cpp"
#include "../string_utils.cpp"
using namespace std;
/*
Пользователь вводит текст. Вывести исходный текст, заменив в нем слово
«Pascal» на «C++». подсчитав их количество. Вычислить количество слов «компьютер»,
 */
int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wstring input = readWstring();
    // Компьютер Pascal C++ компьютер слово компьютер Pascal PascalPascalPaskalкомпьютер
    wstring strToCount = L"компьютер";
    wstring oldString = L"Pascal";
    wstring newString = L"C++";

    int computerCounter = 0;
    int index = 0;
    while (index < input.size()) {
        index = input.find(strToCount, index);
        if (index >= input.size())
            break;
        computerCounter++;
        index += strToCount.size();
    }

    int replacementCounter = replaceAllInString(input, oldString, newString);

    wcout << L"Слов 'компьютер' найдено: " << computerCounter << endl;
    wcout << L"Замен '" << oldString << L"' на '" << newString << L"' сделано: " << replacementCounter << endl;
    wcout << L"Итоговая строка: " << input;

    return 0;
}