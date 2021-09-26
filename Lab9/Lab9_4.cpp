#include "../utilities.cpp"
using namespace std;
/*
Описать подпрограмму-функцию типа void с передачей параметров по ссылке
или указателю, определяющую середину отрезка (точку О(x0,y0)), заданного
координатами его концов (точки М1(x1,y1) M2(x2,y2)) следующим формулам:

Входные параметры: x1,y1,x2,y2 , выходные параметры (по
ссылке или указателю): x0,y0.
В главной программе для двух заданных отрезков выяснить, не совпадают ли их
середины.
 */
void middle(double &x1, double &y1, double& x2, double &y2, double& xM, double &yM) {
    xM = (x1 + x2) / 2.;
    yM = (y1 + y2) / 2.;
}

int main() {
    double x1_1 = 5, y1_1 = 0;
    double x1_2 = -5, y1_2 = 0;
    double x1_M, y1_M;
    middle(x1_1, y1_1, x1_2, y1_2, x1_M, y1_M);

    double x2_1 = 5, y2_1 = 5;
    double x2_2 = -5, y2_2 = -5;
    double x2_M, y2_M;
    middle(x2_1, y2_1, x2_2, y2_2, x2_M, y2_M);



    printf("(%.2f, %.2f):(%.2f, %.2f) -> (%.2f, %.2f)\n", x1_1, y1_1, x1_2, y1_2, x1_M, y1_M);
    printf("(%.2f, %.2f):(%.2f, %.2f) -> (%.2f, %.2f)\n", x2_1, y2_1, x2_2, y2_2, x2_M, y2_M);
    cout << "Line's centers are " << ((abs(x1_M - x2_M) < 0.01 && abs(y1_M - y2_M) < 0.01) ? "" : "not ") << "equal";

    return 0;
}