#ifndef HANDLE_JSON_HPP
#define HANDLE_JSON_HPP

#include <dirent.h>

#include <fstream>
#include <vector>

#include "iostream"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;
struct Task {
    std::string taskName;
    std::string expirationDate;
    std::string status;
};

struct BankAccount {
    string account;
    string password;
    string rePassword;
    string pinCode;
};

class HandleJson {
   protected:
   public:
    vector<Task> vectorData;
    vector<BankAccount> vectorBankAcc;
    void storeDataTask(const std::string& nameOfFile, const std::vector<Task>& taskList);
    void getDataInExistFile(const std::string& nameOfFile);
    void listAllTasks(string nameOfFile);
    string setName(string folderPath);
    bool hasJsonExtension(const char* fileName);
    string listFileJsonInFolder(string folderPath);
    bool wasValueExist(const string& nameOfFile, const string& valueInsert, const string& keyToCheck);
    void storeDataBankAccount(const string& nameOfFile, const vector<BankAccount>& vectorBankAccount);
};

#endif
