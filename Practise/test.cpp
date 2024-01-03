/*
    đang phát triển các tính năng lưu trữ data, quay ngược lại các bước trước đó, xử lý với files có sẵn hoặc chưa
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
    vector<Task> vectorData;

    bool hasJsonExtension(const char* fileName) {
        const char* dot = strrchr(fileName, '.');
        return dot && !strcmp(dot, ".json");
    }

    void storeData(string nameOfFile, const std::vector<Task>& taskList) {
        cout << "[2] Data was saved" << endl;

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

    bool isJsonFileExist(string nameJsonFileToCheck) {
        string folderPath = ".";  // Replace with the actual path to your folder
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.path().filename() == nameJsonFileToCheck && entry.path().extension() == ".json") {
                return true;
            }
        }
        return false;
    }

   public:
    Management() {
        cout << "\033[1;32mWelcome to my app\033[0m" << endl;
        string fileName = listJson();
        getDataInExistFile(fileName);
        while (1) {
            cout << "============ MENU ============" << endl;
            cout << "\t\033[33m1.\033[0m Assign new task\n\t\033[33m2.\033[0m Store data\n\t\033[33m3.\033[0m Edit data\n\t\033[33m4.\033[0m List all tasks\n\t\033[33m5.\033[0m Remove task\n\t\033[33m6.\033[0m Back\n\t\033[33m7.\033[0m Quit" << endl;
            cout << "---> Enter active (\033[33mnumber\033[0m): ";
            cin >> chooseTask;
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
                    storeData(fileName, vectorData);
                    break;
                case 3:
                    cout << "nothing to do here" << endl;
                    break;
                case 4:
                    listAllTasks(fileName);
                    // listJson();
                    break;
                case 5:
                    removeByTask(fileName, false);
                    break;
                case 6:
                    vectorData.clear();  // clear data inside of vector
                    fileName = listJson();
                    break;
                case 7:
                    exit(0);
                default:
                    cout << "\033[1;31mError !!! Please re-enter.\033[0m\n";
                    break;
            }
        }
    }
    void assignTask(string nameOfFile) {
        Task insertTask;
        cout << "[1] New task: ";
        cin >> insertTask.taskName;

        cout << "Expiration date (dd/mm/yyyy): ";
        cin >> insertTask.expirationDate;

        cout << "List of status: " << endl;
        cout << "\tOpen\n\tHolding\n\tReopen\n\tDone" << endl;
        cout << "Status: ";
        cin >> insertTask.status;

        vectorData.push_back(insertTask);
    }
    void removeByTask(string nameOfFile, bool flag) {
        string taskRemove;
        cout << "[5] Enter name of task to remove: ";
        cin >> taskRemove;
        ifstream input(nameOfFile);
        json jsonData;
        input >> jsonData;
        input.close();

        for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
            if (it->at("taskName") == taskRemove) {
                flag = true;  // enable flag to notice that is exist in json's file
                jsonData.erase(it);
                break;
            }
        }
        // flag to check 'taskRemove' is exist in json's file
        if (!flag) {
            cout << "\033[1;31mError !!! \033[0m Could not find " << taskRemove << " in json's file." << endl;
            return;
        }

        ofstream output(nameOfFile);
        output << setw(4) << jsonData << endl;
        output.close();
    }

    void listAllTasks(string nameOfFile) {
        cout << "[4] List all task" << endl;
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