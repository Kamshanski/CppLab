#include <ostream>
#include "../utilities.cpp"
#include "../sorting.cpp"
using namespace std;
/*
4Сформировать массив, каждый элемент которого имеет следующую структуру
студент= фамилия: string; номергр: string; оценка1: integer; оценка2: integer; оценка3:
integer;
Вывести на экран сообщение пользователю вида:
Выберете номер действия:
1. загрузить все данные из файла на экран;
2. ввести новые данные в файл
3. добавить данных в конец файла;
4. сортировка базы данных по алфавиту (по фамилии);
5. список задолжников;
6. *фамилию того, кто лучше всех сдал экзамены
7. определить средний балл по данному предмету
0--выход из программы;
Ваш выбор___
Основную программу организовать в виде цикла do – while «пока не выбран
пункт 0—выход».
Для вариантов выбора использовать оператор SWITCH - CASE.
Каждый пункт меню (действие) оформить виде метода (подпрограммы-функции
или подпрограммы-процедуры)
*и по желанию разместить их в отдельном модуле .
** (дополнительно) При выборе пунктов №1 №2№3 запросить имя и путь к
файлу для отображения (чтения) базы и осуществить
***проверку возможности открытия данного файла
 */

struct Student {
    wstring name;
    wstring group;
    int mark1, mark2, mark3;

    friend wostream &operator<<(wostream &os, const Student &student) {
        os << student.name <<  L" "
           << student.group << L" "
           << student.mark1 << L" "
           << student.mark2 << L" "
           << student.mark3;
        return os;
    }

    bool hasDebts() {
        return mark1 < 55 || mark2 < 55 || mark3 < 55;
    }
};

wstring FILE_PATH = L"..\\Lab13\\students.txt";

Student* students = nullptr;
int size = 0;

wfstream* openFile() {
    return new wfstream(asString(FILE_PATH));
}

void closeFile(wfstream* f) {
    if (f != nullptr) {
        f->close();
        delete f;
    }
}

void clearFile() {
    wofstream(asString(FILE_PATH), wios::out | wios::trunc).close();
}

void readAll() {
    wfstream* f = openFile();
    size = 0;
    while (!f->eof()) {
        Student *s = &students[size++];
        *f >> s->name >> s->group >> s->mark1 >> s->mark2 >> s->mark3;
    }
    closeFile(f);
}


Student readStudent() {
    wcout << L"Введите: фамилия группа оценка1 оценка2 оценка3" << endl;
    Student s;
    wcin >> s.name >> s.group >> s.mark1 >> s.mark2 >> s.mark3;
    return s;
}

void saveStudents() {
    clearFile();
    wfstream* f = openFile();
    for (int i = 0; i < size; ++i) {
        *f << students[i].name  << " "
           << students[i].group << " "
           << students[i].mark1 << " "
           << students[i].mark2 << " "
           << students[i].mark3;
        if (i != size - 1) {
            *f << endl;
        }
    }
    closeFile(f);
}

void printAll() {
    for (int i = 0; i < size; ++i) {
        wcout << setw(3) << i << L") " << students[i] << endl;
    }
}

void insertFirst() {
    Student s = readStudent();

    size++;
    for (int i = size; i > 0; --i) {
        students[i] = students[i-1];
    }
    students[0] = s;

    saveStudents();
}

void insertLast() {
    Student s = readStudent();
    students[size++] = s;
    saveStudents();
}

void sortDb() {
    selectionSort(students, size, true, [](const Student& s1, const Student& s2) -> bool {
        return s1.name > s2.name;
    });
    saveStudents();
    printAll();
}

void printDebtors() {
    for (int i = 0; i < size; ++i) {
        if (students[i].hasDebts()) {
            wcout << students[i] << endl;
        }
    }
}

void printBest() {
    Student max[3];
    int mark[3];
    for (int i = 0; i < size; ++i) {
        if (mark[0] < students[i].mark1) {
            mark[0] = students[i].mark1;
            max[0] = students[i];
        }
        if (mark[1] < students[i].mark2) {
            mark[1] = students[i].mark2;
            max[1] = students[i];
        }
        if (mark[2] < students[i].mark3) {
            mark[2] = students[i].mark3;
            max[2] = students[i];
        }
    }
    for (int i = 0; i < 3; ++i) {
        wcout << L"Лучший по предмету " << i << L": " << max[i] << endl;
    }
}

void printMeanMark() {
    int subject;
    wcout << L"Введите номер предмета (1, 2 или 3): ";
    wcin >> subject;

    int sum = 0;
    for (int i = 0; i < size; ++i) {
        switch (subject) {
            case 1: sum += students[i].mark1; break;
            case 2: sum += students[i].mark2; break;
            case 3: sum += students[i].mark3; break;
            default: break;
        }
    }
    double mean = ((double) sum) / size;
    wcout << L"Средняя оценка: " << mean << endl;
}

int main() {
    setlocale( LC_ALL , "russian_russia.866" );
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wostringstream o;
    o << L"Выберете номер действия:" << endl
        << L"1. загрузить все данные из файла на экран" << endl
        << L"2. ввести новые данные в файл" << endl
        << L"3. добавить данных в конец файла" << endl
        << L"4. сортировка базы данных по алфавиту (по фамилии)" << endl
        << L"5. список задолжников" << endl
        << L"6. фамилия того, кто лучше всех сдал экзамены" << endl
        << L"7. определить средний балл по данному предмету" << endl
        << L"0. выход из программы";
    wstring infoMsg = o.str();
    wstring yourChoiceMsg = L"\nВаш выбор: ";

    students = new Student[100];
    readAll();

    wcout << infoMsg << endl;

    bool mayExit = false;
    do {
        wcout << yourChoiceMsg;
        wchar_t command;
        while (true) {
            wcin >> command;
            if (command >= L'0' && command <= L'z') break;
        }
        wcout << L'\n';

        switch (command) {
            case L'1': printAll(); break;
            case L'2': insertFirst(); break;
            case L'3': insertLast(); break;
            case L'4': sortDb(); break;
            case L'5': printDebtors(); break;
            case L'6': printBest(); break;
            case L'7': printMeanMark(); break;
            case L'0': mayExit = true; break;
            default: wcout << L"Неизвестная команда. Попробуйте заново." << endl << infoMsg << endl;
        }
    } while (!mayExit);

    cout << "\nshutdown program\n";
    return 0;
}