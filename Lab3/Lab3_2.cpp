#include "../utils.cpp"
using namespace std;
/*
Даны 3 слова - ваши Имя, Отчество, Фамилия в 3-х разных переменных. =
Образовать новую символьную переменную, хранящую полностью «имя отчество
фамилию». (использовать склейку «+»)(не использовать find, erase, substr…)
 */
int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    // read string
    wstring lastName = L"Рубан";
    wstring firstName = L"Евгений";
    wstring fathersName = L"Павлович";

    wstring name = lastName + L' ' + firstName + L" " + fathersName;
    wcout << name;

    return 0;
}