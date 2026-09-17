#include <quantmath/Matrix.h>

#include <stdexcept>

namespace quantmath {

// Constructor
Matrix::Matrix(
    std::initializer_list<std::initializer_list<double>> values
) {
    std::size_t init{};

    if (values.size() == 0) {
        throw std::invalid_argument("This matrix is empty");
    }
    else {
        init = values.begin()->size();
    }

    for (const auto& row : values) {

        if (row.size() != init) {
            throw std::invalid_argument(
                "All rows must be of same length"
            );
        }

        data.push_back(Vector(row));
    }
}


// Number of rows
std::size_t Matrix::rows() const {
    return data.size();
}


// Number of columns
std::size_t Matrix::columns() const {

    if (data.empty()) {
        return 0;
    }

    return data[0].size();
}


// Access / modify matrix element
double& Matrix::operator()(long long row, long long column) {

    long long row_position{row};
    long long column_position{column};

    if (row_position < 0) {
        row_position += static_cast<long long>(data.size());
    }

    if (column_position < 0) {
        column_position += static_cast<long long>(data[0].size());
    }

    if (
        row_position < 0 ||
        row_position >= static_cast<long long>(data.size()) ||
        column_position < 0 ||
        column_position >= static_cast<long long>(data[0].size())
    ) {
        throw std::out_of_range(
            "Matrix position does not exist"
        );
    }

    return data[row_position][column_position];
}


// Const matrix access
const double& Matrix::operator()(
    long long row,
    long long column
) const {

    long long row_position{row};
    long long column_position{column};

    if (row_position < 0) {
        row_position += static_cast<long long>(data.size());
    }

    if (column_position < 0) {
        column_position += static_cast<long long>(data[0].size());
    }

    if (
        row_position < 0 ||
        row_position >= static_cast<long long>(data.size()) ||
        column_position < 0 ||
        column_position >= static_cast<long long>(data[0].size())
    ) {
        throw std::out_of_range(
            "Matrix position does not exist"
        );
    }

    return data[row_position][column_position];
}


// Matrix addition
Matrix Matrix::operator+(const Matrix& other) const {

    Matrix result = *this;

    if (
        rows() != other.rows() ||
        columns() != other.columns()
    ) {
        throw std::invalid_argument(
            "Matrices must be of same dimension for addition"
        );
    }

    for (std::size_t i{0}; i < rows(); ++i) {
        result.data[i] += other.data[i];
    }

    return result;
}


// Matrix subtraction
Matrix Matrix::operator-(const Matrix& other) const {

    Matrix result = *this;

    if (
        rows() != other.rows() ||
        columns() != other.columns()
    ) {
        throw std::invalid_argument(
            "Matrices must be of same dimension for subtraction"
        );
    }

    for (std::size_t i{0}; i < rows(); ++i) {
        result.data[i] -= other.data[i];
    }

    return result;
}


// Scalar multiplication
Matrix Matrix::operator*(double scalar) const {

    Matrix result = *this;

    for (std::size_t i{0}; i < rows(); ++i) {
        result.data[i] = result.data[i] * scalar;
    }

    return result;
}


// Scalar division
Matrix Matrix::operator/(double scalar) const {

    Matrix result = *this;

    if (scalar == 0) {
        throw std::invalid_argument(
            "Cannot divide by 0"
        );
    }

    for (std::size_t i{0}; i < rows(); ++i) {
        result.data[i] = result.data[i] / scalar;
    }

    return result;
}


// Unary minus
Matrix Matrix::operator-() const {

    Matrix result = *this;

    for (std::size_t i{0}; i < rows(); ++i) {
        result.data[i] = -result.data[i];
    }

    return result;
}


// +=
Matrix& Matrix::operator+=(const Matrix& other) {
    *this = *this + other;
    return *this;
}


// -=
Matrix& Matrix::operator-=(const Matrix& other) {
    *this = *this - other;
    return *this;
}


// *=
Matrix& Matrix::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}


// /=
Matrix& Matrix::operator/=(double scalar) {
    *this = *this / scalar;
    return *this;
}

bool Matrix::operator==(const Matrix& other) const {

    if (rows() != other.rows() || columns() != other.columns()) {
        return false;
    }

    for (std::size_t i{0}; i < rows(); ++i) {
        if (data[i] != other.data[i]){
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Vector Matrix::operator*(const Vector& vec) const {

    if (columns() != vec.size()){
        throw std::invalid_argument("Cannot multiply these two");
    }

    Vector result{};

    for (std::size_t i{0}; i < rows(); ++i){
        result.append(data[i].dot(vec));
    }

    return result;
}

Vector Matrix::column(std::size_t index) const {

    if (index >= columns()) {
        throw std::out_of_range("Column index out of range");
    }

    Vector result{};

    for (size_t i{0}; i < rows(); ++i){
        result.append(data[i][index]);
    }

    return result;
}

// Matrix Matrix::operator*(const Matrix& other) const {
//     Matrix result = *this;

//     for (size_t i{0}; i < other.rows(); ++i) 

// }

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (size_t i{0}; i < matrix.rows(); ++i) {
        os << "[";
        for (size_t j{0}; j < matrix.columns(); ++j){
            os << matrix(i, j);

            if (j  < matrix.columns()-1){
                os << ", ";
            }
        }
        os << "]";
        os << std::endl;

    }
    return os;
}


} // namespace quantmath