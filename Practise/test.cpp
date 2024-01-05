/*
    đang lỗi ở func: assignTask, vì đang phát triển tính năng phát triển trùng lặp tên của task
*/

#include <dirent.h>

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stack>

#include "iostream"
#include "nlohmann/json.hpp"
#include "string"
#include "vector"
using namespace std;

using json = nlohmann::json;

class Init {
   private:
    // string nameFile;

   public:
};

struct Task {
    string taskName;
    string expirationDate;
    string status;
};

class Management {
   private:
    int chooseTask;
    string befOrPast;
    int chooseKeyRemove;
    vector<Task> vectorData;

    bool hasJsonExtension(const char* fileName) {
        const char* dot = strrchr(fileName, '.');
        return dot && !strcmp(dot, ".json");
    }

    bool compareDates(const string& dateStr1, const string& dateStr2) {
        tm tm1 = {}, tm2 = {};
        istringstream ss1(dateStr1), ss2(dateStr2);
        ss1 >> get_time(&tm1, "%d/%m/%Y");
        ss2 >> get_time(&tm2, "%d/%m/%Y");
        if (ss1.fail() || ss2.fail()) {
            throw runtime_error("Failed to parse date");
        }
        time_t t1 = mktime(&tm1);
        time_t t2 = mktime(&tm2);
        return t1 < t2;  // return true if date was insert before date in json
    }

    void storeData(string nameOfFile, const std::vector<Task>& taskList) {
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

    /*
        this function in order to check has file existed, get data into this file and put it into vector
    */
    void getDataInExistFile(string nameOfFile) {
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
    string listJson() {
        string fileNameJson;
        string folderPath = ".";  // Assuming the code file is in the same directory as the JSON files
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
            fileNameJson = setName();
        } else {
            cout << "We have \033[1;32m" << countFile << "\033[0m json's files!" << endl;
            if ((dir = opendir(folderPath.c_str())) != NULL) {
                while ((ent = readdir(dir)) != NULL) {
                    if (hasJsonExtension(ent->d_name)) {
                        cout << ent->d_name << "\t";
                        countFile++;
                        foundJsonFile = true;
                    }
                }
                cout << "\n";
                closedir(dir);
            }
            fileNameJson = setName();
        }
        return fileNameJson;
    }
    string setName() {
        string fileJson = "";
        cout << "\033[1;32mInsert name of file: \033[0m";
        cin >> fileJson;
        fileJson = fileJson + ".json";
        return fileJson;
    }

   public:
    Management() {
        cout << "\033[1;32mWelcome to my app\033[0m" << endl;
        string fileName = listJson();
        getDataInExistFile(fileName);
        while (1) {
            cout << "\033[1;1m============\033[0m \033[1;32mMENU\033[0m \033[1;1m============\033[0m" << endl;
            cout << "\t\033[33m1.\033[0m Assign new task\n\t\033[33m2.\033[0m Store data\n\t\033[33m3.\033[0m Edit data\n\t\033[33m4.\033[0m List all tasks\n\t\033[33m5.\033[0m Remove task\n\t\033[33m6.\033[0m Back\n\t\033[33m7.\033[0m Exit" << endl;
            cout << "---> Enter active (\033[33mnumber\033[0m): ";
            cin >> chooseTask;
            cout << "\033[1;1m==============================\033[0m" << endl;
            // Does the value entered from the keyboard have the format of the variable?
            if (cin.fail()) {
                cin.clear();                                                    // Clear the error state
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
            }
            switch (chooseTask) {
                case 1:
                    assignTask(fileName);
                    break;
                case 2:
                    cout << "\033[33m[2] \033[0m Saving data" << endl;
                    storeData(fileName, vectorData);
                    break;
                case 3:
                    cout << "nothing to do here" << endl;
                    break;
                case 4:
                    listAllTasks(fileName);
                    break;
                case 5:
                    removeByTask(fileName, false);
                    break;
                case 6:
                    // set condition
                    cout << "\033[33m[6] \033[0mBack" << endl;
                    vectorData.clear();  // clear data inside of vector
                    fileName = listJson();
                    getDataInExistFile(fileName);
                    break;
                case 7:
                    cout << "\033[33m[7] \033[0mExit" << endl;
                    exit(0);
                default:
                    cout << "\033[1;31mError !!! Please re-enter.\033[0m\n";
                    break;
            }
        }
    }
    void assignTask(string nameOfFile) {
        Task insertTask;
        cout << "\033[33m[1] \033[0mAssign new task (press 'q' to back)" << endl;
        cout << "New task: ";
        cin >> insertTask.taskName;

        if (insertTask.taskName == "q") {
            return;
        }
        ifstream input(nameOfFile);
        json jsonData;
        input >> jsonData;
        input.close();
        for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
            if (it->at("taskName") == insertTask.taskName) {
                cout << "This task \033[1;31m" << insertTask.taskName << "\033[0m was exist in file, pls re-enter another name" << endl;
                assignTask(nameOfFile);
            }
        }
        cout << "Expiration date (dd/mm/yyyy): ";
        cin >> insertTask.expirationDate;

        cout << "List of status: " << endl;
        cout << "\tOpen\n\tHolding\n\tReopen\n\tDone" << endl;
        cout << "Status: ";
        cin >> insertTask.status;

        vectorData.push_back(insertTask);
    }
    void removeByTask(string nameOfFile, bool flag) {
        bool outWhile = false;
        while (1) {
            cout << "\033[33m[5] \033[0mRemove task inside file (enter '4' to back to Main menu)" << endl;
            cout << "\t[5]\033[33m[1] \033[0m Remove by name of task." << endl;
            cout << "\t[5]\033[33m[2] \033[0m Remove by status of task." << endl;
            cout << "\t[5]\033[33m[3] \033[0m Remove by expiry date of task." << endl;
            cout << "\t[5]\033[33m[4] \033[0m Back." << endl;
            cout << "\t[5]\033[33m[5] \033[0m Exit." << endl;
            cout << "---> Enter choice (\033[33mnumber\033[0m): ";
            cin >> chooseKeyRemove;

            string strDel;
            if (cin.fail()) {
                cin.clear();                                                    // Clear the error state
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
            }

            ifstream input(nameOfFile);
            json jsonData;
            input >> jsonData;
            input.close();
            auto it = jsonData.begin();
            switch (chooseKeyRemove) {
                case 1:
                    cout << "Enter task (press \033[33m'q' \033[0m to go back): ";
                    cin >> strDel;
                    if (strDel == "q") {
                        removeByTask(nameOfFile, false);
                    }

                    for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
                        if (it->at("taskName") == strDel) {
                            flag = true;  // enable flag to notice that is exist in json's file
                            jsonData.erase(it);
                            break;
                        }
                    }

                    // flag to check 'strDel' is exist in json's file
                    if (!flag) {
                        cout << "Could not find task: \033[1;31m" << strDel << "\033[0m in json's file to remove." << endl;
                        // return;
                    }
                    break;
                case 2:
                    cout << "Enter status (press \033[33m'q' \033[0m to go back): ";
                    cin >> strDel;
                    if (strDel == "q") {
                        removeByTask(nameOfFile, false);
                    }

                    while (it != jsonData.end()) {
                        if (it->at("status") == strDel) {
                            flag = true;
                            it = jsonData.erase(it);
                        } else {
                            ++it;
                        }
                    }

                    // flag to check 'strDel' is exist in json's file
                    if (!flag) {
                        cout << "Could not find status: \033[1;31m" << strDel << "\033[0m in json's file to remove." << endl;
                        // return;
                    } else {
                        cout << "All tasks have status \033[32m" << strDel << "\033[0m was removed!" << endl;
                    }
                    break;
                case 3:

                    cout << "Enter date (dd/mm/yyyy) (press 'q' to go back): ";
                    cin >> strDel;
                    cout << "Do you want to delete tasks in the \033[33mpast \033[0m or in the \033[33mfuture \033[0m (past/future): ";
                    cin >> befOrPast;
                    if (strDel == "q") {
                        removeByTask(nameOfFile, false);
                    }
                    if (befOrPast == "future") {
                        for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
                            if (compareDates(strDel, it->at("expirationDate"))) {
                                // if (== strDel) {
                                flag = true;  // enable flag to notice that is exist in json's file
                                jsonData.erase(it);
                                break;
                            }
                        }
                    } else if (befOrPast == "past") {
                        for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
                            if (!compareDates(strDel, it->at("expirationDate"))) {
                                // if (== strDel) {
                                flag = true;  // enable flag to notice that is exist in json's file
                                jsonData.erase(it);
                                break;
                            }
                        }
                    } else {
                        cout << "\033[1;31mInvalid date, pls re-enter\033[0m" << endl;
                        removeByTask(nameOfFile, false);
                    }

                    // flag to check 'strDel' is exist in json's file
                    if (!flag) {
                        cout << "Could not find date: \033[1;31m" << strDel << "\033[0m in json's file to remove." << endl;
                        // return;
                    }
                    break;
                case 4:
                    return;
                case 5:
                    exit(0);
                default:
                    cout << "\033[1;31mInvalid value, pls re-enter\033[0m" << endl;
                    break;
            }

            ofstream output(nameOfFile);
            output << setw(4) << jsonData << endl;
            output.close();
            flag = false;
        }
    }

    void listAllTasks(string nameOfFile) {
        cout << "\033[33m[4]\033[0m List all task" << endl;
        ifstream input(nameOfFile);
        json jsonData;
        input >> jsonData;
        input.close();

        // Display all the data in the JSON file
        cout << jsonData.dump(4) << endl;
    }
};

int main() {
    Management management;
    // management.assignTask(jsonFile);

    return 0;
}