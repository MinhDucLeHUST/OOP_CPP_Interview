#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    // Read existing JSON data from the file
    std::ifstream file("data.json");
    json existingData;
    file >> existingData;
    file.close();

    // Create new JSON data to add to the existing data
    json newData;
    newData["name"] = "Minh Duc";
    newData["has"] = 30;
    newData["citdasdasdy"] = "Thanh Hoa city";

    // Add the new data to the existing JSON object
    existingData["newData"] = newData;

    // Write the updated JSON object back to the file
    std::ofstream outFile("data.json");
    outFile << std::setw(4) << existingData;
    outFile.close();

    std::cout << "New data has been added to data.json" << std::endl;

    return 0;
}
