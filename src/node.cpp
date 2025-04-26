#pragma once

#include "node.h"

Node::Node() {
    val = Person();
    nextCld = nullptr;
    nextBro = nullptr;
}

Node::Node(const Person &v) {
    val = v;
    nextCld = nullptr;
    nextBro = nullptr;
}

Node::Node(const string &_n, int _b, int _d, const string &_p) {
    val = Person(_n, _b, _d, _p);
    nextCld = nullptr;
    nextBro = nullptr;
}

Node::Node(const string &_n, int _b, int _d, const string &_p, Node *nC, Node *nB) {
    val = Person(_n, _b, _d, _p);
    nextCld = nC;
    nextBro = nB;
}