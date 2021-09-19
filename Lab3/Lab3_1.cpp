#include "../utils.cpp"
#include "../string_utils.cpp"
using namespace std;
/*
Дан текст. Опередить в каких позициях в нем встречаются символы «;».(не
использовать find, erase, substr…) ( другими словами : Вывести на экран номера
позиций в которых встречается символ «;»)
 */
int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    // read string
    wstring input;
    //input = readWstring();
    input = randomWstring(40, 0);
    wcout << "Input: " << input << endl;

    // search for semicolons
    int* indexes = new int[input.size()];
    int size = 0;
    for (int i = 0; i < input.size(); ++i) {
        auto c = input[i];
        if (c == L';') {
            indexes[size] = i;
            size++;
        }
    }

    // print result
    if (size == 0) {
        wcout << "Semicolons were not found";
    } else {
        wcout << "Semicolons on: " << asWstring(joinToString(indexes, size));
    }

    //awdвлфць;цврфовр; вц;;;
    return 0;
}