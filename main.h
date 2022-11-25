#include"Base_Function.h"
void init();
void info();
void newfile(char* strp, int size, Dir_Entry* p);
void cd(string name, string& path, Dir_Entry* p);
void md(string name, int index, Dir_Entry* p);
void rd(char* strp, Dir_Entry* p, int this_index);
void cat(int index);
void del(int file_index);
void dir(Dir_Entry* p);
