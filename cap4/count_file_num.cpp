#include "apue.h"
#include <iostream>
#include <dirent.h>
#include <limits.h>

#define F_DIR   1
#define F_FILE  2
#define F_LINK  3


static long lnk, dir, file, socket, fifo, blk, chr, tot;

int myFtw(std::string pathName);
void doIt(std::string pathName, int type, const struct stat *stat_ptr);

void doIt(std::string pathName, int type, const struct stat *stat_ptr)
{
    switch (type)
    {
    case F_DIR:
        dir++;
        break;
    case F_FILE:
        switch (stat_ptr->st_mode & S_IFMT)
        {
            case S_IFSOCK:  socket++;   break;
            case S_IFBLK:   blk++;      break;
            case S_IFCHR:   chr++;      break;
            case S_IFLNK:   lnk++;     break;
            case S_IFIFO:   fifo++;     break;
            default:                    break;
        }
    default:
        std::cout << "can't read dir:" << pathName << std::endl;
        break;
    }
}

int myFtw(std::string pathName)
{
    struct stat     stat_buf;
    struct dirent   *dir = NULL;
    DIR             *dp = NULL;
    int             ret = 0;

    if (lstat(pathName.c_str(), &stat_buf))
    {
        std::cout << "lstat error!" << std::endl;
    }
    if (S_ISDIR(stat_buf.st_mode) == 0)     // 是文件而非目录
    {
        doIt(pathName, F_FILE, &stat_buf);
    }

    // 目录
    doIt(pathName, F_DIR, &stat_buf);
    if ((dp = opendir(pathName.c_str())) != NULL)
    {
        while ((dir = readdir(dp)) != NULL)
        {
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            {
                continue;
            }
            else
            {
                std::string tmp = pathName.append("/").append(dir->d_name);
                myFtw(tmp);
            }
        }
        return 1;
        
    }

}

int main(int argc, char **argv)
{
    int ret = 0;

    if (argc > 2)
    {
        std::cout << "cannot use as this way!\n";
    }

    ret = myFtw(argv[1]);
    tot = lnk + dir + file + socket + fifo + blk + chr;

    printf("link num = %7ld, %5.2f %%\n", lnk, lnk * 100.0 / tot);
    printf("dir num = %7ld, %5.2f %%\n", dir, dir * 100.0 / tot);
    printf("file num = %7ld, %5.2f %%\n", file, file * 100.0 / tot);
    printf("socket num = %7ld, %5.2f %%\n", socket, socket * 100.0 / tot);
    printf("fifo num = %7ld, %5.2f %%\n", fifo, fifo * 100.0 / tot);
    printf("blk num = %7ld, %5.2f %%\n", blk, blk * 100.0 / tot);
    printf("chr num = %7ld, %5.2f %%\n", chr, chr * 100.0 / tot);
}