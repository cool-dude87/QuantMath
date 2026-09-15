#include <benmath/Vector.h>

#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace benmath {

/*********************************************************** 
* Constructors
***********************************************************/

Vector::Vector(std::initializer_list<double> values)
    : components{values} {
}


// Allows std::vector<double> to be converted into our Vector
Vector::Vector(const std::vector<double>& values)
    : components{values} {
}


/*********************************************************** 
* Factory Functions
***********************************************************/

Vector Vector::zeros(size_t dimension) {
    return Vector(std::vector<double>(dimension, 0.0));
}


Vector Vector::ones(size_t dimension) {
    return Vector(std::vector<double>(dimension, 1.0));
}


Vector Vector::full(size_t dimension, double value) {
    return Vector(std::vector<double>(dimension, value));
}


/*********************************************************** 
* Size / zero checking
***********************************************************/

size_t Vector::size() const {
    return components.size();
}


bool Vector::is_zero() const {

    const double eps = 1e-12;

    for (size_t i{0}; i < components.size(); ++i) {

        if (std::abs(components[i]) > eps) {
            return false;
        }
    }

    return true;
}


/*********************************************************** 
* Indexing
***********************************************************/

double& Vector::operator[](long long position) {

    long long n = static_cast<long long>(size());

    if (position < 0) {
        position = n + position;
    }

    if (position < 0 || position >= n) {
        throw std::out_of_range(
            "No such position exists in this vector"
        );
    }

    return components[position];
}


const double& Vector::operator[](long long position) const {

    long long n = static_cast<long long>(size());

    if (position < 0) {
        position = n + position;
    }

    if (position < 0 || position >= n) {
        throw std::out_of_range(
            "Index out of range"
        );
    }

    return components[position];
}


/*********************************************************** 
* Norm
***********************************************************/
double Vector::norm() const {

    double total{};

    for (double x : components) {
        total += x * x;
    }

    return std::sqrt(total);
}


/*********************************************************** 
* Append
***********************************************************/

void Vector::append(double value) {
    components.push_back(value);
}

/*********************************************************** 
* Addition
***********************************************************/

Vector Vector::operator+(const Vector& other) const {

    Vector addition{};

    if (components.size() != other.size()) {
        throw std::invalid_argument(
            "Vectors must be of equal size"
        );
    }

    for (size_t i{0}; i < components.size(); ++i) {
        addition.append(components[i] + other[i]);
    }

    return addition;
}


Vector& Vector::operator+=(const Vector& other) {

    if (size() != other.size()) {
        throw std::invalid_argument(
            "Vectors must be of equal size"
        );
    }

    for (size_t i{0}; i < size(); ++i) {
        components[i] += other[i];
    }

    return *this;
}


/*********************************************************** 
* Subtraction
***********************************************************/

Vector Vector::operator-(const Vector& other) const {

    Vector subtraction{};

    if (components.size() != other.size()) {
        throw std::invalid_argument(
            "Vectors must be of equal size"
        );
    }

    for (size_t i{0}; i < components.size(); ++i) {
        subtraction.append(components[i] - other[i]);
    }

    return subtraction;
}


Vector& Vector::operator-=(const Vector& other) {

    if (size() != other.size()) {
        throw std::invalid_argument(
            "Vectors must be of equal size"
        );
    }

    for (size_t i{0}; i < size(); ++i) {
        components[i] -= other[i];
    }

    return *this;
}

/*********************************************************** 
* Scalar Multiplication
***********************************************************/

Vector Vector::operator*(double scalar) const {

    Vector scalar_mult{};

    for (size_t i{0}; i < components.size(); ++i) {
        scalar_mult.append(components[i] * scalar);
    }

    return scalar_mult;
}


// Allows scalar * Vector
Vector operator*(double scalar, const Vector& vec) {
    return vec * scalar;
}


/*********************************************************** 
* Scalar Division
***********************************************************/

Vector Vector::operator/(double scalar) const {

    if (scalar == 0) {
        throw std::invalid_argument(
            "Cannot divide vector by 0"
        );
    }

    Vector scalar_div{};

    for (size_t i{0}; i < components.size(); ++i) {
        scalar_div.append(components[i] / scalar);
    }

    return scalar_div;
}


/*********************************************************** 
* Unary Minus
***********************************************************/

Vector Vector::operator-() const {

    Vector unary_minus{};

    for (size_t i{0}; i < components.size(); ++i) {
        unary_minus.append(-components[i]);
    }

    return unary_minus;
}


/*********************************************************** 
* Dot product
***********************************************************/

double Vector::dot(const Vector& other) const {

    if (components.size() != other.size()) {
        throw std::invalid_argument(
            "Vectors must be of equal size"
        );
    }

    double dot_product{};

    for (size_t i{0}; i < components.size(); ++i) {
        dot_product += components[i] * other[i];
    }

    return dot_product;
}


/*********************************************************** 
* Cross Product
***********************************************************/

Vector Vector::cross(const Vector& other) const {

    if (size() != 3 || other.size() != 3) {
        throw std::invalid_argument(
            "Cross product requires two vectors in R3"
        );
    }

    return Vector{
        components[1] * other[2]
            - components[2] * other[1],

        components[2] * other[0]
            - components[0] * other[2],

        components[0] * other[1]
            - components[1] * other[0]
    };
}

/*********************************************************** 
* Normalisation
***********************************************************/

Vector Vector::normalised() const {

    double mag = norm();

    if (is_zero()) {
        throw std::invalid_argument(
            "Cannot normalise the zero vector"
        );
    }

    return *this / mag;
}


/*********************************************************** 
* Distance
***********************************************************/

double Vector::distance_from(const Vector& other) const {
    return (*this - other).norm();
}


/*********************************************************** 
* Angle
***********************************************************/

double Vector::angle(const Vector& other) const {

    double mag1 = norm();
    double mag2 = other.norm();

    if (is_zero() || other.is_zero()) {
        throw std::invalid_argument(
            "Cannot calculate angle with the zero vector"
        );
    }

    double cos_theta =
        dot(other) / (mag1 * mag2);

    cos_theta = std::clamp(
        cos_theta,
        -1.0,
        1.0
    );

    return std::acos(cos_theta);
}

/*********************************************************** 
* Vector Projection
***********************************************************/

Vector Vector::project_onto(const Vector& other) const {

    if (other.is_zero()) {
        throw std::invalid_argument(
            "Cannot project onto the zero vector"
        );
    }

    double denominator = other.dot(other);

    double scalar =
        dot(other) / denominator;

    return other * scalar;
}


/*********************************************************** 
* Scalar Projection
***********************************************************/

double Vector::scalar_projection(
    const Vector& other
) const {

    if (other.is_zero()) {
        throw std::invalid_argument(
            "Cannot project onto the zero vector"
        );
    }

    return dot(other) / other.norm();
}


/*********************************************************** 
* Equality
***********************************************************/

bool Vector::operator==(const Vector& other) const {

    if (size() != other.size()) {
        return false;
    }

    const double eps = 1e-10;

    for (size_t i{0}; i < components.size(); ++i) {

        if (
            std::abs(components[i] - other[i])
            > eps
        ) {
            return false;
        }
    }

    return true;
}


bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}


/*********************************************************** 
* Orthogonality
***********************************************************/

bool Vector::is_orthogonal(
    const Vector& other
) const {

    const double eps = 1e-12;

    return std::abs(dot(other)) <= eps;
}


/*********************************************************** 
* Output - so i can just state v and it prints the vector 
***********************************************************/

std::ostream& operator<<(
    std::ostream& os,
    const Vector& vec
) {

    os << "(";

    for (size_t i{0}; i < vec.size(); ++i) {

        os << vec[i];

        if (i < vec.size() - 1) {
            os << ", ";
        }
    }

    os << ")";

    return os;
}


}