#include <handleJson.hpp>

using namespace std;
using json = nlohmann::json;

void HandleJson::storeDataTask(const string& nameOfFile, const vector<Task>& taskList) {
    json jsonData;

    for (const auto& task : taskList) {
        json taskData;
        taskData["taskName"] = task.taskName;
        taskData["expirationDate"] = task.expirationDate;
        taskData["status"] = task.status;
        jsonData.push_back(taskData);
    }

    ofstream file(nameOfFile);
    file << jsonData.dump(4);  // Pretty-print with 4 spaces
    // cout << "Data was saved" << endl;
    file.close();
}

void HandleJson::storeDataBankAccount(const string& nameOfFile, const vector<BankAccountStruct>& vectorBankAccount) {
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
}

/*
    this function in order to check has file existed, get data into this file and put it into vector
*/
void HandleJson::getDataInExistFile(const string& nameOfFile) {
    ifstream inputFile(nameOfFile);
    if (inputFile.good()) {
        json jsonData;
        inputFile >> jsonData;
        for (const auto& task : jsonData) {
            Task newTask;
            newTask.taskName = task["taskName"];
            newTask.expirationDate = task["expirationDate"];
            newTask.status = task["status"];
            vectorData.push_back(newTask);
        }
        inputFile.close();
    }
}

void HandleJson::listAllTasks(string nameOfFile) {
    ifstream input(nameOfFile);
    json jsonData;
    input >> jsonData;
    input.close();

    // Display all the data in the JSON file
    cout << jsonData.dump(4) << endl;
}

string HandleJson::setName(string folderPath) {
    string fileJson = "";
    cout << "\033[1;32mInsert name of file: \033[0m";
    cin >> fileJson;
    fileJson = folderPath + fileJson + ".json";
    return fileJson;
}

bool HandleJson::hasJsonExtension(const char* fileName) {
    const char* dot = strrchr(fileName, '.');
    return dot && !strcmp(dot, ".json");
}

string HandleJson::listFileJsonInFolder(string folderPath) {
    string fileNameJson;
    // string folderPath = ".";  // Assuming the code file is in the same directory as the JSON files
    int countFile = 0;
    DIR* dir;
    struct dirent* ent;
    bool foundJsonFile = false;
    if ((dir = opendir(folderPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (hasJsonExtension(ent->d_name)) {
                countFile++;
                foundJsonFile = true;
            }
        }
        closedir(dir);
    } else {
        cerr << "Error opening directory" << endl;
    }

    if (!foundJsonFile) {
        cout << "There is no Json's file in the folder, you need to create new file to store your data." << endl;
        fileNameJson = setName(folderPath);
    } else {
        cout << "We have \033[1;32m" << countFile << "\033[0m json's files!" << endl;
        if ((dir = opendir(folderPath.c_str())) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (hasJsonExtension(ent->d_name)) {
                    cout << ent->d_name << "\t";  // list all files json in folder
                    countFile++;
                    foundJsonFile = true;
                }
            }
            cout << "\n";
            closedir(dir);
        }
        fileNameJson = setName(folderPath);
    }
    return fileNameJson;
}
/*
    This function in order to check value of a key was exist in a json file.
*/
bool HandleJson::wasValueExist(const string& nameOfFile, const string& valueInsert, const string& keyToCheck) {
    ifstream input(nameOfFile);
    json jsonData;
    input >> jsonData;
    input.close();

    for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
        if (it->at(keyToCheck) == valueInsert) {
            return true;
        }
    }
    return false;
}
