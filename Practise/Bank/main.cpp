#include <algorithm>
#include <cctype>

#include "handleJson.hpp"
#include "iostream"
#include "signUp.hpp"
#include "string"
// #include "vector"

using namespace std;

class BankManage {
   private:
    HandleJson handleJson;
    SignUp signUp;
    string fileName;
    BankAccount bankAccount;

   public:
    bool quitWhile = false;
    BankManage() {
        fileName = handleJson.setName("./Data/");
        handleJson.storeDataBankAccount(fileName, handleJson.vectorBankAcc);
    }
    void signIn() {
        cout << "Enter name of account: ";
        cin >> bankAccount.account;
        handleJson.wasValueExist(fileName, bankAccount.account, "account");
        while (!signUp.isSetPasswordDone(bankAccount.password, 0, 0) && !signUp.isPasswordSame(bankAccount.password, bankAccount.rePassword)) {
            cout << "Enter password: ";
            cin >> bankAccount.password;

            cout << "Re-enter password: ";
            cin >> bankAccount.rePassword;
        }
    }
};

int main() {
    BankManage bankManage;
    bankManage.signIn();
    return 0;
}