#include "../utils.cpp"
using namespace std;
/*
Определить структурный тип, описывающий музыкальные CD-диски
(название альбома, исполнитель, стиль, год выпуска, длительность, стоимость).
Заполнить структурный массив 10-ю записями. Переписать из исходного массива в
другой массив, информацию только о тех CD-дисках, название альбома которых
начинается на сочетание букв (3 - 4) введенных пользователем. Затем новый массив
отсортировать по стилю по алфавиту. (рационально переставлять все поля структуры
разом )
 */

struct CD {
    string name;
    string author;
    string style;
    int year;
    int duration;
    int cost;

    string toString() const {
        ostringstream o;
        o << name << " " << author << " " << style << " " << year << " " << duration << "m " << cost << "$";
        return o.str();
    }
};

int main() {
    /*
Album0 Viktor Style1 2021 55 41
Album1 Vladimir Style1 2018 52 51
Album2 Elena Style1 2020 72 51
Album3 Anna Style1 2020 72 50
Album4 Vladimir Style4 2020 72 54
Album5 Vladislav Style3 2019 24 38
Album6 Yaroslav Style2 2021 46 44
Album7 Aleksandr Style2 2021 46 24
Album8 Dmitii Style2 2021 46 24
Album9 Natalya Style3 2021 45 21
     */
    CD disks[10];
    for (int i = 0; i < 10; ++i) {
        cin >> disks[i].name >> disks[i].author >> disks[i].style >> disks[i].year >> disks[i].duration >> disks[i].cost;
    }

    string query;
    cout << "\nEnter author search query: ";
    cin >> query;

    auto* filtered = new CD[10];
    int filteredSize = 0;
    for (int i = 0; i < 10; ++i) {
        if (disks[i].author.compare(0, query.size(), query) == 0) {
            filtered[filteredSize++] = disks[i];
        }
    }

    if (filteredSize > 0) {
        sort(filtered, filtered + filteredSize,
             [](const CD& a, const CD& b) -> bool {
                 return (a.style < b.style);
             });

        for (int i = 0; i < filteredSize; ++i) {
            cout << filtered[i].toString() << endl;
        }
    } else {
        cout << "No people with name that starts with " << query;
    }


    return 0;
}