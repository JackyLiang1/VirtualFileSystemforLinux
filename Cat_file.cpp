#include"Base_Function.h"
void cat(int index)
{
    bf_read_file(index);
    cout << "write?[Y/N]" << endl;
    char choice = '?';
    cin >> choice;
    if (choice == 'y')
    {
        fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
        f.seekg(ri.index, ios::beg);
        f.read((char*)&ri, sizeof(Inode_Table));
        if (ri.permission == 'y')
        {
            ri.permission = 'n';
            f.seekp(ri.index, ios::beg);
            f.write((char*)&ri, sizeof(Inode_Table));
            f.close();

            cout << "Copy or Rewrite?[c/r]" << endl;
            cin >> choice;
            if (choice == 'r')
            {
                cout << "Please input the content:" << endl;
                string w;
                cin >> w;

                f.open("C:\\disk.dat", ios::in | ios::out | ios::binary);
                string null_string(1024, ' ');
                for (int j = 0; j < ri.size; j++)
                {
                    f.seekp(ri.blk_adres[j] * 1024, ios::beg);
                    f.write(null_string.c_str(), sizeof(char) * (null_string.size()));
                }

                int strsize = w.length();
                for (int j = 0; j < ri.size; j++)
                {
                    f.seekg(ri.blk_adres[j] * 1024, ios::beg);
                    if (strsize <= 1024)
                    {
                        f.write((char*)&w[0], strsize);
                        break;
                    }
                    else
                    {
                        f.write((char*)&w[0], 1024);
                        w = w.substr(1024);
                        strsize = w.length();
                    }
                }
                f.seekp(ri.index, ios::beg);
                ri.permission = 'y';
                f.write((char*)&ri, sizeof(Inode_Table));
                f.close();
            }
            else if (choice == 'c')
            {
                cout << "Please input the host address:\n";
                string host_add;
                cin >> host_add;
                //<host>C:\\test.txt
                string judge = host_add.substr(0, 6);
                if (judge != "<host>")
                {
                    cout << "Invalid syntax!" << endl;
                }
                else
                {
                    fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
                    string null_string(1024, ' ');
                    for (int j = 0; j < ri.size; j++)
                    {
                        f.seekp(ri.blk_adres[j] * 1024, ios::beg);
                        f.write(null_string.c_str(), sizeof(char) * (null_string.size()));
                    }
                    f.close();

                    host_add = host_add.substr(6);
                    bf_copy(host_add, index);
                }
            }

            fstream f("C:\\disk.dat", ios::in | ios::out | ios::binary);
            f.seekp(ri.index, ios::beg);
            ri.permission = 'y';
            f.write((char*)&ri, sizeof(Inode_Table));
            f.close();
        }
        else
        {
            cout << "Warning:Someone is writing this file!" << endl;
            f.close();
            //Çå¿ÕÊäÈë»º´æ
            char clear = ' ';
            while ((clear = getchar()) != '\n');
            return;
        }
    }
    //Çå¿ÕÊäÈë»º´æ
    char clear = ' ';
    while ((clear = getchar()) != '\n');
}