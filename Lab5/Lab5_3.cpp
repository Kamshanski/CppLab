#include "../utilities.cpp"
#include "../string_utils.cpp"
using namespace std;
/*
Задан список из десяти городов. (массив [.] string). Подсчитать
количество названий, в которых есть ровно по 3 буквы «о».
 */
int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

/*
Торонто
Петроград
Калиниград
Ярослвль
Вологодск
Новгород
Сталинград
Димитровград
Вологда
Коломна
    */
    wstring cities[10];
    int cityCounter = 0;
    for (int i = 0; i < 10; ++i) {
        cities[i] = readWstring();
        size_t len = cities[i].size();
        int index = 0;
        int counter = 0;
        while (true) {
            index = cities[i].find(L'о', index);
            if (index == string::npos) {
                break;
            }
            index++;
            counter++;
        }
        if (counter == 3) {
            cityCounter++;
        }
    }

    wcout << L"Города с тремя 'o': "<< cityCounter <<endl;

    return 0;
}