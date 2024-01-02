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
        cout << "Insert name of file: ";
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
        cout << "[2] Data saving" << endl;

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
            cout << "\t1. Assign new task\n\t2. Store data\n\t3. Task was resolved\n\t4. List all tasks\n\t5. Remove task\n\t6. Quit" << endl;
            cout << "---> Enter active (number): ";
            cin >> chooseTask;
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
                    removeByTask(fileName);
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
    void removeByTask(string nameOfFile) {
        bool flag = false;
        string taskRemove;
        cout << "[5] Enter name of task to remove: ";
        cin >> taskRemove;
        ifstream input(nameOfFile);
        json jsonData;
        input >> jsonData;
        input.close();

        for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
            if (it->at("taskName") == taskRemove) {
                flag = true;
                jsonData.erase(it);
                break;
            }
        }
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