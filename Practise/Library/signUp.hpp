#ifndef SIGN_UP_HPP
#define SIGN_UP_HPP

#include <algorithm>
#include <cctype>
#include <fstream>
#include <vector>

#include "iostream"
#include "string"

// using json = nlohmann::json;
using namespace std;

class SignUp {
   private:
   public:
    bool isSetPasswordDone(string password, bool hasSpecialChar, bool hasUppercase);
    bool isPasswordSame(string pass1st, string pass2nd);
    bool checkUppercase(const string& str);
};

#endif
