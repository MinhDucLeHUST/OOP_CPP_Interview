#include <algorithm>
#include <cctype>

#include "handleJson.hpp"
#include "iostream"
#include "signUp.hpp"
#include "string"
#include "vector"
using namespace std;
// using jsonn = nlohmann::json;
struct IsValid {
    bool isAccountValid = false;
    bool isPasswordValid = false;
    bool isRePasswordValid = false;
    bool isPinCodeValid = false;
};

struct StructBankAcc {
    string account;
    string password;
    string rePassword;
    string pinCode;
};

class BankManage {
   private:
    /*
        Variable & object
    */
    HandleJson handleJson;
    SignUp signUp;
    string fileName;
    string fileAccount = "./Data/AccountData.json";
    StructBankAcc structBankAcc;
    vector<StructBankAcc> vectorBankAcc;
    /*
        Function
    */
    void saveDataBankAccount(const string& nameOfFile, const vector<StructBankAcc>& vectorBankAccount) {
        json jsonData;

        for (const auto& accBank : vectorBankAccount) {
            json accountData;
            accountData["account"] = accBank.account;
            accountData["password"] = accBank.password;
            accountData["pinCode"] = accBank.pinCode;
            jsonData.push_back(accountData);
        }

        ofstream file(nameOfFile);
        file << jsonData.dump(4);
        file.close();
        cout << "Data saved" << endl;
    }

   public:
    IsValid isValid;
    void signIn() {
        while (!isValid.isAccountValid) {
            cout << "Enter name of account: ";
            cin >> structBankAcc.account;

            if (!isJsonEmpty(fileAccount)) {
                cout << "File is not empty\n";
                if (!handleJson.wasValueExist(fileAccount, structBankAcc.account, "account")) {
                    isValid.isAccountValid = true;
                }
            } else {
                isValid.isAccountValid = true;
            }
        }
        while (!isValid.isPasswordValid) {
            cout << "Enter password: ";
            cin >> structBankAcc.password;
            if (signUp.isSetPasswordDone(structBankAcc.password, 0, 0)) {
                isValid.isPasswordValid = true;
            }
        }
        while (!isValid.isRePasswordValid) {
            cout << "Re-enter password: ";
            cin >> structBankAcc.rePassword;
            if (signUp.isPasswordSame(structBankAcc.password, structBankAcc.rePassword)) {
                isValid.isRePasswordValid = true;
            }
        }

        do {
            cout << "Please enter PIN code: ";
            cin >> structBankAcc.pinCode;
        } while (!isValidPIN(structBankAcc.pinCode));
        getDataInExistFile(fileAccount);
        vectorBankAcc.push_back(structBankAcc);
        saveDataBankAccount(fileAccount, vectorBankAcc);
    }

    void getDataInExistFile(string nameOfFile) {
        ifstream inputFile(nameOfFile);
        if (inputFile.good()) {
            json jsonData;
            inputFile >> jsonData;
            for (const auto& task : jsonData) {
                StructBankAcc newDataAcc;
                newDataAcc.account = task["account"];
                newDataAcc.password = task["password"];
                newDataAcc.pinCode = task["pinCode"];
                vectorBankAcc.push_back(newDataAcc);
            }
            inputFile.close();
        }
    }

    bool isJsonEmpty(const string& pathFile) {
        ifstream file_stream(pathFile);
        json data;

        if (file_stream >> data) {
            return data.empty();
        } else {
            return true;  // Assuming an error means the file is empty
        }
    }

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
};

int main() {
    BankManage bankManage;
    bankManage.signIn();
    return 0;
}