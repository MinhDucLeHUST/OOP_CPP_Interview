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
        for (auto& i : taskList) {
            cout << "--- Task Name: " << i.taskName << ", Expiration Date: " << i.expirationDate << ", Status: " << i.status << endl;
        }

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

   public:
    Management(string fileName) {
        cout << "==== Choose number of your action ====" << endl;
        cout << "\t1. Assign new task\n\t2. Store data\n\t3. Task was resolved\n\t4. List all tasks\n\t5. Remove task\n\t6. Quit" << endl;
        cin >> chooseTask;
        // Init init_obj;
        // string fileName = init_obj.setName();
        switch (chooseTask) {
            case 1:
                assignTask(fileName);
                break;
            case 2:
                storeData(fileName, vectorData);
                break;
            case 6:
                exit(0);
            default:
                cout << "Error !!!\n";
                break;
        }
    }
    void assignTask(string nameOfFile) {
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
        while (1) {
            Task insertTask;
            cout << "Task: ";
            cin >> insertTask.taskName;

            cout << "Expiration date (dd/mm/yyyy): ";
            cin >> insertTask.expirationDate;

            cout << "List of status: " << endl;
            cout << "\tOpen\n\tHolding\n\tReopen\n\tDone" << endl;
            cout << "Status: ";
            cin >> insertTask.status;

            vectorData.push_back(insertTask);
            storeData(nameOfFile, vectorData);

            string continueInput;
            cout << "'Exit' to quit: ";
            cin >> continueInput;

            if (continueInput == "exit") {
                exit(0);
            }
        }
    }
    void removeTask(string taskDelete, string fileJson) {
    }
};

int main() {
    Init initObj;
    string jsonFile = initObj.setName();

    Management management(jsonFile);
    management.assignTask(jsonFile);

    return 0;
}