#ifndef JSONFILELISTER_HPP
#define JSONFILELISTER_HPP

#include <dirent.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

class JsonFileLister {
   public:
    void listJsonFilesInCurrentDirectory();
};

#endif  // JSONFILELISTER_HPP
