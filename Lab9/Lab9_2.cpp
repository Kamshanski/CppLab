#include "../utilities.cpp"
using namespace std;
/*
Реализовать функцию типа void с передачей параметров-результатов
по ссылке. Функция вычисляет характеристики равнобедренной трапеции по заданным
двум основаниям a,b и высоте h. Выходные результаты функции Характеристики
равнобедренной трапеции – это периметр, и площадь s= ½ (a +b) h..В главной
программе задано две равнобедренные трапеции . Найти их характеристики, вызвав
функцию 2 раза
 */

void trapezoidArea(double& a, double& b, double& h, double& area) {
    area = (a+b) * h / 2.;
}
int main() {
    double a, b, h, area;
    for (int i = 0; i < 3; ++i) {
        a = rand() & 63 - 32;
        b = rand() & 63 - 32;
        h = rand() & 63 - 32;
        trapezoidArea(a, b, h, area);
        cout << "(" << a << " + " << b << ") * " << h << " / 2 = " << area << endl;
    }
    return 0;
}