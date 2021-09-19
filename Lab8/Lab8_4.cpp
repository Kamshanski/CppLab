#include "../utils.cpp"
using namespace std;
/*
Создать комбинированный (структурный) тип для списка CD-дисков
(название альбома, исполнитель, стиль, год выпуска, длительность, стоимость). Описать
функцию нахождения общей длительности всех музыки на всех дисках в коллекции.
Пользователь задает два комбинированных массива по N элементов в каждом.(для двух
коллекций). Применить функцию два раза для заданных двух коллекций. . (Так же будет
уместно описать процедуру ввода комбинированного массива и процедуру вывода.)
 */
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
struct CD {
    string name;
    string author;
    string style;
    int year;
    int duration;
    int cost;
};

int countDuration(CD* disks, int size) {
    int duration = 0;
    for (int i = 0; i < size; ++i) {
        duration += disks[i].duration;
    }
    return duration;
}

CD* readCds(int size) {
    CD* disks = new CD[size];
    for (int i = 0; i < size; ++i) {
        cin >> disks[i].name >> disks[i].author >> disks[i].style >> disks[i].year >> disks[i].duration
            >> disks[i].cost;
    }
    return disks;
}
int main() {

    int n;
    cout << "Enter array length: ";
    cin >> n;

    CD* disks1 = readCds(n);
    CD* disks2 = readCds(n);

    int duration1 = countDuration(disks1, n);
    int duration2 = countDuration(disks2, n);

    cout << "array1 duration: " << duration1 << endl;
    cout << "array2 duration: " << duration2 << endl;
    return 0;
}