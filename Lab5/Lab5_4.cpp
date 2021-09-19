#include "../utils.cpp"
#include "../string_utils.cpp"
using namespace std;
/*
Дан список фамилий сотрудников. Переписать в другой список только те
фамилии, в которых вторая буква ‘л’. Затем упорядочить по алфавиту второй список
методом «пузырька».
 */
int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
/*
Рубан
Иванов
Плющев
Киров
Клинов
Плисов
 */
    int inputSize = 6;
    wstring* input = new wstring[inputSize];
    for (int i = 0; i < inputSize; ++i) {
        input[i] = readWstring();
    }

    wstring* filtered = new wstring[inputSize];
    int filteredSize = 0;
    for (int i = 0; i < inputSize; ++i) {
        if (input[i][1] == L'л') {
            filtered[filteredSize++] = input[i];
        }
    }

    for (int i = 0; i < filteredSize - 1; ++i) {
        bool sorted = true;
        wstring min;
        for (int j = i; j < filteredSize - 1; ++j) {
            if (filtered[i] > filtered[i+1]) {
                wstring temp = filtered[i];
                filtered[i] = filtered[i+1];
                filtered[i+1] = temp;
                sorted = false;
            }
        }
        if (sorted) {
            break;
        }
    }

    wcout << L"Итоговый список:" << endl;
    for (int i = 0; i < filteredSize; ++i) {
        wcout << filtered[i] << endl;
    }

    return 0;
}