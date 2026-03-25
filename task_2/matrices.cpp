#include "matrices.h"
#include <cstring>
#include <cstdlib>
#include <cctype>


Matrix::Matrix(int n, int m) {
    if (n <= 0 || m <= 0) {
        throw MatrixError("Matrix dimensions must be positive", __LINE__);
    }
    allocData(n, m); 
}

Matrix::Matrix(double val) {
    allocData(1, 1); 
    data[0] = val;  
}

Matrix::Matrix(const Matrix& other) {
    allocData(other.rows_cnt, other.columns_cnt); 
    memcpy(data, other.data, rows_cnt * columns_cnt * sizeof(double));
}

Matrix::Matrix(double* arr, int m) {
    if (m <= 0) {
        throw MatrixError("Row matrix must have positive length", __LINE__);
    }
    if (arr == nullptr) {
        throw MatrixError("Null pointer to array", __LINE__);
    }
    
    allocData(1, m);
    
    for (int j = 0; j < m; j++) {
        data[j] = arr[j];  
    }
}

Matrix::Matrix(int n, double* arr) {
    if (n <= 0) {
        throw MatrixError("Column matrix must have positive length", __LINE__);
    }
    if (arr == nullptr) {
        throw MatrixError("Null pointer to array", __LINE__);
    }
    
    allocData(n, 1);
    
    for (int i = 0; i < n; i++) {
        data[i * 1] = arr[i];  
    }
}

Matrix::Matrix(const char* str) {
    if (!str) {
        throw MatrixError("Null string pointer", __LINE__);
    }
    
    int rows = 0;
    int cols = -1;
    bool inRow = false;
    
    const char* p = str;  
    
    while (*p && isspace(*p)) 
        p++;  
    if (*p != '{') {
        throw MatrixError("Expected '{'", __LINE__);
    }
    p++;
    
    while (*p) {

        while (*p && isspace(*p)) p++;
        
        if (*p == '{') {  
            if (inRow) {
                throw MatrixError("Nested '{' not allowed", __LINE__);
            }
            inRow = true;
            p++;
            rows++;
            
            int colsInRow = 0;
            bool expectNumber = true;
            
            while (*p && *p != '}') {
                while (*p && (isspace(*p) || *p == ',')) p++;
                
                if (*p == '}') break;
                
                if (*p && *p != '}') {
                    char* endptr;
                    strtod(p, &endptr);
                    if (endptr == p) {
                        throw MatrixError("Expected number", __LINE__);
                    }
                    p = endptr;
                    colsInRow++;
                }
            }
            
            if (cols == -1) {
                cols = colsInRow;
            } else if (colsInRow != cols) {
                throw MatrixError("Inconsistent number of columns", __LINE__);
            }
            
            inRow = false;
            if (*p == '}') p++;
            
        } else if (*p == '}') {  
            p++;
            break;
        } else if (*p == ',') {  
            p++;
        } else {
            throw MatrixError("Unexpected character", __LINE__);
        }
    }
    
    if (rows == 0 || cols <= 0) {
        throw MatrixError("Invalid matrix format", __LINE__);
    }
    
    allocData(rows, cols);
    
    p = str;
    while (*p && *p != '{') p++;
    p++;  
    
    for (int i = 0; i < rows; i++) {
        while (*p && *p != '{') p++;
        if (*p != '{') {
            throw MatrixError("Missing '{'", __LINE__);
        }
        p++;  
        
        for (int j = 0; j < cols; j++) {
            while (*p && (isspace(*p) || *p == ',')) p++;
            
            char* endptr;
            double val = strtod(p, &endptr);
            if (endptr == p) {
                throw MatrixError("Failed to parse number", __LINE__);
            }
            p = endptr;
            
            data[i * cols + j] = val;
        }
        
        while (*p && *p != '}') p++;
        if (*p == '}') p++;
    }
}

Matrix Matrix::row(int r) const {
    if (r < 0 || r >= rows_cnt)
        throw MatrixError("Row index is out of range", __LINE__);
    Matrix result(1, columns_cnt);
    for (int i = 0; i < columns_cnt; i++) {
        result[0][i] = (*this)[r][i];
    }
    return result;
}

Matrix Matrix::column(int c) const {
    if (c < 0 || c >= columns_cnt)
        throw MatrixError("Column index is out of range", __LINE__);
    Matrix result(rows_cnt, 1);
    for (int i = 0; i < rows_cnt; i++) {
        result[i][0] = (*this)[i][c];
    }
    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows_cnt != other.rows_cnt || columns_cnt != other.columns_cnt)
        return false;
    for (int i = 0; i < rows_cnt*columns_cnt; i++) {
        if (data[i] != other.data[i])
            return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows_cnt != other.rows_cnt || columns_cnt != other.columns_cnt)
        throw MatrixError("Matrix dimensions do not match", __LINE__);
    for (int i = 0; i < rows_cnt*columns_cnt; i++)
        data[i] += other.data[i];
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(*this);
    result += other;
    return result;
}

Matrix Matrix::operator-() const {
    Matrix result(*this);

    for (int i = 0; i < rows_cnt*columns_cnt; i++) 
        result.data[i] = -result.data[i];
    return result;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows_cnt != other.rows_cnt || columns_cnt != other.columns_cnt)
        throw MatrixError("Matrix dimensions do not match", __LINE__);
    for (int i = 0; i < rows_cnt*columns_cnt; i++)
        data[i] -= other.data[i];
    return *this;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(*this);
    result -= other;
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (columns_cnt != other.rows_cnt)
        throw MatrixError("Matrix dimensions do not match", __LINE__);
    Matrix result(rows_cnt, other.columns_cnt);    
    
    for (int i = 0; i < rows_cnt; i++) 
        for (int j = 0; j < other.columns_cnt; j++) {
            double sum = 0;
            for (int k = 0; k < columns_cnt; k++)
                sum += (*this)[i][k] * other[k][j];
            result[i][j] = sum;
        }
    return result;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    *this = *this*other;
    return *this;
}

Matrix Matrix::operator|(const Matrix& other) const {
    if (columns_cnt != other.columns_cnt)
        throw MatrixError("Number of columns do not match", __LINE__);

    Matrix result(rows_cnt + other.rows_cnt, columns_cnt);
    for (int i = 0; i < rows_cnt; i++)
        for (int j = 0; j < columns_cnt; j++) 
            result[i][j] = (*this)[i][j];
    
    for (int i = 0; i < other.rows_cnt; i++)
        for (int j = 0; j < columns_cnt; j++) 
            result[rows_cnt + i][j] = other[i][j];
    
    return result;
}

Matrix Matrix::operator/(const Matrix& other) const {
    if (rows_cnt != other.rows_cnt)
        throw MatrixError("Number of rows do not match", __LINE__);

    Matrix result(rows_cnt, columns_cnt + other.columns_cnt);
    for (int i = 0; i < rows_cnt; i++)
        for (int j = 0; j < columns_cnt; j++) 
            result[i][j] = (*this)[i][j];
    
    for (int i = 0; i < rows_cnt; i++)
        for (int j = 0; j < other.columns_cnt; j++) 
            result[i][columns_cnt + j] = other[i][j];
    
    return result;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) 
        return *this;
    
    freeData();
    allocData(other.rows_cnt, other.columns_cnt); 
    memcpy(data, other.data, rows_cnt * columns_cnt * sizeof(double));
    
    return *this;
}

Matrix::~Matrix() {
    freeData();
}

Matrix Matrix::identity(int n) {
    if (n <= 0) {
        throw MatrixError("Identity matrix size must be positive", __LINE__);
    }
    
    Matrix result(n, n);
    for (int i = 0; i < n; i++) {
        result.data[i*n + i] = 1.0;
    }
    
    return result;
}

Matrix Matrix::diagonal(const double* vals, int n) {
    if (n <= 0) {
        throw MatrixError("Diagonal matrix size must be positive", __LINE__);
    }
    if (!vals) {
        throw MatrixError("Null pointer to diagonal values", __LINE__);
    }
    
    Matrix result(n, n);
    for (int i = 0; i < n; i++) {
        result.data[i*n + i] = vals[i];
    }
    
    return result;
}

void Matrix::set(int i, int j, double val) {
    if (i < 0 || i >= rows_cnt) {
        throw MatrixError("Row index out of range in set()", __LINE__);
    }
    if (j < 0 || j >= columns_cnt) {
        throw MatrixError("Column index out of range in set()", __LINE__);
    }
    
    data[i * columns_cnt + j] = val;
}

double Matrix::get(int i, int j) const {
    if (i < 0 || i >= rows_cnt) {
        throw MatrixError("Row index out of range in get()", __LINE__);
    }
    if (j < 0 || j >= columns_cnt) {
        throw MatrixError("Column index out of range in get()", __LINE__);
    }
    
    return data[i * columns_cnt + j];
}


Matrix Matrix::operator*(double scalar) const {
    Matrix result(*this); 
    
    for (int i = 0; i < rows_cnt * columns_cnt; i++) {
        result.data[i] *= scalar;
    }
    
    return result;
}

Matrix& Matrix::operator*=(double scalar) {
    for (int i = 0; i < rows_cnt * columns_cnt; i++) {
        data[i] *= scalar;
    }
    
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    os << "Matrix " << mat.rows_cnt << "x" << mat.columns_cnt << ":\n";
    
    for (int i = 0; i < mat.rows_cnt; i++) {
        os << "|";
        for (int j = 0; j < mat.columns_cnt; j++) {
            os.width(6);
            os.precision(2);
            os << std::fixed << mat.data[i * mat.columns_cnt + j];
            
            if (j < mat.columns_cnt - 1) {
                os << " ";
            }
        }
        os << "  |\n";
    }
    
    return os;
}
