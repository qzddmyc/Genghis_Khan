#pragma once

// 保存了所有的基本头文件，及定义的常值，普通函数，其余所有.h及main均包含有该文件。

#include "iostream"
#include "string"
#include "fstream"
#include "sstream"
#include "iomanip"
#include "limits"
#include "windows.h"

using namespace std;

extern int GAP;
extern int INF_YEAR;
extern int MAX_AGE;

extern HANDLE hConsole;

//更改终端颜色
void set_cout_RED();

void set_cout_GREEN();

//恢复终端颜色
void reset_cout_color();

//清空缓冲区所有内容
void clear_all();

//获取用户输入的一个int数字，且保证该数字在区间[fro, to]内，flag决定了输入有误时的报错语句。
int GetIndex(int, int, int);

int min(int, int);

int max(int, int);