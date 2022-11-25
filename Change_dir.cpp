#include"Base_Function.h"
void cd(string name, string& path, Dir_Entry* p)
{
    Dir_Entry* tempp = p;
    if (name == "..")
    {
        if (path == "/");
        else
        {
            int pathsize = path.length();
            pathsize -= 2;
            for (; pathsize > 0; pathsize--)
            {
                if (path[pathsize] == '/')
                {
                    break;
                }
            }
            //更新cd后的路径
            path = path.substr(0, pathsize);
            if (pathsize == 0)
            {
                path = "/>";
                pathsize++;
            }
            else
            {
                path += ">";
            }
            string tem = path.substr(0, path.length() - 1);
            int idx = 0;
            for (int i = 0; i < pathsize; i++)
            {
                if (path[i] == '/')
                {
                    idx = i;
                }
            }
            if (p->index < 109)
            {
                tem = tem.substr(idx);
            }
            else
            {
                tem = tem.substr(idx + 1);
            }

            //p指向操作后的目录项
            char* up = bf_fix_name(tem);
            strcpy_s(p->filename, up);
            //cout << p->filename << endl;
            p->index = bf_Get_Dir_Index(p->filename);
            //cout << p << endl;
        }
    }
    else//切到下一级目录
    {
        Dir_Entry next(0, name);
        fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
        if (f.is_open())
        {
            int j = 1;
            for (; j < 30; j++)
            {
                f.seekg(p->index * 1024 + j * 32, ios::beg);
                f.read((char*)&r, sizeof(Dir_Entry));
                if (strcmp(r.filename, next.filename) == 0)
                {
                    next.index = r.index;
                    break;
                }
            }
            if (j == 30 || next.index > MIN_File_index)
            {
                cout << "cd:The dir doesn't exist!" << endl;
                return;
            }
            //保存上一级目录名
            strcpy_s(p->filename, next.filename);
            p->index = next.index;
            path = path.substr(0, path.length() - 1);
            //cout << name << endl;
            if (p->index < 109);
            else
            {
                path += '/';
            }
            path += name;
            path += ">";
        }
        f.close();
    }
}