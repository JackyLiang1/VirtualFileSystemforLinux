#include"Base_Function.h"
void rd(char* strp, Dir_Entry* p, int this_index)
{
    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
    //ɾ����Ŀ¼������
    f.seekp(this_index * 1024, ios::beg);
    for (int j = 0; j < 32; j++)
    {
        f.write((char*)&Dir_null, sizeof(Dir_Entry));
    }

    //ɾ����һ��Ŀ¼�麬�еı�Ŀ¼��
    for (int i = DIRBLKBEG; i <= DIRBLKEND; i++)
    {
        f.seekg(i * 1024, ios::beg);
        f.read((char*)&r, sizeof(Dir_Entry));
        if (strcmp(r.filename, p->filename) == 0)
        {
            int j = 1;
            for (; j < 31; j++)
            {
                f.seekp(i * 1024 + j * 32, ios::beg);
                f.read((char*)&r, sizeof(Dir_Entry));
                if (strcmp(r.filename, strp) == 0)
                {
                    f.seekp(i * 1024 + j * 32, ios::beg);
                    f.write((char*)&Dir_null, sizeof(Dir_Entry));
                    //cout << "haha" << endl;
                    break;
                }
            }
            break;
        }
    }

    //ɾ��i���
    int i_index = this_index + 900;
    //cout << i_index << endl;
    f.seekp(i_index * 1024, ios::beg);
    Inode_Table Inull(0);
    f.write((char*)&Inull, sizeof(Inode_Table));

    f.close();
}