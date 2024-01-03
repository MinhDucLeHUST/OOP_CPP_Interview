/*
    (ok) đã phát triển xong các tính năng: 1,2,4,6,5
    (ok) ở tính năng 5: chưa fix được lỗi "nhập tên task ko có trong file data"
    (ok) phát triển tính năng: nếu nhập sai định dạng option, ví dụ phải nhập số nhưng nhập chữ thì báo sao và nhập lại
        các tính năng cần phát triển thêm: tính năng back lại cái option trước đó, ví dụ từ nhập task => back về MENU
        phát triển tính năng 3
        phát triển tính năng thay đổi value của các key trong file json
        phát triển tính năng: xóa tất cả các task có "status" = "Done"
*/

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
    string setName() {
        string fileJson = "";
        cout << "\033[1;32mInsert name of file: \033[0m";
        cin >> fileJson;
        fileJson = fileJson + ".json";
        return fileJson;
    }
};

struct Task {
    string taskName;
    string expirationDate;
    string status;
};

class Management {
   private:
    int chooseTask;
    // json dataJson;

    vector<Task> vectorData;
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

   public:
    Management(string fileName) {
        getDataInExistFile(fileName);
        while (1) {
            cout << "============ MENU ============" << endl;
            cout << "\t\033[33m1.\033[0m Assign new task\n\t\033[33m2.\033[0m Store data\n\t\033[33m3.\033[0m Task was resolved\n\t\033[33m4.\033[0m List all tasks\n\t\033[33m5.\033[0m Remove task\n\t\033[33m6.\033[0m Quit" << endl;
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
                case 4:
                    listAllTasks(fileName);
                    break;
                case 5:
                    removeByTask(fileName, false);
                    break;
                case 6:
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
    Init initObj;
    string jsonFile = initObj.setName();

    Management management(jsonFile);
    // management.assignTask(jsonFile);

    return 0;
}