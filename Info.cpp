#include"Base_Function.h"
void info()
{
    cout << "Filesystem OS type:\tLinux" << endl;
    //i结点总数
    cout << "Inode count:\t\t" << 6400 << endl;
    //盘块大小1k,所以共有102400个块
    cout << "Block count:\t\t" << 102400 << endl;

    fstream f("C:\\disk.dat", ios::in | ios::binary);
    f.seekg(102400, ios::beg);
    f.read((char*)&Free_blocks, sizeof(int));
    f.read((char*)&Free_inode, sizeof(int));
    f.close();

    //剩余可使用的块
    cout << "Free blocks:\t\t" << Free_blocks << endl;
    //剩余可使用的i结点
    cout << "Free inode:\t\t" << Free_inode << endl;
    //块的大小
    cout << "Block size:\t\t" << 1024 << "B" << endl;
    //第一个i结点位置
    cout << "First inode:\t\t" << 1001 << endl;
    //i结点大小
    cout << "Inode size:\t\t" << 64 << "B" << endl;
}