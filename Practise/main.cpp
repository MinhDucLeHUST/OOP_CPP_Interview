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
    // Management() {
    //     cout << "Choose your action: " << endl;
    //     cout << "\tAssign new task\n\tRemove task\n\tTask was resolved\n\tList all tasks" << endl;
    //     cout << "What do you want to do?";
    //     cin << task;
    // }
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