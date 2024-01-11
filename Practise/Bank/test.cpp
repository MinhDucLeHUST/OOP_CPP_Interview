#include <cctype>
#include <iostream>
#include <string>

bool isValidPIN(const std::string& pin) {
    if (pin.length() != 6) {
        return false;  // PIN length is not 6
    }
    for (char c : pin) {
        if (!std::isdigit(c)) {
            return false;  // PIN contains non-digit characters
        }
    }
    return true;  // PIN is valid
}

int main() {
    std::string pin;
    do {
        std::cout << "Please enter your 6-digit PIN code: ";
        std::cin >> pin;
    } while (!isValidPIN(pin));

    std::cout << "Valid PIN entered: " << pin << std::endl;

    return 0;
}
