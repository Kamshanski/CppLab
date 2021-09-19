#include "../utils.cpp"
#include "../string_utils.cpp"
using namespace std;
/*
Даны две строки текста. Определить сколько раз встречается каждый
символ первой строки во второй строке. Например: Str1 : “xyz”; Str2: “x a d c x y x w” .
Тогда “х” – встречается 3 раза “y”- встречается 1 раз, “z”- встречается 0 раз. Далее
заменить все слова «компьютер» на слова «ПК» .
 */
// https://stackoverflow.com/questions/3136520/determine-if-map-contains-a-value-for-a-key
// https://stackoverflow.com/questions/26281979/c-loop-through-map
int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wstring str1 = readWstring();
    wstring str2 = readWstring();
    /*
987 к
111222333444555666777888999компьютеркомпьютер999
     */

    map<wchar_t, int> counter;

    // add all chars of str1 to counter map
    for (int i = 0; i < str1.size(); ++i) {
        counter[str1[i]] = 0;
    }

    for (int i = 0; i < str2.size(); ++i) {
        auto c = str2[i];
        if (counter.count(c)) {
            counter[c]++;
        }
    }

    for (auto const& entity: counter) {
        wcout << "'" << entity.first<< "': " << entity.second << endl;
    }


    wstring oldString = L"компьютер";
    wstring newString = L"ПК";

    replaceAllInString(str1, oldString, newString);
    replaceAllInString(str2, oldString, newString);

    wcout << "Str 1: "<< str1 << endl;
    wcout << "Str 2: "<< str2 << endl;
    return 0;
}