#include <algorithm>
#include <cctype>

#include "handleJson.hpp"
#include "iostream"
#include "signUp.hpp"
#include "string"
// #include "vector"

using namespace std;

struct IsOk {
    bool isAccountValid = false;
    bool isPasswordValid = false;
};

class BankManage {
   private:
    HandleJson handleJson;
    SignUp signUp;
    string fileName;
    BankAccountStruct bankAccountStruct;
    string nameOfFile = "./Data/AccountData.json";

   public:
    IsOk isOk;
    void signIn() {
        while (!isOk.isAccountValid) {
            cout << "Enter name of account: ";
            cin >> bankAccountStruct.account;
            if (handleJson.wasValueExist(nameOfFile, bankAccountStruct.account, "account")) {
                isOk.isAccountValid = true;
            }
        }
        while (!signUp.isSetPasswordDone(bankAccountStruct.password, 0, 0) && !signUp.isPasswordSame(bankAccountStruct.password, bankAccountStruct.rePassword)) {
            cout << "Enter password: ";
            cin >> bankAccountStruct.password;

            cout << "Re-enter password: ";
            cin >> bankAccountStruct.rePassword;
        }
        getDataInExistFile(nameOfFile);
        handleJson.storeDataBankAccount(nameOfFile, handleJson.vectorBankAcc);
    }

    void getDataInExistFile(string nameOfFile) {
        ifstream inputFile(nameOfFile);
        if (inputFile.good()) {
            json jsonData;
            inputFile >> jsonData;
            for (const auto& task : jsonData) {
                BankAccountStruct newDataAcc;
                newDataAcc.account = task["account"];
                newDataAcc.password = task["password"];
                newDataAcc.pinCode = task["pinCode"];
                handleJson.vectorBankAcc.push_back(newDataAcc);
            }
            inputFile.close();
        }
    }
};

int main() {
    BankManage bankManage;
    bankManage.signIn();
    return 0;
}