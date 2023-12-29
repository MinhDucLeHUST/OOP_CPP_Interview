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

class Management {
   private:
    struct Task {
        string taskName;
        string expirationDate;
        string status;
    };
    int chooseTask;

   public:
    json dataJson;
    Task insertTask;
    vector<Task> saveData;
    Management(string fileName) {
        cout << "==== Choose number of your action ====" << endl;
        cout << "\t1. Assign new task\n\t2. Storage data\n\t3. Task was resolved\n\t4. List all tasks\n\t5. Remove task" << endl;
        cin >> chooseTask;
        // Init init_obj;
        // string fileName = init_obj.setName();
        switch (chooseTask) {
            case 1:
                assignTask(fileName);
                break;
            case 2:
                storeData(fileName, saveData);
                break;
            default:
                cout << "Error !!!\n";
                break;
        }
    }

    void assignTask(string nameOfFile) {
        cout << "Task: ";
        cin >> insertTask.taskName;

        cout << "Expiration date (dd/mm/yyyy): ";
        cin >> insertTask.expirationDate;

        cout << "List of status: " << endl;
        cout << "\tOpen\n\tHolding\n\tReopen\n\tDone" << endl;
        cout << "Status: ";
        cin >> insertTask.status;

        saveData.push_back(insertTask);
        for (auto& i : saveData) {
            cout << "--- Task Name: " << i.taskName << ", Expiration Date: " << i.expirationDate << ", Status: " << i.status << endl;
        }

        json jsonData;

        for (const auto& task : saveData) {
            json taskData;
            taskData["taskName"] = task.taskName;
            taskData["expirationDate"] = task.expirationDate;
            taskData["status"] = task.status;
            jsonData.push_back(taskData);
        }

        ofstream file(nameOfFile, ios::app);
        file << jsonData.dump(4);  // Pretty-print with 4 spaces
        file.close();
        // dataJson[insertTask.taskName]["name"] = insertTask.taskName;
        // dataJson[insertTask.taskName]["expireDate"] = insertTask.expirationDate;
        // dataJson[insertTask.taskName]["state"] = insertTask.status;
    }
    void removeTask(string taskDelete, string fileJson) {
    }

    void storeData(string nameOfFile, vector<Task> dataToJson) {
        // saveData.push_back(insertTask);
        // cout << "check inside number 2" << endl;
        for (auto& i : dataToJson) {
            cout << "--- Task Name: " << i.taskName << ", Expiration Date: " << i.expirationDate << ", Status: " << i.status << endl;
        }

        json jsonData;

        for (const auto& task : dataToJson) {
            json taskData;
            taskData["taskName"] = task.taskName;
            taskData["expirationDate"] = task.expirationDate;
            taskData["status"] = task.status;
            jsonData.push_back(taskData);
        }

        ofstream file(nameOfFile, ios::app);
        file << jsonData.dump(4);  // Pretty-print with 4 spaces
        file.close();
    }
};

int main() {
    Init initObj;
    string jsonFile = initObj.setName();
    char stop = 'n';
    while (stop != 'y') {
        Management managementObj(jsonFile);
        cout << "Press 'y' to stop, 'n' to continue: ";
        cin >> stop;
    }

    return 0;
}