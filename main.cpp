#include <iostream>
using namespace std;
class Complex {
   private:
    double real;
    double imag;

   public:
    Complex(double r, double i) : real(r), imag(i) {}

    // Overloading the + operator to add two Complex numbers
    Complex operator+(const Complex& other) {
        cout << "call add" << endl;
        return Complex(real + other.real, imag + other.imag);
    }

    // Overloading the - operator to subtract two Complex numbers
    Complex operator-(const Complex& other) {
        cout << "call minus" << endl;
        return Complex(real - other.real, imag - other.imag);
    }

    // Overloading the * operator to multiply two Complex numbers
    Complex operator*(const Complex& other) {
        cout << "call times" << endl;
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    // Overloading the << operator to output a Complex number
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};

int main() {
    Complex c1(2.0, 3.0);
    Complex c2(4.0, 1.0);

    Complex sum = c1 + c2;         // Calls the overloaded + operator
    Complex product = c1 * c2;     // Calls the overloaded * operator
    Complex difference = c1 - c2;  // Calls the overloaded - operator

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << difference << std::endl;
    std::cout << "Product: " << product << std::endl;

    return 0;
}
