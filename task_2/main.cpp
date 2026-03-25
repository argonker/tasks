#include "matrices.h"
#include <iostream>

int main() {
    std::cout << "MATRIX TESTS" << std::endl;
    
    // ТЕСТ 1: Конструктор размеров
    std::cout << "\nTEST 1: Matrix with dimensions" << std::endl;
    std::cout << "matrix(3,4)" << std::endl;
    Matrix m1(3, 4);
    std::cout << m1 << std::endl;
    
    // ТЕСТ 2: Конструктор из числа
    std::cout << "TEST 2: Matrix from double" << std::endl;
    std::cout << "matrix(3.14)" << std::endl;
    Matrix m2(3.14);
    std::cout << m2 << std::endl;

    // ТЕСТ 3: Конструктор матрица-строка
    std::cout << "TEST 3: Row matrix from array" << std::endl;
    double row_arr[] = {1.125, 2.236, 3.347};
    std::cout << "array = [1.125, 2.236, 3.347]; matrix(array, 3)" << std::endl;
    Matrix m3(row_arr, 3);
    std::cout << m3 << std::endl;

    // ТЕСТ 4: Конструктор матрица-столбец
    std::cout << "TEST 4: Column matrix from array" << std::endl;
    double col_arr[] = {-1.125, -2.236, -3.347};
    std::cout << "array = [-1.125, -2.236, -3.347]; matrix(3, array)" << std::endl;
    Matrix m4(3, col_arr);
    std::cout << m4 << std::endl;

    // ТЕСТ 5: Конструктор из строки
    std::cout << "TEST 5: Matrix from string" << std::endl;
    std::cout << "matrix(\"{{1,2,3},{4,5,6}}\")" << std::endl;
    Matrix m5("{{1,2,3},{4,5,6}}");
    std::cout << m5 << std::endl;
    
    // ТЕСТ 6: Единичная матрица
    std::cout << "TEST 6: Identity matrix" << std::endl;
    std::cout << "Matrix::identity(3)" << std::endl;
    Matrix I = Matrix::identity(3);
    std::cout << I << std::endl;
    
    // ТЕСТ 7: Диагональная матрица
    std::cout << "TEST 7: Diagonal matrix" << std::endl;
    double diag_vals[] = {2.73, 3.14, 6.67, -1.18};
    std::cout << "vals = [2.73, 3.14, 6.67, -1.18]; Matrix::diagonal(vals, 4)" << std::endl;
    Matrix D = Matrix::diagonal(diag_vals, 4);
    std::cout << D << std::endl;
    
    // ТЕСТ 8: rows() и columns()
    std::cout << "TEST 8: rows() and columns()" << std::endl;
    std::cout << "matrix(6,8)" << std::endl;
    Matrix m6(6, 8);
    std::cout << m6;
    std::cout << "rows() = " << m6.rows() << ", columns() = " << m6.columns() << "\n" << std::endl;

    // ТЕСТ 9: set() и get()
    std::cout << "TEST 9: set() and get()" << std::endl;
    std::cout << "matrix(2,3); set(0,0,10.5); set(0,2,20.5); set(1,2,30.5)" << std::endl;
    Matrix m7(2, 3);
    m7.set(0, 0, 10.5);
    m7.set(0, 2, 20.5);
    m7.set(1, 2, 30.5);
    std::cout << m7;
    std::cout << "get(0,2) = " << m7.get(0, 2) << "\n" << std::endl;

    // ТЕСТ 10: row() и column()
    std::cout << "TEST 10: row() and column()" << std::endl;
    std::cout << "matrix(\"{{1,2,3},{4,5,6},{7,8,9}}\")" << std::endl;
    Matrix test10("{{1,2,3},{4,5,6},{7,8,9}}");
    std::cout << test10;
    std::cout << "row(2):" << std::endl;
    std::cout << test10.row(2);
    std::cout << "column(1):" << std::endl;
    std::cout << test10.column(1) << std::endl;

    // ТЕСТ 11: Умножение на скаляр
    std::cout << "TEST 11: operator*=(double)" << std::endl;
    std::cout << "matrix(\"{{1,2},{3,4}}\") *= 2.5" << std::endl;
    Matrix s("{{1,2},{3,4}}");
    std::cout << "Before:\n" << s;
    s *= 2.5;
    std::cout << "After:\n" << s << std::endl;
    
    // ТЕСТ 12: Сложение
    std::cout << "TEST 12: operator+" << std::endl;
    std::cout << "matrix(\"{{1,2},{3,4}}\") + matrix(\"{{5,6},{7,8}}\")" << std::endl;
    Matrix a("{{1,2},{3,4}}");
    Matrix b("{{5,6},{7,8}}");
    Matrix c = a + b;
    std::cout << c << std::endl;
    
    // ТЕСТ 13: Вычитание
    std::cout << "TEST 13: operator-" << std::endl;
    std::cout << "matrix(\"{{1,2},{3,4}}\") - matrix(\"{{5,6},{7,8}}\")" << std::endl;
    Matrix d = a - b;
    std::cout << d << std::endl;
    
    // ТЕСТ 14: Унарный минус
    std::cout << "TEST 14: operator-()" << std::endl;
    std::cout << "-matrix(\"{{1,2},{3,4}}\")" << std::endl;
    Matrix e = -a;
    std::cout << e << std::endl;
    
    // ТЕСТ 15: Умножение матриц
    std::cout << "TEST 15: operator*(Matrix)" << std::endl;
    std::cout << "matrix(\"{{1,2,3},{4,5,6}}\") * matrix(\"{{7,8},{9,10},{11,12}}\")" << std::endl;
    Matrix A("{{1,2,3},{4,5,6}}");
    Matrix B("{{7,8},{9,10},{11,12}}");
    Matrix C = A * B;
    std::cout << C << std::endl;
    
    // ТЕСТ 16: Вертикальная конкатенация
    std::cout << "TEST 16: operator|" << std::endl;
    std::cout << "matrix(\"{{1,2,3},{4,5,6}}\") | matrix(\"{{7,8,9},{10,11,12}}\")" << std::endl;
    Matrix vert1("{{1,2,3},{4,5,6}}");
    Matrix vert2("{{7,8,9},{10,11,12}}");
    Matrix vert = vert1 | vert2;
    std::cout << vert << std::endl;
    
    // ТЕСТ 17: Горизонтальная конкатенация
    std::cout << "TEST 17: operator/" << std::endl;
    std::cout << "matrix(\"{{1,2},{3,4}}\") / matrix(\"{{5,6},{7,8}}\")" << std::endl;
    Matrix horiz1("{{1,2},{3,4}}");
    Matrix horiz2("{{5,6},{7,8}}");
    Matrix horiz = horiz1 / horiz2;
    std::cout << horiz << std::endl;
    
    // ТЕСТ 18: Сравнение
    std::cout << "TEST 18: operator== and operator!=" << std::endl;
    Matrix eq1("{{1,2},{3,4}}");
    Matrix eq2("{{1,2},{3,4}}");
    Matrix eq3("{{1,2},{3,5}}");
    std::cout << "eq1 == eq2: " << (eq1 == eq2) << std::endl;
    std::cout << "eq1 == eq3: " << (eq1 == eq3) << std::endl;
    std::cout << "eq1 != eq2: " << (eq1 != eq2) << std::endl;
    
    // ТЕСТ 19: Копирование
    std::cout << "\nTEST 19: Copy constructor" << std::endl;
    Matrix original("{{1,2,3},{4,5,6}}");
    Matrix copy(original);
    copy[0][0] = 100;
    std::cout << "Original:\n" << original;
    std::cout << "Copy (modified):\n" << copy << std::endl;
    
    // ТЕСТ 20: Ошибка сложения
    std::cout << "TEST 20: Error - dimension mismatch (+)" << std::endl;
    try {
        Matrix err1(2, 3);
        Matrix err2(3, 2);
        Matrix err3 = err1 + err2;
    } catch (const Matrix::MatrixError& e) {
        std::cerr << "Caught: " << e.what() << " (line " << e.getLine() << ")" << std::endl;
    }
    
    // ТЕСТ 21: Ошибка умножения
    std::cout << "\nTEST 21: Error - dimension mismatch (multiplication)" << std::endl;
    try {
        Matrix err1(2, 3);
        Matrix err2(2, 3);
        Matrix err3 = err1 * err2;
    } catch (const Matrix::MatrixError& e) {
        std::cerr << "Caught: " << e.what() << " (line " << e.getLine() << ")" << std::endl;
    }
    
    // ТЕСТ 22: Ошибка вертикальной конкатенации
    std::cout << "\nTEST 22: Error - dimension mismatch (|)" << std::endl;
    try {
        Matrix err1(2, 3);
        Matrix err2(3, 2);
        Matrix err3 = err1 | err2;
    } catch (const Matrix::MatrixError& e) {
        std::cerr << "Caught: " << e.what() << " (line " << e.getLine() << ")" << std::endl;
    }
    
    // ТЕСТ 23: Ошибка горизонтальной конкатенации
    std::cout << "\nTEST 23: Error - dimension mismatch (/)" << std::endl;
    try {
        Matrix err1(2, 3);
        Matrix err2(3, 2);
        Matrix err3 = err1 / err2;
    } catch (const Matrix::MatrixError& e) {
        std::cerr << "Caught: " << e.what() << " (line " << e.getLine() << ")" << std::endl;
    }
    
    // ТЕСТ 24: Ошибка индекса
    std::cout << "\nTEST 24: Error - index out of range" << std::endl;
    try {
        Matrix err(2, 2);
        err[5][5] = 10;
    } catch (const Matrix::MatrixError& e) {
        std::cerr << "Caught: " << e.what() << " (line " << e.getLine() << ")" << std::endl;
    }

    // ТЕСТ 25: Оператор +=
    std::cout << "\nTEST 25: operator+=" << std::endl;
    std::cout << "matrix(\"{{1,2},{3,4}}\") += matrix(\"{{5,6},{7,8}}\")" << std::endl;
    Matrix plus_eq("{{1,2},{3,4}}");
    std::cout << "Before:\n" << plus_eq;
    plus_eq += Matrix("{{5,6},{7,8}}");
    std::cout << "After:\n" << plus_eq << std::endl;

    // ТЕСТ 26: Оператор -=
    std::cout << "TEST 26: operator-=" << std::endl;
    std::cout << "matrix(\"{{10,20},{30,40}}\") -= matrix(\"{{1,2},{3,4}}\")" << std::endl;
    Matrix minus_eq("{{10,20},{30,40}}");
    std::cout << "Before:\n" << minus_eq;
    minus_eq -= Matrix("{{1,2},{3,4}}");
    std::cout << "After:\n" << minus_eq << std::endl;

    // ТЕСТ 27: Цепочка += и -=
    std::cout << "TEST 27: Chained += and -=" << std::endl;
    std::cout << "matrix(\"{{1,2},{3,4}}\") += matrix(\"{{1,1},{1,1}}\") -= matrix(\"{{1,0},{0,1}}\")" << std::endl;
    Matrix chain("{{1,2},{3,4}}");
    std::cout << "Start:\n" << chain;
    chain += Matrix("{{1,1},{1,1}}");
    std::cout << "After +=:\n" << chain;
    chain -= Matrix("{{1,0},{0,1}}");
    std::cout << "After -=:\n" << chain << std::endl;

    // ТЕСТ 28: Ошибка += с разными размерами
    std::cout << "TEST 28: Error - operator+= dimension mismatch" << std::endl;
    try {
        Matrix err1(2, 3);
        Matrix err2(3, 2);
        err1 += err2;
    } catch (const Matrix::MatrixError& e) {
        std::cerr << "Caught: " << e.what() << " (line " << e.getLine() << ")" << std::endl;
    }

    // ТЕСТ 29: Ошибка -= с разными размерами
    std::cout << "\nTEST 29: Error - operator-= dimension mismatch" << std::endl;
    try {
        Matrix err1(2, 3);
        Matrix err2(3, 2);
        err1 -= err2;
    } catch (const Matrix::MatrixError& e) {
        std::cerr << "Caught: " << e.what() << " (line " << e.getLine() << ")" << std::endl;
    }

    std::cout << "\nTESTS COMPLETED" << std::endl;
    return 0;
}