#pragma once

#include "constant_vals_funcs.h"

int GAP = 18;

int INF_YEAR = 2025;

int MAX_AGE = 120;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void set_cout_RED() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}

void set_cout_GREEN() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}

void reset_cout_color() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void clear_all() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int GetIndex(int fro, int to, int flag) {
    int idx;
    while (!(cin >> idx) or idx > to or idx < fro) {
        if (flag == 0)
            cout << "输入格式或内容错误，请重新输入：";
        if (flag == 1)
            cout << "输入错误，年份应在" << fro << "至" << to << "内！请重新输入：";
        clear_all();
    }
    clear_all();
    return idx;
}

int min(int a, int b) {
    if (a <= b)
        return a;
    return b;
}

int max(int a, int b) {
    if (a <= b)
        return b;
    return a;
}