#include <iostream>
#include "../include/sys/path.h"

using namespace std;


int main()
{
    char dir[200];
    cout << "Enter a directory (ends with \'\\\'): ";
    cin.getline(dir, 200);

    std::vector<std::string> files;
    std::vector<std::string> dirs;
    listFiles(dir, files, dirs);
    for (auto s : files)
        std::cout << s << std::endl;

    for (auto s : dirs)
        std::cout << s << std::endl;

    return 0;
}
