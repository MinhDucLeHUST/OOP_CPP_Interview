#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    // Read existing JSON data from the file
    // std::ifstream file("input.json");
    // json existingData;
    // file >> existingData;
    // file.close();
    std::ifstream inputFile("input.json");
    if (inputFile.is_open()) {
        std::ifstream file("input.json");
        json existingData;
        file >> existingData;
        file.close();
        json newData = {
            {"expireDate", {{"day", 20}, {"month", 12}, {"year", 2024}}},
            {"name", "MinhDuc"},
            {"state", "InProgress"}};
        existingData["bug10"] = newData;

        // Write the updated JSON object back to the file
        std::ofstream outFile("input.json", std::ios::app);
        outFile << std::setw(4) << existingData;
        outFile.close();

        std::cout << "New data has been added to input.json" << std::endl;
        inputFile.close();
    } else {
        std::ofstream fileCreate("input.json", std::ios_base::app);
        fileCreate << "[" << std::endl;
        fileCreate << "]" << std::endl;
        // Close the file
        fileCreate.close();
        std::cout << "Characters { and } have been added to data.json" << std::endl;
    }
    // Add new data to the JSON object
    // json newData = {
    //     {"expireDate", {{"day", 20}, {"month", 12}, {"year", 2024}}},
    //     {"name", "bug10"},
    //     {"state", "InProgress"}};
    // existingData["bug10"] = newData;

    // // Write the updated JSON object back to the file
    // std::ofstream outFile("data.json");
    // outFile << std::setw(4) << existingData;
    // outFile.close();

    // std::cout << "New data has been added to data.json" << std::endl;

    return 0;
}
