#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#define BITMAPEND 100
#define DIRBLKBEG 101
#define DIRBLKEND 1000
#define INODEBEG 1001
#define INODEEND 7400
#define DATABLKBEG 7401
#define DATABLKEND 102398
#define ROOTBLK 102399
#define MIN_File_index 1025024
char* bf_fix_name(string s);
struct Dir_Entry
{
    int index;//4B
    char filename[28];//28B
    Dir_Entry(int i, string s)
    {
        index = i;
        strcpy_s(filename, bf_fix_name(s));
    }
};
struct Inode_Table//64B
{
    int index;//4B
    char type;//1B
    char permission;//1B
    int linkcount;//4B
    int size;//4B
    int blk_adres[12] = { 0 };//4B*12?
    Inode_Table(int i, char t = '-', char p = 'y', int l = 0, int s = 0)
    {
        index = i;
        type = t;
        permission = p;
        linkcount = l;
        size = s;
    }
};
static Dir_Entry r(-1, "-");
static Dir_Entry Dir_null(0, "");
static Inode_Table ri(0);
extern int Free_blocks;
extern int Free_inode;
string bf_show_str(string s);
int bf_Get_Dir_Index(char* strp);
int bf_Assign_Dir_Index(char* strp);
void bf_copy(string host, int disk_index);
void bf_write_info();
Inode_Table bf_read_file(int index);