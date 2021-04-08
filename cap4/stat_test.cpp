#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include "apue.h"

int main(int argc, char** argv)
{
    // file_mode test
    struct stat file_stat;

    for(int i = 0; i < argc; i++)
    {
        if(stat(argv[i], &file_stat) < 0)
        {
            std::cout << "stat error" << std::endl;
        }else if(S_ISDIR(file_stat.st_mode))
        {
            std::cout << "dir" << std::endl;
        }else if(S_ISLNK(file_stat.st_mode))
        {
            std::cout << "link" << std::endl;
        }else if(S_ISREG(file_stat.st_mode))
        {
            std::cout << "file" << std::endl;
        }
    }

    return 1;
}