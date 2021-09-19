#include "../utils.cpp"
#include "../string_utils.cpp"
using namespace std;
/*
Задан список из десяти городов. (массив [.] string). Поменять местами
названия самого длинного и самого короткого слова
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
Димитровград
Вологда
Volgograd
    */
    wstring cities[10];
    size_t max = INT_MIN;
    size_t min = INT_MAX ;
    int maxIndex = 0;
    int minIndex = 0;
    for (int i = 0; i < 10; ++i) {
        cities[i] = readWstring();
        size_t len = cities[i].size();
       if (len > max) {
           max = len;
           maxIndex = i;
       } else if (len < min) {
           min = len;
           minIndex = i;
       }
    }

    wstring temp = cities[minIndex];
    cities[minIndex] = cities[maxIndex];
    cities[maxIndex] = temp;

    for (int i = 0; i < 10; ++i) {
        wcout << cities[i] << L":  \t"<< cities[i].size() <<endl;
    }

    return 0;
}