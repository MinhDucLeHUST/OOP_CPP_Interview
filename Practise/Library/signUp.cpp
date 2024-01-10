#include "signUp.hpp"

using namespace std;

bool SignUp::checkUppercase(const string& str) {
    return any_of(str.begin(), str.end(), [](char c) { return isupper(c); });
}

bool SignUp::isPasswordSame(string pass1st, string pass2nd) {
    return pass1st == pass2nd;
}

bool SignUp::isSetPasswordDone(string password, bool hasSpecialChar, bool hasUppercase) {
    if (password.length() < 10) {
        cout << "Password should be at least 10 characters long." << endl;
        return false;
    }

    for (char c : password) {
        if (!isalnum(c) && !isdigit(c)) {
            hasSpecialChar = true;
            break;
        }
    }

    if (checkUppercase(password)) {
        hasUppercase = true;
    }

    return hasSpecialChar && hasUppercase;
}