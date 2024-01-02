#include <fstream>
#include <iostream>
#include <vector>

#include "nlohmann/json.hpp"
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
    std::string taskName;
    std::string expirationDate;
    std::string status;
};

class TaskManager {
   private:
    std::vector<Task> taskList;

    void saveDataToJson(string nameOfFile) {
        json jsonData;

        for (const auto& task : taskList) {
            json taskJson;
            taskJson["taskName"] = task.taskName;
            taskJson["expirationDate"] = task.expirationDate;
            taskJson["status"] = task.status;
            jsonData.push_back(taskJson);
        }

        std::ofstream file(nameOfFile);
        file << jsonData.dump(4);  // Lưu JSON vào tệp với định dạng thụt lề
        file.close();
    }

   public:
    void start(string nameOfFile) {
        // Đọc dữ liệu từ file JSON nếu file đã tồn tại
        std::ifstream inputFile(nameOfFile);
        if (inputFile.good()) {
            json jsonData;
            inputFile >> jsonData;
            for (const auto& task : jsonData) {
                Task newTask;
                newTask.taskName = task["taskName"];
                newTask.expirationDate = task["expirationDate"];
                newTask.status = task["status"];
                taskList.push_back(newTask);
            }
            inputFile.close();
        }

        while (true) {
            Task insertTask;

            std::cout << "Task: ";
            std::cin >> insertTask.taskName;

            std::cout << "Expiration date (dd/mm/yyyy): ";
            std::cin >> insertTask.expirationDate;

            std::cout << "List of status: " << std::endl;
            std::cout << "\tOpen\n\tHolding\n\tReopen\n\tDone" << std::endl;
            std::cout << "Status: ";
            std::cin >> insertTask.status;

            taskList.push_back(insertTask);

            saveDataToJson(nameOfFile);  // Lưu dữ liệu vào file JSON sau mỗi lần nhập

            std::string continueInput;
            std::cout << "Exit to quit: ";
            std::cin >> continueInput;

            if (continueInput == "exit") {
                break;
            }
        }
    }
};

int main() {
    Init initObj;
    string jsonFile = initObj.setName();
    TaskManager taskManager;
    taskManager.start(jsonFile);

    return 0;
}
