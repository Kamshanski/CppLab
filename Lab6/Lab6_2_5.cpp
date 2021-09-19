#include "../utils.cpp"
using namespace std;
/*
Определить комбинированный (структурный) тип, описывающий
окружность и состоящий из двух полей: «радиус» и «центр». Поле «центр» в свою
очередь состоит еще из двух полей: «координата X» и «координата Y». Ввести
информацию по 10 окружностям. Вывести координаты центра окружности, чей радиус
самой маленький

 Определить комбинированный (структурный) тип, описывающий
окружность и состоящий из двух полей: «радиус» и «центр». Поле «центр» в свою
очередь состоит еще из двух полей: «координата X» и «координата Y». Ввести
информацию по 10 окружностям. Вывести радиус окружности, чей центр расположен
ближе всего к оси OX(оси абсцисс). Затем вывести информацию, отсортированную по
возрастанию радиуса окружности. (рационально переставлять все поля структуры разом
)
 */

struct Point {
    int x, y;
};

struct Circle {
    Point center;
    int radius;

    string toString() const {
        ostringstream o;
        o << "[" << center.x << ", " << center.y << "] " << radius;
        return o.str();
    }
};
int main() {
    /*
X Y R
1 2 3
4 5 6
-7 8 99
3 2 10
-6 5 44
9 8 7
6 5 45
-77 5 1
41 2 8
4 5 16
     */
    Circle items[10];
    for (int i = 0; i < 10; ++i) {
        cin >> items[i].center.x >> items[i].center.y >> items[i].radius;
    }
    sort(items, items+10,
         [](const Circle& a, const Circle& b) -> bool {
             return (abs(a.radius) < abs(b.radius));
         });
    cout << "Circle with the smallest radius: " << items[0].toString() << endl;

    sort(items, items+10,
         [](const Circle& a, const Circle& b) -> bool {
             return (abs(a.center.x) < abs(b.center.x));
         });
    cout << "Circle with the closest to OX center: " << items[0].toString() << endl;


    return 0;
}