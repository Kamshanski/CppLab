#include "../utils.cpp"
#include "../string_utils.cpp"
using namespace std;
/*
Задан список из десяти городов. (массив [.] string). Найти количество
городов, название которых заканчивается сочетанием букв «град» или “grad”.
 */
int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    /*
Petrograd
Петроград
Калиниград
Ярослвль
Tomsk
Yakutsk
Сталинград
Зеленоград
Вологда
Volgograd
     */
    wstring cities[10];
    int engCounter = 0;
    int rusCounter = 0;
    for (int i = 0; i < 10; ++i) {
        cities[i] = readWstring();
        size_t len = cities[i].size();
        if (len > 4) {
            if (cities[i].compare(len-4u,4,L"grad")==0) {
                engCounter++;
            } else if (cities[i].compare(len-4u, 4, L"град")==0) {
                rusCounter++;
            }
        }
    }

    wcout << L"Городов на 'град': " << rusCounter << endl;
    wcout << L"Городов на 'grad': " << engCounter << endl;

    return 0;

}