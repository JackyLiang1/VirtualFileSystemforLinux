#include"Base_Function.h"
void dir(Dir_Entry* p)
{
    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
    //读完上一级目录
    //cout << p->index * 1024 + 32 << endl;//110592=108*1024
    f.seekg(p->index * 1024 + 32, ios::beg);
    int j = 1;
    string s;
    cout << "Name" << '\t' << "Type" << '\t' << "Permission"
        << '\t' << "Linkcount" << '\t' << "Size" << '\t' << "Address" << endl;
    for (; j < 30; j++)
    {
        f.seekg(p->index * 1024 + j * 32, ios::beg);
        f.read((char*)&r, sizeof(Dir_Entry));

        if (r.index > MIN_File_index)f.seekg(r.index, ios::beg);
        else f.seekg((r.index + 900) * 1024, ios::beg);
        f.read((char*)&ri, sizeof(Inode_Table));

        s = bf_show_str(r.filename);
        if (ri.index == 0 || r.filename == "");
        else
        {
            cout << s << '\t' << ri.type << '\t' << ri.permission
                << "\t\t" << ri.linkcount << "\t\t" << ri.size << "\t" << ri.blk_adres[0] << endl;
        }

    }
    f.close();
}