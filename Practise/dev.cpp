#include <iostream>
#include <regex>

int main() {
    std::string input;
    std::regex date_regex("\\b(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}\\b");

    do {
        std::cout << "Enter by format dd/mm/yyyy: ";
        std::cin >> input;
    } while (!std::regex_match(input, date_regex));

    std::cout << "Valid date: " << input << std::endl;

    return 0;
}
