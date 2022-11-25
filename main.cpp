#pragma once
#include"Base_Function.h"
#include"main.h"

int main()
{
    string input;
    Dir_Entry* p = new Dir_Entry(DIRBLKBEG + 7, "home");
    string path = "/home>";
    cout << path;
    while (getline(cin, input))
    {   
        if (input == "init" || input == "INIT")
        {
            init();
            cout << "Init:Initialized successfully!" << endl;
            cout << path;
            continue;
        }
        if (input == "exit" || input == "EXIT")
        {
            cout << "Exit successfully!" << endl;
            exit(0);
        }
        int index1= input.find_first_of(' ');
        string fir_str;
        string sec_str;       
        fir_str = input.substr(0, index1);
        sec_str = input.substr(index1 + 1);
        int index2 = sec_str.find_first_of(' ');
        char* strp = bf_fix_name(sec_str);
        //如果输入有空格，比如md newfile而不是info或check指令
        if (index1 != -1)
        {    
            //文件名不允许有空格
            if (fir_str == "newfile" && index2 != -1)
            {
                //判断第三段是否是文件大小
                string third_str = sec_str.substr(index2 + 1);
                int toint = atoi(third_str.c_str());
                string tostr = to_string(toint);
                sec_str = sec_str.substr(0, index2);
                strp = bf_fix_name(sec_str);
                //还需要判断大小是否在长度范围内（0~12kb）
                if (tostr != third_str || toint <= 0 || toint > 12)
                {
                    cout << "Invalid syntax!" << endl;
                }
                else
                {
                    newfile(strp, toint, p);
                    Free_blocks -= toint + 1;
                    Free_inode--;
                    bf_write_info();
                }
            }
            else if (fir_str == "cd")
            {
                cd(sec_str, path, p);
            }
            else if (fir_str == "md")
            {
                if (bf_Get_Dir_Index(strp)!=-1)
                {
                    cout << "md:The dir has existed!" << endl;
                }
                else
                {
                    int assign = bf_Assign_Dir_Index(strp);
                    if (assign < 0)
                    {
                        cout << "The dirblk is full!" << endl;
                    }
                    else
                    {
                        md(sec_str, assign, p);
                        Free_blocks--;
                        Free_inode--;
                        bf_write_info();
                    }
                }
            }
            else if (fir_str == "rd")
            {
                int i = bf_Get_Dir_Index(strp);
                if (i == -1)cout << "rd:The dir doesn't exist!" << endl;
                else
                {
                    rd(strp, p,i);
                    Free_blocks++;
                    Free_inode++;
                    bf_write_info();
                }       
            }
            else if (fir_str == "cat")
            {
                fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
                if (f.is_open())
                {
                    char* strp = bf_fix_name(sec_str);
                    int file_index = 0;
                    int j = 1;
                    int dir_index = bf_Get_Dir_Index(p->filename);
                    for (; j < 31; j++)
                    {
                        f.seekg(dir_index * 1024 + j * 32, ios::beg);
                        f.read((char*)&r, sizeof(Dir_Entry));
                        if (strcmp(r.filename, strp) == 0)
                        {
                            file_index = r.index;
                            j = 30;
                        }
                    }
                    f.close();
                    if (j != 31 || file_index < 1001 * 1024)cout << "cat:The file doesn't exist!" << endl;
                    else cat(file_index);
                }
            }
            else if (fir_str == "del")
            {
                int dir_index = bf_Get_Dir_Index(p->filename);
                int file_index = 0;
                int j = 1;
                fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
                for (; j < 31; j++)
                {
                    f.seekg(dir_index * 1024 + j * 32, ios::beg);
                    f.read((char*)&r, sizeof(Dir_Entry));
                    if (strcmp(r.filename, strp) == 0)
                    {
                        //写空
                        f.seekp(dir_index * 1024 + j * 32, ios::beg);
                        f.write((char*)&Dir_null, sizeof(Dir_Entry));

                        //获得i结点索引
                        file_index = r.index;
                        j = 30;
                    }
                }
                f.close();

                if (j != 31 || file_index < 1001 * 1024)
                {
                    cout << "del:The file doesn't exist!" << endl;
                }
                else
                {
                    del(file_index);
                }
            }
            else cout << "Invalid syntax!" << endl;
        }
        else if (input == "info")info();
        else if (input == "dir")dir(p);
        else if (input == "check")
        {

        }
        else cout << "Invalid syntax!" << endl;
        cout << path;
    }
}

