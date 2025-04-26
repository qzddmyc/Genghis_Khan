#pragma once

#include "constant_vals_funcs.h"
#include "node.h"

// ջ���Ƚ������

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

    // ����������Ϣ��push��
    void push(Node *, int);

    bool IsEmpty();

    // ��ȡ��ǰ��ջ�е����д��ڵġ�������������λͼ����һ��int���������Ķ�����λ��1��Ϊ��ʾ�á��������ڡ�
    int GetIndexExistInStack_byBitmap();

};