#pragma once

#include "queue.h"

Queue::~Queue() {
    this->clear();
}

void Queue::clear() {
    while (!IsEmpty()) {
        this->pop();
    }
}

void Queue::push(Node *n) {
    if (head == nullptr) {
        head = n;
        return;
    }
    Node *tmp = head;
    while (tmp->next_used_ONLY_in_QUEUE) {
        tmp = tmp->next_used_ONLY_in_QUEUE;
    }
    tmp->next_used_ONLY_in_QUEUE = n;
}

void Queue::push(Node *n, int i) {
    if (n == nullptr) {
        cout << "Warning: empty node adding to the Queue!" << endl;
        return;
    }

    n->Generation_used_ONLY_in_Queue = i;

    if (head == nullptr) {
        head = n;
        return;
    }
    Node *tmp = head;
    while (tmp->next_used_ONLY_in_QUEUE) {
        tmp = tmp->next_used_ONLY_in_QUEUE;
    }
    tmp->next_used_ONLY_in_QUEUE = n;
}

Node *Queue::pop() {
    if (this->IsEmpty()) {
        cout << "Warning: Pop out the empty Queue!" << endl;
        return nullptr;
    }
    Node *ret = head;
    head = head->next_used_ONLY_in_QUEUE;
    ret->next_used_ONLY_in_QUEUE = nullptr;
    return ret;
}

bool Queue::IsEmpty() {
    return head == nullptr;
}