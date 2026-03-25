#include <iostream>
#include <exception>

class Matrix {
private:
    double* data;
    int rows_cnt;
    int columns_cnt;

    void freeData() {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
    }
    
    void allocData(int rows, int columns) {
        rows_cnt = rows;
        columns_cnt = columns;
        data = new double[rows * columns];

        for (int i = 0; i < rows * columns; i++)
            data[i] = 0.0;
    }
    

public:

    class MatrixError: public std::exception {
    private:
        const char* error_msg;
        int error_line;

    public:
        MatrixError(const char* msg, int line): error_msg(msg), error_line(line) {}

        virtual const char* what() const noexcept override {
            return error_msg;
        }

        int getLine() const {
            return error_line;
        }
    };


    Matrix(int n, int m);
    Matrix(double val);
    Matrix(const char* str);

    Matrix(double* r, int m);
    Matrix(int n, double* c);
    
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix row(int r) const;
    Matrix column(int c) const;

    Matrix& operator = (const Matrix& other);
    Matrix& operator += (const Matrix& other);
    Matrix operator + (const Matrix& other) const;
    Matrix& operator -= (const Matrix& other);
    Matrix operator - (const Matrix& other) const;
    bool operator != (const Matrix& other) const;
    bool operator == (const Matrix& other) const;
    Matrix operator -() const;
    Matrix operator*(double scalar) const;
    Matrix& operator*=(double scalar);
    Matrix operator*(const Matrix& other) const;
    Matrix& operator*=(const Matrix& other);
    Matrix operator|(const Matrix& other) const;
    Matrix operator/(const Matrix& other) const;
    
    static Matrix identity(int n);
    static Matrix diagonal(const double* vals, int n);
    
    int rows() const { 
        return rows_cnt;
    }
    int columns() const {
        return columns_cnt;
    }
    
    void set(int i, int j, double val);

    double get(int i, int j) const;

    class MatrixRow {
    private:
        double* rowData;
        int cols;

    public:
        MatrixRow(double* data, int c): rowData(data), cols(c) {}
        
        double& operator[](int j) {
            if (j < 0 || j >= cols) 
                throw MatrixError("Column index is out of range", __LINE__);
            return rowData[j];
        }
        
        const double& operator[](int j) const {
            if (j < 0 || j >= cols) {
                throw MatrixError("Column index is out of range", __LINE__);
            }
            return rowData[j];
        }
    };
    
    MatrixRow operator[](int i) {
        if (i < 0 || i >= rows_cnt) {
            throw MatrixError("Row index is out of range", __LINE__);
        }
        return MatrixRow(data + i*columns_cnt, columns_cnt);
    }
    
    const MatrixRow operator[](int i) const {
        if (i < 0 || i >= rows_cnt) {
            throw MatrixError("Row index is out of range", __LINE__);
        }
        return MatrixRow(data + i*columns_cnt, columns_cnt);
    } 
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};

std::ostream& operator<<(std::ostream& os, const Matrix& mat);