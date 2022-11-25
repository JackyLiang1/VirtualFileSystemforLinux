#include"Base_Function.h"
void info()
{
    cout << "Filesystem OS type:\tLinux" << endl;
    //i�������
    cout << "Inode count:\t\t" << 6400 << endl;
    //�̿��С1k,���Թ���102400����
    cout << "Block count:\t\t" << 102400 << endl;

    fstream f("C:\\disk.dat", ios::in | ios::binary);
    f.seekg(102400, ios::beg);
    f.read((char*)&Free_blocks, sizeof(int));
    f.read((char*)&Free_inode, sizeof(int));
    f.close();

    //ʣ���ʹ�õĿ�
    cout << "Free blocks:\t\t" << Free_blocks << endl;
    //ʣ���ʹ�õ�i���
    cout << "Free inode:\t\t" << Free_inode << endl;
    //��Ĵ�С
    cout << "Block size:\t\t" << 1024 << "B" << endl;
    //��һ��i���λ��
    cout << "First inode:\t\t" << 1001 << endl;
    //i����С
    cout << "Inode size:\t\t" << 64 << "B" << endl;
}