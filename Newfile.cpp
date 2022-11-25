#include"Base_Function.h"
void newfile(char* strp, int size, Dir_Entry* p)
{
    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
    int filesize = size;
    if (f.is_open())
    {
        //i是真实位置
        int i = INODEBEG * 1024;
        int end = INODEEND * 1024;
        f.seekg(i, ios::beg);
        for (; i <= end; i += 64)
        {
            f.read((char*)&ri, sizeof(Inode_Table));
            if (ri.index == 0)
            {
                break;
            }
        }
        if (i < end)
        {
            char blkmap = 'N';
            f.seekp(i, ios::beg);
            //cout << i << endl;
            Inode_Table wi(i);
            wi.size = filesize;
            wi.type = 'f';
            int j = DATABLKBEG;
            for (int k = 0; k < filesize; k++)
            {
                for (; j < DATABLKEND; j++)
                {
                    f.seekg(j, ios::beg);
                    f.read((char*)&blkmap, 1);
                    if (blkmap == 'N')
                    {
                        f.seekp(j, ios::beg);
                        f.write("Y", 1);
                        wi.blk_adres[k] = j;
                        //cout << wi.blk_adres[k] << endl;
                        j++;
                        break;
                    }
                }

            }
            if (j == DATABLKEND)
            {
                cout << "newfile:The datablocks is full!" << endl;
            }
            else
            {
                //写i结点
                f.seekp(i, ios::beg);
                f.write((char*)&wi, sizeof(Inode_Table));
            }
        }
        int dir_index = bf_Get_Dir_Index(p->filename);

        Dir_Entry wd(i, strp);
        int j = 1;
        for (; j <= 30; j++)
        {
            f.seekg(dir_index * 1024 + j * 32, ios::beg);
            f.read((char*)&r, sizeof(Dir_Entry));
            if (strcmp(r.filename, "") == 0)
            {
                break;
            }
        }
        if (j < 31)
        {
            f.seekp(dir_index * 1024 + j * 32, ios::beg);
            f.write((char*)&wd, sizeof(Dir_Entry));
        }
        else
        {
            cout << "newfile:The dir is full!" << endl;
        }

        f.close();
    }
}