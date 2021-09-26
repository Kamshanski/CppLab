#include "../utilities.cpp"
#include "../matrixes.cpp"
using namespace std;
/*
Дано 3 квадратные матрицы А,В и С. Вычислить квадрат той матрицы (А*А), в
которой сумма элементов последней строки наибольшая. Вычисление суммы элементов
оформить в виде функции. Вычисление квадрата матрицы оформить в виде процедуры
 */

double sum(const double* array, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum;
}

void square(double **M, int size, double** R) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            R[i][j] = 0;
            for (int k = 0; k < size; k++)
                R[i][j] += M[i][k] * M[k][j];
        }
    }
}

int main() {
    int size = 5;
    double** A = createCppMatrix(size, size, 1);
    double** B = createCppMatrix(size, size, 2);
    double** C = createCppMatrix(size, size, 3);

    double sumA = sum(A[size-1], size); 
    double sumB = sum(B[size-1], size);
    double sumC = sum(C[size-1], size);
    
    double** sqr = createCppMatrix(size, size);
    double** M = (sumA > sumB && sumA > sumC) ? A : (sumB > sumC) ? B : C;
    square(M, size, sqr);
    

    cout << "A:\n" << joinToString(A, size, size) << endl;
    cout << "B:\n" << joinToString(B, size, size) << endl;
    cout << "C:\n" << joinToString(C, size, size) << endl;
    
    cout << "A last row sum: " << sumA << endl;
    cout << "B last row sum: " << sumB << endl;
    cout << "C last row sum: " << sumC << endl;
    
    cout << "Square of matrix " << ((sumA > sumB && sumA > sumC) ? "A" : (sumB > sumC) ? "B" : "C") << ":"
         << endl << joinToString(sqr, size, size, 5);
    
    return 0;
}