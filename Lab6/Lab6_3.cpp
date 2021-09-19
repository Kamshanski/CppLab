#include "../utils.cpp"
using namespace std;
/*
)
Определить комбинированный (структурный) тип для представления
анкеты жителя, состоящей из его фамилии, названия города, где он проживает, и
городского адреса. Адрес состоит из полей: «улица», «дом», «квартира». Ввести
информацию по 10 жителям. Переписать из исходного массива в другой массив,
информацию только о тех жителях, фамилия которых начинается на указанную букву
(указанную букву вводит пользователь клавиатуры)

 */
struct Address {
    string street;
    int building;
    int apartment;
};
struct Person {
    string name;
    string city;
    Address addr;

    string toString() const {
        ostringstream o;
        o << name << " " << city << " " << addr.street << " " << addr.building << " " << addr.apartment;
        return o.str();
    }
};
int main() {
    /*
Nikita Moscow Selyonaya 15 5
Dima Tomsk Kirova 8 8
Nastya Kemerovo Lenina 7 17
Anna Barnaul Kantemirova 1 84
Fedor Blagoveshchensk Teatralnaya 7 78
Elena Vladivostok Uchebnaya 78 9
Maria Madrid Gonzales 8 17
Viktor Tomsk Severnaya 7 98
Evgenii Blagoveshchensk Lenina 74 8
Tanya Moscow Komsomolskaya 2 65
     */
    Person people[10];
    for (int i = 0; i < 10; ++i) {
        cin >> people[i].name >> people[i].city >> people[i].addr.street >> people[i].addr.building >> people[i].addr.apartment;
    }

    char firstLetter;
    cout << "\nEnter letter: ";
    cin >> firstLetter;

    auto* filtered = new Person[10];
    int filteredSize = 0;
    for (int i = 0; i < 10; ++i) {
        if (people[i].name[0] == firstLetter) {
            filtered[filteredSize++] = people[i];
        }
    }

    if (filteredSize > 0) {
        for (int i = 0; i < filteredSize; ++i) {
            cout << filtered[i].toString() << endl;
        }
    } else {
        cout << "No people with name that starts with " << firstLetter;
    }
    return 0;
}