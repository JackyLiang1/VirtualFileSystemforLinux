#include"Base_Function.h"
void init()
{
    Free_blocks = 102400 - 18;
    Free_inode = 6400 - 8;
    fstream f("C:\\disk.dat", ios::out | ios::binary);
    if (f.is_open())
    {
        //初始化块位图(0-99)
        f.seekp(0, ios::beg);
        int locate = 100 * 1024;
        for (int i = 0; i < locate; i++)
        {
            f.write("N", 1);
        }

        //0-99用来做块位图
        f.seekp(0, ios::beg);
        for (int i = 0; i < 100; i++)
        {
            f.write("Y", 1);
        }

        //100是超级块，初始化就会使用
        f.write("Y", 1);

        //102399是最后一块，作为根目录也是初始化就被使用了
        f.seekp(1024 * 100 - 1, ios::beg);
        f.write("Y", 1);

        //目录块
        Dir_Entry d1(DIRBLKBEG, "/");
        //cout << d1.filename << endl;
        //cout << sizeof(d1) << endl;
        Dir_Entry d2(DIRBLKBEG + 1, "bin");
        Dir_Entry d3(DIRBLKBEG + 2, "dev");
        Dir_Entry d4(DIRBLKBEG + 3, "lib");
        Dir_Entry d5(DIRBLKBEG + 4, "etc");
        Dir_Entry d6(DIRBLKBEG + 5, "usr");
        Dir_Entry d7(DIRBLKBEG + 6, "tmp");
        Dir_Entry d8(DIRBLKBEG + 7, "home");

        f.seekp(DIRBLKBEG * 1024, ios::beg);
        f.write((char*)&d1, sizeof(Dir_Entry));
        f.write((char*)&d2, sizeof(Dir_Entry));
        f.write((char*)&d3, sizeof(Dir_Entry));
        f.write((char*)&d4, sizeof(Dir_Entry));
        f.write((char*)&d5, sizeof(Dir_Entry));
        f.write((char*)&d6, sizeof(Dir_Entry));
        f.write((char*)&d7, sizeof(Dir_Entry));
        f.write((char*)&d8, sizeof(Dir_Entry));

        f.seekp((DIRBLKBEG + 1) * 1024, ios::beg);
        f.write((char*)&d2, sizeof(Dir_Entry));

        f.seekp((DIRBLKBEG + 2) * 1024, ios::beg);
        f.write((char*)&d3, sizeof(Dir_Entry));

        f.seekp((DIRBLKBEG + 3) * 1024, ios::beg);
        f.write((char*)&d4, sizeof(Dir_Entry));

        f.seekp((DIRBLKBEG + 4) * 1024, ios::beg);
        f.write((char*)&d5, sizeof(Dir_Entry));

        f.seekp((DIRBLKBEG + 5) * 1024, ios::beg);
        f.write((char*)&d6, sizeof(Dir_Entry));

        f.seekp((DIRBLKBEG + 6) * 1024, ios::beg);
        f.write((char*)&d7, sizeof(Dir_Entry));

        f.seekp((DIRBLKBEG + 7) * 1024, ios::beg);
        f.write((char*)&d8, sizeof(Dir_Entry));

        f.seekp(1024 * 1024 * 100 - 1024, ios::beg);
        for (int i = 0; i < 1024; i++)
        {
            f.write("R", 1);
        }

        Inode_Table i1(d1.index);
        i1.blk_adres[0] = 101;

        f.seekp((i1.index + 900) * 1024, ios::beg);
        f.write((char*)&i1, sizeof(Inode_Table));

        Inode_Table i2(d2.index);
        i2.blk_adres[0] = 102;
        f.seekp((i2.index + 900) * 1024, ios::beg);
        f.write((char*)&i2, sizeof(Inode_Table));

        Inode_Table i3(d3.index);
        i3.blk_adres[0] = 103;
        f.seekp((i3.index + 900) * 1024, ios::beg);
        f.write((char*)&i3, sizeof(Inode_Table));

        Inode_Table i4(d4.index);
        i4.blk_adres[0] = 104;
        f.seekp((i4.index + 900) * 1024, ios::beg);
        f.write((char*)&i4, sizeof(Inode_Table));

        Inode_Table i5(d5.index);
        i5.blk_adres[0] = 105;
        f.seekp((i5.index + 900) * 1024, ios::beg);
        f.write((char*)&i5, sizeof(Inode_Table));

        Inode_Table i6(d6.index);
        i6.blk_adres[0] = 106;
        f.seekp((i6.index + 900) * 1024, ios::beg);
        f.write((char*)&i6, sizeof(Inode_Table));

        Inode_Table i7(d7.index);
        i7.blk_adres[0] = 107;
        f.seekp((i7.index + 900) * 1024, ios::beg);
        f.write((char*)&i7, sizeof(Inode_Table));

        Inode_Table i8(d8.index);
        i8.blk_adres[0] = 108;
        f.seekp((i8.index + 900) * 1024, ios::beg);
        f.write((char*)&i8, sizeof(Inode_Table));


        //初始化超级块(100),记录可用的块数和i结点数
        f.seekp(1024 * 100, ios::beg);
        f.write((char*)&Free_blocks, sizeof(int));
        f.write((char*)&Free_inode, sizeof(int));

        //初始化根目录,用字符R来填充作为模拟
        f.seekp(1024 * 1024 * 100 - 1024, ios::beg);
        for (int i = 0; i < 1024; i++)
        {
            f.write("R", 1);
        }

        //cout << "The disk is created successfully.\n";
    }
    else
    {
        cout << "Fail to create the disk!\n";
    }
    f.close();
}