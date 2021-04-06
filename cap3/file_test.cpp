#include "apue.h"
#include <fcntl.h>
#include <iostream>

using namespace std;

/**************************
DATE : 2021-4-6
PARA : creat_hole-创建的文件是否带空洞；
DISC : 测试文件空洞，可以在文件末尾lseek，再在lseek之后写
        文件，可以写成功，但将导致文件存在空洞；
**************************/
void make_hole(bool creat_hole)
{
    int fd = 0;
    std::string buf1("czp and ma_mi");
    std::string buf2("buy a big house");
    std::string path;
    if(creat_hole)
    {
        path = "/home/czp/code/unix_book/cap3/czp.hole";
    }else
    {
        path = "/home/czp/code/unix_book/cap3/czp.nohole";
    }
    
    if((fd = creat(path.c_str(), FILE_MODE)) < 0)
    {
        cout << "creat error!" << endl;
    }
    if(write(fd, buf1.c_str(), buf1.length()) != buf1.length())
    {
        cout << "buf1 write error!" << endl;
    }
    if(creat_hole && (lseek(fd, 16380, SEEK_SET) == -1))
    {
        cout << "lseek error!" << endl;
    }
    if(write(fd, buf2.c_str(), buf2.length()) != buf2.length())
    {
        cout << "buf2 write error!" << endl;
    }
}

/**************************
DATE : 2021-4-6
PARA ：old_fd-旧的文件描述符； 
       new_fd-重定向的文件描述符；
DISC : 利用“/dev/fd/”下的文件描述符重新实现dup2()函数功能
TODO : 出错处理待完善；
**************************/
int my_dup2(int old_fd, int new_fd)
{
    string fd_path = "/dev/fd/" + new_fd;
    if(old_fd = open(fd_path.c_str(), O_RDWR) != -1)
    {
        cout << "open " << old_fd << " error!"  << endl;
    }

    return old_fd;
}

int main()
{
    // TEST : file hole;
    make_hole(false);
    make_hole(true);

    // TEST : myself dup2;
    int fd1 = open("/home/czp/code/unix_book/cap3/czp.nohole", O_RDWR);
    cout << "before" << fd1 << endl;
    fd1 = my_dup2(fd1, 0);
    cout << "after" << fd1 << endl;
    write(0, "kkkkkkkk", 3);

    return 1;
}