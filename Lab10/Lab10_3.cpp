#include "../utilities.cpp"
#include "../sorting.cpp"
using namespace std;
/*
Создать комбинированный (структурный) тип для сведения о студентах
(Ф. И. О., курс, группа, номер зачетки, средний балл). Описать процедуру сортировки
по алфавиту по фамилии в одном таком комбинированном массиве. Пользователь задает
два комбинированных массива по N элементов в каждом.(для двух университетов).
Применить функцию два раза для заданных двух университетов. . (Так же будет уместно
описать процедуру ввода комбинированного массива и процедуру вывода.)
 */
struct Student {
    string fullName;
    int year;
    int id;
    double gpa;

    Student() {}
    Student(string fullName, int year, int id, double gpa) : fullName(std::move(fullName)), year(year), id(id), gpa(gpa) {}

    };
/*
S4 3 18467 4.2
S46 3 15724 7
S49 2 24464 6.3
S43 2 16827 8.2
S60 4 11942 9.6

S25 3 14604 9.2
S28 2 12382 9.3
S30 4 19895 1.9
S8 2 11538 7.2
S38 4 26299 6.8
S61 3 23811 0.4
S31 2 4664 7.4
S60 4 6868 5.4
 */
Student* readStudents(int size) {
    Student* students = new Student[size];
    for (int i = 0; i < size; ++i) {
        students[i] = Student(
                "S" + to_string(rand() & 63),
                (rand() % 4) + 1,
                rand(),
                ((rand() % 100) + 1) / 10.
        );
//        Student *s = new Student();
//        cin >> s->fullName >> s->year >> s->id >> s->gpa;
//        students[i] = *s;
    }
    return students;
}

int main() {
    for (int uniNum = 0; uniNum < 2; ++uniNum) {
        int size;
        cout << "University " << uniNum <<"\nEnter array length: ";
        cin >> size;

        Student* students = readStudents(size);
        cout << "Original array: " << endl << joinToString(students, size, ",\n", 40) << endl;

        selectionSort(students, size, true, [](const Student& s1, const Student& s2) -> bool {return s1.fullName > s2.fullName;});
        cout << "Sorted array: " << endl << joinToString(students, size, ",\n", 40) << endl;
    }

    return 0;
}