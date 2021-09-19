#include "../utils.cpp"
using namespace std;
/*
Дана строка текста. Известно, что в ней есть один символ ‘*’, найти где он
находится и отсортировать по возрастанию элементы массива , расположенные перед
ним.
 */
int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wstring input = readWstring();
    // esjf5;iw4ef*effwfwe15.

    wstring needle = L"*";
    auto iter = search(input.cbegin(), input.cend(), needle.cbegin(), needle.cend());
    int offset = distance(input.cbegin(), iter);
    sort(input.begin(), input.begin() + offset);

    wcout << L"Результат: " << input;
    return 0;
}