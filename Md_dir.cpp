#include"Base_Function.h"
void md(string name, int index, Dir_Entry* p)
{
    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
    Dir_Entry wd(index, name);
    //cout << wd.filename << endl;
    //目录块从前往后写
    f.seekp(index * 1024, ios::beg);
    f.write((char*)&wd, sizeof(Dir_Entry));

    int j = 1;
    for (; j <= 30; j++)
    {
        f.seekg(p->index * 1024 + j * 32, ios::beg);
        f.read((char*)&r, sizeof(Dir_Entry));
        if (strcmp(r.filename, "") == 0)
        {
            //cout << "find the empty place!" << endl;
            f.seekp(p->index * 1024 + j * 32);
            f.write((char*)&wd, sizeof(Dir_Entry));
            break;
        }
    }
    if (j == 31)cout << "The dir is full.Cannot makdir!" << endl;

    //写i结点块
    int iassign = index + 900;//要设置范围！！
    //cout << "i node index:" << index << endl;
    Inode_Table wi(index);
    wi.blk_adres[0] = iassign;
    wi.size = j - 1;
    f.seekp(iassign * 1024, ios::beg);
    //cout << "i node blk:" << iassign * 1024 << endl;
    f.write((char*)&wi, sizeof(Inode_Table));

    //cout << w.filename << "  " << w.index << endl;
    //cout << "dir is made successfully!" << endl;
    //写块位图
    //f.seekp(assign, ios::beg);
    //f.write("Y", 1);



    f.close();
}