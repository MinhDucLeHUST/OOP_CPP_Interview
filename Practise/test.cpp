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
    Task insertTask;
    json dataJson;

   public:
    Management(string fileName) {
        cout << "Choose your action: " << endl;
        cout << "\t1. Assign new task\n\t2. Remove task\n\t3. Task was resolved\n\t4. List all tasks" << endl;
        cin >> chooseTask;
        // Init init_obj;
        // string fileName = init_obj.setName();
        switch (chooseTask) {
            case 1:
                assignTask();
                break;
            case 2:
                storeData(fileName);
            default:
                cout << "Error !!!\n";
                break;
        }
    }
    vector<Task> saveData;
    void assignTask() {
        cout << "Task: ";
        cin >> insertTask.taskName;

        cout << "Expiration date (dd/mm/yyyy): ";
        cin >> insertTask.expirationDate;

        cout << "List of status: " << endl;
        cout << "\tOpen\n\tHolding\n\tReopen\n\tDone" << endl;
        cout << "Status: ";
        cin >> insertTask.status;

        // dataJson[insertTask.taskName]["name"] = insertTask.taskName;
        // dataJson[insertTask.taskName]["expireDate"] = insertTask.expirationDate;
        // dataJson[insertTask.taskName]["state"] = insertTask.status;
    }
    void removeTask(string taskDelete, string fileJson) {
        ifstream inputFile(fileJson);
        json jsonData;
        inputFile >> jsonData;
        inputFile.close();

        // Remove data based on key
        string keyToRemove = "age";
        if (jsonData.find(keyToRemove) != jsonData.end()) {
            jsonData.erase(keyToRemove);
            cout << "Key '" << keyToRemove << "' and its associated value have been removed from the JSON." << endl;
        } else {
            cout << "Key '" << keyToRemove << "' not found in the JSON." << endl;
        }

        // Write the updated JSON back to the file
        ofstream outputFile(fileJson);
        outputFile << jsonData.dump(4);  // The '4' is for pretty printing
        outputFile.close();
    }
    // bool isDoneTask(){

    // }
    // void listAllTask();

    void storeData(string nameOfFile) {
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
    }
};

int main() {
    Init initObj;
    string jsonFile = initObj.setName();
    char stop = 'f';
    while (stop != 't') {
        Management managementObj(jsonFile);
        cout << "Press 't' to stop (if you want)";
        cin >> stop;
    }
    // managementObj.assignTask();
    // managementObj.assignTask();
    // managementObj.storeData(nameJson);

    return 0;
}