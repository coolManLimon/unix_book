#include "apue.h"
#include <fcntl.h>
#include <iostream>

using namespace std;

void make_hole(bool creat_hole)
{
    /**************************
    DATE : 2021-4-6
    DISC : 测试文件空洞，可以在文件末尾lseek，再在lseek之后写
           文件，可以写成功，但将导致文件存在空洞；
    **************************/
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

int main()
{
    // test file hole;
    make_hole(false);
    make_hole(true);


    

    return 1;
}