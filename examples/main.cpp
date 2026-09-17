#include <iostream>
#include <quantmath/Matrix.h>
#include <quantmath/Vector.h>

using namespace quantmath;
using namespace std;

int main() {

    // -------------------------------------------------
    // 1. Rectangular matrix multiplication
    // -------------------------------------------------

    Matrix A{
        {1, 2, 3},
        {4, 5, 6}
    };

    Matrix B{
        {7, 8},
        {9, 10},
        {11, 12}
    };

    cout << "A * B:\n";
    cout << A * B << '\n';

    // Expected:
    // [58, 64]
    // [139, 154]


    // -------------------------------------------------
    // 2. Transpose
    // -------------------------------------------------

    cout << "Transpose of A:\n";
    cout << A.T() << '\n';

    // Expected:
    // [1, 4]
    // [2, 5]
    // [3, 6]


    // -------------------------------------------------
    // 3. Negative indexing
    // -------------------------------------------------

    cout << "A(-1, -1): " << A(-1, -1) << '\n';
    cout << "A(-2, -3): " << A(-2, -3) << '\n';

    // Expected:
    // 6
    // 1


    // -------------------------------------------------
    // 4. Zero matrix
    // -------------------------------------------------

    Matrix Z = Matrix::zeros(3, 4);

    cout << "Zero matrix:\n";
    cout << Z << '\n';

    // Expected:
    // [0, 0, 0, 0]
    // [0, 0, 0, 0]
    // [0, 0, 0, 0]


    // -------------------------------------------------
    // 5. Matrix * Vector
    // -------------------------------------------------

    Vector v{1, 2, 3};

    cout << "A * v:\n";
    cout << A * v << '\n';

    // Expected:
    // (14, 32)


    // -------------------------------------------------
    // 6. Equality
    // -------------------------------------------------

    Matrix A_copy{
        {1, 2, 3},
        {4, 5, 6}
    };

    cout << "A == A_copy: " << (A == A_copy) << '\n';
    cout << "A != A_copy: " << (A != A_copy) << '\n';

    // Expected:
    // 1
    // 0


    // -------------------------------------------------
    // 7. Invalid matrix multiplication
    // -------------------------------------------------

    try {

        Matrix C{
            {1, 2},
            {3, 4}
        };

        Matrix D{
            {1, 2},
            {3, 4},
            {5, 6}
        };

        cout << C * D;

    }
    catch (const exception& e) {
        cout << "Caught multiplication error: "
             << e.what() << '\n';
    }


    // -------------------------------------------------
    // 8. Invalid indexing
    // -------------------------------------------------

    try {       // try allows the code to still run knowing itll give exception 
        cout << A(100, 100);
    }
    catch (const exception& e) {
        cout << "Caught indexing error: "
             << e.what() << '\n';
    }


    // -------------------------------------------------
    // 9. Division by zero
    // -------------------------------------------------

    try {
        cout << A / 0;
    }
    catch (const exception& e) {
        cout << "Caught division error: "
             << e.what() << '\n';
    }


    // -------------------------------------------------
    // 10. Invalid column access
    // -------------------------------------------------

    try {
        cout << A.column(100);
    }
    catch (const exception& e) {
        cout << "Caught column error: "
             << e.what() << '\n';
    }


    return 0;
}