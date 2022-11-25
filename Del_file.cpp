#include"Base_Function.h"
void del(int file_index)
{
    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
    string Dir_null(1024, NULL);
    Inode_Table none(0);
    int i = file_index;
    f.seekg(i, ios::beg);
    f.read((char*)&ri, sizeof(Inode_Table));

    Free_blocks += ri.size + 1;
    Free_inode++;
    bf_write_info();

    for (int j = 0; j < ri.size; j++)
    {
        f.seekp(ri.blk_adres[j] * 1024, ios::beg);
        f.write((char*)&Dir_null[0], 1024);
    }

    f.seekp(i, ios::beg);
    f.write((char*)&none, sizeof(Inode_Table));

    //дλͼ
    f.seekp(ri.blk_adres[0], ios::beg);
    int size = ri.size;
    for (int k = 0; k < size; k++)
    {
        f.write("N", 1);
    }
    f.close();
}