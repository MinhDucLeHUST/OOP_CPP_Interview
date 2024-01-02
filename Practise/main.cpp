#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stack>

#include "iostream"
#include "nlohmann/json.hpp"
#include "string"

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
    string expireDate;
    string task;
    string state;
    json data;

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
                for (auto& i : vectorData) {
                    cout << "1--- Task Name: " << i.taskName << ", Expiration Date: " << i.expirationDate << ", Status: " << i.status << endl;
                }
                storeData(fileName, vectorData);
                break;
            case 6:
                exit(0);
            default:
                cout << "Error !!!\n";
                break;
        }
    }

    void assignTask() {
        cout << "Task: ";
        cin >> task;

        cout << "Expiration date (dd/mm/yyyy): ";
        cin >> expireDate;

        cout << "List of status: " << endl;
        cout << "\tOpen\n\tHolding\n\tReopen\n\tDone" << endl;
        cout << "Status: ";
        cin >> state;

        data[task]["name"] = task;
        data[task]["expireDate"] = expireDate;
        data[task]["state"] = state;
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
        stack<json> dataStack;
        dataStack.push(data);
        json jsonArray;
        while (!dataStack.empty()) {
            jsonArray.push_back(dataStack.top());
            cout << "--- " << jsonArray << endl;
            dataStack.pop();
        }

        ofstream file(nameOfFile, ios::app);
        file << jsonArray.dump(4);
        file.close();

        cout << "=== Data has been stored in data.json ===" << endl;
    }
};

int main() {
    Management managementObj;
    Init initObj;
    string nameJson = initObj.setName();
    managementObj.assignTask();
    managementObj.assignTask();
    managementObj.storeData(nameJson);

    return 0;
}