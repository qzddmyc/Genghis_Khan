#pragma once

#include "stack.h"

Stack::~Stack() {
    this->clear();
}

void Stack::clear() {
    while (!IsEmpty()) {
        this->pop();
    }
}

void Stack::push(Node *n) {
    if (head == nullptr) {
        head = n;
        return;
    }
    Node *tmp = head;
    while (tmp->next_used_ONLY_in_STACK) {
        tmp = tmp->next_used_ONLY_in_STACK;
    }
    tmp->next_used_ONLY_in_STACK = n;
}

void Stack::push(Node *n, int i) {
    if (n == nullptr) {
        cout << "Warning: empty node adding to the Stack!" << endl;
        return;
    }

    n->Generation_used_ONLY_in_Stack = i;

    if (head == nullptr) {
        head = n;
        return;
    }
    Node *tmp = head;
    while (tmp->next_used_ONLY_in_STACK) {
        tmp = tmp->next_used_ONLY_in_STACK;
    }
    tmp->next_used_ONLY_in_STACK = n;
}

Node *Stack::pop() {
    if (this->IsEmpty()) {
        cout << "Warning: Pop out the empty Stack!" << endl;
        return nullptr;
    }
    Node *ret = head;
    if (!ret->next_used_ONLY_in_STACK) {
        head = nullptr;
        return ret;
    }
    while (ret->next_used_ONLY_in_STACK->next_used_ONLY_in_STACK) {
        ret = ret->next_used_ONLY_in_STACK;
    }
    Node *tmp = ret->next_used_ONLY_in_STACK;
    ret->next_used_ONLY_in_STACK = nullptr;
    return tmp;
}

bool Stack::IsEmpty() {
    return head == nullptr;
}

int Stack::GetIndexExistInStack_byBitmap() {
    int ans = 0;
    Node *tmp = head;
    while (tmp) {
        ans |= (1 << tmp->Generation_used_ONLY_in_Stack);
        tmp = tmp->next_used_ONLY_in_STACK;
    }
    return ans;
}