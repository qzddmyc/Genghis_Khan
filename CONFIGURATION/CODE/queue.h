#pragma once

#include "constant_vals_funcs.h"
#include "node.h"

// 队列，先进先出。

class Queue {
private:
    Node *head;
public:
    Queue()
            : head(nullptr) {}

    ~Queue();

    void clear();

    void push(Node *);

    //包含第几代信息的push。
    void push(Node *, int);

    Node *pop();

    // 判断是否为空
    bool IsEmpty();
};