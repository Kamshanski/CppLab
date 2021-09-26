#include "../utilities.cpp"
using namespace std;
/*
Исходный текст набран с ошибками: между некоторыми словами по
несколько пробелов. Заменить в тексте подряд идущие пробелы одним пробелом. (не
использовать find)
 */
int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wstring input = readWstring();
    //    nmkwad  awkdnawkjdn     akwdmawod   lkawdm lkwadmalwkdm awkdm    .

    bool foundSpace = false;
    int spaceEnd = 0;
    int spaceCount = 0;
    for (int i = input.size() - 1; i > -1; --i) {
        auto c = input[i];
        if (c == L' ') {
            spaceCount++;
            if (!foundSpace) {
                spaceEnd = i;
            }
            foundSpace = true;
        } else {
            if (foundSpace) {
                input.replace(spaceEnd - spaceCount+1, spaceCount, L" ");
                spaceEnd = 0;
                spaceCount = 0;
            }
            foundSpace = false;
        }
    }
    if (foundSpace) {
        input.replace(0, spaceCount, L" ");
    }

    wcout << L"Итоговая стока: '" << input << "'";
    return 0;
}