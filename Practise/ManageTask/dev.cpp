#include "filelib.hpp"
#include "filelib2.hpp"

int main() {
    HandleJson fileLib;
    fileLib.printFileContent("duc1.txt");

    HandleJson2 fileLib2;
    fileLib2.printFileContent("duc2.txt");
    fileLib2.putData();
    return 0;
}
