#include <iomanip>
#include <iostream>
#include <sstream>

bool compareDates(const std::string& dateStr1, const std::string& dateStr2) {
    std::tm tm1 = {}, tm2 = {};
    std::istringstream ss1(dateStr1), ss2(dateStr2);
    ss1 >> std::get_time(&tm1, "%d/%m/%Y");
    ss2 >> std::get_time(&tm2, "%d/%m/%Y");
    if (ss1.fail() || ss2.fail()) {
        throw std::runtime_error("Failed to parse date");
    }
    time_t t1 = std::mktime(&tm1);
    time_t t2 = std::mktime(&tm2);
    return t1 < t2;
}

int main() {
    std::string dateStr1 = "20/03/1993";
    std::string dateStr2 = "19/07/1993";

    if (compareDates(dateStr1, dateStr2)) {
        std::cout << dateStr1 << " is before " << dateStr2 << std::endl;
    } else {
        std::cout << dateStr1 << " is after or the same as " << dateStr2 << std::endl;
    }

    return 0;
}
