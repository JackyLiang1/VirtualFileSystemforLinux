#include"Base_Function.h"

int Free_blocks = 102400;
int Free_inode = 6400;

char* bf_fix_name(string s)
{
    char* fix = new char[28];
    int len = s.length();
    s.copy(fix, len);
    for (int i = len; i < 27; i++)
    {
        fix[i] = '*';
    }
    fix[27] = '\0';
    return fix;
}
int bf_Assign_Dir_Index(char* strp)
{
    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
    int dassign = 0;
    int i = DIRBLKBEG;
    for (; i <= DIRBLKEND; i++)
    {
        f.seekg(i * 1024, ios::beg);
        f.read((char*)&r, sizeof(Dir_Entry));
        if (r.index == 0)
        {
            dassign = i;
            break;
        }
    }
    f.close();
    if (i > DIRBLKEND)return -1;
    else return dassign;

}
int bf_Get_Dir_Index(char* strp)
{
    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
    int i = 0;
    for (i = DIRBLKBEG; i <= DIRBLKEND; i++)
    {
        f.seekg(i * 1024, ios::beg);
        f.read((char*)&r, sizeof(Dir_Entry));
        if (strcmp(r.filename, strp) == 0)
        {
            return i;
        }
    }
    f.close();
    return -1;
}
string bf_show_str(string s)
{
    int cut = s.find_first_of('*');
    //cout << cut << endl;
    s = s.substr(0, cut);
    return s;
}
Inode_Table bf_read_file(int index)
{
    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
    f.seekg(index, ios::beg);
    f.read((char*)&ri, sizeof(Inode_Table));

    char rstr[1025];
    rstr[1024] = '\0';
    //cout << "The file datablks are :" << endl;

    /*for (int j = 0; j < ri.size; j++)
    {
        f.seekg(ri.blk_adres[j] * 1024, ios::beg);
        f.read((char*)&rstr, 1024);
        for (int i = 0; i < 1024; i++)
        {
            cout << rstr[i];
        }
        //cout << ri.blk_adres[j]-7400 << "\t";
    }*/

    string null_string(1024, ' ');
    bool isnull = 1;
    for (int j = 0; j < ri.size; j++)
    {
        f.seekg(ri.blk_adres[j] * 1024, ios::beg);
        f.read((char*)&rstr, sizeof(char) * (null_string.size()));
        for (int i = 0; i < 1024; i++)
        {
            if (rstr[i] != ' ')isnull = 0;
            break;
        }
        if (isnull == 0)
        {
            for (int i = 0; i < 1024; i++)
            {
                cout << rstr[i];
            }
        }
        isnull = 1;
    }


    cout << endl;
    return ri;
}
void bf_copy(string host, int disk_index)
{
    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
    Inode_Table des = bf_read_file(disk_index);
    char c = ' ';
    ifstream file_in(host);
    if (file_in.is_open());
    else
    {
        cout << "copy:The host file doesn't exist!\n";
        return;
    }
    f.seekp(ri.blk_adres[0] * 1024, ios::beg);
    file_in >> noskipws;
    while (file_in >> c)
    {
        //<host>C:\\test.txt
        f.write((char*)&c, 1);
    }
    f.close();
}
void bf_write_info()
{
    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
    f.seekp(1024 * 100, ios::beg);
    f.write((char*)&Free_blocks, sizeof(int));
    f.write((char*)&Free_inode, sizeof(int));
    f.close();
}
