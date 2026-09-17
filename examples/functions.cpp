#include "functions.h"
#include <iostream>
#include <cmath>
#include <utility>

using namespace std;

/**************************************************************************************************************
***************************************************************************************************************
* WORK BOOK 1 FUNCTIONS
***************************************************************************************************************
**************************************************************************************************************/

/***************************************************************
 * 1.1 functions - simple operations to a vector 
***************************************************************/ 
int len(vector<double> vector) {

    int amount{};
    for (auto vec: vector) {
        amount += 1;
    }

    return amount;
};

double maximum(vector<double> vector) {
    
    double init{vector[0]};

    for (auto vec: vector) {
        if (vec >= init){
            init = vec;
        }
    }
    return init;
};

double minimum(vector<double> vector) {
    
    double init{vector[0]};

    for (auto vec: vector) {
        if (vec <= init){
            init = vec;
        }
    }
    return init;
};

double sum(vector<double> vector) {
    double sum{};

    for (auto vec: vector) {
        sum += vec;
    }
    return sum;
};

double average(vector<double> vector) {
    double mean = sum(vector) / len(vector);
    return mean;
};

/***************************************************************
 * 1.2 functions - ranges
***************************************************************/ 

vector<double> vrange(double start, double stop, double step) {
    vector<double> array {};
    double values {(stop - start)/step};

    array.push_back(start);
    values -= 1;

    for (int i{0}; i < values; ++i) {
        double new_number = array.back() + step;
        array.push_back(new_number);
    }

    return array;
};

vector<double> linspace(double start, double stop, int amount) {
    vector<double> array{start};
    double h = (stop - start) / (amount - 1) ;
    int num{1};

    while (num < amount) {
        double new_number = array.back() + h;
        array.push_back(new_number);
        num += 1;
    }

    return array;
};

/***************************************************************
 * 1.4 functions - Least squares estimation  
***************************************************************/ 

double least_squares_error(
    vector<double> x,
    vector<double> y,
    double m,
    double c
) {
    double sum_of_squares{};

    for (int i{0}; i < x.size(); ++i) {
        double f_value = m*x[i] + c;
        double residual = y[i] - f_value;

        sum_of_squares += residual * residual;
    }
    return sum_of_squares;
}

vector<double> linear_fit(vector<double> x, vector<double> y){
    double n = x.size();
    double sum_x{}, sum_y{}, sum_xy{}, sum_xx{};

    for (int i{0}; i < x.size(); ++i){
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_xx += x[i] * x[i];
    }

    double beta1 = (sum_xy - (sum_x*sum_y)/n) / (sum_xx - (sum_x*sum_x)/n);
    double beta0 = sum_y/n - beta1*(sum_x/n);

    return {beta0, beta1};
}

/**************************************************************************************************************
***************************************************************************************************************
* WORK BOOK 2 FUNCTIONS
***************************************************************************************************************
**************************************************************************************************************/

/***************************************************************
 * 2.1 functions - Polyval and Herner Method  
***************************************************************/ 

double polyval(vector<double> coefficients, double x) {
    double result = coefficients[0];
    size_t n = coefficients.size();

    for (size_t i{1}; i < n; ++i) {
        result = (result * x) + coefficients[i];
    }

    return result;
}

vector<double> polyval(vector<double> coefficients, vector<double> x) {
    vector<double> result{};

    for (auto value: x) {
        result.push_back(polyval(coefficients, value));
    }

    return result;
}

/**************************************************************************************************************
***************************************************************************************************************
* WORK BOOK 4 FUNCTIONS
***************************************************************************************************************
**************************************************************************************************************/

/***************************************************************
 * 4.1 functions - Bisection Method and Newton-Raphson  
***************************************************************/ 

pair<double, int> bisection(double (*f)(double), double lower, double upper, double eps){
    double x_l{};
    double x_u{};
    int iterations{};

    if (f(lower)*f(upper) > 0) {
        cout << "Unable to find root as both values give same sign...";
        return {0, 0};
    }

    if (f(lower)<0){
        x_l = lower;
        x_u = upper;
    }
    else{
        x_l = upper;
        x_u = lower;
    }

    double x_mid {};

    while(abs(x_u - x_l) > eps){

        x_mid = (x_u + x_l)/2;

        if (f(x_mid) < 0){
            x_l = x_mid;
        }
        else {
            x_u = x_mid;
        }
        iterations += 1;
    }
    return {x_mid, iterations};
}

pair<double, int> newton_raphson(double (*f)(double), double (*dfdx)(double), double x0, double eps, int max_iter){
    double x = x0;
    int iterations{0};

    while (abs(f(x))>eps && iterations < max_iter){

        if (abs(dfdx(x)) < 1e-14){
            cout << "Derivative too close to zero. Newton Raphson stopped." << endl;
            break;
        }

        x = x - (f(x)/dfdx(x));
        iterations += 1;
    }
    if (iterations == max_iter && abs(f(x)) > eps) {
        cout << "Maximum iterations reached without convergence." << endl;
    }

    return {x, iterations};
}