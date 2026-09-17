#pragma once

#include <vector>
#include <initializer_list>
#include <iostream>

namespace quantmethods {

class Vector {

private:
    std::vector<double> components;

public:

    // Constructors
    Vector(std::initializer_list<double> values);
    Vector(const std::vector<double>& values);

    // Factory functions
    static Vector zeros(size_t dimension);
    static Vector ones(size_t dimension);
    static Vector full(size_t dimension, double value);

    // Basic properties
    size_t size() const;
    bool is_zero() const;

    // Indexing
    double& operator[](long long position);
    const double& operator[](long long position) const;

    // Magnitude / norm
    double norm() const;

    // Add value to vector
    void append(double value);

    // Arithmetic
    Vector operator+(const Vector& other) const;
    Vector& operator+=(const Vector& other);

    Vector operator-(const Vector& other) const;
    Vector& operator-=(const Vector& other);

    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;

    Vector operator-() const;

    // Vector operations
    double dot(const Vector& other) const;
    Vector cross(const Vector& other) const;

    Vector normalised() const;

    double distance_from(const Vector& other) const;
    double angle(const Vector& other) const;

    Vector project_onto(const Vector& other) const;
    double scalar_projection(const Vector& other) const;

    bool is_orthogonal(const Vector& other) const;

    // Comparisons
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
};


// Non-member operators
std::ostream& operator<<(std::ostream& os, const Vector& vec);

Vector operator*(double scalar, const Vector& vec);

}