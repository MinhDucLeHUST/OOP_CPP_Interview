#include <cstdlib>
#include <ctime>
#include <fstream>

#include "iostream"
#include "nlohmann/json.hpp"
#include "string"

using namespace std;

using json = nlohmann::json;

class Management {
   private:
    typedef struct {
        int day;
        int month;
        int year;
    } date_t;
    string task;
    string state;

   public:
    void assignTask() {
        date_t expireDate;
        cout << "Task: ";
        cin >> task;

        cout << "Expiration date: " << endl;
        cout << "Day: ";
        cin >> expireDate.day;
        cout << "Month: ";
        cin >> expireDate.month;
        cout << "Year: ";
        cin >> expireDate.year;

        cout << "List of status: " << endl;
        cout << "\tOpen\n\tHolding\n\tReopen\n\tDone" << endl;
        cout << "Status: ";
        cin >> state;

        json data;
        data[task]["name"] = task;
        data[task]["expireDate"]["day"] = expireDate.day;
        data[task]["expireDate"]["month"] = expireDate.month;
        data[task]["expireDate"]["year"] = expireDate.year;
        data[task]["state"] = state;

        // Write the JSON object to a file
        ofstream file("data.json", ios::app);
        file << data.dump(4);
        file.close();

        cout << "Data has been stored in data.json" << endl;
    }
    void removeTask() {
    }
    // bool isDoneTask();
    // void listAllTask();

    // void storeData()
};

int main() {
    Management manageTask;
    manageTask.assignTask();

    // manageTask.assignTask();
    return 0;
}