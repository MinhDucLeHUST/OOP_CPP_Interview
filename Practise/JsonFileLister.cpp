#include <dirent.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

class JsonFileLister {
   public:
    void listJsonFilesInCurrentDirectory() {
        std::string folderPath = ".";  // Assuming the code file is in the same directory as the JSON files

        DIR* dir;
        struct dirent* ent;
        bool foundJsonFile = false;
        if ((dir = opendir(folderPath.c_str())) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (hasJsonExtension(ent->d_name)) {
                    std::cout << ent->d_name << std::endl;
                    foundJsonFile = true;
                }
            }
            closedir(dir);
        } else {
            std::cerr << "Error opening directory" << std::endl;
        }

        if (!foundJsonFile) {
            std::cout << "No JSON files found in the directory." << std::endl;
        }
    }

   private:
    bool hasJsonExtension(const char* fileName) {
        const char* dot = strrchr(fileName, '.');
        return dot && !strcmp(dot, ".json");
    }
};

int main() {
    JsonFileLister lister;
    lister.listJsonFilesInCurrentDirectory();

    return 0;
}
