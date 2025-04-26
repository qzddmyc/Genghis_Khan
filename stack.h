#pragma once

#include "constant_vals_funcs.h"
#include "node.h"

// 栈，先进后出。

class Stack {
private:
    Node *head;
public:
    Stack()
            : head(nullptr) {}

    ~Stack();

    void clear();

    void push(Node *);

    Node *pop();

    // 包含朝代信息的push。
    void push(Node *, int);

    bool IsEmpty();

    // 获取当前在栈中的所有存在的“代”数，利用位图返回一个int数，该数的二进制位“1”为表示该“代”存在。
    int GetIndexExistInStack_byBitmap();

};