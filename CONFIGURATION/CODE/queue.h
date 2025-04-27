#pragma once

#include "constant_vals_funcs.h"
#include "node.h"

// ���У��Ƚ��ȳ���

class Queue {
private:
    Node *head;
public:
    Queue()
            : head(nullptr) {}

    ~Queue();

    void clear();

    void push(Node *);

    //�����ڼ�����Ϣ��push��
    void push(Node *, int);

    Node *pop();

    // �ж��Ƿ�Ϊ��
    bool IsEmpty();
};