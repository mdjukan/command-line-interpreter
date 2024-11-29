#include "touch.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <iostream>
#include <sys/stat.h>
//#include <filesystem>
Touch::Touch(std::string arg) :arg(arg)
{

}

void Touch::exec()
{
    struct stat fileStat;
    //std::filesystem::path currentPath = std::filesystem::current_path();
    //std::string folderPath = "C:\\Users\\SunnySnowy\\Downloads\\command-line-interpreter-main\\command-line-interpreter-main\\";
    if (stat(arg.c_str(), &fileStat) == 0) {
        // File exists: Report an error
        (*output) << " File '" << arg << "' already exists.\n";
    }
    else {
        // File does not exist: Create the file
        std::ofstream new_file(arg);
        if (new_file) {
            
            (*output) << "File '" << arg << "' created successfully.\n";
        }
        else {
            (*output) << " Unable to create the file.\n";
        }
    }
}
