#pragma once

#include "constant_vals_funcs.h"

// 人物类，包含单个人物的所有信息。

struct Person {
    string name;
    int birth_year;
    int death_year;
    string parent;

    Person()
            : name("None"), birth_year(-1), death_year(-1), parent("None") {};

    Person(string, int, int, string);

    Person(string, int, int);

    Person &operator=(const Person &);
};