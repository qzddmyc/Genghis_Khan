#pragma once

// ���������еĻ���ͷ�ļ���������ĳ�ֵ����ͨ��������������.h��main�������и��ļ���

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

//�����ն���ɫ
void set_cout_RED();

void set_cout_GREEN();

//�ָ��ն���ɫ
void reset_cout_color();

//��ջ�������������
void clear_all();

//��ȡ�û������һ��int���֣��ұ�֤������������[fro, to]�ڣ�flag��������������ʱ�ı�����䡣
int GetIndex(int, int, int);

int min(int, int);

int max(int, int);