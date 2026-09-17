#pragma once

#include <vector>
#include <initializer_list>
#include <iosfwd>
#include <cstddef>

#include <quantmath/Vector.h>

namespace quantmath {

class Matrix {

private:
    std::vector<Vector> data;

public:
    Matrix(std::initializer_list<std::initializer_list<double>> values);

    Matrix(std::size_t rows, std::size_t columns, double value);
    static Matrix zeros(std::size_t rows, std::size_t columns);

    std::size_t rows() const;
    std::size_t columns() const;

    double& operator()(long long row, long long column);
    const double& operator()(long long row, long long column) const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;
    Matrix operator-() const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    Vector operator*(const Vector& vec) const;
    Vector column(std::size_t index) const;

    Matrix operator*(const Matrix& other) const;

    Matrix T() const;
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

}