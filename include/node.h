#pragma once

#include "constant_vals_funcs.h"
#include "person.h"

// 二叉树节点类，包含单个成员的val，及其左子树（儿子）和右子树（兄弟）的指针。
// 另外一些参数用于存储保存在队列/堆时的顺序信息，及被存储时的“代”信息。

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