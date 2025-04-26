#pragma once

#include "constant_vals_funcs.h"
#include "person.h"

// �������ڵ��࣬����������Ա��val�����������������ӣ������������ֵܣ���ָ�롣
// ����һЩ�������ڴ洢�����ڶ���/��ʱ��˳����Ϣ�������洢ʱ�ġ�������Ϣ��

class Node {
private:
    Person val;
    Node *nextCld;
    Node *nextBro;

    Node *next_used_ONLY_in_QUEUE = nullptr;
    int Generation_used_ONLY_in_Queue = -1;

    Node *next_used_ONLY_in_STACK = nullptr;
    int Generation_used_ONLY_in_Stack = -1;

public:
    friend class Data;

    friend class Queue;

    friend class Stack;

    Node();

    Node(const Person &);

    Node(const string &, int, int, const string &);

    Node(const string &, int, int, const string &, Node *, Node *);
};