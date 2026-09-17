#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>        //to clamp down our cos in the angle function
#include "functions.h"
#include <string>
#include <utility>
#include <cstdlib>

using namespace std;

class Vector {

private:
    vector<double> components;

public:
    Vector(initializer_list<double> values)
        : components{values} {
    }

    // allows for turning vectors into my own vector 
    Vector(const vector<double>& values)
        : components{values} {
    }

    // vector full of zeros called with Vector::zeros()
    static Vector zeros(size_t dimension) {
        return Vector(vector<double>(dimension, 0.0));
    }

    // vector full of ones
    static Vector ones(size_t dimension) {
        return Vector(vector<double>(dimension, 1.0));
    }

    // vector full of value
    static Vector full(size_t dimension, double value) {
        return Vector(vector<double>(dimension, value));
    }
    
    size_t size() const{
        return components.size();
    }

    bool is_zero() const {
        const double eps = 1e-12;
        for (size_t i{0}; i < components.size(); ++i){
            if (abs(components[i]) > eps){
                return false;
            }
        }
        return true;
    }

    double& operator[](long long position) {

        long long n= static_cast<long long>(size());

        if (position < 0){
            position = n + position;
        }

        if (position < 0 || position >=n ){
            throw out_of_range("No such position exists in this vector");
        }

        return components[position];
    }

    // returns number associated with the position given 
    const double& operator[](long long position) const {

        long long n = static_cast<long long>(size());

        if (position < 0) {
            position = n + position;
        }

        if (position < 0 || position >= n) {
            throw out_of_range("Index out of range");
        }

        return components[position];
    }

    double norm() const {
        double total{};

        for (double x: components) {
            total += x * x;
        }

        return sqrt(total);
    }

    // adds a value to the vector
    void append(double value) {
        components.push_back(value);
    }

    // replaced with the inline output below the class code instead
    // void display() const {
    //     cout << "(";
    //     for (int i{0}; i < components.size(); ++i){
    //         cout << components[i];

    //         if (i < components.size() - 1){
    //             cout << ", ";
    //         }
    //     }
    //     cout << ")";
    // }

    Vector operator+(const Vector& other) const {
        Vector addition{};

        if (components.size() != other.size()){
            throw invalid_argument("Vectors must be of equal size");
        }

        for (size_t i{0}; i < components.size(); ++i){
            addition.append(components[i] + other[i]);
        }
        return addition;
    }

    Vector& operator+=(const Vector& other) {

        if (size() != other.size()) {
            throw invalid_argument("Vectors must be of equal size");
        }

        for (size_t i{0}; i < size(); ++i) {
            components[i] += other[i];
        }

        return *this;
    }

    Vector operator-(const Vector& other) const {
        Vector subtraction{};

        if (components.size() != other.size()){
            throw invalid_argument("Vectors must be of equal size");
        }

        for (size_t i{0}; i < components.size(); ++i){
            subtraction.append(components[i] - other[i]);
        }
        return subtraction;
    }

    Vector& operator-=(const Vector& other) {

        if (size() != other.size()) {
            throw invalid_argument("Vectors must be of equal size");
        }

        for (size_t i{0}; i < size(); ++i) {
            components[i] -= other[i];
        }

        return *this;
    }

    Vector operator*(double scalar) const {
        Vector scalar_mult{};

        for (size_t i{0}; i < components.size(); ++i){
            scalar_mult.append(components[i] * scalar);
        }
        return scalar_mult;
    }

    Vector operator/(double scalar) const {
        Vector scalar_div{};

        if (scalar == 0) {
            throw invalid_argument("Cannot divide vector by 0");
        }

        for (size_t i{0}; i < components.size(); ++i){
            scalar_div.append(components[i] / scalar);
        }
        return scalar_div;
    }

    Vector operator-() const {
        Vector unary_minus{};
        for (size_t i{0}; i < components.size(); ++i){
            unary_minus.append(-components[i]);
        }
        return unary_minus;
    }

    double dot(const Vector& other) const {

        if (components.size() != other.size()){
            throw invalid_argument("Vectors must be of equal size");
        }

        double dot_product{};

        for (size_t i{0}; i < components.size(); ++i){
            dot_product += components[i] * other[i];
        }
        return dot_product;
    }

    Vector cross(const Vector& other) const {

        if (size() != 3 || other.size() != 3) {
            throw invalid_argument("Cross product requires two vectors in R3");
        }

        return Vector{
            components[1] * other[2] - components[2] * other[1],
            components[2] * other[0] - components[0] * other[2],
            components[0] * other[1] - components[1] * other[0]
        };
    }

    Vector normalised() const {
        double mag = norm();

        if (is_zero()){
            throw invalid_argument("Cannot normalise the zero vector");
        }

        return *this / mag;
    }

    double distance_from(const Vector& other) const {
        // *this basically uses the current object i want to perfrom on 
        return (*this - other).norm();
    }

    double angle(const Vector& other) const {
        double mag1 = norm();
        double mag2 = other.norm();

        if (is_zero() || other.is_zero()){
            throw invalid_argument("Cannot calculate angle with the zero vector");
        }

        double cos_theta = dot(other) / (mag1*mag2);
        cos_theta = clamp(cos_theta, -1.0, 1.0);

        return acos(cos_theta);
    }

    Vector project_onto(const Vector& other) const {

        double denominator = other.dot(other);

        if (other.is_zero()) {
            throw invalid_argument("Cannot project onto the zero vector");
        }

        double scalar = dot(other) / denominator;

        return other * scalar;
    }

    bool operator==(const Vector& other) const{
        if (size() != other.size()){
            return false;
        }

        const double eps = 1e-10;

        for (size_t i{0}; i < components.size(); ++i) {
            if (abs(components[i] - other[i]) > eps){
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector& other) const{
        return !(*this == other);
    }

    bool is_orthogonal(const Vector& other) const {
        double eps = 1e-12;
        if (abs(dot(other))> eps){
            return false;
        }
        return true;
    }

    double scalar_projection(const Vector& other) const{
        if (other.is_zero()){
            throw invalid_argument("Cannot project onto the zero vector");
        }
        return dot(other) / other.norm();
    }



};

// allows to display the vector inline . 
ostream& operator<<(ostream& os, const Vector& vec) {

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


Vector operator*(double scalar, const Vector& vec) {
    return vec * scalar;
};

class Matrix {

private:
    vector<Vector> data;

public:

    Matrix(initializer_list<initializer_list<double>> values){

        size_t init{};

        if (values.size()== 0){
            throw invalid_argument("this matrix is empty");
        }
        else
            init = values.begin() -> size();
        
        for (const auto& row: values) {

            if (row.size() != init){
                throw invalid_argument("All rows must be of same length");
            }
            
            data.push_back(Vector(row));
        }
    }

    size_t rows() const {
       return data.size();
    }

    size_t columns() const {
        if (data.empty()){
            return 0;
        }

        return data[0].size();
    }


    double& operator()(long long row, long long column) {
        long long row_position{row}, column_position{column};
        
        if (row_position < 0){
            row_position = row_position + static_cast<long long>(data.size());
        }

        if (column_position < 0){
            column_position = column_position + static_cast<long long>(data[0].size());
        }

        if (
            row_position < 0 ||
            row_position >= static_cast<long long>(data.size()) ||
            column_position < 0 ||
            column_position >= static_cast<long long>(data[0].size())
        ) {
            throw out_of_range("Matrix position does not exist");
        }

        return data[row_position][column_position];
    }

    const double& operator()(long long row, long long column) const {
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
            throw out_of_range("Matrix position does not exist");
        }

        return data[row_position][column_position];
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result = *this;

        if ((rows() != other.rows()) || (columns() != other.columns())){
            throw invalid_argument("Matrices must be of same dimension for addition");
        }

        // for (size_t i{0}; i < other.rows(); ++i) {
        //     for (size_t j{0}; j < other.columns(); ++j){
        //         result(i, j) = (i, j) + other(i,j);
        //     }
        // }

        // above code simplified using already defined vector addition
        for(size_t i{0}; i < rows(); ++i){
            result.data[i] += other.data[i];
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result = *this;

        if ((rows() != other.rows()) || (columns() != other.columns())){
            throw invalid_argument("Matrices must be of same dimension for addition");
        }

        for(size_t i{0}; i < rows(); ++i){
            result.data[i] -= other.data[i];
        }
        return result;
    }

    Matrix operator*(double scalar) const {
        Matrix result = *this;
        
        for (size_t i{0}; i < rows(); ++i){
            result.data[i] = result.data[i] * scalar;
        }

        return result;
    }

    Matrix operator/(double scalar) const {
        Matrix result = *this;
        if (scalar == 0){
            throw invalid_argument("Cannot divide by 0");
        }
        
        for (size_t i{0}; i < rows(); ++i){
            result.data[i] = result.data[i] / scalar;
        }

        return result;
    }

    Matrix operator-() const {
        Matrix result = *this;
        for (size_t i{0}; i < rows(); ++i){
            result.data[i] = -result.data[i];
        }
        return result;
    }

    Matrix& operator+=(const Matrix& other) {
        *this = *this + other;
        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        *this = *this - other;
        return *this;
    }

    Matrix& operator*=(double scalar) {
        *this = *this * scalar;
        return *this;
    }

    Matrix& operator/=(double scalar) {
        *this = *this / scalar;
        return *this;
    }

    bool operator==(const Matrix& other) const {

        if (rows() != other.rows() || columns() != other.columns()) {
            return false;
        }

        for (size_t i{0}; i < rows(); ++i) {
            if (data[i] != other.data[i]){
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    Vector operator*(const Vector& vec) const {

        if (columns() != vec.size()){
            throw invalid_argument("Cannot multiply these two");
        }

        Vector result{};

        for (size_t i{0}; i < rows(); ++i){
            result.append(data[i].dot(vec));
        }

        return result;
    }

    // column extraction before matrix multiplication
    Vector column(size_t index) const {

        if (index >= columns()) {
            throw out_of_range("Column index out of range");
        }

        Vector result{};

        for (size_t i{0}; i < rows(); ++i){
            result.append(data[i][index]);
        }

        return result;
    }

    /***********************************************
    * MATRIX MULTIPLICATION
    ***********************************************/
    Matrix operator*(const Matrix& other) const {
        Matrix result = *this;

        for (size_t i{0}; i < other.rows(); ++i) 

    }

};



ostream& operator<<(ostream& os, const Matrix& matrix) {
    for (size_t i{0}; i < matrix.rows(); ++i) {
        os << "[";
        for (size_t j{0}; j < matrix.columns(); ++j){
            os << matrix(i, j);

            if (j  < matrix.columns()-1){
                os << ", ";
            }
        }
        os << "]";
        os << endl;

    }
    return os;
}

// code pasted from other source to help with plots
void plot(initializer_list<pair<string, Vector>> vectors) {

    string command = "python plot_vectors.py";

    for (const auto& item : vectors) {

        string label = item.first;
        const Vector& vec = item.second;

        if (vec.size() != 2) {
            throw invalid_argument(
                "2D plotting requires vectors of size 2"
            );
        }

        command += " " + to_string(vec[0]);
        command += " " + to_string(vec[1]);
        command += " \"" + label + "\"";
    }

    system(command.c_str());
}

void plot3D(initializer_list<pair<string, Vector>> vectors) {

    string command = "python plot_vectors_3d.py";

    for (const auto& item : vectors) {

        string label = item.first;
        const Vector& vec = item.second;

        if (vec.size() != 3) {
            throw invalid_argument(
                "3D plotting requires vectors of size 3"
            );
        }

        command += " " + to_string(vec[0]);
        command += " " + to_string(vec[1]);
        command += " " + to_string(vec[2]);
        command += " \"" + label + "\"";
    }

    system(command.c_str());
}

int main() {

    cout << endl;
    return 0;

}