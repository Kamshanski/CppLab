#include "../utils.cpp"
#include "../string_utils.cpp"
using namespace std;
/*
Образовать последовательность символов, включив в нее символы данной
последовательности, расположенные на четных позициях. (не использовать if) (не
использовать find, erase, substr…)
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

    for (int i = 0; i < input.size(); i+=2) {
        output += input[i];
    }

    wcout << output;
    return 0;
}