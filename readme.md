# Matrix Class Implementation

A C++ implementation of a matrix abstract data type with mathematical operations.

## Class Features

### Constructors
- `Matrix(int n, int m)` - creates n×m matrix filled with zeros
- `Matrix(double val)` - creates 1×1 matrix with given value
- `Matrix(double* arr, int m)` - creates 1×m row matrix from array
- `Matrix(int n, double* arr)` - creates n×1 column matrix from array
- `Matrix(const char* str)` - parses matrix from string format like "{{1,2},{3,4}}"
- `Matrix(const Matrix& other)` - copy constructor (deep copy)

### Static Methods
- `Matrix::identity(int n)` - returns n×n identity matrix
- `Matrix::diagonal(const double* vals, int n)` - returns n×n diagonal matrix

### Access Methods
- `int rows() const` - returns number of rows
- `int columns() const` - returns number of columns
- `void set(int i, int j, double val)` - sets element at position (i,j)
- `double get(int i, int j) const` - returns element at position (i,j)
- `Matrix row(int r) const` - returns r-th row as 1×n matrix
- `Matrix column(int c) const` - returns c-th column as n×1 matrix

### Operators

| Operator | Description |
|----------|-------------|
| `Matrix& operator=(const Matrix& other)` | assignment |
| `Matrix operator+(const Matrix& other) const` | matrix addition |
| `Matrix& operator+=(const Matrix& other)` | addition with assignment |
| `Matrix operator-(const Matrix& other) const` | matrix subtraction |
| `Matrix& operator-=(const Matrix& other)` | subtraction with assignment |
| `Matrix operator-() const` | unary minus (negation) |
| `Matrix operator*(const Matrix& other) const` | matrix multiplication |
| `Matrix& operator*=(const Matrix& other)` | multiplication with assignment |
| `Matrix operator*(double scalar) const` | scalar multiplication |
| `Matrix& operator*=(double scalar)` | scalar multiplication with assignment |
| `Matrix operator|(const Matrix& other) const` | vertical concatenation (rows) |
| `Matrix operator/(const Matrix& other) const` | horizontal concatenation (columns) |
| `bool operator==(const Matrix& other) const` | equality comparison |
| `bool operator!=(const Matrix& other) const` | inequality comparison |
| `MatrixRow operator[](int i)` | row access for element indexing (supports [i][j]) |
| `friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)` | stream output |

### Error Handling
- Nested exception class `MatrixError` derived from `std::exception`
- Includes line number information for debugging
- Thrown on invalid dimensions, out-of-range indices, and parsing errors

## Requirements
- C++11 or later

## Build
```bash
make
./matrix_test
```