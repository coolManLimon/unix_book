#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include "apue.h"

// stat test
void file_mode_test(int num, char **files)
{
    struct stat file_stat;

    for(int i = 0; i < num; i++)
    {
        if(lstat(files[i], &file_stat) < 0)
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
}

void umask_test()
{
    umask(0);

    if(creat("czp", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) < 0)
    {
        // err_sys("creat file fail!");
    }

    umask(S_IRGRP | S_IWGRP);
    if(creat("mimi", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) < 0)
    {
        // err_sys("creat file fail!");
    }
    umask(0);

    return;
}

int main(int argc, char** argv)
{
    // 文件stat；
    file_mode_test(argc, argv);

    // 文件umask 
    umask_test();

    printf("%8.2f\n", 12.1);


    return 1;
}