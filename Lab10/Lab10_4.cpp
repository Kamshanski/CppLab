#include "../utilities.cpp"
#include "../matrixes.cpp"
using namespace std;
/*
Даны три матрицы A(n*n), B(n*n), C(n*n) и три вектора x(n),y(n),z(n).
Вычислить u=Ax+By–Cz+Bx. Использовать функцию типа void для вычисления
произведения матрицы на вектор
 */
void square(double **M, int size, double** R) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            R[i][j] = 0;
            for (int k = 0; k < size; k++)
                R[i][j] += M[i][k] * M[k][j];
        }
    }
}

void multiply(double** A, int rowA, int colA, double** B,int rowB, int colB, double** C) {
    for (int i = 0; i < rowA; ++i){
        for (int j = 0; j < colB; ++j){
            C[i][j] = 0;
            for (int k = 0; k < colA; ++k)
                C[i][j] += A[i][k] * A[k][j];
        }
    }
}

void sum(double** A, double** B, int row, int col, double** C) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    int size = 3;
    double** A  = createCppMatrix(size, size, rand());
    double** B  = createCppMatrix(size, size, rand());
    double** C  = createCppMatrix(size, size, rand());
    double** x  = createCppMatrix(size, 1, rand());
    double** y  = createCppMatrix(size, 1, rand());
    double** z  = createCppMatrix(size, 1, rand());
    double** Ax     = createCppMatrix(size, 1, rand());
    double** By     = createCppMatrix(size, 1, rand());
    double** AxBy   = createCppMatrix(size, 1, rand());
    double** Cz     = createCppMatrix(size, 1, rand());
    double** u  = createCppMatrix(size, 1, rand());

    multiply(A, size, size, x, size, 1, Ax);
    multiply(B, size, size, y, size, 1, By);
    multiply(C, size, size, z, size, 1, Cz);
    sum(Ax, By, size, 1, AxBy);
    sum(AxBy, Cz, size, 1, u);

    cout << "A:" << endl << joinToString(A, size, size) << endl;
    cout << "B:" << endl << joinToString(B, size, size) << endl;
    cout << "C:" << endl << joinToString(C, size, size) << endl;
    cout << "x:" << endl << joinToString(x, size, 1) << endl;
    cout << "y:" << endl << joinToString(y, size, 1) << endl;
    cout << "z:" << endl << joinToString(z, size, 1) << endl;
    cout << "u:" << endl << joinToString(u, size, 1) << endl;

    return 0;
}