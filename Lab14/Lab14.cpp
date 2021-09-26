#include <ostream>
#include <utility>
#include "../utilities.cpp"
#include "../sorting.cpp"
#include "Library14.cpp"
using namespace std;
/*
Составить программу, которая содержит текущую информацию о книгах в
библиотеке. Сведения о книгах включают:
 номер УДК;
 фамилию и инициалы автора;
 название;
 год издания;
 количество экземпляров данной книги в библиотеке.

Программа должна обеспечивать:
 начальное формирование данных обо всех книгах в библиотеке в виде
односвязного списка;
 добавление книги, отсортированной по автору;
 добавление книги перед указанной книгой;
 добавление книги после указанной книги.
 удаление выбранной книги.
 при выдаче каждой книги на руки вводится номер УДК, и программа
уменьшает значение количества книг на единицу или выдает сообщение о том, что
требуемой книги в библиотеке нет или требуемая книга находится на руках;
 при возвращении каждой книги вводится номер УДК, и программа
увеличивает значение количества книг на единицу;
 по запросу выдаются сведения о наличии книг в библиотеке.
 */

int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    Library14* library = new Library14(new WBookReader());

    for (int i = 0; i < 5; ++i) {
        Book* book = new Book(
                L"UDK_" + to_wstring(i),
                L"A" + to_wstring(rand() & 5),
                L"B" + to_wstring(i),
                rand() % 122 + 1900,
                rand() % 10);
        library->directInsert(book);
    }

    wostringstream o;
    o << L"Выберете номер действия:" << endl
        << L"1. Вывести все книги" << endl
        << L"2. Добавить книгу, отсортированной по автору (знать бы, что имел ввиду автор)" << endl
        << L"3. Добавить книгу после существующей книги" << endl
        << L"4. Добавить книгу перед существующей книгой" << endl
        << L"5. Удалить книгу" << endl
        << L"6. Выдать книгу" << endl
        << L"7. Вернуть книгу" << endl
        << L"8. Проверить наличие" << endl
        << L"0. Выход из программы";
    wstring infoMsg = o.str();
    wstring yourChoiceMsg = L"\nВаш выбор: ";

    wcout << infoMsg << endl;

// U78 A45 B12 4567 99 | U44 A66 B99 1256 4 | U65 A66 B65 2020 7
/*
UDK_99
Аркадий
B44
1234
15
 */

    bool mayExit = false;
    do {
        wchar_t command;
        wcout << yourChoiceMsg;
        while (true) {
            wcin >> command;
            if (command >= L'0' && command <= L'z') break;
        }
        switch (command) {
            case L'1': library->printAll(); break;
            case L'2': library->Library::insertSorted(); break;
            case L'3': library->Library::insertBefore(); break;
            case L'4': library->Library::insertAfter(); break;
            case L'5': library->Library::deleteBook(); break;
            case L'6': library->issueBook(); break;
            case L'7': library->returnBook(); break;
            case L'8': library->checkPresence(); break;
            case L'0': mayExit = true; break;
            default: wcout << L"Неизвестная команда. Попробуйте заново." << endl << infoMsg << endl;
        }
    } while (!mayExit);

    cout << "\nshutdown program\n";
    return 0;
}