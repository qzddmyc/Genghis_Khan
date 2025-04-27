#pragma once

#include "person.h"

Person::Person(string _name, int b_y, int d_y, string _parent) {
    this->name = _name;
    this->birth_year = b_y;
    this->death_year = d_y;
    this->parent = _parent;
}

Person::Person(string _name, int b_y, int d_y) {
    this->name = _name;
    this->birth_year = b_y;
    this->death_year = d_y;
}

Person &Person::operator=(const Person &other) {
    if (this == &other)
        return *this;
    this->name = other.name;
    this->birth_year = other.birth_year;
    this->death_year = other.death_year;
    this->parent = other.parent;
    return *this;
}