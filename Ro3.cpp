#include "common.hpp"

class A {
    A() = default;

    ~A() = default;
    A(const A&) = default;
    A& operator=(const A&) = default;
};

int main() {}