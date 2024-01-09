/*
    phát triển xong các tính năng remove của task [5]
    còn task 3 chưa làm
    (!) lỗi => chưa clear hết data ra khỏi vector khi thực thi [5]
*/
#include <dirent.h>

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

struct Task {
    string taskName;
    string expirationDate;
    string status;
};

class TaskManager {
   private:
    int chooseTask;
    string befOrPast;
    int chooseKeyRemove;
    vector<Task> vectorData;
    bool isJsonFile(const char* fileName) {
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

    // Kiểm tra xem một tên file có phải là file JSON không
    bool hasJsonExtension(const string& fileName) {
        // Code kiểm tra phần mở rộng của tên file
    }

    // Thiết lập tên cho file JSON
    string setJsonFileName() {
        // Code thiết lập tên cho file JSON
    }

   public:
    // Hàm khởi tạo
    TaskManager() {
        // Code khởi tạo
    }

    // Giao diện chính của ứng dụng
    void mainMenu() {
        // Code giao diện chính của ứng dụng
    }

    // Phương thức thêm một task mới
    void addTask(string nameOfFile) {
        // Code thêm một task mới
    }

    void storeData(string nameOfFile, const vector<Task>& taskList) {
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

    // Phương thức xóa task theo các tiêu chí
    void removeTask(string nameOfFile) {
        // Code xóa task theo các tiêu chí
    }

    // Phương thức hiển thị tất cả các task
    void listAllTasks(string nameOfFile) {
        // Code hiển thị tất cả các task
    }
};

int main() {
    TaskManager taskManager;
    taskManager.mainMenu();

    return 0;
}
